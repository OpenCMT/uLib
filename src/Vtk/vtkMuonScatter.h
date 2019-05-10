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



#ifndef VTKMUONSCATTER_H
#define VTKMUONSCATTER_H

#include <vtkConfigure.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkLineSource.h>
#include <vtkActor.h>

#include <vtk3DWidget.h>
#include <vtkBoxWidget.h>

#include <vtkRenderWindowInteractor.h>

#include <vtkCommand.h>
#include <vtkTransform.h>

#include "Math/Dense.h"

#include "uLibVtkInterface.h"
#include "Detectors/MuonScatter.h"

class vtkRenderWindowInteractor;

namespace uLib {
namespace Vtk {

class vtkMuonScatter : public Puppet, public Polydata {
    typedef MuonScatter Content;
public:

    vtkMuonScatter(const MuonScatter &content);
    vtkMuonScatter(MuonScatter &content);

    ~vtkMuonScatter();

    Content &GetContent();

    void PrintSelf(std::ostream &o) const;

    virtual vtkPolyData* GetPolyData() const;

    void AddPocaPoint(HPoint3f poca);

    HPoint3f GetPocaPoint();

    void vtkStartInteractive();

protected:
    void ConnectInteractor(vtkRenderWindowInteractor *interactor);

private:
    void InstallPipe();

    vtkMuonScatter::Content *m_Content;
    vtkLineSource           *m_LineIn;
    vtkLineSource           *m_LineOut;
    vtkSphereSource         *m_SpherePoca;
    vtkPolyData             *m_PolyData;
};

} // vtk
} // uLib

#endif // VTKMUONSCATTER_H
