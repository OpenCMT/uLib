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



#ifndef VOXIMAGEFILTER_H
#define VOXIMAGEFILTER_H

#include "Core/StaticInterface.h"
#include "Core/Object.h"
#include "Math/Dense.h"

#include "Math/VoxImage.h"


namespace uLib {


namespace Interface {
struct VoxImageFilterShape {
    template <class Self> void check_structural() {
        uLibCheckFunction(Self,operator(),float,float);
        uLibCheckFunction(Self,operator(),float,const Vector3f&);
    }
};
}

template < typename VoxelT > class Kernel;


namespace Abstract {
class VoxImageFilter {
public:
    virtual void Run() = 0;

    virtual void SetImage(Abstract::VoxImage *image) = 0;

protected:
    virtual ~VoxImageFilter() {}
};
}


template < typename VoxelT, typename AlgorithmT >
class VoxImageFilter : public Abstract::VoxImageFilter, public Object
{   

public:
    VoxImageFilter(const Vector3i &size);

    void Run();

    void SetKernelNumericXZY(const Vector<float> &numeric);

    void SetKernelSpherical(float (*shape)(float));

    template < class ShapeT >
    void SetKernelSpherical( ShapeT shape );

    void SetKernelWeightFunction(float (*shape)(const Vector3f &));

    template < class ShapeT >
    void SetKernelWeightFunction( ShapeT shape );

    uLibGetMacro(KernelData,Kernel<VoxelT>)

    uLibGetMacro(Image,VoxImage<VoxelT> *)

    void SetImage(Abstract::VoxImage *image);

protected:

    float Convolve(const VoxImage<VoxelT> &buffer, int index); // remove //

    void SetKernelOffset();

    float Distance2(const Vector3i &v);

    // protected members for algorithm access //
    Kernel<VoxelT>    m_KernelData;
    VoxImage<VoxelT> *m_Image;

private:
    AlgorithmT       *t_Algoritm;

};






}


#endif // VOXIMAGEFILTER_H

#include "VoxImageFilter.hpp"

#include "VoxImageFilterLinear.hpp"
#include "VoxImageFilterThreshold.hpp"
#include "VoxImageFilterMedian.hpp"
#include "VoxImageFilterABTrim.hpp"
#include "VoxImageFilterBilateral.hpp"
#include "VoxImageFilter2ndStat.hpp"
#include "VoxImageFilterCustom.hpp"

