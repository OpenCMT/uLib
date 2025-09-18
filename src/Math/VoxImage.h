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



#ifndef U_MATH_VOXIMAGE_H
#define U_MATH_VOXIMAGE_H

#include "Core/StaticInterface.h"
#include "Math/Dense.h"
#include "Math/StructuredGrid.h"

#include <iostream>
#include <stdlib.h>
#include <vector>

namespace uLib {

////////////////////////////////////////////////////////////////////////////////
//  ABSTRACT VOX IMAGE    //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace Abstract {

class VoxImage : public uLib::StructuredGrid {
public:
    typedef uLib::StructuredGrid BaseClass;

    virtual float GetValue(const Vector3i &id) const = 0;
    virtual float GetValue(const int id) const = 0;
    virtual void SetValue(const Vector3i &id, float value) = 0;
    virtual void SetValue(const int id, float value) = 0;

    virtual void SetDims(const Vector3i &size) = 0;

    void ExportToVtk(const char *file, bool density_type = 0);

    // use this function to export to VTK binary format
    void ExportToVti (const char *file, bool density_type = 0, bool compressed = 0);
    
    // this function has been deprecated in favor of ExportToVti
    // but it is kept for backward compatibility and because it 
    // does not depend on vtk library
    void ExportToVtkXml(const char *file, bool density_type = 0);

    int ImportFromVtk(const char *file, bool density_type = 0);

    int ImportFromVti(const char *file, bool density_type = 0);

protected:

    virtual ~VoxImage() {}
    VoxImage(const Vector3i &size) : BaseClass(size) {}
};

}

////////////////////////////////////////////////////////////////////////////////
//  VOXEL   ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace Interface {
struct Voxel {
    template<class Self> void check_structural() {
        uLibCheckMember(Self,Value, Scalarf);
    }
};
}

struct Voxel {
    Scalarf      Value;
};


////////////////////////////////////////////////////////////////////////////////
//  VOX IMAGE  /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template< typename T >
class VoxImage :  public Abstract::VoxImage {
public:
    typedef Abstract::VoxImage BaseClass;

    VoxImage();

    VoxImage(const Vector3i &size);

    VoxImage(const VoxImage<T> &copy) :
        BaseClass(copy)
    {
        this->m_Data = copy.m_Data;
    }

    inline std::vector<T> & Data() { return this->m_Data; }
    inline const std::vector<T>& ConstData() const { return m_Data; }

    inline const T& At(int i)              const { return m_Data.at(i); }
    inline const T& At(const Vector3i &id) const { return m_Data.at(Map(id)); }
    inline T& operator[](unsigned int i)     { return m_Data[i]; }
    inline T& operator[](const Vector3i &id) { return m_Data[Map(id)]; }

    // this implements Abstract interface //
    inline Scalarf GetValue(const Vector3i &id) const {
        return this->At(id).Value;
    }
    inline Scalarf GetValue(const int id) const {
        return this->At(id).Value;
    }

    inline void SetValue(const Vector3i &id, Scalarf value) {
        this->operator [](id).Value = value;
    }
    inline void SetValue(const int id, float value) {
        this->operator [](id).Value = value;
    }

    inline void SetDims(const Vector3i &size) {
        this->m_Data.resize(size.prod());
        BaseClass::BaseClass::SetDims(size); // FIX horrible coding style !
    }

    inline VoxImage<T> clipImage(const Vector3i begin, const Vector3i end) const;
    inline VoxImage<T> clipImage(const HPoint3f begin, const HPoint3f end) const;
    inline VoxImage<T> clipImage(const float density) const;
    inline VoxImage<T> clipImage(const float densityMin, const float densityMax) const;

    inline VoxImage<T> maskImage(const HPoint3f begin, const HPoint3f end, float value) const;
    inline VoxImage<T> maskImage(const float threshold, float belowValue=0, float aboveValue=0) const;
    inline VoxImage<T> fixVoxels(const float threshold, float tolerance) const;
    inline VoxImage<T> fixVoxels(const float threshold, float tolerance, const HPoint3f begin, const HPoint3f end) const;
    inline VoxImage<T> fixVoxelsAroundPlane(const float threshold, float tolerance, const HPoint3f begin, const HPoint3f end, bool aboveAir) const;
    inline VoxImage<T> fixVoxels(const HPoint3f begin, const HPoint3f end) const;
    inline VoxImage<T> Abs() const;

