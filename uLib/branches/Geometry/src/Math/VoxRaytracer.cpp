/*//////////////////////////////////////////////////////////////////////////////
// CMT Cosmic Muon Tomography project //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  Copyright (c) 2014, Universita' degli Studi di Padova, INFN sez. di Padova
  All rights reserved

  Authors: Andrea Rigoni Garola < andrea.rigoni@pd.infn.it >

  ------------------------------------------------------------------
  This library is free software;  you  can  redistribute  it  and/or
  modify it  under the  terms  of  the  GNU  Lesser  General  Public
  License as published  by  the  Free  Software  Foundation;  either
  version 3.0 of the License, or (at your option) any later version.

  This library is  distributed in  the hope that it will  be useful,
  but  WITHOUT ANY WARRANTY;  without  even  the implied warranty of
  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of  the GNU Lesser General  Public
  License along with this library.

//////////////////////////////////////////////////////////////////////////////*/




#include "VoxRaytracer.h"
#include "Utils.h"

inline float fast_sign(float f) { return 1 - 2 * (f < 0); }

namespace uLib {

////////////////////////////////////////////////////////////////////////////////
///// RAY DATA /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void VoxRaytracer::RayData::AddElement(Id_t id, float L)
{
    Element el = {id, L};
    m_Data.push_back(el);
    m_TotalLength += L;
}


void VoxRaytracer::RayData::AppendRay(const VoxRaytracer::RayData &in)
{
    if (unlikely(!in.m_Data.size())) {
        std::cout << "Warinig: PoCA on exit border!\n";
        return;
    }
    else if (unlikely(!m_Data.size())) {
        m_Data = in.m_Data;
        std::cout << "Warinig: PoCA on entrance border!\n";
        return;
    }
    else {
        // Opzione 1) un voxel in piu' //
        m_Data.reserve(m_Data.size() + in.m_Data.size());
        m_Data.insert(m_Data.end(), in.m_Data.begin(), in.m_Data.end());
        // Opzione 2) merge dei voxel nel poca.
        //        RayData::Element &e1 = m_Data.back();
        //        const RayData::Element &e2 = in.m_Data.front();
        //        if(e1.vox_id == e2.vox_id)
        //        {
        //            m_Data.reserve(m_Data.size() + in.m_Data.size() - 1);
        //            e1.L += e2.L; //fix//
        //            m_Data.insert(m_Data.end(), in.m_Data.begin()+1, in.m_Data.end());
        //        }
        //        else {
        //            m_Data.reserve(m_Data.size() + in.m_Data.size());
        //            m_Data.insert(m_Data.end(), in.m_Data.begin(), in.m_Data.end());
        //        }
        m_TotalLength += in.m_TotalLength;
    }
}

void VoxRaytracer::RayData::PrintSelf(std::ostream &o)
{
    o << "Ray: \n";
    Vector<Element>::Iterator it;
    for(it = m_Data.begin(); it < m_Data.end(); ++it)
        o << "[ " << (*it).vox_id << ", " << (*it).L << "] \n";
}


////////////////////////////////////////////////////////////////////////////////
//// RAY TRACER ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


bool VoxRaytracer::GetEntryPoint(const HLine3f line, Vector4f &pt) const
{
    Vector4f s = m_Image->GetLocalPoint(line.direction());
    pt = m_Image->GetLocalPoint(line.origin());

    // Considers Structured grid dimensions //
    Vector4f dims = m_Image->GetDims().homogeneous().cast<float>();
    pt = pt.cwiseQuotient(dims);
    s  = s.cwiseQuotient(dims);

    float l = s.head(3).norm();
    Vector3f L(l/s(0), l/s(1), l/s(2));

    Vector3f offset;
    for(int i=0;i<3;++i)
        offset(i) = (s(i)>0) - (pt(i)-floor(pt(i))) ;
    offset = offset.cwiseProduct(L).cwiseAbs();

    int id; float d;
    for(int loop=0; loop<8; loop++)
    {
        int check_border = 0;
        for ( int i=0; i<3 ;++i) {
            check_border += pt(i) > 1;
            check_border += pt(i) < 0;
        }
        if(check_border == 0) {
            for(int i=0;i<3;++i)
                pt(i) *= (float)dims(i);
            pt = m_Image->GetWorldPoint(pt);
            return true;
        }

       d = offset.minCoeff(&id);
       for(int i=0; i<3; ++i)
           pt(i) += d / L(i);

       pt(id) = rintf(pt(id));


       offset.array() -= d;
       offset(id) = fabs(L(id));
    }
    for(int i=0;i<3;++i)
        pt(i) *= (float)dims(i);
    pt = m_Image->GetWorldPoint(pt);
    return false;
}

bool VoxRaytracer::GetExitPoint(const HLine3f line, Vector4f &pt) const
{
    HLine3f out = line;
    out.direction() *= -1;
    return GetEntryPoint(out,pt);
}


VoxRaytracer::RayData VoxRaytracer::TraceBetweenPoints(const Vector4f &in,
                                                       const Vector4f &out)
const
{
    RayData ray;
    Vector4f pt1 = m_Image->GetLocalPoint(in);
    Vector4f pt2 = m_Image->GetLocalPoint(out);
    Vector4f s = pt2 - pt1;



    Vector3f scale; // FIXXX
    scale << (m_Image->GetWorldMatrix() * Vector4f(1,0,0,0)).norm(),
            (m_Image->GetWorldMatrix() * Vector4f(0,1,0,0)).norm(),
            (m_Image->GetWorldMatrix() * Vector4f(0,0,1,0)).norm();

    float l = s.head(3).norm();
    Vector3f L(l/s(0), l/s(1), l/s(2));

    Vector3f offset;
    for(int i=0;i<3;++i)
        offset(i) = (s(i)>=0) - (pt1(i)-floor(pt1(i))) ;

    offset = offset.cwiseProduct(L).cwiseAbs();
    L = L.cwiseAbs();

    int id; float d;
    Vector3i vid = m_Image->Find(in);
    while(l>0)
    {
        d = offset.minCoeff(&id);

        if(m_Image->IsInsideGrid(vid))
            ray.AddElement(m_Image->Map(vid), d * scale(id) );

        // nan check //
        //        if(unlikely(!isFinite(d * scale(id)))) {
        //            std:: cout << "NAN in raytracer\n";
        //            exit(1);
        //        }

        vid(id) += (int)fast_sign(s(id));

        l -= d;
        offset.array() -= d;
        offset(id) = fmin(L(id),l);
    }
    return ray;
}


}
