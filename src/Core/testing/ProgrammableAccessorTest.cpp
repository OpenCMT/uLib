
#include <iostream>
#include <typeinfo>
#include <functional>

#include "testing-prototype.h"
#include "Core/Types.h"

#include <Core/Vector.h>
#include <Core/ProgrammableAccessor.h>

#include <iterator>

namespace Test {

class TestVoxel {
public:
    float m_data;
    float Get() { return m_data; }
    float ConstGet() const { return m_data; }
    float & GetRef() { return m_data; }
    const float & ConstGetRef() const { return m_data; }
};


class Vox {
public:
    float value;
    int count;
    TestVoxel v;
};


struct StaticVoxAcc {
    static float Get(const Vox *v)  {
        return v->value;
    }
    static void Set(Vox *v, float data) {
        v->value = data;
    }
};

struct StaticVoxAccRef {
    static float Get(const Vox &v) {
        return v.value;
    }
    static void Set(Vox &v, float data) {
        v.value = data;
    }
};

} // Test


namespace uLib {



} // uLib



using namespace uLib;

template < typename T >
void print_is_iter(const T &t, typename boost::disable_if< detail::is_iterator<T> >::type *dummy = 0  ) {
    std::cout << "no";
}

template < typename T >
void print_is_iter(const T &t, typename boost::enable_if< detail::is_iterator<T> >::type *dummy = 0 ) {
    std::cout << "yes";
}




int main() {
    BEGIN_TESTING(Function Test);

    using Test::TestVoxel;
    using Test::Vox;

    { // TEST 1
        Vector<TestVoxel> v;
        v.push_back(TestVoxel());
        v.push_back(TestVoxel());
        v.push_back(TestVoxel());
        v.push_back(TestVoxel());
        v.push_back(TestVoxel());
        v.push_back(TestVoxel());
        v.push_back(TestVoxel());


        v[5].m_data = 5552368.0;

        ProgrammableAccessor<int> f1(&TestVoxel::m_data);
        ProgrammableAccessor<char> f2(&TestVoxel::ConstGet);

        int i=0;
        if(0)
            foreach (TestVoxel &el,v) {
                f1.Set(&el,i++);
                std::cout << " -> " << f2.Get(&el) /*<< " - " << f1(&el).Get()*/ << "\n";

            }

        TEST1(f1.Get(&v[5]) == 5552368);
    }


    { // TEST accessing internal object //
        Vox v1,v2;
        v1.v.m_data = 111;
        v2.v.m_data = 222;

        ProgrammableAccessor<TestVoxel> va("test voxel");
        va.SetAccessFunctions(&Vox::v);
        va.Set(&v2,v1.v);
        //        TEST1(v2.v == v1.v);
    }

    { // TEST Static access
        using Test::Vox;
        using Test::StaticVoxAcc;
        using Test::StaticVoxAccRef;

        ProgrammableAccessor<float> va1("static ptr");
        va1.SetAccessFunctions(&StaticVoxAcc::Get, &StaticVoxAcc::Set);

        ProgrammableAccessor<float> va2("static ref");
        va2.SetAccessFunctions(&StaticVoxAcc::Get, &StaticVoxAcc::Set);

        Vox v;
        v.value = 111;
        TEST1 ( va1.Get(v) == 111 );
        TEST1 ( va2.Get(v) == 111 );

        std::cout << va1.Get(v) << "\n";
        std::cout << va2.Get(v) << "\n";

        TEST1 ( va1.Get(&v) == 111 );
        TEST1 ( va2.Get(&v) == 111 );

        std::cout << va1.Get(&v) << "\n";
        std::cout << va2.Get(&v) << "\n";
    }

    {
        Vector<Vox>::Iterator it;
        Vox v;
        std::cout << "is iter? ";
        print_is_iter(it);
        std::cout << " is iter? ";
        print_is_iter(v);
        std::cout << "\n";
    }


    { // TEST Iterators
        Vector<Vox> vc;
        vc.push_back(Vox());
        vc.push_back(Vox());
        vc.push_back(Vox());
        vc.push_back(Vox());
        vc.push_back(Vox());

        ProgrammableAccessor<float> acc("scalar");
        acc.SetAccessFunctions(&Vox::value);

        int count = 0;
        for( Vector<Vox>::Iterator it = vc.begin(); it < vc.end(); it++ ) {
            acc.Set(it,count++);
            std::cout << " -> " << acc.Get(it) << "\n";
        }
    }



    END_TESTING;
}

