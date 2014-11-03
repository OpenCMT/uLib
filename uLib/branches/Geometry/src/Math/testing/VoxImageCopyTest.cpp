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



#include "testing-prototype.h"

#include "Math/VoxImage.h"

using namespace uLib;


struct TestVoxel {
    Scalarf Value;
    unsigned int Count;
};

int main() {
    BEGIN_TESTING(Math VoxImage Copy);

    {
        VoxImage<TestVoxel> img(Vector3i(10,10,10));
        TestVoxel zero = {0,0};
        img.InitVoxels(zero);
        TestVoxel nonzero = {5.552368, 0};
        img[Vector3i(5,1,7)] = nonzero;
        img[img.Find(HPoint3f(3,3,3))].Value = 5.552369;
        TEST1( img.GetValue(Vector3i(5,1,7)) == 5.552368f );


        img.SetOrigin(Vector3f(4,5,6));

        std::cout << "\n";

        img.PrintSelf(std::cout);

        VoxImage<TestVoxel> img2 = img;
        img2.PrintSelf(std::cout);

        TEST1( img.GetOrigin() == img2.GetOrigin() );
        TEST1( img.GetSpacing() == img2.GetSpacing() );

        img2 = img;

    }







    std::cout << "returns " << _fail << "\n";
    END_TESTING;
}
