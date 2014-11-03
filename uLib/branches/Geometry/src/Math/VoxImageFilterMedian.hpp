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



#ifndef VOXIMAGEFILTERMEDIAN_HPP
#define VOXIMAGEFILTERMEDIAN_HPP

#include <Math/Dense.h>
#include "Math/VoxImage.h"
#include "VoxImageFilter.h"

////////////////////////////////////////////////////////////////////////////////
/////  VOXIMAGE FILTER MEDIAN  /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace uLib {

template <typename VoxelT>
class VoxFilterAlgorithmMedian :
        public VoxImageFilter<VoxelT, VoxFilterAlgorithmMedian<VoxelT> > {
public:
    typedef VoxImageFilter<VoxelT, VoxFilterAlgorithmMedian<VoxelT> > BaseClass;
    VoxFilterAlgorithmMedian(const Vector3i &size) : BaseClass(size) {}

    float Evaluate(const VoxImage<VoxelT> &buffer, int index)
    {
        const Vector<VoxelT> &vbuf = buffer.ConstData();
        const Vector<VoxelT> &vker = this->m_KernelData.ConstData();
        int vox_size = vbuf.size();
        int ker_size = vker.size();
        int pos;

        Vector<float> mfh(ker_size);
        for (int ik = 0; ik < ker_size; ik++) {
            pos = index + vker[ik].Count - vker[this->m_KernelData.GetCenterData()].Count;
            pos = (pos + vox_size) % vox_size;
            mfh[ik] = vbuf[pos].Value * vker[ik].Value;
        }
        std::sort(mfh.begin(), mfh.end());
        pos = 0;
        // count zeroes in filter kernel to move it out of median //
        for (int i = 0; i < ker_size; ++i)
            if (vker[i].Value == 0.0) pos++;
        // median //
        pos += (ker_size - pos) / 2;
        return mfh[pos];
    }
};

}

#endif // VOXIMAGEFILTERMEDIAN_HPP
