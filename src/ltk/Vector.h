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



/* 
 * File:   denseVector.h
 * Author: andrea
 *
 * Created on July 6, 2012, 3:41 PM
 */

#ifndef VECTOR_H
#define	VECTOR_H

#include <stdlib.h>      // for std allocator   //
#include <string.h>      // for memcpy //
#include <assert.h>

#include "templates.h"

BEGIN_NAMESPACE(ltk) 

/* ////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////// VECTOR  ///////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

C_BEGIN_DECLS

#define LTK_VECTOR_DECLARE(Type,Type_name,size)				\
    typedef Type *Type_name;						\
    LTK_SIMPLE_ALLOC_FUNC(Type,Type_name,ltk_vector,size)                 \
    inline unsigned int Type_name##_ltk_vector_size() { return size; }	\
    inline Type Type_name##_ltk_vector_get(Type_name vector, unsigned int i)    \
      { return *(vector+i); }						      \
    inline void Type_name##_ltk_vector_set(Type_name vector, unsigned int i,    \
      Type data) { *(vector+i) = data; }

C_END_DECLS

#ifdef __cplusplus

template <typename T, unsigned int size> class ltkVector
: public ltkAbstractBuffer< T, size >
{
    T m_vector [size];
protected:
    typedef ltkVector<T, size>          ThisClass;
    typedef ltkAbstractBuffer<T, size>  BaseClass;
public:
    ltkVector() {}
    ltkVector(const ltkVector<T, size> &copy) {
	CType_ltk_vector_copy(m_vector, (const CType) copy.getBuffer());
    }

    virtual ~ltkVector() { }

    inline unsigned int getSize() const {
	return size;
    }
    inline T* getBuffer() {
	return (T*)m_vector;
    }
    inline const T* getBuffer() const {
	return (const T*)m_vector;
    }



    ThisClass & operator =(const ThisClass &src) {
	if (this != &src) {
	    CType_ltk_vector_copy(m_vector, (const CType) src.getBuffer());
	}
    }

    typedef struct BaseClass::CommaInit CommaInit;
    inline CommaInit operator = (T scalar) {
	return this->operator <<(scalar);
    }

    // MATH //
    inline bool operator ==(const ThisClass &in) {
	int test = 0;
	for (int i = 0; i < size; ++i) test += this->at(i) != in(i);
	return test == 0;
    }

    inline bool operator !=(const ThisClass &in) {
	return !this->operator ==(in);
    }

    inline void operator +=(const ThisClass &in) {
	for (int i = 0; i < size; ++i) this->at(i) += in(i);
    }
    inline void operator -=(const ThisClass &in) {
	for (int i = 0; i < size; ++i) this->at(i) -= in(i);
    }
    inline void operator *=(const ThisClass &in) {
	for (int i = 0; i < size; ++i) this->at(i) *= in(i);
    }
    inline void operator /=(const ThisClass &in) {
	for (int i = 0; i < size; ++i) this->at(i) /= in(i);
    }

    inline void operator +=(const T t) {
	for (int i = 0; i < size; ++i) this->at(i) += t;
    }
    inline void operator -=(const T t) {
	for (int i = 0; i < size; ++i) this->at(i) -= t;
    }
    inline void operator *=(const T t) {
	for (int i = 0; i < size; ++i) this->at(i) *= t;
    }
    inline void operator /=(const T t) {
	for (int i = 0; i < size; ++i) this->at(i) /= t;
    }

    inline ThisClass & operator + (const ThisClass &in) {
	ThisClass *out = new ThisClass();
	for (int i = 0; i < size; ++i) out->at(i) = this->at(i) + in(i);
	return *out;
    }
    inline ThisClass & operator - (const ThisClass &in) {
	ThisClass *out = new ThisClass();
	for (int i = 0; i < size; ++i) out->at(i) = this->at(i) - in(i);
	return *out;
    }

    // fix with constructor and product null element ------------- //
    inline T operator * (const ThisClass &in) {
	T out = 0;
	for (int i = 0; i < size; ++i) out += this->at(i) * in(i);
	return out;
    }
    inline T operator / (const ThisClass &in) {
	T out = 0;
	for (int i = 0; i < size; ++i) out += this->at(i) / in(i);
	return out;
    }
    // ------------------------------------------------------------- //

    inline ThisClass & operator +(const T t) {
	ThisClass *out = new ThisClass();
	for (int i = 0; i < size; ++i) out->at(i) = this->at(i) + t;
	return *out;
    }
    inline ThisClass & operator -(const T t) {
	ThisClass *out = new ThisClass();
	for (int i = 0; i < size; ++i) out->at(i) = this->at(i) - t;
	return *out;
    }
    inline ThisClass & operator *(const T t) {
	ThisClass *out = new ThisClass();
	for (int i = 0; i < size; ++i) out->at(i) = this->at(i) * t;
	return *out;
    }
    inline ThisClass & operator /(const T t) {
      ThisClass *out = new ThisClass();
      for (int i = 0; i < size; ++i) out->at(i) = this->at(i) / t;
      return *out;
    }
private:
    LTK_VECTOR_DECLARE(T,CType, size)
};

#endif // __cplusplus




END_NAMESPACE // ltk
#endif	/* DENSEVECTOR_H */

