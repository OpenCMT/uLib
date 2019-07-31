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



#ifndef VOXIMAGEFILTER_HPP
#define VOXIMAGEFILTER_HPP

#include <Math/Dense.h>
#include "Math/StructuredData.h"
#include "Math/VoxImage.h"
#include "VoxImageFilter.h"

namespace uLib {


// KERNEL //////////////////////////////////////////////////////////////////////

template < typename T >
class Kernel : public StructuredData {
    typedef StructuredData BaseClass;
public:
    Kernel(const Vector3i &size);

    inline T& operator[](const Vector3i &id) { return m_Data[Map(id)]; }
    inline T& operator[](const int &id) { return m_Data[id]; }
    inline int GetCenterData() const;

    inline std::vector<T> & Data() { return this->m_Data; }

    inline const std::vector<T>& ConstData() const { return this->m_Data; }

    void PrintSelf(std::ostream &o) const;

private:
    std::vector<T> m_Data;
};

template < typename T >
Kernel<T>::Kernel(const Vector3i &size) :
    BaseClass(size),
    m_Data(size.prod())
{
    Interface::IsA<T,Interface::Voxel>();
}

template < typename T >
inline int Kernel<T>::GetCenterData() const
{
    static int center = Map(this->GetDims() / 2);
    return center;
}

template < typename T >
void Kernel<T>::PrintSelf(std::ostream &o) const
{
    o << " Filter Kernel Dump [XZ_Y]: \n";
    Vector3i index;
    o << "\n Value: \n\n"
      << "------------------------------------------------- \n";
    for (int y = 0 ; y < this->GetDims()(1); ++y ) {
        o << "[y=" << y << "]\n";
        for (int z = 0 ; z < this->GetDims()(2); ++z ) {
            for (int x = 0 ; x < this->GetDims()(0); ++x ) {
                index << x,y,z;
                o << m_Data[Map(index)].Value << " ";
            } o << "\n";
        } o << " --------------------------------------------------- \n";
    }
    o << "\n Offset: \n"
      << "------------------------------------------------- \n";
    for (int y = 0 ; y < this->GetDims()(1); ++y ) {
        o << "[y=" << y << "]\n";
        for (int z = 0 ; z < this->GetDims()(2); ++z ) {
            for (int x = 0 ; x < this->GetDims()(0); ++x ) {
                index << x,y,z;
                o << m_Data[Map(index)].Count << " ";
            } o << "\n";
        } o << " --------------------------------------------------- \n";
    }
}

////////////////////////////////////////////////////////////////////////////////








#define _TPL_  template < typename VoxelT , typename AlgorithmT >
#define _TPLT_ VoxelT,AlgorithmT



_TPL_
VoxImageFilter<_TPLT_>::VoxImageFilter(const Vector3i &size) :
    m_KernelData(size),
    t_Algoritm(static_cast<AlgorithmT *>(this))
{

}

_TPL_
void VoxImageFilter<_TPLT_>::Run()
{
    VoxImage<VoxelT> buffer = *m_Image;
    #pragma omp parallel for
    for(int i=0 ; i < m_Image->Data().size() ; ++i)
        m_Image->operator [](i).Value = this->t_Algoritm->Evaluate(buffer,i);
    #pragma omp barrier
}

_TPL_
void VoxImageFilter<_TPLT_>::SetKernelOffset()
{
    Vector3i id(0,0,0);
    for( int z=0 ; z < m_KernelData.GetDims()(2); ++z ) {
        for( int x=0 ; x < m_KernelData.GetDims()(0); ++x ) {
            for( int y=0 ; y < m_KernelData.GetDims()(1); ++y ) {
                id << x,y,z;
                m_KernelData[id].Count = id.transpose() * m_Image->GetIncrements();
            }
        }
    }
}

_TPL_
float VoxImageFilter<_TPLT_>::Distance2(const Vector3i &v)
{
    Vector3i tmp = v;
    const Vector3i &dim = this->m_KernelData.GetDims();
    Vector3i center = dim / 2;
    tmp = tmp - center;
    center = center.cwiseProduct(center);
    tmp    = tmp.cwiseProduct(tmp);
    return (float)(tmp.sum()) / (float)( center.sum() + 0.25 *
                                         (3 - (dim(0) % 2) - (dim(1) % 2) - (dim(2) % 2)));
}


_TPL_
void VoxImageFilter<_TPLT_>::SetKernelNumericXZY(const std::vector<float> &numeric)
{
    // set data order //
    StructuredData::Order order = m_KernelData.GetDataOrder();
    //m_KernelData.SetDataOrder(StructuredData::XZY);
    Vector3i id;
    int index = 0;
    for( int y=0 ; y < m_KernelData.GetDims()(1); ++y ) {
        for( int z=0 ; z < m_KernelData.GetDims()(2); ++z ) {
            for( int x=0 ; x < m_KernelData.GetDims()(0); ++x ) {
                id << x,y,z;
                m_KernelData[id].Value = numeric[index++];
            }
        }
    }
    //m_KernelData.SetDataOrder(order);
}

_TPL_
void VoxImageFilter<_TPLT_>::SetKernelSpherical(float(* shape)(float))
{
    Vector3i id;
    for( int y=0 ; y < m_KernelData.GetDims()(1); ++y ) {
        for( int z=0 ; z < m_KernelData.GetDims()(2); ++z ) {
            for( int x=0 ; x < m_KernelData.GetDims()(0); ++x ) {
                id << x,y,z;
                m_KernelData[id].Value = shape(this->Distance2(id));
            }
        }
    }
}


_TPL_ template <class ShapeT>
void VoxImageFilter<_TPLT_>::SetKernelSpherical(ShapeT shape)
{
    Interface::IsA<ShapeT,Interface::VoxImageFilterShape>();
    Vector3i id;
    for( int y=0 ; y < m_KernelData.GetDims()(1); ++y ) {
        for( int z=0 ; z < m_KernelData.GetDims()(2); ++z ) {
            for( int x=0 ; x < m_KernelData.GetDims()(0); ++x ) {
                id << x,y,z;
                m_KernelData[id].Value = shape(this->Distance2(id));
            }
        }
    }
}

_TPL_
void VoxImageFilter<_TPLT_>::SetKernelWeightFunction(float (*shape)(const Vector3f &))
{
    const Vector3i &dim = m_KernelData.GetDims();
    Vector3i id;
    Vector3f pt;
    for( int y=0 ; y < dim(1); ++y ) {
        for( int z=0 ; z < dim(2); ++z ) {
            for( int x=0 ; x < dim(0); ++x ) {
                // get voxels centroid coords from kernel center //
                id << x,y,z;
                pt << id(0) - dim(0)/2 + 0.5 * !(dim(0) % 2),
                      id(1) - dim(1)/2 + 0.5 * !(dim(1) % 2),
                      id(2) - dim(2)/2 + 0.5 * !(dim(2) % 2);
                // compute function using given shape //
                m_KernelData[id].Value = shape(pt);
            }
        }
    }
}

_TPL_ template < class ShapeT >
void VoxImageFilter<_TPLT_>::SetKernelWeightFunction(ShapeT shape)
{
    Interface::IsA<ShapeT,Interface::VoxImageFilterShape>();
    const Vector3i &dim = m_KernelData.GetDims();
    Vector3i id;
    Vector3f pt;
    for( int y=0 ; y < dim(1); ++y ) {
        for( int z=0 ; z < dim(2); ++z ) {
            for( int x=0 ; x < dim(0); ++x ) {
                // get voxels centroid coords from kernel center //
                id << x,y,z;
                pt << id(0) - dim(0)/2 + 0.5 * !(dim(0) % 2),
                      id(1) - dim(1)/2 + 0.5 * !(dim(1) % 2),
                      id(2) - dim(2)/2 + 0.5 * !(dim(2) % 2);
                // compute function using given shape //
                m_KernelData[id].Value = shape(pt);
            }
        }
    }
}




_TPL_
void VoxImageFilter<_TPLT_>::SetImage(Abstract::VoxImage *image)
{
    this->m_Image = reinterpret_cast<VoxImage<VoxelT> *> (image);
    this->SetKernelOffset();
}


_TPL_
float VoxImageFilter<_TPLT_>::Convolve(const VoxImage<VoxelT> &buffer, int index)
{
    const std::vector<VoxelT> &vbuf = buffer.ConstData();
    const std::vector<VoxelT> &vker = m_KernelData.ConstData();
    int vox_size = vbuf.size();
    int ker_size = vker.size();
    int pos;
    float conv = 0, ksum = 0;
    for (int ik = 0; ik < ker_size; ++ik) {
        pos = index + vker[ik].Count - vker[m_KernelData.GetCenterData()].Count;
        pos = (pos + vox_size) % vox_size;
        conv += vbuf[pos].Value * vker[ik].Value;
        ksum += vker[ik].Value;
    }
    return conv / ksum;
}



#undef _TPLT_
#undef _TPL_







}




#endif // VOXIMAGEFILTER_HPP