    inline void SelectScalarfComponent(T &element, Scalarf *scalar);

    inline void InitVoxels(T t);

    // MATH OPERATORS //
    inline void operator *=(Scalarf scalar) {
        for(unsigned int i = 0; i < m_Data.size(); ++i)
            m_Data[i].Value *= scalar;
    }
    inline void operator +=(Scalarf scalar) {
        for(unsigned int i = 0; i < m_Data.size(); ++i)
            m_Data[i].Value += scalar;
    }
    inline void operator /=(Scalarf scalar) {
        for(unsigned int i = 0; i < m_Data.size(); ++i)
            m_Data[i].Value /= scalar;
    }
    inline void operator -=(Scalarf scalar) {
        for(unsigned int i = 0; i < m_Data.size(); ++i)
            m_Data[i].Value -= scalar;
    }

    // MATH VoxImage Operators //
    template <typename S>
    void operator +=(VoxImage<S> &sibling) {
        if (this->GetDims() != sibling.GetDims()) {
            //printf("Warning when adding VoxImages: I'm NOT doing it!\n");
            return;
        }// WARNING! You must Warn the user!
        for(unsigned int i = 0; i < m_Data.size(); ++i) {
            m_Data[i].Value += sibling.At(i).Value;
        }
    }

    template <typename S>
    void operator -=(VoxImage<S> &sibling) {
        if (this->GetDims() != sibling.GetDims()) {
            //printf("Warning when subtracting VoxImages: I'm NOT doing it!\n");
            return;
        }// WARNING! You must Warn the user!
        for(unsigned int i = 0; i < m_Data.size(); ++i) {
            m_Data[i].Value -= sibling.At(i).Value;
        }
    }

    template <typename S>
    void operator *=(VoxImage<S> &sibling) {
        if (this->GetDims() != sibling.GetDims()) {
            //printf("Warning when multiplying VoxImages: I'm NOT doing it!\n");
            return;
        }// WARNING! You must Warn the user!
        for(unsigned int i = 0; i < m_Data.size(); ++i) {
            m_Data[i].Value *= sibling.At(i).Value;
        }
    }

    template <typename S>
    void operator /=(VoxImage<S> &sibling) {
        if (this->GetDims() != sibling.GetDims()) {
            //printf("Warning when dividing VoxImages: I'm NOT doing it!\n");
            return;
        }// WARNING! You must Warn the user!
        for(unsigned int i = 0; i < m_Data.size(); ++i) {
            m_Data[i].Value /= sibling.At(i).Value;
        }
    }

private:
    std::vector<T> m_Data;
};


template<typename T>
VoxImage<T>::VoxImage() :
    m_Data(0),
    BaseClass(Vector3i(0,0,0))
{ Interface::IsA <T,Interface::Voxel>(); /* structural check for T */ }

template<typename T>
VoxImage<T>::VoxImage(const Vector3i &size) :
    m_Data(size.prod()),
    BaseClass(size)
{ Interface::IsA <T,Interface::Voxel>(); /* structural check for T */ }


template <typename T>
VoxImage<T> VoxImage<T>::clipImage(const Vector3i begin, const Vector3i end) const
{
        Vector3i dim = (end-begin)+Vector3i(1,1,1);
        VoxImage<T> out(*this);
        out.SetDims(dim);
        out.SetPosition(this->GetPosition() + this->GetSpacing().cwiseProduct(begin.cast<float>()) );

        for(uint x = 0; x<dim(0); ++x )
            for(uint y = 0; y<dim(1); ++y )
                for(uint z = 0; z<dim(2); ++z )
                {
                    Vector3i id = Vector3i(x,y,z);
                    out[id] = this->At(begin + id);
                }
        return out;
}

template <typename T>
VoxImage<T> VoxImage<T>::clipImage(const HPoint3f begin, const HPoint3f end) const
{
    Vector3i v1 = this->Find(begin);
    Vector3i v2 = this->Find(end);
    return this->clipImage(v1,v2);
}

