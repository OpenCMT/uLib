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



#include "testing-prototype.h"
#include "Core/Object.h"


using namespace uLib;


//class Derived : public uLib::Object {
//public:
//    Derived(int flags) : uLib::Object(flags) {}
//    enum Flags {
//        a = 1<<0, // 1
//        b = 1<<1, // 2
//        c = 1<<2  // 4
//    };
//};





int main() {
    BEGIN_TESTING(ObjectFlags);

//    Object o(2);
//    o.flags() = 4;
//    o.flags() |= 1;
//    TEST1( o.flags() == 5);
//    o.flags() &= 1;
//    TEST1( o.flags() == 1);
//    TEST1( o.flags().testFlag(1) );

//    Derived d( Derived::a | Derived::b);
//    d.flags() = Derived::c;
//    d.flags() |= Derived::a;
//    TEST1( d.flags() == Derived::a | Derived::c);
//    d.flags() &= 1;
//    TEST1( d.flags() == Derived::a);
//    TEST1( d.flags().testFlag(Derived::a) );

    END_TESTING
}
