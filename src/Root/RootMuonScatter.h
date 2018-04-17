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

namespace uLib {
class MuonScatter;
}

namespace ROOT {
namespace Mutom {

struct MuonTrack {
    float X;
    float Y;
    float Z;

    float dirX;
    float dirY;
    float dirZ;

    float  p;
};

struct MuonScatter {
public:
    MuonTrack in, out;
    inline float p_mean() const;
};

// this is only for testing function link in dictionary ... //
float MuonScatter::p_mean() const  {
    return (in.p + out.p)/2;
}

MuonScatter &operator <<(MuonScatter &rmu, const uLib::MuonScatter &mu);
uLib::MuonScatter &operator >>(const MuonScatter &rmu, uLib::MuonScatter &mu);


} // Mutom
} // ROOT

#endif // ROOTMUONSCATTER_H
