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




class VoxCountInterface {

//    int (* p_Count)(void * const);
//    template <class T> static int S_Count(void * const ob) { return static_cast<T*>(ob)->Count(); }

    void * const m_ob;
public:
    template < class T >
    VoxCountInterface( T &t ) :
        m_ob(&t)/*,
        p_Count(&S_Count<T>)*/
    {}

//    int Count() const { return (*p_Count)(m_ob); }
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




template < class Container,
           class CounterType >
class VoxelVector :
        public VoxelVectorBase,
        public ClassCompound< Container, CounterType>
{
    typedef ClassCompound< Container, CounterType> Compound;

public:

    VoxelVector() {}

    template < class Other >
    VoxelVector(const Other &copy) : Compound(copy) {}

    float Get(int id) const { return this->at(id).Get(); }

    void Set(int id, float data) {
        if(id >= Size()) this->resize(id+1);
        this->at(id).Set(data);
    }

    int Size() const { return this->size(); }

    int Count() const {
        return CounterType::Count( this->A0() );
    }
private:
//    friend class VoxelVectorFactory;
};



template < class ContainerInterface,
           class CounterInterface >
class VoxelVectorFactory
{
public:

    template < class T0, class T1 >
    static VoxelVector<T0,T1> * create( const T0 &t0, const T1 &t1) {
        VoxelVector<T0,T1> *out = new VoxelVector<T0,T1>;

        ULIB_INTERFACE_ASSERT(VoxCountInterface,T1);

        out->A0() = t0;
        out->A1() = t1;
        return out;
    }

//    template < class H0, class A, int n >
//    static void Set(const H0 &hold, const A &alg) {

//    }



//    template < class A, int n >
//    typename mpl::replace_el<Seq,A,n>::type
//    SetComponent(const A &alg) {
//        typedef typename mpl::replace_el<Seq,A,n>::type _seq;

//        result_type out = *this;
//        static_cast< A& >(out) = alg;
//        return out;
//    }



};





} // Test


using namespace Test;



int main() {



    VoxelVector< Vector<VoxelMean>, VoxCountOver > img;
    img.Set(0,555);
    img.Set(1,23);
    img.Set(1,25);
    img.Set(2,68);

    {
        // these are equivalent access methods //
        img.A1().m_threshold = 50;

        img.VoxCountOver::m_threshold = 50;

        VoxCountOver counter;
        counter.m_threshold = 50;
        img.A1() = counter;
        // ----------------------------------- //
    }

    std::cout << "-> ";
    for(int i=0; i<3; ++i) {
        std::cout << img.Get(i) << " ";
    }
    std::cout << " count threshold: " << img.A1().m_threshold << " ";
    std::cout << " count: " << img.Count() << "\n";



    VoxelVector< Vector<VoxelVal>, VoxCountOver > img2;
    img2 = img;

    // voxel is changed so objects must be copied //
    foreach (VoxelMean &el, img) {
        VoxelVal v; v.Set(el.Get());
        img2.push_back(v);
    }


    // manual copy of content //
    img2.Set(1,0);
    std::cout << "-> ";
    for(int i=0; i<3; ++i) {
        std::cout << img2.Get(i) << " ";
    }
    std::cout << " count threshold: " << img2.A1().m_threshold << " ";
    std::cout << " count: " << img2.Count() << "\n";


    VoxelVector< Vector<VoxelVal>, VoxCount > img3 = img2;

    std::cout << "-> ";
    for(int i=0; i<3; ++i) {
        std::cout << img3.Get(i) << " ";
    }
    std::cout << " count: " << img3.Count() << "\n";

    VoxelVector< Vector<VoxelVal>, VoxCount > img4;
    img4 = img3.SetComponent<1>(VoxCountOver());

    std::cout << "-> ";
    for(int i=0; i<3; ++i) {
        std::cout << img4.Get(i) << " ";
    }
    std::cout << " count: " << img4.Count() << "\n";

    {
        // Voxel Vector Factory //

        VoxelVectorFactory< Vector<VoxelVal>, VoxCount > factory;

        Vector<VoxelVal> vector;
        VoxCount counter;
        VoxelVectorBase * base = factory.create(vector,counter);

        base->Set(0,123);
        base->Set(1,234);
        base->Set(2,345);
        std::cout << "-> ";
        for(int i=0; i<3; ++i) {
            std::cout << base->Get(i) << " ";
        }
        std::cout << " count: " << base->Count() << "\n";
    }





}















