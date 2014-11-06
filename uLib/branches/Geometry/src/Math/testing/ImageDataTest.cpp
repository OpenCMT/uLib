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
#include "Math/ImageData.h"

using namespace uLib;

namespace {
struct MyVoxel {
    MyVoxel() : value(0), count(0) {}
    float value;
    int count;
};


struct VoxelMean : public MyVoxel {
    VoxelMean() {}
    void SetValue(const float value) { this->value += value; ++count; }
    float GetValue() const { return value/count; }
};
}




int main() {

    DataVector<MyVoxel> v;

    DataVectorImage img;

    img.Data() = v;
    img.Scalars().SetAccessFunctions(&MyVoxel::value);
    img.SetDims(Vector3i(3,3,3));

    for (int x=0; x<img.GetDims().prod(); ++x){
        img.SetValue(x,x);
        std::cout << img.UnMap(x).transpose() << " -> " << img.GetValue(x) << "\n";
    }

    DataVector<VoxelMean> vm;

    img.Data() = vm;
    img.SetDims(Vector3i(3,3,3));
    img.Scalars().SetAccessFunctions(&VoxelMean::GetValue,&VoxelMean::SetValue);

    for (int x=0; x<img.GetDims().prod(); ++x){
        img.SetValue(x,x);
        img.SetValue(x,x+2);
        img.SetValue(x,x-1);
        std::cout << img.UnMap(x).transpose() << " -> " << img.GetValue(x) << "\n";
    }


}
