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



#ifndef U_CORE_ARRAY_H
#define U_CORE_ARRAY_H

#include <array> // std::array

#include "Types.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//// ERROR NOT WORKING CLASS, USE VECTOR INSTEAD      //////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace uLib {

template< typename T, Size_t size >
class Array : public std::array<T,size> {

};


template< typename T, Size_t size >
class SmartArray : public SmartPointer< Array<T,size> > {
    typedef SmartPointer< Array<T,size> > ptr;
public:
    SmartArray() : ptr(new Array<T,size>()) { }
    SmartArray( const SmartArray &copy) : ptr(copy) { }
    virtual ~SmartArray() {}

    T& operator[](unsigned int p) {
        return ptr::get()->at(p);
    }



};



}

#endif // ARRAY_H
