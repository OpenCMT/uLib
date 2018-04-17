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



#ifndef VOXIMAGEFILTERBILATERAL_HPP
#define VOXIMAGEFILTERBILATERAL_HPP

#include <Math/Dense.h>
#include "Math/VoxImage.h"
#include "VoxImageFilter.h"

////////////////////////////////////////////////////////////////////////////////
/////  VOXIMAGE FILTER LINEAR  /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace uLib {


template <typename VoxelT>
class VoxFilterAlgorithmBilateral :
        public VoxImageFilter<VoxelT, VoxFilterAlgorithmBilateral<VoxelT> > {
public:
    typedef VoxImageFilter<VoxelT, VoxFilterAlgorithmBilateral<VoxelT> > BaseClass;
    VoxFilterAlgorithmBilateral(const Vector3i &size) : BaseClass(size) {
        m_sigma = 1;
    }

    float Evaluate(const VoxImage<VoxelT> &buffer, int index)
    {
        const Vector<VoxelT> &vbuf = buffer.ConstData();
        const Vector<VoxelT> &vker = this->m_KernelData.ConstData();
        int vox_size = vbuf.size();
        int ker_size = vker.size();
        int pos;
        float conv = 0, ksum = 0;
        float gamma_smooth;
        for (int ik = 0; ik < ker_size; ++ik) {
            //            if (ik==this->m_KernelData.GetCenterData()) continue;
            pos = index + vker[ik].Count - vker[this->m_KernelData.GetCenterData()].Count;
            pos = (pos + vox_size) % vox_size;
            gamma_smooth = compute_gauss( fabs(vbuf[index].Value - vbuf[pos].Value) * 1.E6 );
            conv += vbuf[pos].Value * vker[ik].Value * gamma_smooth;
            ksum += vker[ik].Value * gamma_smooth;
        }
        return conv / ksum;
    }

    inline void SetIntensitySigma(const float s) { m_sigma = s; }

private:
    inline float compute_gauss(const float x) {
        return 1/(sqrt(2*M_PI)* m_sigma) * exp(-0.5*(x*x)/(m_sigma*m_sigma));
    }

    Scalarf m_sigma;
};


template <typename VoxelT>
class VoxFilterAlgorithmBilateralTrim :
        public VoxImageFilter<VoxelT, VoxFilterAlgorithmBilateralTrim<VoxelT> > {

    typedef std::pair<float,float> FPair;

    struct KernelSortAscending
    {
        bool operator()(const FPair& e1, const FPair& e2)
        { return e1.second < e2.second; }
    };

public:
    typedef VoxImageFilter<VoxelT, VoxFilterAlgorithmBilateralTrim<VoxelT> > BaseClass;
    VoxFilterAlgorithmBilateralTrim(const Vector3i &size) : BaseClass(size) {
        m_sigma = 1;
        mAtrim = 0;
        mBtrim = 0;
    }

    float Evaluate(const VoxImage<VoxelT> &buffer, int index)
    {
        const Vector<VoxelT> &vbuf = buffer.ConstData();
        const Vector<VoxelT> &vker = this->m_KernelData.ConstData();
        int img_size = vbuf.size();
        int ker_size = vker.size();
        int pos;



        Vector<FPair> mfh(ker_size);
        for (int i = 0; i < ker_size; ++i)
            mfh[i].first = vker[i].Value; // kernel value in first
        for (int ik = 0; ik < ker_size; ik++) {
            pos = index + vker[ik].Count - vker[this->m_KernelData.GetCenterData()].Count;
            pos = (pos + img_size) % img_size;
            mfh[ik].second = vbuf[pos].Value; // image value in second
        }
        std::sort(mfh.begin(), mfh.end(), KernelSortAscending());

        float conv = 0, ksum = 0;
        float gamma_smooth;
        //        for (int ik = 0; ik < mAtrim; ik++)
        //            ksum += mfh[ik].first;
        for (int ik = mAtrim; ik < ker_size - mBtrim; ik++) {
            gamma_smooth = compute_gauss( fabs(vbuf[index].Value - mfh[ik].second) * 1.E6 );
            conv += mfh[ik].first * mfh[ik].second * gamma_smooth;
            ksum += mfh[ik].first * gamma_smooth;
        }
        //        for (int ik = ker_size - mBtrim; ik < ker_size; ik++)
        //            ksum += mfh[ik].first;

        return conv / ksum;
    }

    inline void SetIntensitySigma(const float s) { m_sigma = s; }
    inline void SetABTrim(int a, int b) { mAtrim = a; mBtrim = b; }

private:
    inline float compute_gauss(const float x) {
        return 1/(sqrt(2*M_PI)* m_sigma) * exp(-0.5*(x*x)/(m_sigma*m_sigma));
    }

    Scalarf m_sigma;
    int mAtrim;
    int mBtrim;
};

}

#endif // VOXIMAGEFILTERBILATERAL_HPP
