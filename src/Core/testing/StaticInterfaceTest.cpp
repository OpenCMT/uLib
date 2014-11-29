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

#include "testing-prototype.h"
#include <Core/StaticInterface.h>



namespace uLib {

//// INTERFACE TO COMPLEX CLASS /////

namespace Interface {
struct Test {
    MAKE_TRAITS
    template<class Self> void check_structural() {
        uLibCheckFunction(Self,test,bool,int,float);
        uLibCheckMember(Self,testmemb,int);
    }
};
} // Interface

struct Test {
    bool test(int i, float f){}
    int testmemb;
};

/////////////////////////

template <class T>
class UseTest {
public:
    UseTest() {
        Interface::IsA<T,Interface::Test>();
        T t;
        int i; float f;
        t.test(i,f);
    }
};


template <class T>
class UseTest2 {
    Interface::StaticIsA<T, Interface::Test> x;
public:
    UseTest2() {
        T t;
        int i; float f;
        t.test(i,f);
    }
};

} // uLib



using namespace uLib;

int main()
{
    BEGIN_TESTING(Static Interface);

    UseTest<Test> u;

    UseTest2<Test> u2;

    END_TESTING;
}

