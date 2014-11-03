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

    rmu.in.origin.SetX(mu.LineIn().origin()(0));
    rmu.in.origin.SetY(mu.LineIn().origin()(1));
    rmu.in.origin.SetZ(mu.LineIn().origin()(2));
    rmu.in.direction.SetX(mu.LineIn().direction()(0));
    rmu.in.direction.SetY(mu.LineIn().direction()(1));
    rmu.in.direction.SetZ(mu.LineIn().direction()(2));

    rmu.out.origin.SetX(mu.LineOut().origin()(0));
    rmu.out.origin.SetY(mu.LineOut().origin()(1));
    rmu.out.origin.SetZ(mu.LineOut().origin()(2));
    rmu.out.direction.SetX(mu.LineOut().direction()(0));
    rmu.out.direction.SetY(mu.LineOut().direction()(1));
    rmu.out.direction.SetZ(mu.LineOut().direction()(2));

    rmu.in.p  = mu.GetMomentum();
    rmu.out.p = mu.GetMomentumPrime();

    return rmu;
}

uLib::MuonScatter &operator >>(const MuonScatter &rmu, uLib::MuonScatter &mu) {

    mu.LineIn().origin() << rmu.in.origin.x(), rmu.in.origin.z(), rmu.in.origin.z();
    mu.LineIn().direction() << rmu.in.direction.x(), rmu.in.direction.z(), rmu.in.direction.z();
    mu.LineOut().origin() << rmu.out.origin.x(), rmu.out.origin.z(), rmu.out.origin.z();
    mu.LineOut().direction() << rmu.out.direction.x(), rmu.out.direction.z(), rmu.out.direction.z();

    mu.SetMomentum(rmu.in.p);
    mu.SetMomentumPrime(rmu.out.p);

    return mu;
}



}
}

