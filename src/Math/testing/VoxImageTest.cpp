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




#include "testing-prototype.h"
#include "Math/StructuredGrid.h"
#include "Math/VoxImage.h"

using namespace uLib;


struct TestVoxel {
    Scalarf Value;
    unsigned int Count;
};

int main() {
    BEGIN_TESTING(Math StructuredGrid);

    {   // SIMPLE TESTS //
        StructuredGrid img(Vector3i(10,10,10));
        img.SetSpacing(Vector3f(3,3,3));
        TEST1( img.GetWorldPoint(2,0,0) == HPoint3f(6,0,0) );
        TEST1( img.GetWorldPoint(1,1,1) == HPoint3f(3,3,3) );

        img.SetPosition(Vector3f(1,1,1));
        TEST1( img.GetWorldPoint(1,1,1) == HPoint3f(4,4,4) );
        TEST1( img.GetLocalPoint(4,4,4) == HPoint3f(1,1,1) );

        TEST0( img.IsInsideBounds(HPoint3f(5,33,-5)));
        TEST0( img.IsInsideBounds(HPoint3f(0,0,0)));
        TEST1( img.IsInsideBounds(HPoint3f(1,1,1)));
    }

    {   // TEST WITH ORIGIN //
        StructuredGrid img(Vector3i(10,10,10));
        img.SetSpacing(Vector3f(3,3,3));
        img.SetOrigin(Vector3f(-1,1,-1));
        img.SetPosition(Vector3f(1,1,1));
        TEST1( img.GetWorldPoint(1,1,1) == HPoint3f(3,5,3) );
    }


    {
        VoxImage<TestVoxel> img(Vector3i(10,10,10));
        TestVoxel zero = {0,0};
        img.InitVoxels(zero);
        TestVoxel nonzero = {5.552368, 0};
        img[Vector3i(5,1,7)] = nonzero;
        img[img.Find(HPoint3f(3,3,3))].Value = 5.552369;
        img.ExportToVtk("./test_vox_image.vtk",0);
        img.ExportToVtkXml("./test_vox_image.vti",0);
        TEST1( img.GetValue(Vector3i(5,1,7)) == 5.552368f );
    }

    {
        VoxImage<TestVoxel> img(Vector3i(4,4,4));
        TestVoxel zero = {0,0};
        img.InitVoxels(zero);
        img.SetSpacing(Vector3f(2,2,2));
        img.SetPosition(Vector3f(-4,-4,-4));
        TEST1( img.GetWorldPoint(img.GetLocalPoint(HPoint3f(5,5,5))) == HPoint3f(5,5,5));
    }

    {
        VoxImage<TestVoxel> imgR(Vector3i(0,0,0));
        imgR.ImportFromVtk("./test_vox_image.vtk");
        imgR.ExportToVtk("./read_and_saved.vtk");
    }

    {
        VoxImage<TestVoxel> img(Vector3i(4,4,4));
        img.InitVoxels({0,0});
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                for (int k=0; k<4; k++) {
                    img[Vector3i(i,j,k)] = {i+j+k,0};
                }
            }
        }
        img.ExportToVti("./vti_saved.vti",0,1);
        // img.ImportFromVtkXml("./test_vox_image.vti");
    }


    {
        VoxImage<TestVoxel> img1(Vector3i(5,5,5));
        VoxImage<TestVoxel> img2;
        img2 = img1;
        TEST1( img1.GetDims() == img2.GetDims() );
    }




    END_TESTING
}
