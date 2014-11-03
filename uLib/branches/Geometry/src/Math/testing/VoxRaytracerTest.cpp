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




#include "Math/ImageData.h"
#include "Math/VoxRaytracer.h"
#include "testing-prototype.h"

using namespace uLib;


int Vector4f0(Vector4f c)
{
  c(3) = 0;
  if ( fabs(c(0)) < 0.001 && fabs(c(1)) < 0.001 && fabs(c(2)) < 0.001 )
    return 0;
  else
    return 1;
}

//bool Comapare(const  &t1, const T2 &t2)
//{
//    int out = 0;
//    out += t1.vox_id != t2.vox_id;
//    out += (fabs(t1.L) - fabs(t2.L)) > 0.001;
//    return out == 0;
//}


typedef VoxRaytracer Raytracer;

int main()
{
    BEGIN_TESTING(Math VoxRaytracer);

    ImageData img(Vector3i(2,2,2));
    img.SetSpacing(Vector3f(2,2,2));
    img.SetPosition(Vector3f(-2,0,-2));

    {
        HLine3f line;
        line.origin << 0.1, 4.1, 0.1, 1;
        line.direction << 0.1, -0.1, 0.1,0;
        Raytracer rt(img);
        HPoint3f pt;
        TEST1( rt.GetEntryPoint(line,pt) );
        TEST0( Vector4f0( pt - HPoint3f(0.2,4,0.2)  ) );
    }

    {
        HLine3f line;
        line.origin << 4,0,4, 1;
        line.direction << -0.1, 0.1, -0.1, 0;
        Raytracer rt(img);
        HPoint3f pt;
        TEST1( rt.GetEntryPoint(line,pt) );
        TEST0( Vector4f0( pt - HPoint3f(2,2,2)  ) );
    }

    {   // Test a point inside image //
        ImageData img(Vector3i(4,4,4));
        img.SetSpacing(Vector3f(2,2,2));
        img.SetPosition(Vector3f(-4,-4,-4));
        Raytracer ray(img);
        HPoint3f pt;
        HLine3f  line;
        line.origin = HPoint3f(-3,-3,-3);
        //        line.direction = HVector3f(1,1,1); //
        TEST1( ray.GetEntryPoint(line,pt) );
        TEST1( pt == HPoint3f(-3,-3,-3) );

        Raytracer::RayData rdata = ray.TraceBetweenPoints(HPoint3f(-3,-3,-3), HPoint3f(3,3,3));
        foreach (const Raytracer::RayData::Element &el, rdata.Data())
        {
            std::cout << " " << el.vox_id << " , " << el.L << "\n";
        }
    }


    {
        Vector4f pt1(1,-0.5,1);
        Vector4f pt2(1,4.5,1);
        Raytracer rt(img);

        Raytracer::RayData ray = rt.TraceBetweenPoints(pt1,pt2);
        TEST1( ray.Data().size() == 2 );
        TEST1( ray.Data().at(0).vox_id == 6 );
        TEST1( ray.Data().at(1).vox_id == 7 );
        ray.PrintSelf(std::cout);
    }

    {
        Vector4f pt1(5,1,1);
        Vector4f pt2(-3,1,1);
        Raytracer rt(img);

        Raytracer::RayData ray = rt.TraceBetweenPoints(pt1,pt2);
        TEST1( ray.Data().size() == 2 );
        TEST1( ray.Data().at(0).vox_id == 6 );
        TEST1( ray.Data().at(1).vox_id == 4 );
        ray.PrintSelf(std::cout);
    }

    {
        Vector4f pt1(1,1,1);
        Vector4f pt2(-1,3,-1);
        Raytracer rt(img);

        Raytracer::RayData ray = rt.TraceBetweenPoints(pt1,pt2);
        TEST1( ray.Data().size() == 4 );
        TEST1( ray.Data().at(0).vox_id == 6 );
        TEST1( ray.Data().at(1).vox_id == 4 );
        TEST1( ray.Data().at(2).vox_id == 5 );
        TEST1( ray.Data().at(3).vox_id == 1 );
        ray.PrintSelf(std::cout);
    }

    END_TESTING
}








