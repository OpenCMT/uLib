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
#include "Core/MplSequenceCombiner.h"
#include "Core/ClassFactory.h"
#include "Core/Serializable.h"



#include "testing-prototype.h"

using namespace uLib;




















//namespace {
class Base {
public:
    Base() {}
    Base(const Base &copy) {}

    virtual void Go() {}
};

class Derived : public Base {
public:
    void Go() { std::cout << "Derived Go\n"; }
};

class Derived2 : public Base {
public:
    void Go() { std::cout << "Derived2 Go\n"; }
};

class Derived3 : public Base {
public:
    void Go() { std::cout << "Derived3 Go\n"; }
};

class Derived4 : public Base {
public:
    void Go() { std::cout << "Derived4 Go\n"; }
};


template <
        class A1,
        class A2
        >
class AlgHolder : public Base {
    A1 m_a1;
    A2 m_a2;
public:
    void Go() {
        std::cout << "AlgHolder Go: \n";
        std::cout << " A1 -> "; m_a1.Go();
        std::cout << " A2 -> "; m_a2.Go();
    }
};

//}





typedef mpl::vector< Derived, Derived2, Derived3, Derived4 > seq;


class ProgrammableAlgHolder {
public:
    ProgrammableAlgHolder() : m_id1(0), m_id2(0)
    { m_base = m_factory.Create(0,0); }

    template < typename T >
    void SetA1(const T *alg = NULL) {
        int id = m_factory.FindS1<T>();
        Base * newbase = m_factory.Create(id,m_id2);
        *newbase = *m_base;
        delete m_base;
        m_base = newbase;
    }

    template < typename T >
    void SetA2(const T *alg = NULL) {
        int id = m_factory.FindS2<T>();
        Base * newbase = m_factory.Create(m_id1,id);
        *newbase = *m_base;
        delete m_base;
        m_base = newbase;
    }

    Base * operator -> () { return m_base; }

private:
    RegisteredClassFactory2<Base, AlgHolder, seq, seq> m_factory;
    int    m_id1, m_id2;
    Base * m_base;
};



//int main() {
//    ProgrammableAlgHolder ah;
//    ah.SetA1<Derived4>();
//    ah->Go();

//    return 0;
//}




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
    int Count(const Vector<T> &ref ) {
        return ref.size();
    }
};

class VoxCountOver {
public:
    VoxCountOver() : m_threshold(0) {}

    template < class T >
    int Count(const Vector<T> &ref ) {
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
class VoxelVector : public VoxelVectorBase {
public:
    float Get(int id) const { return m_data[id].Get(); }
    void Set(int id, float data) {
        if(id >= Size()) m_data.resize(id+1);
        m_data[id].Set(data);
    }
    int Size() const { return m_data.size(); }
    int Count() const { return m_counter.Count(m_data); }
private:
    friend class VoxelVectorFactory;
    CounterType     m_counter;
    Vector<VoxType> m_data;
};




class VoxelVectorFactory {
public:
    VoxelVectorFactory() : m_id1(0), m_id2(0) { m_base = m_factory.Create(0,0); }
    VoxelVectorBase * operator -> () const { return m_base; }

    template < typename T >
    void SetVoxel() {
        int id = m_factory.FindS1<T>();
        VoxelVectorBase * newbase = m_factory.Create(id,m_id2);
        Test::copy(m_base,newbase); // *newbase = *m_base;
        delete m_base;
        m_base = newbase;
    }

    template < typename T >
    void SetCounter(const T &ref) {
        int id = m_factory.FindS2<T>();
        VoxelVectorBase * newbase = m_factory.Create(m_id1,id);
        Test::copy(m_base,newbase); // *newbase = *m_base;
        // ????? come copiare i membri ???? ////
        delete m_base;
        m_base = newbase;
    }


private:
    RegisteredClassFactory2< VoxelVectorBase, VoxelVector, mpl::vector<VoxelMean,VoxelVal>, mpl::vector<VoxCount,VoxCountOver> > m_factory;
    int m_id1, m_id2;
    VoxelVectorBase * m_base;
};
} // Test






int main() {
    Test::VoxelVectorFactory factory;

    for(int i=0; i<10; ++i)
        factory->Set(i,i);

    factory.SetVoxel<Test::VoxelVal>();

    for(int i=0; i<10; ++i)
        std::cout << factory->Get(i) << " ";
    std::cout << "\n";

    std::cout << "vox count = " << factory->Count() << "\n";




}














