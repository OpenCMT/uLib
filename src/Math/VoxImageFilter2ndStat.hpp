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



#ifndef VOXIMAGEFILTER2NDSTAT_HPP
#define VOXIMAGEFILTER2NDSTAT_HPP

#include <Math/Dense.h>
#include "Math/VoxImage.h"
#include "VoxImageFilter.h"

////////////////////////////////////////////////////////////////////////////////
/////  VOXIMAGE FILTER ABTRIM  /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace uLib {

template <typename VoxelT>
class VoxFilterAlgorithm2ndStat :
        public VoxImageFilter<VoxelT, VoxFilterAlgorithm2ndStat<VoxelT> > {

public:
    typedef VoxImageFilter<VoxelT, VoxFilterAlgorithm2ndStat<VoxelT> > BaseClass;
    VoxFilterAlgorithm2ndStat(const Vector3i &size) :
        BaseClass(size)
    { }

    float Evaluate(const VoxImage<VoxelT> &buffer, int index)
    {
        const Vector<VoxelT> &vbuf = buffer.ConstData();
        const Vector<VoxelT> &vker = this->m_KernelData.ConstData();
        int vox_size = vbuf.size();
        int ker_size = vker.size();
        int pos;

        // mean //
        float conv = 0, ksum = 0;
        for (int ik = 0; ik < ker_size; ++ik) {
            pos = index + vker[ik].Count - vker[this->m_KernelData.GetCenterData()].Count;
            pos = (pos + vox_size) % vox_size;
            conv += vbuf[pos].Value * vker[ik].Value;
            ksum += vker[ik].Value;
        }
        float mean = conv / ksum;

        // rms //
        conv = 0;
        for (int ik = 0; ik < ker_size; ++ik) {
            pos = index + vker[ik].Count - vker[this->m_KernelData.GetCenterData()].Count;
            pos = (pos + vox_size) % vox_size;
            conv += pow((vbuf[pos].Value * vker[ik].Value) - mean , 2);
        }
        return conv / (vker.size() - 1) ;
    }


};

}
#endif // VOXIMAGEFILTER2NDSTAT_HPP
