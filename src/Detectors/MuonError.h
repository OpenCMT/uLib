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



#ifndef U_MUONERROR_H
#define U_MUONERROR_H

#include "Math/Dense.h"

namespace uLib {


class MuonErrorData {
public:
    inline const Scalarf & Theta() const { return this->m_Theta; }
    inline const Scalarf & Phi() const { return this->m_Phi; }
protected:
    Scalarf m_Theta;
    Scalarf m_Phi;
};


class MuonError  : public MuonErrorData {
public:
    inline Scalarf & Theta() { return this->m_Theta; }
    inline Scalarf & Phi() { return this->m_Phi; }
};


} // end ulib space


#endif // U_MUONERROR_H
