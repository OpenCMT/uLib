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

#ifndef U_CORE_COMMAINITIALIZER_H
#define U_CORE_COMMAINITIALIZER_H

namespace uLib {

// Comma Initializer template ...
// ContentT should provide operator[] and resize() methods.
// Waiting for Static interface check

template < typename ContainerT, typename ContentT >
struct CommaInitializer
{
    inline explicit CommaInitializer(ContainerT *container, ContentT s)
        : container(container)
    {
        this->index = 0;
        container->resize(1);
        this->container->operator[](0) = s;
    }
    inline CommaInitializer & operator, (ContentT s) {
        this->index++;
        container->resize(index + 1);
        this->container->operator[](this->index) = s;
        return *this;
    }

    ContainerT *container;
    unsigned int index;
};


// Comma Initializer template for fixed array...
// ContentT should provide operator[] and size() methods.
// Waiting for Static interface check

template < typename ContainerT, typename ContentT >
struct CommaInitializerFixed
{
    inline explicit CommaInitializerFixed(ContainerT *container, ContentT s)
        : container(container)
    {
        this->index = 0;
        this->container->operator[](0) = s;
    }
    inline CommaInitializerFixed & operator, (ContentT s) {
        this->index++;
        this->container->operator[](this->index) = s;
        return *this;
    }

    ContainerT *container;
    unsigned int index;
};






} // uLib



#endif // COMMAINITIALIZER_H
