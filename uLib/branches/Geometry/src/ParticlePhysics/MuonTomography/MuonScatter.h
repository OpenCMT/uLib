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



#ifndef U_PPMUTOM_MUONSCATTER_H
#define U_PPMUTOM_MUONSCATTER_H

#include "Core/Macros.h"
#include "Core/Serializable.h"

#include "Math/Dense.h"

namespace uLib {



class MuonTrack {
    ULIB_SERIALIZE_ACCESS
public:
    HLine3f  track;
    Scalarf  momentum;
};

class MuonScatter {
    ULIB_SERIALIZE_ACCESS
public:
    MuonTrack in, out;
    MuonTrack error_in, error_out;
};


} // uLib

ULIB_SERIALIZABLE(uLib::MuonTrack)
ULIB_SERIALIZE(uLib::MuonTrack) {
    ar & AR(line);
}



ULIB_SERIALIZABLE(uLib::MuonScatter)
ULIB_SERIALIZE(uLib::MuonScatter) {
    ar
            & " MuonScatter: ----------------- \n"
            & "IN : " & AR(in)  & "\n"
            & "OUT: " & AR(out) & "\n"
            & " ------------------------------ \n";
}


std::ostream &
operator << (std::ostream &o, const uLib::MuonScatter &d) {
    uLib::Archive::hrt_oarchive(o) << d;
    return o;
}

inline std::istream &
operator >> (std::istream &is, uLib::MuonScatter &d)
{
    uLib::Archive::hrt_iarchive(is) >> d;
    return is;
}



#endif // MUONSCATTER_H