template <typename T>
VoxImage<T> VoxImage<T>::clipImage(const float density) const
{
    Vector3i v1 = this->GetDims();
    Vector3i v2 = Vector3i(0,0,0);
    for(uint i=0; i< this->m_Data.size(); ++i) {
        if( this->GetValue(i) >= density ) {
            Vector3i id = this->UnMap(i);
            v1 = v1.array().min(id.array());
            v2 = v2.array().max(id.array());
        }
    }
    return this->clipImage(v1,v2);
}

template <typename T>
VoxImage<T> VoxImage<T>::clipImage(const float densityMin, const float densityMax) const
{
    Vector3i v1 = this->GetDims();
    Vector3i v2 = Vector3i(0,0,0);
    for(uint i=0; i< this->m_Data.size(); ++i) {
        if( this->GetValue(i) >= densityMin && this->GetValue(i) <= densityMax) {
            Vector3i id = this->UnMap(i);
            v1 = v1.array().min(id.array());
            v2 = v2.array().max(id.array());
        }
    }
    return this->clipImage(v1,v2);
}

template <typename T>
VoxImage<T> VoxImage<T>::maskImage(const HPoint3f begin, const HPoint3f end, float value) const
{
    VoxImage<T> out(*this);
    out.SetDims(this->GetDims());
    out.SetPosition(this->GetPosition());

    Vector3i voxB = this->Find(begin);
    Vector3i voxE = this->Find(end);

    Vector3i ID;

    for(int ix=voxB(0); ix<voxE(0); ix++)
        for(int iy=voxB(1); iy<voxE(1); iy++)
            for(int iz=voxB(2); iz<voxE(2); iz++){
                ID << ix,iy,iz;
                out.SetValue(ID,value*1.E-6);
            }

    return out;
}

template <typename T>
VoxImage<T> VoxImage<T>::maskImage(const float threshold, float belowValue, float aboveValue) const
{
    std::cout << "VoxImage: maskImage, fixing voxels under threshold " << threshold;
    if(belowValue)
        std::cout << " at value " << belowValue;
    else
        std::cout << " at -value";
    std::cout << ", voxels above threshold at value ";
    if(aboveValue)
        std::cout << aboveValue;
    else
        std::cout << "found";


    VoxImage<T> out(*this);
    out.SetDims(this->GetDims());
    out.SetPosition(this->GetPosition());

    for(uint i=0; i< this->m_Data.size(); ++i) {
        // skip negative voxels: they are already frozen
        if( this->GetValue(i) >= 0 ){
            // voxels under threshold
            if( this->GetValue(i) <= threshold*1.E-6 ){
                if(belowValue){
                    //                std::cout << "vox " << i << ", " << this->GetValue(i);
                    //                std::cout << " ----> set to " << -1.*belowValue*1.E-6 << std::endl;
                    out.SetValue(i,-1.*belowValue*1.E-6);}
                else
                    out.SetValue(i,-1.*this->GetValue(i));
            }
            // voxels over threshold
            else{
                if(aboveValue)
                    out.SetValue(i,aboveValue*1.E-6);
                else
                    out.SetValue(i,this->GetValue(i));
            }
        }
    }
    return out;
}

template <typename T>
VoxImage<T> VoxImage<T>::fixVoxels(const float threshold, float tolerance) const
{
    std::cout << "VoxImage: fixing voxels with value " << threshold << std::endl;

    VoxImage<T> out(*this);
    out.SetDims(this->GetDims());
    out.SetPosition(this->GetPosition());

    for(uint i=0; i< this->m_Data.size(); ++i) {
        // voxels around threshold
        if( fabs(this->GetValue(i) - threshold*1.E-6) < tolerance* 1.E-6 ){
//            std::cout << "vox " << i << ", " << this->GetValue(i);
//            std::cout << " ----> set to " << -1.*this->GetValue(i) << std::endl;
                out.SetValue(i,-1.*this->GetValue(i));
        }
    }
    return out;
}

