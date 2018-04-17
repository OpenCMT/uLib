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



#ifndef HIT_H
#define HIT_H

#include "Math/BitCode.h"

namespace uLib {





class HitRawCode_CMSDrift :
        public BitCode4<unsigned short,6,3,2,5>
{
    typedef unsigned short T;
public:
    HitRawCode_CMSDrift() : BitCode4(0) {}
    HitRawCode_CMSDrift(const Vector4i &v) : BitCode4(v) {}
    HitRawCode_CMSDrift(T Chamber, T ROB, T TDC, T Channel ) {
        (*this) << Chamber, ROB, TDC, Channel;
    }

    inline T Chamber() const { return m_data.bitf.field1; }
    inline void SetChamber(const T data) { m_data.bitf.field1 = data; }
    inline T ROB() const { return m_data.bitf.field2; }
    inline void SetROB(const T data) { m_data.bitf.field2 = data; }
    inline T TDC() const { return m_data.bitf.field3; }
    inline void SetTDC(const T data) { m_data.bitf.field3 = data; }
    inline T Channel() const { return m_data.bitf.field4; }
    inline void SetChannel(const T data) { m_data.bitf.field4 = data; }

};









}
#endif // HIT_H
