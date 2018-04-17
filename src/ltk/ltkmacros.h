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
 * File:   macros.h
 * Author: andrea
 *
 * Created on May 23, 2012, 9:01 AM
 */

#ifndef LTK_MACROS_H
#define	LTK_MACROS_H

// C code in headers, while including them from C++
#ifdef  __cplusplus

# define C_BEGIN_DECLS  extern "C" {
# define C_END_DECLS    }

#define BEGIN_NAMESPACE(name) namespace name {
#define END_NAMESPACE         }

#else

# define C_BEGIN_DECLS
# define C_END_DECLS

#define BEGIN_NAMESPACE(name)
#define END_NAMESPACE

#endif




#endif	/* MACROS_H */

