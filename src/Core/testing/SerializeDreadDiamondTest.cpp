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
#include <fstream>
#include <typeinfo>
#include <string>

#include "Core/Object.h"

#include "testing-prototype.h"

using namespace uLib;







struct A :  Object {
    uLibTypeMacro(A,Object)
    A() : numa(5552368) {}
    int numa;
};


ULIB_SERIALIZABLE_OBJECT(A)
ULIB_SERIALIZE_OBJECT(A,Object) {
   ar & AR(numa);
}

struct B : virtual Object {
    uLibTypeMacro(B,Object)
    B() : numb(5552369) {}
    int numb;
};

ULIB_SERIALIZABLE_OBJECT(B)
ULIB_SERIALIZE_OBJECT(B,Object) { ar & AR(numb); }


struct C : B {
    uLibTypeMacro(C,B)
    C() : numc(5552370) {}
    int numc;
};

ULIB_SERIALIZABLE_OBJECT(C)
ULIB_SERIALIZE_OBJECT(C,B) { ar & AR(numc); }

struct D : A,B {
    uLibTypeMacro(D,A,B)

    D() : numd(5552371) {}
    int numd;
};

ULIB_SERIALIZABLE_OBJECT(D)
ULIB_SERIALIZE_OBJECT(D,A,B) { ar & AR(numd); }



main() {
    A o; o.init_properties();

    Archive::xml_oarchive(std::cout) << NVP(o);

}




















