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




#include "Math/VoxImage.h"
#include "Vtk/vtkVoxImage.h"
#include "Vtk/uLibVtkViewer.h"

#include "testing-prototype.h"

using namespace uLib;

struct TestVoxel {
    Scalarf Value;
    unsigned int Count;
};

int main()
{
    BEGIN_TESTING(Vtk Vox Image);

    TestVoxel zero = {0,0};
    TestVoxel nonzero = {5.5*1E-6,100};

//    {   // SIMPLE TESTS //
//        VoxImage<TestVoxel> img(Vector3i(10,10,10));
//        img.SetSpacing(Vector3f(3,3,3));

//        img.InitVoxels(zero);
//        img[Vector3i(3,3,3)] = nonzero;

//        Vtk::vtkVoxImage vtk_img(img);

//        vtk_img.SaveToXMLFile("test.vti");
//        vtk_img.setShadingPreset(0);

//        //        vtk_img.ReadFromVKTFile("error.vtk");

//        //        VoxImage<TestVoxel> img2 = img;

//        //        Vtk::vtkVoxImage vtk_img2(img2);

//        //        img2.ExportToVtk("error_saved.vtk",0);

//        //        vtk_img2.SaveToXMLFile("error_saved.vti");

//        Vtk::Viewer viewer;
//        viewer.AddPuppet(vtk_img);
//        viewer.Start();
//    }

    {   // SIMPLE TESTS //
        VoxImage<TestVoxel> img(Vector3i(10,10,1));
        img.SetSpacing(Vector3f(3,3,3));

        img.InitVoxels(zero);
        img[Vector3i(3,3,0)] = nonzero;

        Vtk::vtkVoxImage vtk_img(img);

        vtk_img.ReadFromVKTFile("test.vtk");
        vtk_img.Update();

        //        vtk_img.SaveToXMLFile("test.vti");
        //        vtk_img.setShadingPreset(0);

        //        Vtk::vtkVoxImage vtk_img2(img2);
        //        img2.ExportToVtk("error_saved.vtk",0);
        //        vtk_img2.SaveToXMLFile("error_saved.vti");

        Vtk::Viewer viewer;
        viewer.AddPuppet(vtk_img);
        viewer.Start();
    }


    END_TESTING;
}
