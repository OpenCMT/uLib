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



#ifndef VTKMUONEVENT_H
#define VTKMUONEVENT_H

#include "Core/Macros.h"
#include "Math/Dense.h"

#include "uLibVtkInterface.h"
#include "Detectors/MuonEvent.h"




namespace uLib {

class vtkMuonEvent : public Abstract::uLibVtkPolydata {
    typedef MuonEventData Content;
public:
    vtkMuonEvent(const MuonEventData &content);
    vtkMuonEvent(MuonEventData &content);
    ~vtkMuonEvent();

    Content& GetContent();

    void PrintSelf(std::ostream &o) const;

    virtual vtkProp *GetProp();

    virtual vtkPolyData* GetPolyData() const;

    void AddPocaPoint(Vector4f poca);

    Vector4f GetPocaPoint();

    void vtkStartInteractive();


private:
    void InstallPipe();

    friend class vtkMuonEventPimpl;
    class vtkMuonEventPimpl *d;
};


}

#endif // VTKMUONSCATTER_H
