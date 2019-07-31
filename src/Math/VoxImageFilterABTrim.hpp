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



#ifndef VOXIMAGEFILTERABTRIM_HPP
#define VOXIMAGEFILTERABTRIM_HPP

#include <Math/Dense.h>
#include "Math/VoxImage.h"
#include "VoxImageFilter.h"

////////////////////////////////////////////////////////////////////////////////
/////  VOXIMAGE FILTER ABTRIM  /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace uLib {

template <typename VoxelT>
class VoxFilterAlgorithmAbtrim :
        public VoxImageFilter<VoxelT, VoxFilterAlgorithmAbtrim<VoxelT> > {

    struct KernelSortAscending
    {
        bool operator()(const VoxelT& e1, const VoxelT& e2)
        { return e1.Value < e2.Value; }
    };

public:
    typedef VoxImageFilter<VoxelT, VoxFilterAlgorithmAbtrim<VoxelT> > BaseClass;
    VoxFilterAlgorithmAbtrim(const Vector3i &size) :
        BaseClass(size)
    {
        mAtrim = 0;
        mBtrim = 0;
    }

    float Evaluate(const VoxImage<VoxelT> &buffer, int index)
    {
        const std::vector<VoxelT> &vbuf = buffer.ConstData();
        const std::vector<VoxelT> &vker = this->m_KernelData.ConstData();
        int vox_size = vbuf.size();
        int ker_size = vker.size();
        int pos;

        std::vector<VoxelT> mfh(ker_size);
        for (int i = 0; i < ker_size; ++i)
            mfh[i].Count = i; //index key for ordering function
        for (int ik = 0; ik < ker_size; ik++) {
            pos = index + vker[ik].Count - vker[this->m_KernelData.GetCenterData()].Count;
            pos = (pos + vox_size) % vox_size;
            mfh[ik].Value = vbuf[pos].Value;
        }

        std::sort(mfh.begin(), mfh.end(), KernelSortAscending());
        float ker_sum = 0;
        float fconv = 0;
        for (int ik = 0; ik < mAtrim; ik++)
            ker_sum += vker[ mfh[ik].Count ].Value;
        for (int ik = mAtrim; ik < ker_size - mBtrim; ik++) {
            fconv += mfh[ik].Value * vker[ mfh[ik].Count ].Value; // convloution //
            ker_sum += vker[ mfh[ik].Count ].Value;
        }
        for (int ik = ker_size - mBtrim; ik < ker_size; ik++)
            ker_sum += vker[ mfh[ik].Count ].Value;

        return fconv / ker_sum;
    }

    inline void SetABTrim(int a, int b) { mAtrim = a; mBtrim = b; }

private:
    int mAtrim;
    int mBtrim;
};



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Roberspierre Filter //



template <typename VoxelT>
class VoxFilterAlgorithmSPR :
        public VoxImageFilter<VoxelT, VoxFilterAlgorithmSPR<VoxelT> > {

    struct KernelSortAscending
    {
        bool operator()(const VoxelT& e1, const VoxelT& e2)
        { return e1.Value < e2.Value; }
    };

public:
    typedef VoxImageFilter<VoxelT, VoxFilterAlgorithmSPR<VoxelT> > BaseClass;
    VoxFilterAlgorithmSPR(const Vector3i &size) :
        BaseClass(size)
    {
        mAtrim = 0;
        mBtrim = 0;
    }

    float Evaluate(const VoxImage<VoxelT> &buffer, int index)
    {
        const std::vector<VoxelT> &vbuf = buffer.ConstData();
        const std::vector<VoxelT> &vker = this->m_KernelData.ConstData();
        int vox_size = vbuf.size();
        int ker_size = vker.size();
        int pos;

        std::vector<VoxelT> mfh(ker_size);
        for (int i = 0; i < ker_size; ++i)
            mfh[i].Count = i; //index key for ordering function
        for (int ik = 0; ik < ker_size; ik++) {
            pos = index + vker[ik].Count -
                    vker[this->m_KernelData.GetCenterData()].Count;
            pos = (pos + vox_size) % vox_size;
            mfh[ik].Value = vbuf[pos].Value;
        }

        std::sort(mfh.begin(), mfh.end(), KernelSortAscending());
        float spr = vbuf[index].Value;
        if( (mAtrim > 0 && spr <= mfh[mAtrim-1].Value) ||
                (mBtrim > 0 && spr >= mfh[ker_size - mBtrim].Value) )
        {
            float ker_sum = 0;
            float fconv = 0;
            for (int ik = 0; ik < mAtrim; ik++)
                ker_sum += vker[ mfh[ik].Count ].Value;
            for (int ik = mAtrim; ik < ker_size - mBtrim; ik++) {
                fconv += mfh[ik].Value * vker[ mfh[ik].Count ].Value;
                ker_sum += vker[ mfh[ik].Count ].Value;
            }
            for (int ik = ker_size - mBtrim; ik < ker_size; ik++)
                ker_sum += vker[ mfh[ik].Count ].Value;

            return fconv / ker_sum;
        }
        else
            return spr;
    }

    inline void SetABTrim(int a, int b) { mAtrim = a; mBtrim = b; }

private:
    int mAtrim;
    int mBtrim;
};




}

#endif // VOXIMAGEFILTERABTRIM_HPP
