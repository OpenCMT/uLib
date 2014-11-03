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



#ifndef LTKDEBUG_H
#define LTKDEBUG_H


#include "ltkmacros.h"
#include "ltktypes.h"

//! Provide a string for current function, non-concatenatable
#if defined (__GNUC__) || (defined (__STDC_VERSION__) && __STDC_VERSION__ >= 19901L)
#  define __func_to_string__     ((const char*) (__func__))
#else
#  define __func_to_string__  ((const char*) ("???"))
#endif

//! Provide a string for current function in pretty format, non-concatenatable
#if defined (__GNUC__)
#  define __pfunc_to_string__     ((const char*) (__PRETTY_FUNCTION__))
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 19901L
#  define __pfunc_to_string__  ((const char*) (__func__))
#else
#  define __pfunc_to_string__  ((const char*) ("???"))
#endif



////////////////////////////////////////////////////////////////////////////////
//// Pragma Messages for debug allerts during compilation  /////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef PRAGMA_MESSAGES
#define DEBUG_DO_PRAGMA(x) _Pragma (#x)
#else
#define DEBUG_DO_PRAGMA(x) ;
#endif

#define TODO(x) DEBUG_DO_PRAGMA(message ("\n\n [TODO] >> " #x " <<\n"))
#define OPTIMIZE(x) DEBUG_DO_PRAGMA(message ("\n\n [OPTIMIZE]  > " #x " <\n"))
#define DUMP(x) DEBUG_DO_PRAGMA(message ("\n\n [DUMP]  > " #x " <\n"))

//  ------------------------------------------------------------------------  //



C_BEGIN_DECLS


typedef enum
{
    LOG_FLAG_ACTIVE = 1 << 0,
            LOG_FLAG_FATAL = 1 << 1,
            LOG_LEVEL_ERROR = 1 << 2,
            LOG_LEVEL_CRITICAL = 1 << 3,
            LOG_LEVEL_WARNING = 1 << 4,
            LOG_LEVEL_MESSAGE = 1 << 5,
            LOG_LEVEL_INFO = 1 << 6,
            LOG_LEVEL_DEBUG = 1 << 7,
            LOG_LEVEL_ANNOING = 1 << 8,
            LOG_LEVEL_PARANOID = 1 << 9
} LogLevelFlags;




void debug_log(
            void *handler,
            LogLevelFlags flags,
            const char *function_name,
            const char *message,
            ...);



C_END_DECLS




#endif // LTKDEBUG_H
