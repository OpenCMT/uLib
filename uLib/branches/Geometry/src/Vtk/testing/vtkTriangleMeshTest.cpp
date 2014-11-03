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




#include "Math/TriangleMesh.h"
#include "Vtk/vtkTriangleMesh.h"
#include "testing-prototype.h"

using namespace uLib;


int main()
{
    BEGIN_TESTING(Vtk Triangle Mesh);

//    {   // SIMPLE TESTS //


//        TriangleMesh mesh;

//        mesh.AddPoint(Vector3f(0,0,0));
//        mesh.AddPoint(Vector3f(0,1,0));
//        mesh.AddPoint(Vector3f(1,0,0));

//        mesh.AddTriangle(Vector3i(0,1,2));

//        mesh.PrintSelf(std::cout);


//        vtkTriangleMesh v_mesh(mesh);
//        v_mesh.Update();

//        TestingRenderWidow(&v_mesh);
//    }

    {   // SIMPLE TESTS //

        TriangleMesh mesh;

        vtkTriangleMesh v_mesh(mesh);

        v_mesh.ReadFromStlFile("prova.stl");

        mesh.PrintSelf(std::cout);

        TestingRenderWidow(&v_mesh);
    }


    END_TESTING;
}
