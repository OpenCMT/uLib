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
}

struct Test {
    bool test(int i, float f){}
    int testmemb;
};



//// INTERFAC TO SIMPLE CLASS ///////////

namespace Interface {
struct Simple {
    MAKE_TRAITS
    template<class Self> void check_structural() {
        uLibCheckMember(Self,memb1,int);
        uLibCheckMember(Self,memb2,float);
    }
};
}

struct Simple {
    int memb1;
    float memb2;
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
class UseSimple {
public:
    UseSimple() {
        Interface::IsA<T,Interface::Simple>();
    }
};



}

int main()
{
    BEGIN_TESTING(Static Interface);



    uLib::UseTest<uLib::Test> u;

    uLib::UseSimple<uLib::Simple> s;

    END_TESTING;
}

