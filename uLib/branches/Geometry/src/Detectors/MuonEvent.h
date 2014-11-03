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



#ifndef U_MUONEVENT_H
#define U_MUONEVENT_H

#include "Core/Macros.h"
#include "Math/Dense.h"

namespace uLib {


class MuonEventData {
    friend class MuonEvent;
public:
    uLibConstRefMacro(LineIn,HLine3f)
    uLibConstRefMacro(LineOut,HLine3f)
    uLibGetMacro(Momentum,Scalarf)

private:
    HLine3f  m_LineIn;
    HLine3f  m_LineOut;
    Scalarf  m_Momentum;
};


class MuonEvent  : public MuonEventData {
public:
    uLibRefMacro(LineIn,HLine3f)
    uLibRefMacro(LineOut,HLine3f)
    uLibRefMacro(Momentum,Scalarf)

};

inline std::ostream&
operator<< (std::ostream& stream, const MuonEventData &mu) {
    stream << " MuonEventData: --------------- \n"
           << " P: " << mu.GetMomentum() << "\n"
           << " IN:  " << mu.LineIn() << "\n"
           << " OUT: " << mu.LineOut() << "\n"
           << " ------------------------------ \n";
    return stream;
}



} // end ulib space



#endif // U_MUONEVENT_H
