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
#include "Math/StructuredGrid.h"

#include "Math/VoxImage.h"
#include "Math/VoxImageFilter.h"



using namespace uLib;

struct TestVoxel {
    Scalarf Value;
    unsigned int Count;
};

float GaussianShape(float d)
{
    // normalized manually .. fix //
    return 4.5 * exp(-d * 4.5);
}


class GaussianShapeClass : public Interface::VoxImageFilterShape {
public:
    GaussianShapeClass(float sigma) :
        m_sigma(sigma)
    {}

    float operator ()(float d) {
        return (1/m_sigma) * exp(-d/m_sigma);
    }

private:
    float m_sigma;
};


static float MaxInVector(const Vector<float> &v)
{
    float max = 0;
    for(int i=0; i<v.size(); ++i)
        if(v.at(i) > max) max = v.at(i);
    return max;
}


int main()
{
    BEGIN_TESTING(VoxImageFilters);

    VoxImage<TestVoxel> image(Vector3i(20,30,40));
    image[Vector3i(10,10,10)].Value = 1;
    //image[Vector3i(10,10,8)].Value = 1;
    image.ExportToVtk("test_filter_original.vtk",0);



    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    // RPS //

    {
        VoxFilterAlgorithmSPR<TestVoxel> filter(Vector3i(2,3,4));

        VoxImage<TestVoxel> filtered = image;

        Vector<float> values;
        for(int i=0; i < filter.GetKernelData().GetDims().prod(); ++i) {
            values.push_back(1.);
            std::cout << values[i] << " ";
        }
        std::cout << "\n";

        filter.SetImage(&filtered);

        filter.SetKernelNumericXZY(values);

        filter.SetABTrim(0,2);

        filter.GetKernelData().PrintSelf(std::cout);

        filter.Run();

        filtered.ExportToVtk("filter_RPS_out.vtk",0);
    }





    {

        VoxImage<TestVoxel> image(Vector3i(20,30,40));
        image[Vector3i(10,10,10)].Value = 1;
        image[Vector3i(9,10,8)].Value = 2;
        image.ExportToVtk("test_filter_max_original.vtk",0);



        VoxFilterAlgorithmCustom<TestVoxel> filter(Vector3i(3,3,4));

        Vector<float> values;
        for(int i=0; i < filter.GetKernelData().GetDims().prod(); ++i) {
            values.push_back(static_cast<float>(1));
        }

        filter.SetImage(&image);

        filter.SetKernelNumericXZY(values);

        filter.SetCustomEvaluate(MaxInVector);

        filter.Run();

        image.ExportToVtk("test_filter_max.vtk",0);
    }



    END_TESTING;
}
