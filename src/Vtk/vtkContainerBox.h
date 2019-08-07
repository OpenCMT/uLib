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



#ifndef U_VTKCONTAINERBOX_H
#define U_VTKCONTAINERBOX_H


#include "uLibVtkInterface.h"
#include "Math/ContainerBox.h"


namespace uLib {
namespace Vtk {

class vtkContainerBox : public Puppet, public Polydata {
    typedef ContainerBox Content;
public:
    vtkContainerBox(Content &content);
    ~vtkContainerBox();

    virtual class vtkPolyData *GetPolyData() const;

private:
    void InstallPipe();

    vtkActor                 *m_Cube;
    vtkActor                 *m_Axes;
    vtkActor                 *m_Pivot;
    vtkContainerBox::Content *m_Content;
};

} // vtk
} // uLib

#endif // VTKCONTAINERBOX_H
