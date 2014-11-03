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



#ifndef VOXIMAGEFILTERTHRESHOLD_HPP
#define VOXIMAGEFILTERTHRESHOLD_HPP

#include <Math/Dense.h>
#include "Math/VoxImage.h"
#include "VoxImageFilter.h"

////////////////////////////////////////////////////////////////////////////////
/////  VOXIMAGE FILTER THRESHOLD  //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace uLib {

template <typename VoxelT>
class VoxFilterAlgorithmThreshold :
        public VoxImageFilter<VoxelT, VoxFilterAlgorithmThreshold<VoxelT> > {

    typedef VoxImageFilter<VoxelT, VoxFilterAlgorithmThreshold<VoxelT> > BaseClass;
    //    ULIB_OBJECT_PARAMETERS(BaseClass) {
    //        float threshold;
    //    };

    float m_threshold;

public:
    VoxFilterAlgorithmThreshold(const Vector3i &size) : BaseClass(size)
    {
        //        init_parameters();
        m_threshold = 0;
    }

    inline void SetThreshold(float th) { m_threshold = th; }

    float Evaluate(const VoxImage<VoxelT> &buffer, int index)
    {
        return static_cast<float>(buffer.ConstData().at(index).Value >=
                                  //                                  parameters().threshold);
                                  m_threshold );
    }

};

//template <typename VoxelT>
//inline void VoxFilterAlgorithmThreshold<VoxelT>::init_parameters()
//{
//    parameters().threshold = 0;
//}

}

#endif // VOXIMAGEFILTERTHRESHOLD_HPP