template <typename T>
VoxImage<T> VoxImage<T>::Abs() const
{
    std::cout << "VoxImage: set abs voxels value " << std::endl;

    VoxImage<T> out(*this);
    out.SetDims(this->GetDims());
    out.SetPosition(this->GetPosition());

    for(uint i=0; i< this->m_Data.size(); ++i)
        out.SetValue(i,fabs(this->GetValue(i)));

    return out;
}

template <typename T>
VoxImage<T> VoxImage<T>::fixVoxels( const float threshold, float tolerance, const HPoint3f begin, const HPoint3f end) const
{
    VoxImage<T> out(*this);
    out.SetDims(this->GetDims());
    out.SetPosition(this->GetPosition());

    Vector3i voxB = this->Find(begin);
    Vector3i voxE = this->Find(end);

    Vector3i ID;

    for(int ix=voxB(0); ix<voxE(0); ix++)
        for(int iy=voxB(1); iy<voxE(1); iy++)
            for(int iz=voxB(2); iz<voxE(2); iz++){
                ID << ix,iy,iz;
                // voxels around threshold
                if( fabs(this->GetValue(ID) - threshold*1.E-6) < tolerance*1.E-6 ){
                    out.SetValue(ID,-1.*this->GetValue(ID));
                }
            }

    return out;
}

template <typename T>
VoxImage<T> VoxImage<T>::fixVoxels(const HPoint3f begin, const HPoint3f end) const
{
    VoxImage<T> out(*this);
    out.SetDims(this->GetDims());
    out.SetPosition(this->GetPosition());

    Vector3i voxB = this->Find(begin);
    Vector3i voxE = this->Find(end);

    Vector3i ID;

    for(int ix=voxB(0); ix<voxE(0); ix++)
        for(int iy=voxB(1); iy<voxE(1); iy++)
            for(int iz=voxB(2); iz<voxE(2); iz++){
                ID << ix,iy,iz;
                // voxels around threshold
                out.SetValue(ID,-1.*this->GetValue(ID));
            }
    return out;
}


template <typename T>
VoxImage<T> VoxImage<T>::fixVoxelsAroundPlane( const float threshold, float tolerance, const HPoint3f B, const HPoint3f E, bool aboveAir) const
{
    VoxImage<T> out(*this);
    Vector3i dim = this->GetDims();
    out.SetDims(dim);
    out.SetPosition(this->GetPosition());

    HPoint3f  Bcoll = this->GetPosition().homogeneous();

    Vector3i ID;
    for(int ix=0; ix<dim(0); ix++)
        for(int iy=0; iy<dim(1); iy++)
            for(int iz=0; iz<dim(2); iz++){
                ID << ix,iy,iz;

                // B, E voxel position
                Vector3i iv(ix,iy,iz);
                Vector3f v = Vector3f(iv.cast<float>().cwiseProduct(this->GetSpacing()));
                HPoint3f Bvox = Bcoll + HPoint3f(v);
                HPoint3f Evox = Bvox + this->GetSpacing().homogeneous();
                HPoint3f V = Bvox + 0.5*(this->GetSpacing().homogeneous());

                // if distance point (x0,y0) from line by points (x1,y1) and (x2,y2) is less than tolerance
                float x1 = B[1];
                float y1 = B[2];
                float x2 = E[1];
                float y2 = E[2];
                float x0 = V[1];
                float y0 = V[2];
                float dist = fabs( (x2-x1)*(y1-y0) - ((x1-x0)*(y2-y1))) / sqrt( (x2-x1)*(x2-x1)+((y2-y1)*(y2-y1)));
                float distSign = (x2-x1)*(y1-y0) - ((x1-x0)*(y2-y1));

                // set voxel air value
                if(dist < tolerance){
                    //std::cout << "voxel " << iv << ", line " << dist << ", tolerance " << tolerance << std::endl;
                    out.SetValue(ID,threshold*1.E-6);
                }
                else
                    out.SetValue(ID,this->GetValue(ID));

                if((distSign>0 && aboveAir) || (distSign<0 && !aboveAir)  )
                    out.SetValue(ID,threshold*1.E-6);
            }
    return out;
}


template<typename T>
void VoxImage<T>::InitVoxels(T t)
{
    std::fill( m_Data.begin(), m_Data.end(), t ); // warning... stl function //
}

}

#endif // VOXIMAGE_H
