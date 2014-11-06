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

#include "Core/Vector.h"
#include "Core/StaticInterface.h"
#include "Math/Dense.h"
#include "Math/ImageData.h"

#include <iostream>
#include <stdlib.h>

namespace uLib {




////////////////////////////////////////////////////////////////////////////////
//  ABSTRACT VOX IMAGE    //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//namespace Abstract {
//class VoxImage : public uLib::ImageData {
//public:
//    typedef uLib::ImageData BaseClass;

//    virtual float GetValue(const Vector3i id) const = 0;
//    virtual float GetValue(const int id) const = 0;
//    virtual void SetValue(const Vector3i id, float value) = 0;
//    virtual void SetValue(const int id, float value) = 0;

//    virtual void SetDims(const Vector3i &size) = 0;

//    void ExportToVtk(const char *file, bool density_type = 0);
//    void ExportToVtkXml(const char *file, bool density_type = 0);
//    int ImportFromVtk(const char *file);

//protected:

//    virtual ~VoxImage() {}
//    VoxImage(const Vector3i &size) : BaseClass(size) {}
//};
//}

////////////////////////////////////////////////////////////////////////////////
//  VOXEL   ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


struct Voxel {
    Scalarf      Value;
    float & operator()() { return Value; }
    const float & operator()() const { return Value; }
};

template <typename T>
std::basic_ostream<T> & operator << (std::basic_ostream<T> &o, const Voxel &v) {
    o << v.Value;
    return o;
}


////////////////////////////////////////////////////////////////////////////////
//  VOX IMAGE  /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template< typename T >
class VoxImage :  public ImageData {
public:
    typedef ImageData BaseClass;

    VoxImage();

    VoxImage(const Vector3i &size);

    VoxImage(const VoxImage<T> &copy) :
        BaseClass(copy)
    {
        this->m_Data = copy.m_Data;
    }

    uLibRefMacro(Data,Vector<T>)
    inline const Vector<T>& ConstData() const { return m_Data; }

    inline const T& At(int i)              const { return m_Data.at(i); }
    inline const T& At(const Vector3i &id) const { return m_Data.at(Map(id)); }
    inline T& At(int i)                          { return m_Data.at(i); }
    inline T& At(const Vector3i &id)             { return m_Data.at(Map(id)); }

    inline const T& operator[](unsigned int i)     const { return m_Data[i]; }
    inline const T& operator[](const Vector3i &id) const { return m_Data[Map(id)]; }
    inline T& operator[](unsigned int i)     { return m_Data[i]; }
    inline T& operator[](const Vector3i &id) { return m_Data[Map(id)]; }

    // this implements Abstract interface //
    inline void * GetDataPointer(const Id_t id) const { return (void *)&this->At(id); }
    inline Scalarf GetValue(const Vector3i id) const { return this->At(id).Value; }
    inline Scalarf GetValue(const int id) const { return this->At(id).Value; }
    inline void SetValue(const Vector3i id, Scalarf value) { this->operator [](id).Value = value; }
    inline void SetValue(const int id, float value) { this->operator [](id).Value = value; }

    // fix needed
    inline void SetDims(const Vector3i &size) {
        this->m_Data.resize(size.prod());
        ImageMap::SetDims(size);
    }    

    inline VoxImage<T> clipImage(const Vector3i begin, const Vector3i end) const;

    inline VoxImage<T> clipImage(const Vector4f begin, const Vector4f end) const;

    inline VoxImage<T> clipImage(const float density) const;

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
    Vector<T> m_Data;
};


template<typename T>
VoxImage<T>::VoxImage() :
    m_Data(0),
    BaseClass(Vector3i(0,0,0)) {}

template<typename T>
VoxImage<T>::VoxImage(const Vector3i &size) :
    m_Data(size.prod()),
    BaseClass(size) {}


template <typename T>
VoxImage<T> VoxImage<T>::clipImage(const Vector3i begin, const Vector3i end) const
{
        Vector3i dim = (end-begin)+Vector3i(1,1,1);
        VoxImage<T> out(*this);
        out.SetDims(dim);
        // WARNING Origin or Position???
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
VoxImage<T> VoxImage<T>::clipImage(const Vector4f begin, const Vector4f end) const
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


template<typename T>
void VoxImage<T>::InitVoxels(T t)
{
    std::fill( m_Data.begin(), m_Data.end(), t ); // warning... stl function //
}





} // uLib







#endif // VOXIMAGE_H
