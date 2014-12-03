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

#include <iostream>

#include "Core/Vector.h"
#include "Core/ClassCompound.h"

#include "testing-prototype.h"

using namespace uLib;



////////////////////////////////////////////////////////////////////////////////
// WORKING EXAMPLE //

namespace Test {


class Voxel {
public:
    virtual void Set(float) = 0;
    virtual float Get() const = 0;
    virtual ~Voxel() {}
};

class VoxelMean : public Voxel {
public:
    VoxelMean() : m_data(0), m_count(0) {}
    void  Set(float data) { m_data += data; ++m_count; }
    float Get() const { return m_data / m_count; }
private:
    float m_data;
    int m_count;
};

class VoxelVal : public Voxel {
public:
    VoxelVal() : m_data(0) {}
    void Set(float data) { m_data = data; }
    float Get() const { return m_data; }
private:
    float m_data;
};




class VoxCount {
public:
    template < class T >
    int Count(const Vector<T> &ref ) const {
        return ref.size();
    }
};

class VoxCountOver {
public:
    VoxCountOver() : m_threshold(0) {}

    template < class T >
    int Count(const Vector<T> &ref ) const {
        int count = 0 ;
        foreach (const T &el, ref) {
            if( el.Get() >= m_threshold ) ++count;
        }
        return count;
    }
    float m_threshold;
};




class VoxelVectorBase {
public:
    virtual float Get(int) const = 0;
    virtual void Set(int,float) = 0;
    virtual int Size() const = 0;
    virtual int Count() const = 0;
    virtual ~VoxelVectorBase() {}
};

template < class T >
void copy(T *src, T *dst) { }

void copy(VoxelVectorBase *src, VoxelVectorBase *dst) {
    for(int i=0; i<src->Size(); ++i) {
        dst->Set(i,src->Get(i));
    }
}


template < class VoxType,
           class CounterType >
class VoxelVector :
        public VoxelVectorBase,
        public ClassCompound< VoxType, CounterType >
{
    typedef ClassCompound< VoxType, CounterType > Compound;

public:

    VoxelVector() {}

    template < class Other >
    VoxelVector(const Other &t) : Compound(t) {
        // assumes that Other is a voxelvector //
        for(int i=0; i<t.Size(); ++i) {
            this->Set(i, t.Get(i));
        }
    }

    template < class Other >
    VoxelVector & operator = (const Other &t) {
        for(int i=0; i<t.Size(); ++i) {
            this->Set(i, t.Get(i));
        }
        (Compound &)(*this) = t;
        return *this;
    }

    using Compound::operator =;

    float Get(int id) const { return m_data[id].Get(); }
    void Set(int id, float data) {
        if(id >= Size()) m_data.resize(id+1);
        m_data[id].Set(data);
    }
    int Size() const { return m_data.size(); }
    int Count() const {
        return CounterType::Count(m_data);
    }
private:
    friend class VoxelVectorFactory;
    Vector<VoxType> m_data;
};


} // Test


using namespace Test;



int main() {

    VoxelVector< VoxelMean, VoxCountOver > img;
    img.Set(0,555);
    img.Set(1,23);
    img.Set(1,25);
    img.Set(2,68);

    img.A1::m_threshold = 50;

    std::cout << "-> ";
    for(int i=0; i<3; ++i) {
        std::cout << img.Get(i) << " ";
    }
    std::cout << " count: " << img.Count() << "\n";


    VoxelVector< VoxelVal, VoxCountOver > img2 = img;

    img2.Set(1,0);

    std::cout << "-> ";
    for(int i=0; i<3; ++i) {
        std::cout << img2.Get(i) << " ";
    }
    std::cout << " count threshold: " << img2.A1::m_threshold << " ";
    std::cout << " count: " << img2.Count() << "\n";



}















