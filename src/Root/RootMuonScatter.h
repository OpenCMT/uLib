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



#ifndef ROOTMUONSCATTER_H
#define ROOTMUONSCATTER_H

#include <Root/RootMathDense.h>

namespace uLib {
class MuonScatter;
}


namespace ROOT {
namespace Mutom {

struct MuonTrack {
    Vector3f origin;
    Vector3f direction;
    float  p;
};

struct MuonScatter {
public:
    MuonTrack in,out;
    MuonTrack in_err, out_err;
    inline Vector2f p_mean() const;
};

// this is only for testing function link in dictionary ... //
Vector2f MuonScatter::p_mean() const  {
    return Vector2f( (in.p + out.p)/2, (in_err.p + out_err.p)/2 );
}

MuonScatter &operator <<(MuonScatter &rmu, const uLib::MuonScatter &mu);
uLib::MuonScatter &operator >>(const MuonScatter &rmu, uLib::MuonScatter &mu);


} // Mutom
} // ROOT

#endif // ROOTMUONSCATTER_H
