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
#include <typeinfo>


#include "testing-prototype.h"
#include "Core/Types.h"
#include "Core/Object.h"
#include "Core/Signal.h"


using namespace uLib;




class Ob1 : public Object {
public:


signals:
    void V0();

    int V1(int a);

};




// should be done by moc //
void Ob1::V0() {
    ULIB_SIGNAL_EMIT(Ob1::V0);
}

int Ob1::V1(int a) {
    ULIB_SIGNAL_EMIT(Ob1::V1,a);
}





class Ob2 : public Object {

public slots:
    void PrintV0() {
        std::cout << "Ob2 prints V0\n" << std::flush;
    }
};

class Ob3 : public Object {

public slots:
    void PrintV0() {
        std::cout << "Ob3 prints V0\n" << std::flush;
    }

    void PrintNumber(int n) {
        std::cout << "Ob3 is printing number: " << n << "\n";
    }
};




int main() {
    BEGIN_TESTING(Signals);

    Ob1 ob1;
    Ob2 ob2;
    Ob3 ob3;

    Object::connect(&ob1,&Ob1::V0,&ob2,&Ob2::PrintV0);
    Object::connect(&ob1,&Ob1::V0,&ob3,&Ob3::PrintV0);
    Object::connect(&ob1,&Ob1::V1,&ob3,&Ob3::PrintNumber);

    //  not working yet
    //    Object::connect(&ob1,SIGNAL(V0(),&ob2,SLOT(PrintV0())

    ob1.PrintSelf(std::cout);

    emit ob1.V0();
    emit ob1.V1(5552368);

    END_TESTING;
}


