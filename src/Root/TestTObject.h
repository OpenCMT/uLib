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



#ifndef U_ROOT_TESTTOBJECT_H
#define U_ROOT_TESTTOBJECT_H


#if __cplusplus >= 201703L
#else
namespace std {
class string_view {
public:
    string_view(const char *) {}
    string_view(const char *,int) {}
};
} // std
#endif


#include <math.h>
#include <TObject.h>
#include <TTree.h>
#include <TFolder.h>


class TestTObject : public TObject {
public:
    int a,b,c;
    TestTObject() : a(1),b(2),c(3) {}
    virtual ~TestTObject() {}
    ClassDef(TestTObject,1)
};




#endif // TESTTOBJECT_H
