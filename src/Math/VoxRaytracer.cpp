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


#include <iostream>
#include <unordered_map>

#include "VoxRaytracer.h"
#include "Utils.h"

inline float fast_sign(float f) { return 1 - 2 * (f < 0); }

typedef std::unordered_map<uLib::Id_t, uLib::Scalarf> RayTable;

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
    if (!in.m_Data.size())
    {
        std::cout << "Warinig: PoCA on exit border!\n";
    }
    else if (!m_Data.size())
    {
        m_Data = in.m_Data;
        std::cout << "Warinig: PoCA on entrance border!\n";
    }
    else
    {
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
    o << "Ray: total lenght " << m_TotalLength << "\n";
    for(std::vector<Element>::iterator it = m_Data.begin(); it < m_Data.end(); ++it)
    {
        o << "[ " << (*it).vox_id << ", " << (*it).L << "] \n";
    }
}


////////////////////////////////////////////////////////////////////////////////
//// RAY TRACER ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

VoxRaytracer::VoxRaytracer(StructuredGrid &image) : m_Image(&image)
{
    m_scale << (m_Image->GetWorldMatrix() * Vector4f(1,0,0,0)).norm(),
               (m_Image->GetWorldMatrix() * Vector4f(0,1,0,0)).norm(),
               (m_Image->GetWorldMatrix() * Vector4f(0,0,1,0)).norm();
}

bool VoxRaytracer::GetEntryPoint(const HLine3f &line, HPoint3f &pt)
{
    Vector4f s = m_Image->GetLocalPoint(line.direction);
    pt = m_Image->GetLocalPoint(line.origin);

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

bool VoxRaytracer::GetExitPoint(const HLine3f &line, HPoint3f &pt)
{
    HLine3f out = line;
    out.direction *= -1;
    return GetEntryPoint(out,pt);
}


VoxRaytracer::RayData VoxRaytracer::TraceBetweenPoints(const HPoint3f &in, const HPoint3f &out) const
{
    RayData ray;
    Vector4f pt1 = m_Image->GetLocalPoint(in);
    Vector4f pt2 = m_Image->GetLocalPoint(out);
    Vector4f s = pt2 - pt1;

    float l = s.head(3).norm();
    Vector3f L(l/s(0), l/s(1), l/s(2));

    Vector3f offset;
    for(int i=0;i<3;++i)
    {
        offset(i) = (s(i)>=0) - (pt1(i)-floor(pt1(i)));
    }
    offset = offset.cwiseProduct(L).cwiseAbs();
    L = L.cwiseAbs();

    //---- Check if the ray only crosses one voxel
    Vector3i vid = m_Image->Find(in);
    if (vid == m_Image->Find(out))
    {
        ray.AddElement(m_Image->Map(vid),s.norm());
        return ray;
    }

    //---- Otherwise, loop until ray is finished
    int id; float d;
    while (l>0)
    {
        d = offset.minCoeff(&id);

        if (m_Image->IsInsideGrid(vid))
        {
            ray.AddElement(m_Image->Map(vid), d * m_scale(id));
        }

        vid(id) += (int)fast_sign(s(id));

        l -= d;
        offset.array() -= d;
        offset(id) = fmin(L(id),l);
    }
    return ray;
}


// Rectangular beam
VoxRaytracer::RayData VoxRaytracer::BeamBetweenPoints(const HPoint3f &in, const HPoint3f &out,
                                                      int h_thick, int v_thick) const
{
    if (h_thick < 0) h_thick = 0;
    if (v_thick < 0) v_thick = 0;

    RayData ray = TraceBetweenPoints(in, out);
    if (h_thick == 0 && v_thick == 0) return ray;

    RayTable rTable = RayTable(ray.Data().size());
    for(auto it = ray.Data().begin(); it < ray.Data().end(); ++it)
    {
        rTable.emplace(it->vox_id, it->L);
    }

    RayData beam;
    for(auto it = ray.Data().begin(); it < ray.Data().end(); ++it)
    {
        Vector3i rPos = m_Image->UnMap(it->vox_id);

        for (int k = h_thick * -1; k <= h_thick; k++)
        {
            for (int j = v_thick * -1; j <= v_thick; j++)
            {
                // TODO check data order in StructuredData
                Vector3i offset { j, k, 0 };
                Vector3i n_id = rPos + offset;
                if (!m_Image->IsInsideGrid(n_id)) continue;

                Id_t n_vox_id = m_Image->Map(n_id);

                auto tPair = rTable.find(n_vox_id);
                if (tPair == rTable.end())
                {
                    beam.AddElement(n_vox_id, 0);        //TODO Verify any condition with L==0
                }
                else if (tPair->second != 0) 
                {
                    beam.AddElement(n_vox_id, tPair->second);
                    rTable[n_vox_id] = 0;
                }
            }
        }
    }
    return beam;
}



// 20150528 SV for absorbed muons
VoxRaytracer::RayData VoxRaytracer::TraceLine(const HLine3f &line) const
{
    RayData ray;
    Vector4f pt = m_Image->GetLocalPoint(line.origin);
    Vector4f s = m_Image->GetLocalPoint(line.direction);

    float l = s.head(3).norm();
    // intersection between track and grid when spacing is +1
    Vector3f L(l/s(0), l/s(1), l/s(2));

    // RayTracer works with a grid of interspace +1
    // Vector3f scale; // FIXXX
    // scale << (m_Image->GetWorldMatrix() * Vector4f(1,0,0,0)).norm(),
    //          (m_Image->GetWorldMatrix() * Vector4f(0,1,0,0)).norm(),
    //          (m_Image->GetWorldMatrix() * Vector4f(0,0,1,0)).norm();

    // offset is the fraction of the segment between grid lines when origin is insiede voxel
    // cwiseAbs for having positive distances
    Vector3f offset;
    for(int i=0;i<3;++i)
        offset(i) = (s(i)>=0) - (pt(i)-floor(pt(i)));
    offset = offset.cwiseProduct(L).cwiseAbs();
    L = L.cwiseAbs();

    int id; float d;
    Vector3i vid = m_Image->Find(line.origin);
    while(m_Image->IsInsideGrid(vid))
    {
        // minimun coefficient of offset: id is the coordinate, d is the value
        // dependig on which grid line horizontal or vertical it is first intercept
        d = offset.minCoeff(&id);

        // add Lij to ray
        ray.AddElement(m_Image->Map(vid), d * m_scale(id) );

        // move to the next voxel
        vid(id) += (int)fast_sign(s(id));

        offset.array() -= d;
        offset(id) = L(id);
    }
    return ray;
}

} //end of namespace uLib
