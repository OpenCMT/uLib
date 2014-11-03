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


#include <stddef.h>

#include "testing-prototype.h"

#include "Math/Dense.h"
#include "Math/ContainerBox.h"
#include "Math/StructuredData.h"
#include "Math/DataSet.h"

#include <iostream>

using namespace uLib;


struct Data {
    Data() : d1(123), d2(234), i3(345) {}
    float d1,d2;
    int i3;
    float D2() { return d2; }
    float operator()() { return d2; }
};



int main() {
    BEGIN_TESTING(Structured Data);

    Data data;

    VectorData<Data> vd;
    vd.push_back(data);
    vd.push_back(Data());
    vd.push_back(Data());

    vd.SetScalar(sizeof(float));
    std::cout << vd.Value<float>(2) << "\n";

    vd.SetScalar(offsetof(Data,i3));
    std::cout << vd.Value<int>(2) << "\n";

//    vd.SetBindScalar(&data,&Data::D2);
//    std::cout << vd.BindValue(2) << "\n";


    END_TESTING;
}



int main2() {
    BEGIN_TESTING(Structured Data);

    { // testing unmap function ////////////////////////////////////////////////
        StructuredData sdata(Vector3i(2,3,4));
        for(int i=0; i < sdata.GetDims().prod() ; ++i) {
            Vector3i d = sdata.UnMap(i);
            std::cout << "TEST1( sdata.UnMap(" << i << ") == Vector3i("
                      << d(0) << "," << d(1) << "," << d(2) << ")); \n";
        }
        TEST1( sdata.UnMap(0) == Vector3i(0,0,0));
        TEST1( sdata.UnMap(1) == Vector3i(0,1,0));
        TEST1( sdata.UnMap(2) == Vector3i(0,2,0));
        TEST1( sdata.UnMap(3) == Vector3i(1,0,0));
        TEST1( sdata.UnMap(4) == Vector3i(1,1,0));
        TEST1( sdata.UnMap(5) == Vector3i(1,2,0));
        TEST1( sdata.UnMap(6) == Vector3i(0,0,1));
        TEST1( sdata.UnMap(7) == Vector3i(0,1,1));
        TEST1( sdata.UnMap(8) == Vector3i(0,2,1));
        TEST1( sdata.UnMap(9) == Vector3i(1,0,1));
        TEST1( sdata.UnMap(10) == Vector3i(1,1,1));
        TEST1( sdata.UnMap(11) == Vector3i(1,2,1));
        TEST1( sdata.UnMap(12) == Vector3i(0,0,2));
        TEST1( sdata.UnMap(13) == Vector3i(0,1,2));
        TEST1( sdata.UnMap(14) == Vector3i(0,2,2));
        TEST1( sdata.UnMap(15) == Vector3i(1,0,2));
        TEST1( sdata.UnMap(16) == Vector3i(1,1,2));
        TEST1( sdata.UnMap(17) == Vector3i(1,2,2));
        TEST1( sdata.UnMap(18) == Vector3i(0,0,3));
        TEST1( sdata.UnMap(19) == Vector3i(0,1,3));
        TEST1( sdata.UnMap(20) == Vector3i(0,2,3));
        TEST1( sdata.UnMap(21) == Vector3i(1,0,3));
        TEST1( sdata.UnMap(22) == Vector3i(1,1,3));
        TEST1( sdata.UnMap(23) == Vector3i(1,2,3));


        // testing map /////////////////////////////////////////////////////////
        int i=0;
        // PREDEFINED ORDER IS YXZ //
        for(int z=0; z<sdata.GetDims()(2) ; ++z )
            for(int x=0; x<sdata.GetDims()(0) ; ++x )
                for(int y=0; y<sdata.GetDims()(1) ; ++y )
                {
                    Vector3i index(x,y,z);
                    std::cout << sdata.Map(index) << " ";
                    TEST1( sdata.Map(index) == i++ );
                }
        std::cout << "\n";
    }



    END_TESTING;
}
