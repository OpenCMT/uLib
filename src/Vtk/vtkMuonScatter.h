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

#include "Core/Macros.h"
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

    void AddPocaPoint(Vector4f poca);

    Vector4f GetPocaPoint();

    void vtkStartInteractive();

protected:
    void ConnectInteractor(vtkRenderWindowInteractor *interactor);

private:
    void InstallPipe();

    friend class vtkMuonScatterPimpl;
    class vtkMuonScatterPimpl *d;
};

} // vtk
} // uLib

#endif // VTKMUONSCATTER_H
