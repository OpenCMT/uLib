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



// Curiously Recurring Template Pattern //


template < typename V, typename T >
class Base {
public:
    Base(int a) : value(a) {
        Algorithm = static_cast<T*>(this);
    }

    void Print()
    {
        std::cout << Algorithm->Value() << "\n";
    }

    int value;
    V voxel;
    T* Algorithm;
};


template < typename V >
class Derived : public Base< V ,Derived<V> > {
    typedef Base< V ,Derived<V> > BaseClass;
public:
    Derived(int a) : BaseClass(a) {}
    int Value() { return this->value+1; }
};





int main()
{
    BEGIN_TESTING(Policy);


    Derived<int> my(5);
    my.Print();

    Base<int, Derived<int> > my2(5);
    my2.Print();

    END_TESTING;
}
