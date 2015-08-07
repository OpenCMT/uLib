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

#include <iostream>

#include "Core/Vector.h"
#include "Core/ClassComposite.h"
#include "Core/ClassCompound.h"

#include "Core/StaticInterface.h"
#include "Core/Mpl.h"
#include "Core/Types.h"
#include "testing-prototype.h"

using namespace uLib;

template < typename _T, class _D >
struct Accessor {
    static inline const _T Get(const _D &data) { return data.Get(); }
    static inline void Set(const _D &data, const _T &value) { data.Set(value); }
};

struct Voxel {    
    float a;
    int b;
    
    const float Get() const { return a; }
    void Set(const float value) { this->a = value; ++this->b; }    
};

template < class _T, class _C >
class DataSet : public ClassCompound<_C> 
{    
    typedef _C Container;
public:       

    
    
};



int main(int argc, char *argv[])
{
    BEGIN_TESTING(ClassComposite);
   
    Voxel v1 = { 1, 2 };
    Voxel v2 = { 555, 2368 };
        
    ClassComposite<int,float> p1;    
    ClassComposite<Voxel, float> p2;    
    ClassComposite<Voxel, float> p3;    
        
    p1.A0() = 0;
    p1.A1() = 555.2368;
    
    p2.A0() = v2;
    p2.A1() = 0;
    
    p2.copy(p1);        
    TEST1( p1.A1() == p2.A1() );
    
    p3.A0() = v1;
    p3 = p2;
    
    std::cout << p2.A0().a << " " << p2.A0().b << "\n";
    
    TEST1( p2.A0().a == 555 );
    TEST1( p2.A0().b == 2368 );
        
    
    
    END_TESTING;           
}
