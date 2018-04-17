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



#include "RootMuonScatter.h"
#include "Detectors/MuonScatter.h"


namespace ROOT {
namespace Mutom {

MuonScatter &operator <<(MuonScatter &rmu, const uLib::MuonScatter &mu)
{

    rmu.in.X=mu.LineIn().origin(0);
    rmu.in.Y=mu.LineIn().origin(1);
    rmu.in.Z=mu.LineIn().origin(2);
    rmu.in.dirX=mu.LineIn().direction(0);
    rmu.in.dirY=mu.LineIn().direction(1);
    rmu.in.dirZ=mu.LineIn().direction(2);

    rmu.out.X=mu.LineOut().origin(0);
    rmu.out.Y=mu.LineOut().origin(1);
    rmu.out.Z=mu.LineOut().origin(2);
    rmu.out.dirX=mu.LineOut().direction(0);
    rmu.out.dirY=mu.LineOut().direction(1);
    rmu.out.dirZ=mu.LineOut().direction(2);

    rmu.in.p  = mu.GetMomentum();
    rmu.out.p = mu.GetMomentumPrime();

    return rmu;
}

uLib::MuonScatter &operator >>(const MuonScatter &rmu, uLib::MuonScatter &mu) {

    mu.LineIn().origin << rmu.in.X, rmu.in.Y, rmu.in.Z;
    mu.LineIn().direction << rmu.in.dirX, rmu.in.dirY, rmu.in.dirZ;
    mu.LineOut().origin << rmu.out.X, rmu.out.Y, rmu.out.Z;
    mu.LineOut().direction << rmu.out.dirX, rmu.out.dirY, rmu.out.dirZ;

    mu.SetMomentum(rmu.in.p);
    mu.SetMomentumPrime(rmu.out.p);

    return mu;
}



}
}

