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



#ifndef VTKMUONCONTAINERSCATTERING_H
#define VTKMUONCONTAINERSCATTERING_H



#include "Core/Macros.h"
#include "Math/Dense.h"

#include "uLibVtkInterface.h"
#include "Detectors/MuonScatter.h"

class vtkRenderWindowInteractor;

namespace uLib {

class vtkMuonContainerScattering : public Abstract::uLibVtkPolydata {
    typedef MuonScatter Content;
public:
    vtkMuonContainerScattering(const MuonScatter &content);
    ~vtkMuonScatter();

    Content& GetContent();

    void PrintSelf(std::ostream &o) const;

    virtual vtkProp *GetProp();

    virtual vtkPolyData* GetPolyData() const;

    void AddPocaPoint(HPoint3f poca);

    HPoint3f GetPocaPoint();

    void vtkStartInteractive();

protected:
    void ConnectInteractor(vtkRenderWindowInteractor *interactor);

private:
    void InstallPipe();

    friend class vtkMuonContainerScatteringPimpl;
    class vtkMuonContainerScatteringPimpl *d;
};


}


#endif // VTKMUONCONTAINERSCATTERING_H
