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




#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

#include "templates.h"
#include "Vector.h"

BEGIN_NAMESPACE(ltk)

/* ////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////// MATRIX ////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */

C_BEGIN_DECLS

#define LTK_MATRIX_DECLARE_FUNC(Type,ltkType,Class_name,csize,rsize)	\
  inline Type ltkType##_##Class_name##_get(ltkType m,			\
					unsigned int c,			\
					unsigned int r)			\
  {									\
    assert(c + r * csize < csize * rsize);				\
    return *((ltkType)m + c + r * csize);				\
  }									\
  inline void ltkType##_##Class_name##_set(ltkType m,			\
			       unsigned int c,				\
			       unsigned int r,				\
			       Type t)					\
  { 									\
    assert (c + r * csize < csize * rsize);				\
    *((ltkType)m + c + r * csize) = t;					\
  }									


#define LTK_MATRIX_DECLARE(Type,Type_name,csize,rsize)	                \
  typedef Type * Type_name;						\
  LTK_SIMPLE_ALLOC_FUNC(Type, Type_name,ltk_matrix,csize * rsize)       \
  LTK_MATRIX_DECLARE_FUNC(Type,Type_name,ltk_matrix,csize,rsize)

C_END_DECLS

#ifdef __cplusplus

template <typename T, unsigned int csize, unsigned int rsize> class ltkDenseMatrix
: public ltkAbstractBuffer< T, csize * rsize >
{
protected:
    typedef ltkDenseMatrix<T, csize, rsize> ThisClass;
    typedef ltkAbstractBuffer<T, csize * rsize> BaseClass;
public:
    ltkDenseMatrix() {}
    ~ltkDenseMatrix() { }
    
    inline T* getBuffer() {
	return (T*)m_buffer;
    }
    inline const T* getBuffer() const {
	return (const T*)m_buffer;
    }

    ThisClass & operator =(const ThisClass &src) {
	if (this != &src) {
	    CType_ltk_matrix_copy(m_buffer, (const CType) src.getBuffer());
	}
    }

    typedef struct BaseClass::CommaInit CommaInit;
    inline CommaInit operator = (T scalar) {
	return this->operator <<(scalar);
    }


private:
    LTK_MATRIX_DECLARE(T,CType, csize, rsize);
    T m_buffer [csize * rsize];
};




#endif // __cplusplus

END_NAMESPACE

#endif // DENSEMATRIX_H
