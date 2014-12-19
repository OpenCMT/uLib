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

#include "Core/MplSequenceCombiner.h"
#include "Core/ClassCompound.h"
#include "Core/ClassFactory.h"

#include "Core/Serializable.h"

#include "testing-prototype.h"

using namespace uLib;



////////////////////////////////////////////////////////////////////////////////
// WORKING EXAMPLE //


namespace Test {

template <
        class BaseType,
        template <class T1, class T2> class DerivedType,
        typename S1,
        typename S2
        >
class Factory2 {
    typedef Factory2 ThisClass;
    typedef void*(ThisClass::* newClassFn)(void *,void *);
    typedef std::vector<newClassFn> newClassFnVector;
    typedef mpl::combine_view< mpl::vector<S1,S2> > AlgView;

    template <class U, class V>
    void * newClass(void *ob1, void *ob2 ) {
        DerivedType<U,V> *out = new DerivedType<U,V>;
        if(ob1) static_cast<U&>(*out) = *static_cast<U*>(ob1);
        if(ob2) static_cast<V&>(*out) = *static_cast<V*>(ob2);
        return out;
    }

    template < typename U, typename V >
    void addType() { m_map.push_back(&ThisClass::newClass< U,V >); }

    struct AddTypeSeqOp {
        AddTypeSeqOp( Factory2 *_p) : m_parent(_p) {}
        template < typename Seq >
        void operator()(Seq) {
            m_parent->addType<
                    typename mpl::at<Seq, mpl::int_<0> >::type,
                    typename mpl::at<Seq, mpl::int_<1> >::type
                    > ();
        }
        Factory2 *m_parent;
    };

    BaseType * create() {
        typename newClassFnVector::iterator itr = m_map.begin() + m_id0 + m_size1 * m_id1;
        return (BaseType *)(this->*(*itr))(m_algs[0], m_algs[1]);
    }
public:

    Factory2() :
        m_id0(0), m_id1(0)
    {
        mpl::for_each< AlgView >(AddTypeSeqOp(this));
        m_algs[0] = NULL;
        m_algs[1] = NULL;
        m_base = create();
    }

    BaseType * operator -> () const { return m_base; }

    template < typename T >
    static inline int FindS1() {
        typedef typename mpl::find<S1,T>::type iter;
        return iter::pos::value;
    }

    template < typename T >
    static inline int FindS2() {
        typedef typename mpl::find<S2,T>::type iter;
        return iter::pos::value;
    }


    template < class A >
    void setA0 (A* alg) {
        m_algs[0] = alg;
        m_id0 = FindS1<A>();
        delete m_base;
        m_base = create();
    }

    template < class A >
    void setA1 (A* alg) {
        m_algs[1] = alg;
        m_id1 = FindS2<A>();
        delete m_base;
        m_base = create();
    }


private:
    newClassFnVector m_map;
    int m_id0, m_id1;
    void * m_algs[2];
    BaseType *m_base;
    static const int m_size1 = mpl::size<S1>::type::value;
    static const int m_size2 = mpl::size<S2>::type::value;
};





} // Test







struct B1 {
    B1() : m_b1(1) {}
    void Print() { std::cout << m_b1; }
    int m_b1;
};

struct B2 {
    B2() : m_b2(2) {}
    void Print() { std::cout << m_b2; }
    int m_b2;
};

struct B3 {
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

    template < class T >
    H<T,A1> SetA0(const T &t) {
        H<T,A1> out(*this);
        (T&)out = t;
        return out;
    }

    void Print() {
        std::cout << "this is a holder of type: " << typeid(this).name() << "\n";
        std::cout << "-> ";
        A0::Print();
        std::cout << " ";
        A1::Print();
        std::cout << "\n";
    }

};

typedef mpl::vector< B1, B2  > seq1;
typedef mpl::vector< B3, B3b > seq2;




int main() {

    Test::Factory2< HB, H, seq1, seq2 > f;

    B1 b1;
    B2 b2;
    B3 b3;

    f.setA0(&b1);
    f.setA1(&b3);
    f->Print();

    f.setA0(&b2);
    f->Print();

}














