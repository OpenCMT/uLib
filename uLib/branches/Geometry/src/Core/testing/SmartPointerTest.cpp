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
#include "Core/SmartPointer.h"
#include "testing-prototype.h"

using namespace uLib;

namespace Test {

struct ObjectMockInterface {
    virtual void PrintValue()=0;
    virtual int& Value()=0;
};

class ObjectMock : ObjectMockInterface {
    int value;
public:
    int& Value() { return value; }
    void PrintValue() { std::cout << "Value: " << value << "\n"; }

};
} // Test


bool test_smpt(SmartPointer<Test::ObjectMock> &p) {

    SmartPointer<Test::ObjectMock> spt = p;
    spt->Value() = 5552368;
    {
        SmartPointer<Test::ObjectMock> copy = spt;
        copy->Value() = 123;
    }
    return (spt->Value() == 123);
}





int main () {
    BEGIN_TESTING(SmartPointer);

    // HOLD REFERENCE //
    {
        SmartPointer<Test::ObjectMock> spt(new Test::ObjectMock);
        TEST1(test_smpt(spt));
    }
    {
        SmartPointer<Test::ObjectMock> spt;
        TEST1(test_smpt(spt));
    }
    {
        SmartPointer<Test::ObjectMock> spt = new SmartPointer<Test::ObjectMock>;
        TEST1(test_smpt(spt));
    }

    // TAKE REFERENCE //
    {
        Test::ObjectMock obj;
        SmartPointer<Test::ObjectMock> spt(obj);
        TEST1(test_smpt(spt));
    }



    END_TESTING;
}
