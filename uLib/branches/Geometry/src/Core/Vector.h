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



#ifndef U_CORE_VECTOR_H
#define U_CORE_VECTOR_H

#include <vector>
#include <iostream>

#include <Core/Macros.h>
#include <Core/SmartPointer.h>
#include <Core/CommaInitializer.h>


namespace uLib {

// Vector Implemetation ... wraps std::vector
template <typename T>
class Vector : public std::vector<T, std::allocator<T> >
{    
    typedef std::vector< T,std::allocator<T> > BaseClass;
    typedef std::allocator<T> Allocator;
public:       
    typedef T TypeData;
    typedef __gnu_cxx::__normal_iterator<T*, BaseClass >       Iterator;
    typedef __gnu_cxx::__normal_iterator<const T*, BaseClass>  ConstIterator;

    typedef CommaInitializer< Vector<T> , T > VectorCommaInit;

    Vector(unsigned int size) : BaseClass(size) {}
    Vector(unsigned int size, T &value) : BaseClass(size,value) {}
    Vector(const Vector<T> &copy) : BaseClass(copy) {}
    Vector() : BaseClass(0) {}


    inline VectorCommaInit operator <<(T scalar) {
        return VectorCommaInit(this, scalar);
    }

    inline void PrintSelf(std::ostream &o);

    void remove_element(unsigned int index) {
        std::swap(this->at(index),this->back());
        this->pop_back();
    }

    void remove_element(T &t) {
      std::swap(t, this->back());
      this->pop_back();
    }   

};

template<typename T>
void Vector<T>::PrintSelf(std::ostream &o)
{
    o << " *** uLib Vector *** \n";
    o << " n. of items = " << this->size() << "\n";
    for(int i=0; i< this->size(); ++i)
        o << (T)this->at(i) << " ";
    o << "\n";
}

template <typename T>
std::ostream &operator << (std::ostream &o, const Vector<T> &v) {
    for(int i=0; i< v.size(); ++i)
        o << (T)v.at(i) << " ";
    o << "\n";
    return o;
}

template <typename T>
std::ofstream &operator << (std::ofstream &o, const Vector<T> &v) {
    for(int i=0; i< v.size(); ++i)
        o << (T)v.at(i) << " ";
    return o;
}


// MATH OPERATIONS //

#define ULIB_CONTAINER_MATHOP(container,op) \
template < typename T1, typename T2 > \
inline container<T1> & operator op##= (container<T1> &src, const T2 data) { \
    foreach (T1 &el, src) { \
        el op##= static_cast<T1>(data); \
    } \
} \
\
template < typename T1, typename T2 > \
inline container<T1> operator op (const container<T1> &src, const T2 data) { \
    container<T1> out(src); \
    out op##= data; \
    return out; \
} \
//
ULIB_CONTAINER_MATHOP(Vector,+)
ULIB_CONTAINER_MATHOP(Vector,-)
ULIB_CONTAINER_MATHOP(Vector,*)
ULIB_CONTAINER_MATHOP(Vector,/)







// Smart pointer Vector Implementation //


template <typename T>
class SmartVector : public SmartPointer< Vector<T> > {
    typedef SmartPointer< Vector<T> > Base;
public:

    SmartVector() : Base(NULL) { }
//    SmartVector() : Base(new Vector<T>()) { }
  SmartVector( const SmartVector &copy) : Base(copy) { }
  SmartVector(unsigned int size) : Base(new Vector<T>((int)size)) { }

  virtual ~SmartVector() {}

  T& operator[](int p) {
      return Base::get()->at(p);
  }

  void swap_elements(unsigned int first, unsigned int second) {
      std::swap(Base::get()->at(first),Base::get()->at(second));
  }

  void remove_element(unsigned int index) {
      std::swap(Base::get()->at(index),Base::get()->back());
      Base::get()->pop_back();
  }

  void remove_element(T &t) {
    std::swap(t, Base::get()->back());
    Base::get()->pop_back();
    }
};




// ------ Utils ------------------------------------------------------------- //



// RIFARE con iteratore !
template <typename _Tp, class _CmpT>
inline const unsigned long
VectorSplice(const _Tp &_it, const _Tp &_end, const float value, _CmpT _comp)
{
    _Tp it = _it;
    _Tp end = _end-1;
    for(it; it != end;)
    {
        if (_comp(*it,value))       ++it;
        else if(_comp(*end,value))  std::swap(*it,*end--);
        else                        --end;
    }
    return it - _it;
}



} // uLib





#endif // VECTOR_H
