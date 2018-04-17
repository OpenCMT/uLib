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



#ifndef U_CORE_COLLECTION_H
#define U_CORE_COLLECTION_H

#include <iostream>
#include <vector>

#include "SmartPointer.h"
#include "Vector.h"

////////////////////////////////////////////////////////////////////////////////
///////  COLLECTION TEMPLATE  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Implements concept of unordered collection of elements

namespace uLib {

namespace Abstract {

template <typename T>
class Collection {
public:
    virtual ~Collection() {}

    virtual void AddItem(T obj)     =0;
    virtual void RemoveItem(int i)  =0;
    virtual int  GetNumberOfItems() =0;
    virtual T& At(unsigned int i)   =0;

    virtual void PrintSelf(std::ostream &o) =0;
};

}


template <typename T>
class Collection : public Abstract::Collection<T> {

public:
    Collection() : data() {}
    Collection(int size) : data(size) {}
    ~Collection() {}

    inline void AddItem(T obj)     { data->push_back(obj); }
    inline void RemoveItem(int i)  { data.remove_element(i); }
    inline int  GetNumberOfItems() { return data->size(); }

    inline T& At(unsigned int i) { return data->at(i); }
    inline T& operator[] (unsigned int i) { return data->at(i); }

    inline void PrintSelf(std::ostream &o);

private:
    SmartVector<T> data;
};


template<typename T>
void Collection<T>::PrintSelf(std::ostream &o)
{
    o << " *** uLib Collection *** \n";
    o << " n. of items = " << this->GetNumberOfItems() << "\n";
}


}







#endif // COLLECTION_H
