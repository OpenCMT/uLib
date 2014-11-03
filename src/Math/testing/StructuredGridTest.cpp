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




#include <Math/VoxImage.h>
#include "testing-prototype.h"

using namespace uLib;

int main()
{
    BEGIN_TESTING(Math Structured Grid);

    VoxImage<Voxel> f_grid(Vector3i(100,100,100));

    f_grid[Vector3i(1,2,3)]() = 5552368;
    TEST1( f_grid.At(30102)() == 5552368 );


    // TESTING MAP //
    VoxImage<Voxel> test_order(Vector3i(2,2,2));
    int index =0;
    for(int z=0;z<2;++z)
        for(int y=0;y<2;++y)
            for(int x=0;x<2;x++)
            {
                test_order[Vector3i(x,y,z)]() = index;
                std::cout << x << " " << y << " " << z << " -> " <<
                             test_order.At(Vector3i(x,y,z))() << "\n";
                index++;
            }
    test_order.Data().PrintSelf(std::cout);

    int result[8] = {0,2,1,3,4,6,5,7};
    for(int i=0;i<8;++i)
        TEST1( test_order.At(i)() == result[i] );

    // TESTING UNMAP //
    std::cout << "unmap = " << test_order.UnMap(7).transpose() << "\n";
    TEST1( test_order.UnMap(7) == Vector3i(1,1,1) );
    TEST1( test_order.UnMap(6) == Vector3i(1,0,1) );
    TEST1( test_order.UnMap(5) == Vector3i(0,1,1) );
    // ...


    _fail > 0 ? std::cout << "FaIL\n" : std::cout << "OK!\n";
    END_TESTING
}
