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



#ifndef U_CORE_MACROS_H
#define U_CORE_MACROS_H

//#ifndef HAVE_CONFIG_H
#include "config.h"
//#endif

#include <assert.h>

#define uLibAssert(condition) assert(condition)


// Symbols visibility attribute, see: http://gcc.gnu.org/wiki/Visibility              //
// http://stackoverflow.com/questions/5116333/dynamic-cast-failed-when-hidding-symbol //
#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif



// foreach Qt style
#ifndef foreach
#include "boost/foreach.hpp"
#define foreach(ref, list) BOOST_FOREACH(ref,list)
#endif








// TODO: verificare necessita' di typecast ////////////////////////////////

#define uLibVGetMacro(name,type) \
    virtual inline const type Get##name() const = 0;

#define uLibVSetMacro(name,type) \
    virtual inline void Set##name(const type name) = 0;

#define uLibVGetSetMacro(name,type) \
    uLibVGet(name,type);       \
    uLibVSet(name,type);

#define uLibVRefMacro(name,type)  \
    virtual inline type & name() = 0;

#define uLibPtrMacro(name,type) \
    inline type name() const { return this->m_##name; }

#define uLibArrayMacro(name,type) \
    inline type name() { return this->m_##name; }

#define uLibGetMacro(name,type) \
    inline type Get##name() const { return this->m_##name; }

#define uLibSetMacro(name,type) \
    inline void Set##name(type name) { this->m_##name = name; }

#define uLibGetSetMacro(name,type) \
    inline type Get##name() const { return this->m_##name; } \
    uLibSetMacro(name,type);

#define uLibRefMacro(name,type)  \
    inline type & name() { return this->m_##name; }

#define uLibConstRefMacro(name,type)  \
    inline const type & name() const { return this->m_##name; }

#define uLibAccessMacro(name,type) \
    inline void name(type name) { this->m_##name = name; } \
    uLibConstRefMacro(name,type)


#define uLib_CRTP_ACCESS(_Derive,_name) \
    inline _Derive * _name() { return reinterpret_cast<_Derive *>(this); } \
    inline const _Derive * _name() const { return reinterpret_cast<const _Derive *>(this); } \
    //

#define uLib_CRTP_ACCESS_CASTED(_Derive,_Target,_name) \
    inline _Target _name() { return (_Target)(static_cast<_Derive &>(*this)); } \
    inline const _Target _name() const { return (const _Target)(static_cast<const _Derive &>(*this)); } \
    //










/* Following macros override usual branch prediction of compiler
 * These are to be used in conditional statement whose result might
 * be Bayesian biased:
 *
 * // previous_line
 * if (likely(a>1)) { // block_1 }
 * else { block_2 }
 *
 * will write the block_1 code right after previous line, without using
 * compiler branch prediction for results. Otherwise
 *
 * // previous_line
 * if (unlikely(a>1)) { // block_1 }
 * else { block_2 }
 *
 * will write block_2 after previous_line, leaving block_1 after
 * (usually after the end of the whole function! Use with care!)
 */

#define unlikely(expr) __builtin_expect(!!(expr), 0)

#define likely(expr) __builtin_expect(!!(expr), 1)

/* Fastsign
 */
// #define sign(x) (( x > 0 ) - ( x < 0 ))
template <typename T>
inline T sign(const T x) { return x>0 - x<0; }


#endif // MACROS_H
