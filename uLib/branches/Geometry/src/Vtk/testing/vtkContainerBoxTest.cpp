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



#include "Vtk/uLibVtkViewer.h"

#include "Math/ContainerBox.h"
#include "Vtk/vtkContainerBox.h"

#include "testing-prototype.h"

using namespace uLib;

int main() {
    BEGIN_TESTING(vtk ContainerBox Test);

    Vtk::Viewer v_viewer;

    ContainerBox box;
    box.SetSize(Vector3f(2,3,4));
    box.SetPosition(Vector3f(1,2,3));

    Vtk::vtkContainerBox v_box(box);

    v_viewer.AddPuppet(v_box);
    v_viewer.Start();


    END_TESTING;
}
