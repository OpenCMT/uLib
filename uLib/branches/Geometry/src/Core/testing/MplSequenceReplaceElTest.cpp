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

#include <iostream>
#include <Core/Types.h>
#include <Core/Mpl.h>

#include <boost/type_traits.hpp>

#include "testing-prototype.h"

using namespace uLib;

struct A0 {};
struct A1 {};
struct A2 {};
struct A3 {};
struct A4 {};
struct A5 {};
struct A6 {};




int main() {
    BEGIN_TESTING(Core MplSequence Replace element);

    typedef mpl::vector<A0,A1,A2,A3,A4> seq;

    typedef mpl::replace_el<seq,A6,2>::type new_seq;

    PrintTypeId::PrintMplSeq<new_seq>();

    //    BOOST_MPL_ASSERT(( boost::is_same< new_seq, mpl::vector<A0,A1,A6,A3,A4> > ));

    END_TESTING;
}

