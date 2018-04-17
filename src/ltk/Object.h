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



#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>      // for std allocator   //
#include <string.h>      // for memcpy //
#include <assert.h>

#include "templates.h"

BEGIN_NAMESPACE(ltk) 


C_BEGIN_DECLS

struct _ltkObject
{
  int element;
};

struct _ltkObjectClass {
  size_t class_size;
  void (* constructor)(struct _ltkObject *);
  void (* destructor) (struct _ltkObject *);
  int  (* GetElement) (struct _ltkObject *);
};

struct _ltkObject *ltk_object_new() 
{
  return NULL;  
}


C_END_DECLS

#ifdef __cplusplus

class Object 
{
  struct _ltkObject *d;
  typedef struct _ltkObject ObjectType;
 public:
 Object() : d(new ObjectType()) { d->element = 5552368; }
  int GetElement() { return d->element; }
};

#endif


END_NAMESPACE

#endif //OBJECT_H
