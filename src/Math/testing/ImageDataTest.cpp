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


#include "Math/DataSet.h"
#include "Math/ImageData.h"

#include <root/TRandom.h>

using namespace uLib;

namespace {
struct MyVoxel {
    MyVoxel() : value(0), count(0) {}
    MyVoxel(float v, int c) : value(v), count(c) {}
    float value;
    int count;
};

struct MyVoxelMeanAccess {
    static void Set(MyVoxel &vox, double val) {
        vox.value = val;
        ++vox.count;
    }
    static double Get(const MyVoxel &vox) { return vox.value/vox.count; }
};

struct MyVoxelValueAccess {
    static void Set(MyVoxel &vox, double val) {
        vox.value = val;
        vox.count = 1;
    }
    static double Get(const MyVoxel &vox) { return vox.value; }
};

struct MyVoxelJitterAccess {
    MyVoxelJitterAccess() : min(-1), max(1) { srand (static_cast <unsigned> (time(0))); }
    MyVoxelJitterAccess(float min, float max) : min(min), max(max) { srand (static_cast <unsigned> (time(0))); }

    float random() const {
        return min + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(max-min)));
    }

    void Set(MyVoxel &vox, double val) {
        vox.value = val + random();
        vox.count = 1;
    }
    double Get(const MyVoxel &vox) const { return vox.value / vox.count + random(); }

    float min, max;
};
}



int main() {

    DataVectorCompound< MyVoxel, MyVoxelMeanAccess > data;
    data.Data().push_back( MyVoxel(5,1) );
    data.Data().push_back( MyVoxel(10,2) );
    data.Data().push_back( MyVoxel(15,3) );
    data.Data().push_back( MyVoxel(2368,1) );

    data[3].value = 123;

    DataVectorCompound< MyVoxel, MyVoxelValueAccess > data2 = data;

    std::cout << "image data test \n";
    foreach (MyVoxel &el, data2.Data()) {
        std::cout << "-> " << el.value << " - " << el.count << "\n";
    }

    DataVectorCompound< MyVoxel, MyVoxelJitterAccess > data3 = data2;
    data3.A0().min = -1;
    data3.A0().max =  1;
    data3.AddScalarAccess("scalars",&MyVoxel::value);
    data3.AddScalarAccess("counts",&MyVoxel::count);

    std::cout << "image data test \n";
    for(int i=0; i<data3.GetSize(); ++i) {
        std::cout << " -> " << data3.GetScalar(i) << " - " << data3.GetScalar("counts",i) << "\n";
    }

}

