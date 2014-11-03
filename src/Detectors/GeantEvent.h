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



#ifndef U_GEANTEVENT_H
#define U_GEANTEVENT_H

#include "Core/Types.h"
#include "Core/Vector.h"
#include "Math/Dense.h"

#include "ChamberHitEvent.h"

namespace uLib {

class GeantEventData {
public:
    uLibGetMacro      (EventID, Id_t    )
    uLibGetMacro      (Momentum,Scalarf )
    uLibConstRefMacro (GenPos,  Vector3f)
    uLibConstRefMacro (GenDir,  Vector3f)
    uLibConstRefMacro (ChEvents,Vector<ChamberHitEventData>)

private:
        friend class GeantEvent;
    Id_t     m_EventID;
    Scalarf  m_Momentum;
    Vector3f m_GenPos;
    Vector3f m_GenDir;
    Vector<ChamberHitEventData> m_ChEvents;
};

class GeantEvent {
public:
    uLibSetMacro (EventID, Id_t    )
    uLibSetMacro (Momentum,Scalarf )
    uLibRefMacro (GenPos,  Vector3f)
    uLibRefMacro (GenDir,  Vector3f)
    uLibRefMacro (ChEvents,Vector<ChamberHitEventData>)
};


}


#endif // GEANTEVENT_H
