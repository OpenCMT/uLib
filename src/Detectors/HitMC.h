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



#ifndef U_HITMC_H
#define U_HITMC_H

#include "Math/Dense.h"
#include "Hit.h"

namespace uLib {


class HitMCData : public HitData{
public:
    enum Type {
        PrimaryMu,
        SecondaryMu,
        DeltaRay
    };

    inline const HPoint3f & Position() const { return this->m_Position; }
    inline enum Type GetType() const { return this->m_Type; }

protected:
    HPoint3f  m_Position;
    enum Type m_Type;
};


class HitMC : public HitMCData {
public:
    inline HPoint3f & Position() { return this->m_Position; }
    inline void SetType(enum Type name) { this->m_Type = name; }
};



}



#endif // HITMC_H
