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

//#include "boost/preprocessor.hpp"
//#include "boost/preprocessor/repetition.hpp"

#include "boost/concept_archetype.hpp"

#include "Core/MplSequenceCombiner.h"

#include "Core/ClassCompound.h"
#include "Core/ClassFactory.h"
#include "Core/StaticInterface.h"

#include "Core/Serializable.h"

#include "testing-prototype.h"

using namespace uLib;



////////////////////////////////////////////////////////////////////////////////

// TEST 1 //

/*
 * TEST 1
namespace Test {

struct BB {};

struct B1 : BB {
    B1() : m_b1(1) {}
    void Print() { std::cout << m_b1; }
    int m_b1;
};

struct B2 : BB {
    B2() : m_b2(2) {}
    void Print() { std::cout << m_b2; }
    int m_b2;
};

struct B3 : BB {
    B3() : m_b3(3) {}
    void Print() { std::cout << m_b3; }
    int m_b3;
};

struct B3b {
    B3b() : m_b3(30) {}
    void Print() { std::cout << m_b3; }
    int m_b3; // learn to handle ambiguity ..
};




struct HB {
    virtual ~HB() {}
    virtual void Print() = 0;
};

template <
        class A0,
        class A1
        >
struct H : HB, ClassCompound<A0,A1> {
    typedef ClassCompound<A0,A1> Compound;

    H() {}

    template < class Other >
    H(const Other &t) : Compound(t) {}

    using Compound::operator =;
    using Compound::SetComponent;

    void Print() {
        std::cout << "this is a holder of type: " << typeid(this).name() << "\n";
        std::cout << "-> ";
        A0::Print();
        std::cout << " ";
        A1::Print();
        std::cout << "\n";
    }

};


struct HFactory {

    template < class T0, class T1 >
    static H<T0,T1>* create(const T0 &t0, const T1 &t1) {
        H<T0,T1> *out = new H<T0,T1>;
        out->A0() = t0;
        out->A1() = t1;
        return out;
    }

};


template < class I0, class I1 >
struct CompoundFactory {

    template < class T0, class T1 >
    static ClassCompound<T0,T1> create(const T0 &t0, const T1 &t1) {
        ClassCompound<T0,T1> out;
        ULIB_INTERFACE_ASSERT(I0,T0);
        ULIB_INTERFACE_ASSERT(I1,T1);
        out.A0() = t0;
        out.A1() = t1;
        return out;
    }


};



typedef mpl::vector< B1, B2  > seq1;
typedef mpl::vector< B3, B3b > seq2;



int main() {

    B1 b1;
    B2 b2;
    B3 b3;
    B3b b3b;

    b1.m_b1 = 111;
    b2.m_b2 = 222;
    b3.m_b3 = 333;
    b3b.m_b3 = 333;


    H<B1,B2> h12;
    h12.A0() = b1;

    H<B1,B3> h13 = h12.SetComponent<1>(b3);
    h13.Print();

    {
        H<B1,B2> h12 = CompoundFactory<BB,BB>::create(b1,b2);
        h12.Print();
    }


}

} // Test

*/












