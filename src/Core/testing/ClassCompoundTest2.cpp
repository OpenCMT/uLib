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
#include "Core/StaticInterface.h"
#include "Core/Mpl.h"

#include "testing-prototype.h"

using namespace uLib;

// This test aims to define a voxel collection object to test the connection
// with an external counter algorithm. The VoxCollection is set from a Voxel
// definition and the Counter should automatically arange to match it.
// 


namespace Test {

class VoxelInterface {
    void * m_ob;
    float (* m_Get)(void * const);
    void (* m_Set)(void * const, float data);
    template <typename T> static float s_Get(void * const ob) { return static_cast<T*>(ob)->Get(); }
    template <typename T> static void s_Set(void * const ob, float data) { static_cast<T*>(ob)->Set(data); }
public:
    template <typename T>
    VoxelInterface( T& t) :
        m_ob(&t),
        m_Get(&s_Get<T>),
        m_Set(&s_Set<T>)
    {}
    float Get() { return (*m_Get)(m_ob); }
    void  Set(float data) { (*m_Set)(m_ob,data); }
};



class Voxel {
public:
    Voxel() : m_data(0) {}
    void Set(float data) { m_data = data; }
    float Get() const { return m_data; }
private:
    float m_data;
};

class VoxelMean {
public:
    VoxelMean() : m_data(0), m_count(0) {}
    void  Set(float data) { m_data += data; ++m_count; }
    float Get() const { return m_data / m_count; }
private:
    float m_data;
    int m_count;
};





class Counter {    
public:
    template < typename V >
    int Count (const V &cnt) const {
        return cnt.size();
    }
};

class CountOverTh {    
public:
    template < typename V >
    int Count (const V &cnt) const {        
        int count = 0;
        foreach (const typename V::value_type &el, cnt) 
            if(el.Get() > m_threshold) count++;
        return count;
    }
    float m_threshold;
};



class VoxelVectorBase {
public:
    virtual ~VoxelVectorBase() {}
    virtual int Count() const = 0;

    template < class T0, class T1 >
    static VoxelVectorBase * New( const T0 &t0, const T1 &t1);
        
};

template < class _V, class _C >
class VoxelVector : 
        public VoxelVectorBase,
        public ClassCompound< _V, _C >
{
    typedef ClassCompound< _V, _C > Compound;
public:    
    typedef _V Data;    
    typedef _C Counter;
    
    VoxelVector() {}
    
    template < class Other >
    VoxelVector(const Other &copy) : Compound(copy) {}
        
    using Compound::operator =;
            
    int Count() const { return this->A1().Count(this->A0()); }    
};


template < class T0, class T1 >
VoxelVectorBase *VoxelVectorBase::New(const T0 &t0, const T1 &t1)
{
    VoxelVector<T0,T1> *out = new VoxelVector<T0,T1>;
    //        ULIB_INTERFACE_ASSERT(VoxCountInterface,T1);
    out->A0() = t0;
    out->A1() = t1;
    return out;
}



} // Test





using namespace Test;

int main(int argc, char *argv[])
{
    BEGIN_TESTING(Class Compound Test2);     
    
    VoxelVector<Vector<Voxel>, Counter> v;
    std::cout << v.Count() << "\n";
    
    v.Data::push_back(Voxel());
    v.Data::back().Set(0.555);
    std::cout << v.Count() << " - value = " << v.Data::back().Get() << "\n";
    
    VoxelVector<Vector<Voxel>, CountOverTh> v2 = v;
    v2.Counter::m_threshold = 1;
    std::cout << v2.Count() << " - value = " << v2.Data::back().Get() << "\n";
    
    
    VoxelVector< Vector<VoxelMean>, CountOverTh> v3 = v2;
    v3.Data::push_back(VoxelMean());
    v3.Data::back().Set(0.555);
    std::cout << v3.Count() << " - value = " << v3.Data::back().Get() << "\n";
    
    VoxelVector< Vector<VoxelMean>, Counter> v4 = v3.SetComponent<1>(Counter());
    std::cout << v4.Count() << " - value = " << v4.Data::back().Get() << "\n";
    
    
    CountOverTh c;
    c.m_threshold = 0.6;
    VoxelVectorBase *v5 = VoxelVectorBase::New(v4.A0(),c);    
    std::cout << v5->Count() << "\n";
    delete v5;
    
    END_TESTING;
}

