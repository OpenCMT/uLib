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

#include "Vtk/vtkStructuredGrid.h"
#include "Vtk/uLibVtkViewer.h"

#include "testing-prototype.h"

using namespace uLib;

int main()
{

    ImageData grid(Vector3i(10,10,100));
    grid.SetSpacing(Vector3f(3,1,1));

    Vtk::vtkStructuredGrid grid_viewer(grid);

    Vtk::Viewer viewer;
    viewer.AddPuppet(grid_viewer);
    viewer.Start();

    return 0;
}
