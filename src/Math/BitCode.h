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


#ifndef U_MATH_BITCODE_H
#define U_MATH_BITCODE_H

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/set_c.hpp>

#include <Math/Dense.h>

namespace uLib {


template < typename ContainerT, typename ContentT >
struct CommaInitializerBitCode
{
    inline explicit CommaInitializerBitCode(ContainerT *container, ContentT s)
        : container(container)
    {
        this->index = 0;
        this->container->operator()().field1 = s;
    }
    inline CommaInitializerBitCode & operator, (ContentT s) {
        this->index++;
        if(index < container->size()) {
            if(index == 1) container->operator()().field2 = s;
            if(index == 2) container->operator()().field3 = s;
            if(index == 3) container->operator()().field4 = s;
        }
        return *this;
    }

    ContainerT *container;
    unsigned int index;
};




template <typename T, uint L1, uint L2>
class BitCode2
{
protected:
    typedef T Type;
    typedef BitCode2<T,L1,L2> ThisClass;
    typedef CommaInitializerBitCode< ThisClass, T > CommaInit;
    BOOST_STATIC_ASSERT_MSG( boost::is_unsigned<T>::value == 1, "CODE TYPE MUST BE UNSIGNED" );
    BOOST_STATIC_ASSERT( L1+L2 == sizeof(T)*8 );

public:
    struct BitField {
        T field1 : L1;
        T field2 : L2;
    };
    union CodeSet {
        BitField bitf;
        T value;
    } m_data;

    BitCode2() {}
    BitCode2(const T& data) { m_data.value = data; }
    BitCode2(const Vector2i & data) {
        (*this) << data(0),data(1);
    }
    inline CommaInit operator <<(T scalar) { return CommaInit(this, scalar); }
    static const int size() { return 2; }

    BitField & operator()() { return m_data.bitf; }
    const BitField & operator()() const { return m_data.bitf; }
    operator Vector2i () { return Vector2i(m_data.bitf.field1,
                                           m_data.bitf.field2); }

    void set(const T data) { m_data.value = data; }
    T get() const { return m_data.value; }
};

template <typename T, uint L1, uint L2>
std::ostream &
operator << (std::ostream &o, const BitCode2<T,L1,L2> &code) {
    o << code().field1 << "," << code().field2;
    return o;
}







template <typename T, uint L1, uint L2, uint L3>
class BitCode3
{
protected:
    typedef T Type;
    typedef BitCode3<T,L1,L2,L3> ThisClass;
    typedef CommaInitializerBitCode< ThisClass, T > CommaInit;
    BOOST_STATIC_ASSERT_MSG( boost::is_unsigned<T>::value == 1, "CODE TYPE MUST BE UNSIGNED" );
    BOOST_STATIC_ASSERT( L1+L2+L3 == sizeof(T)*8 );

public:
    struct BitField {
        T field1 : L1;
        T field2 : L2;
        T field3 : L3;
    };
    union CodeSet {
        BitField bitf;
        T value;
    } m_data;


    BitCode3() {}
    BitCode3(const T& data) { m_data.value = data; }
    BitCode3(const Vector3i & data) {
        (*this) << data(0),data(1),data(2);
    }
    inline CommaInit operator <<(T scalar) { return CommaInit(this, scalar); }
    static const int size() { return 3; }

    BitField & operator()() { return m_data.bitf; }
    const BitField & operator()() const { return m_data.bitf; }
    operator Vector3i () { return Vector3i(m_data.bitf.field1,
                                           m_data.bitf.field2,
                                           m_data.bitf.field3); }

    void set(const T data) { m_data.value = data; }
    T get() const { return m_data.value; }
};

template <typename T, uint L1, uint L2, uint L3>
std::ostream &
operator << (std::ostream &o, const BitCode3<T,L1,L2,L3> &code) {
    o << code().field1 << "," << code().field2 << "," << code().field3;
    return o;
}







template <typename T, uint L1, uint L2, uint L3, uint L4>
class BitCode4
{
protected:
    typedef T Type;
    typedef BitCode4<T,L1,L2,L3,L4> ThisClass;
    typedef CommaInitializerBitCode< ThisClass, T > CommaInit;
    BOOST_STATIC_ASSERT_MSG( boost::is_unsigned<T>::value == 1, "CODE TYPE MUST BE UNSIGNED" );
    BOOST_STATIC_ASSERT( L1+L2+L3+L4 == sizeof(T)*8 );
public:
    struct BitField {
        T field1 : L1;
        T field2 : L2;
        T field3 : L3;
        T field4 : L4;
    };
    union CodeSet {
        BitField bitf;
        T value;
    } m_data;

    BitCode4() {}
    BitCode4(const T& data) { m_data.value = data; }
    BitCode4(const Vector4i & data) {
        (*this) << data(0),data(1),data(2),data(3);
    }
    inline CommaInit operator << (T scalar) { return CommaInit(this, scalar); }
    static const int size() { return 4; }

    BitField & operator()() { return m_data.bitf; }
    const BitField & operator()() const { return m_data.bitf; }
    operator Vector4i () { return Vector4i(m_data.bitf.field1,
                                           m_data.bitf.field2,
                                           m_data.bitf.field3,
                                           m_data.bitf.field4); }

    void set(const T data) { m_data.value = data; }
    T get() const { return m_data.value; }



};

template <typename T, uint L1, uint L2, uint L3, uint L4>
std::ostream &
operator << (std::ostream &o, const BitCode4<T,L1,L2,L3,L4> &code) {
    o << code().field1 << "," << code().field2 << "," << code().field3 << "," << code().field4;
    return o;
}



template <typename T, uint L1, uint L2 = 0, uint L3 = 0>
class BitCode {
    typedef boost::mpl::vector_c<T,L1,L2,L3> BitSet;
    T m_data;

public:

    struct value_printer
    {
        template< typename U > void operator()(U x)
        { std::cout << x << '\n'; }
    };
    void PrintSelf( ) {
//        boost::mpl::for_each<BitSet>( value_printer() );
//        std::cout << boost::mpl::at_c< BitSet,1 >::type::value << "\n";
    }

//    int Get(unsigned short field) const {
//        return boost::mpl::at_c< BitSet, field >::type::value;
//    }
};



} // uLib


#endif // BITCODE_H
