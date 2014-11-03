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



#ifndef U_CHAMBERHITEVENT_H
#define U_CHAMBERHITEVENT_H

#include "Core/Vector.h"
#include "Hit.h"
#include "ChamberDetector.h"

namespace uLib {

class ChamberHitEventData
{
public:
    uLibConstRefMacro (Hits, Vector<HitData>    )
    uLibGetMacro      (Idv,  ChamberDetector::ID)
private:
    friend class ChamberHitEvent;
    Vector<HitData>     m_Hits;
    DetectorChamber::ID m_Idv; // -> chamber/view
};

class ChamberHitEvent : public ChamberHitEventData {
public:
    uLibRefMacro  (Hits, Vector<HitData>    )
    uLibSetMacro  (Idv,  ChamberDetector::ID)
};

}

#endif // CHAMBERHITEVENT_H
