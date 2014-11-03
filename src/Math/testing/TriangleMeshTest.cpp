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

#include "Math/TriangleMesh.h"


using namespace uLib;

int main()
{
    BEGIN_TESTING(Triangle Mesh);

    TriangleMesh mesh;

    mesh.AddPoint(Vector3f(0,0,0));
    mesh.AddPoint(Vector3f(0,1,0));
    mesh.AddPoint(Vector3f(1,0,0));

    mesh.AddTriangle(Vector3i(0,1,2));


    mesh.PrintSelf(std::cout);

    END_TESTING;
}
