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
#include "Core/Vector.h"
#include "Core/Object.h"

using namespace uLib;

static int instanziated_objects_number;

class ObjectTest : public Object {
public:
    ObjectTest() {
        data[0] = 0;
        data[1] = 1;
        data[2] = 2;
        instanziated_objects_number++;
    }
    ObjectTest(const ObjectTest &copy) {
        data[0] = copy.data[0];
        data[1] = copy.data[1];
        data[2] = copy.data[2];
        instanziated_objects_number++;
    }

    ~ObjectTest()
    {
        instanziated_objects_number--;
    }
    float data[3];
};

int main() {
    BEGIN_TESTING(SmartVector);

    instanziated_objects_number =0;


    ///////////////////////// SMART POINTER FUNCIONALITY ///////////////////////

    // int smart vector //
    SmartVector<int> sv(10);
    for (int i=0;i<10;++i)
        sv[i] = i;
    // new shallow copy inside a code block //
    {
        SmartVector<int> newsv = sv;
        newsv[5] = 5552368;
        TEST1(sv[5] == newsv[5]);
    }
    // verify that newsv destruction does not delete instance //
    TEST1( sv[5] == 5552368 );

    SmartVector<ObjectTest> svo(10);
    for (int i=0;i<10;++i)
        svo[i] = ObjectTest();

    TEST1(instanziated_objects_number == 10);
    {
        SmartVector<ObjectTest> newsvo = svo;
        newsvo[5].data[1] = 5552368.0;
        TEST1(svo[5].data[1] == newsvo[5].data[1]);
        TEST1(instanziated_objects_number == 10);
    }
    TEST1(instanziated_objects_number == 10);



    /////////////////////////// ITERATOR FUNCIONALITY //////////////////////////


    Vector<int> v(10);
    Vector<int>::Iterator it;

    int i=1;
    for(it=v.begin() ; it==v.end(); it++, i++)
       *it = i;

    for(i = 0; i<v.size(); i++)
        TEST1( v[i] = i+1 );

    Vector<int>::ConstIterator cit;
    i=1;
    for(cit=v.begin(); cit==v.end(); cit++, i++)
       TEST1( *cit == i+1 );


    END_TESTING
}




