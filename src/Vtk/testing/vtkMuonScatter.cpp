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



#include "Detectors/MuonScatter.h"
#include "Vtk/vtkMuonScatter.h"

#include "Vtk/uLibVtkViewer.h"

#include "testing-prototype.h"

using namespace uLib;

int main()
{
    MuonScatter event;
    event.LineIn().direction() <<   0, -1,  1,  0;
    event.LineIn().origin()   <<    0,  1, -1,  1;

    event.LineOut().direction() <<  0, -1,  0,  0;
    event.LineOut().origin() <<     0, -1,  0,  1;

    Vtk::vtkMuonScatter v_event(event);
    v_event.AddPocaPoint(HPoint3f(0,0,0));

    v_event.SaveToXMLFile("vtk_testing_muonevent.vtp");

    Vtk::Viewer viewer;

//    Vtk::Tie<Vtk::vtkMuonScatter> tms;
//    tms.DoAction();
//    Vtk::Tie<Vtk::Viewer> vms;
//    vms.DoAction();

    viewer.AddPuppet(v_event);
    viewer.Start();

    return 0;
}
