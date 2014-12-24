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



#include <Core/Vector.h>
#include "testing-prototype.h"

#include <algorithm>

template < typename T >
struct __Cmp {
    bool operator()(const T &data, const float value) {
        return data <= value;
    }
};




template<typename _Tp, typename _CmpT>
inline const unsigned long
VectorSplice(const _Tp &_it, const _Tp &_end, const float value, _CmpT _comp)
  {

    _Tp it = _it;
    _Tp end = _end-1;
    for(it; it != end; )
    {
        if ( _comp(*it, value) ) it++;
        else if( _comp(*end, value) )
        {
            std::swap(*it,*end--);
        }
        else --end;
    }
    return it - _it;
}


int main()
{
    BEGIN_TESTING(Vector);

    uLib::Vector<float> v;
    v << 5,4,3,2,6,1,2,3,65,7,32,23,4,3,45,4,34,3,4,4,3,3,4,2,2,3;

    uLib::Vector<float> v2;
    v2 = v;
    std::cout << "v2: " << v2;

    {
        int i = 0;
        foreach (i , v) {
            TEST1(v[i] == v2[i]);
        }
    }

    int id = VectorSplice(v.begin(),v.end(),3,__Cmp<float>());

    std::cout << "id: " << id << "\n";
    std::cout << "vector: ";
    for(uLib::Vector<float>::Iterator it = v.begin(); it!=v.end(); it++)
        std::cout << *it <<" ";
    std::cout << std::endl;

    //    std::sort(v.begin(),v.end(),LT<float>());


    END_TESTING;
}

