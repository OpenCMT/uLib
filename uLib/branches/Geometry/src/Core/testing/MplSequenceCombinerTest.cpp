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
#include <Core/MplSequenceCombiner.h>
#include <Core/ClassFactory.h>

#include "testing-prototype.h"


using namespace uLib;

struct A {};
struct B {};
struct C {};
struct D {};
struct E {};
struct F {};
struct G {};
struct H {};
struct I {};

namespace {
struct PrintTypeId {
    template <class T>
    void operator()(T) const
    { std::cout << typeid(T).name() << "  "; }
};
struct PrintSeq {
    template < typename T >
    void operator()(T) {
        mpl::for_each<T>( PrintTypeId() );
        std::cout << "\n";
    }
};
}

int main() {
    BEGIN_TESTING( Mpl Sequence Combiner Test);

    typedef mpl::vector<A,B,C>   seq1;
    typedef mpl::vector<D,E,F>   seq2;
    typedef mpl::vector<G,H,I>   seq3;

    typedef mpl::combine_view< mpl::vector<seq1,seq2,seq3> > cv;
    mpl::for_each< cv >( PrintSeq() );

    END_TESTING;
}

