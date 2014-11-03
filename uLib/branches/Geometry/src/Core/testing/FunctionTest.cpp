
#include <iostream>
#include <typeinfo>
#include <functional>

#include "testing-prototype.h"
#include "Core/Types.h"

#include <Core/Vector.h>
#include <Core/ProgrammableAccessor.h>

namespace uLib {

class TestVoxel {
public:
    float m_data;
    float Get() { return m_data; }
    float ConstGet() const { return m_data; }
    float & GetRef() { return m_data; }
    const float & ConstGetRef() const { return m_data; }
};



} // uLib

using namespace uLib;

int main() {
    BEGIN_TESTING(Function Test);


    Vector<TestVoxel> v;
    v.push_back(TestVoxel());
    v.push_back(TestVoxel());
    v.push_back(TestVoxel());
    v.push_back(TestVoxel());
    v.push_back(TestVoxel());
    v.push_back(TestVoxel());
    v.push_back(TestVoxel());


    v[5].m_data = 5552368.0;

    ProgrammableAccessor<float> f1(&TestVoxel::m_data);
    ProgrammableAccessor<float> f2(&TestVoxel::GetRef);

    int i=0;
    foreach (TestVoxel &el,v) {
        f1.Set(&el,i++);
        std::cout << " -> " << f2.Get<double>(&el) << "\n";
    }


    END_TESTING;
}

