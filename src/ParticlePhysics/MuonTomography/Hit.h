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


#ifndef U_PPMUTOM_HIT_H
#define U_PPMUTOM_HIT_H

#include <Core/Types.h>
#include <Math/Dense.h>


namespace uLib {

template <typename Type, typename Code>
class Hit {
    Code m_Code;
    Type m_DriftTime;
};







class HitMC {
public:
    virtual Id_t     GetChamber() = 0;
    virtual Vector3f GetPosition() = 0;
    virtual Scalarf  GetDritfTime() = 0;
protected:
    virtual ~HitMC() {}
};



} // uLib





#endif // HIT_H
