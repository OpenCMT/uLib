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



#ifndef VOXIMAGEFILTERCUSTOM_HPP
#define VOXIMAGEFILTERCUSTOM_HPP

#include "Core/Macros.h"
#include <Math/Dense.h>
#include "Math/VoxImage.h"
#include "VoxImageFilter.h"

////////////////////////////////////////////////////////////////////////////////
/////  VOXIMAGE FILTER CUSTOM  /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace uLib {

template <typename VoxelT>
class VoxFilterAlgorithmCustom :
        public VoxImageFilter<VoxelT, VoxFilterAlgorithmCustom<VoxelT> > {


    typedef float (* FunctionPt)(const std::vector<Scalarf> &);
public:
    typedef VoxImageFilter<VoxelT, VoxFilterAlgorithmCustom<VoxelT> > BaseClass;
    VoxFilterAlgorithmCustom(const Vector3i &size) :
        BaseClass(size), m_CustomEvaluate(NULL)
    {}

    float Evaluate(const VoxImage<VoxelT> &buffer, int index)
    {
        if(likely(m_CustomEvaluate)) {
            const std::vector<VoxelT> &vbuf = buffer.ConstData();
            const std::vector<VoxelT> &vker = this->m_KernelData.ConstData();
            int vox_size = vbuf.size();
            int ker_size = vker.size();
            int pos;

            float ker_sum = 0;
            std::vector<Scalarf> mfh(ker_size);
            for (int ik = 0; ik < ker_size; ik++) {
                pos = index + vker[ik].Count - vker[this->m_KernelData.GetCenterData()].Count;
                pos = (pos + vox_size) % vox_size;
                mfh[ik] = vbuf[pos].Value * vker[ik].Value;
                ker_sum += vker[ik].Value;
            }

            return this->m_CustomEvaluate(mfh);
        }
        else
            std::cerr << "Custom evaluate function is NULL \n" <<
                         "No operation performed by filter.\n";

    }

    inline void SetCustomEvaluate(FunctionPt funPt) { this->m_CustomEvaluate = funPt; }

private:
    FunctionPt m_CustomEvaluate;
};

}


#endif // VOXIMAGEFILTERCUSTOM_HPP
