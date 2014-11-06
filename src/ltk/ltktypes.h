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



#ifndef LTK_TYPE_H
#define LTK_TYPE_H

#include <assert.h>
#include <sys/types.h>

//#include "templates.h"
#include "ltkmacros.h"

#ifdef __cplusplus
# define LTK_TYPECAST(T, Type) static_cast< T >(Type)
#else
# define LTK_TYPECAST(T, Type) ((T)(Type))
#endif


BEGIN_NAMESPACE(ltk) 

C_BEGIN_DECLS

/* ////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////// TYPE DEFINITIONS   ////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////// */


#define LTK_VOID            0
#define LTK_BIT             1
#define LTK_CHAR            2
#define LTK_SIGNED_CHAR    15
#define LTK_UNSIGNED_CHAR   3
#define LTK_SHORT           4
#define LTK_UNSIGNED_SHORT  5
#define LTK_INT             6
#define LTK_UNSIGNED_INT    7
#define LTK_LONG            8
#define LTK_UNSIGNED_LONG   9
#define LTK_FLOAT          10
#define LTK_DOUBLE         11
#define LTK_ID_TYPE        12


#define LTK_OBJECT 21




typedef void *     Pointer_t;
typedef id_t       Id_t;
typedef size_t     Size_t;

#ifndef LTK_DOUBLE_PRECISION
typedef float      Real_t;
#else
typedef double     Real_t;
#endif

#define LTK_SIGNED_CHAR_MIN        LTK_TYPECAST(signed char, 0x80)
#define LTK_SIGNED_CHAR_MAX        LTK_TYPECAST(signed char, 0x7f)

#define LTK_UNSIGNED_CHAR_MIN      LTK_TYPECAST(unsigned char, 0u)
#define LTK_UNSIGNED_CHAR_MAX      LTK_TYPECAST(unsigned char, 0xffu) 

#define LTK_SHORT_MIN              LTK_TYPECAST(short, 0x8000)
#define LTK_SHORT_MAX              LTK_TYPECAST(short, 0x7fff)

#define LTK_UNSIGNED_SHORT_MIN     LTK_TYPECAST(unsigned short, 0u)
#define LTK_UNSIGNED_SHORT_MAX     LTK_TYPECAST(unsigned short, 0xffffu)

#define LTK_INT_MIN                LTK_TYPECAST(int, ~(~0u >> 1))
#define LTK_INT_MAX                LTK_TYPECAST(int, ~0u >> 1)

#define LTK_INT8_MIN               LTK_TYPECAST(int8_t, 0x80)
#define LTK_INT8_MAX               LTK_TYPECAST(int8_t,  0x7f)

#define LTK_INT16_MIN              LTK_TYPECAST(int16_t,  0x8000u)
#define LTK_INT16_MAX              LTK_TYPECAST(int16_t,  0x7fffu)

#define LTK_UNSIGNED_INT16_MIN     LTK_TYPECAST(int16_t, 0u)
#define LTK_UNSIGNED_INT16_MAX     LTK_TYPECAST(unsigned int16_t, 0xffffu)

#define LTK_INT32_MIN              LTK_TYPECAST(int32_t,  0x80000000u)
#define LTK_INT32_MAX              LTK_TYPECAST(int32_t,  0x7fffffffu)

#define LTK_UNSIGNED_INT32_MIN     LTK_TYPECAST(unsigned int32_t, 0u)
#define LTK_UNSIGNED_INT32_MAX     LTK_TYPECAST(unsigned int32_t, 0xffffffffu)

#define LTK_INT64_MIN              LTK_TYPECAST(int64_t, 0x8000000000000000u)
#define LTK_INT64_MAX              LTK_TYPECAST(int64_t, 0x7fffffffffffffffu)

#define LTK_UNSIGNED_INT8_MIN      LTK_TYPECAST(int8_t, 0u)
#define LTK_UNSIGNED_INT8_MAX      LTK_TYPECAST(int8_t, 0xffu)

#define LTK_UNSIGNED_INT64_MIN     LTK_TYPECAST(unsigned int64_t, 0u)
#define LTK_UNSIGNED_INT64_MAX     LTK_TYPECAST(unsigned int64_t, \
                                                0xffffffffffffffffu)

#define LTK_UNSIGNED_INT_MIN       LTK_TYPECAST(unsigned int, 0)
#define LTK_UNSIGNED_INT_MAX       LTK_TYPECAST(unsigned int, ~0u)

#define LTK_LONG_MIN               LTK_TYPECAST(long, ~(~0ul >> 1))
#define LTK_LONG_MAX               LTK_TYPECAST(long, ~0ul >> 1)

#define LTK_UNSIGNED_LONG_MIN      LTK_TYPECAST(unsigned long, 0ul)
#define LTK_UNSIGNED_LONG_MAX      LTK_TYPECAST(unsigned long, ~0ul)

#define LTK_FLOAT_MIN              LTK_TYPECAST(float, -1.0e+38f)
#define LTK_FLOAT_MAX              LTK_TYPECAST(float, 1.0e+38f)

#define LTK_DOUBLE_MIN             LTK_TYPECAST(double, -1.0e+299)
#define LTK_DOUBLE_MAX             LTK_TYPECAST(double, 1.0e+299)





C_END_DECLS

END_NAMESPACE


#endif //TYPE_H
