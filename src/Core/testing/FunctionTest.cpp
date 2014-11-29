
#include <iostream>
#include <typeinfo>
#include <functional>

#include "testing-prototype.h"
#include "Core/Types.h"

#include <Core/Vector.h>
#include <Core/ProgrammableAccessor.h>

#include <iterator>

namespace uLib {

class TestVoxel {
public:
    float m_data;
    float Get() { return m_data; }
    float ConstGet() const { return m_data; }
    float & GetRef() { return m_data; }
    const float & ConstGetRef() const { return m_data; }
};



//template<typename _T>
//class PointerIterator :
//    public std::iterator<std::random_access_iterator_tag, _T>
//{
//protected:
//    _T* m_pData;
//public:
//    typedef std::random_access_iterator_tag iterator_category;
//    typedef typename std::iterator<std::random_access_iterator_tag, _T>::value_type      value_type;
//    typedef typename std::iterator<std::random_access_iterator_tag, _T>::difference_type difference_type;
//    typedef typename std::iterator<std::random_access_iterator_tag, _T>::reference       reference;
//    typedef typename std::iterator<std::random_access_iterator_tag, _T>::pointer         pointer;

//    PointerIterator() : m_pData(NULL) {}

//    template<typename T2>
//    PointerIterator(const PointerIterator<T2>& r) : m_pData(&(*r)) {}

//    PointerIterator(pointer pData) : m_pData(pData) {}

//    template<typename T2>
//    PointerIterator& operator=(const PointerIterator<T2>& r)
//        { m_pData = &(*r); return *this; }

//    PointerIterator& operator++()  // PREFIX
//        { ++m_pData; return *this; }
//    PointerIterator& operator--()  // PREFIX
//        { --m_pData; return *this; }
//    PointerIterator operator++(int)  // POSTFIX
//        { return PointerIterator(m_pData++); }
//    PointerIterator operator--(int)  // POSTFIX
//        { return PointerIterator(m_pData--); }
//    PointerIterator operator+(const difference_type& n) const
//        { return PointerIterator(m_pData + n); }
//    PointerIterator& operator+=(const difference_type& n)
//        { m_pData += n; return *this; }
//    PointerIterator operator-(const difference_type& n) const
//        { return PointerIterator(pointer(m_pData - n)); }
//    PointerIterator& operator-=(const difference_type& n) { m_pData -= n; return *this; }
//    reference operator*() const { return *m_pData; }
//    pointer operator->() const { return m_pData; }
//    reference operator[](const difference_type& n) const { return m_pData[n]; }
//};



//class DataSetView {

//    template <typename T>
//    T Get(Id_t id) { return m_view.Get<T>(this->GetPointData(id)); }



//private:
//    ProgrammableAccessorAny m_view;
//};


} // uLib

namespace uLib {

namespace detail {
} // detail



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

    ProgrammableAccessor<int> f1(&TestVoxel::m_data);
    ProgrammableAccessor<char> f2(&TestVoxel::ConstGet);
    ProgrammableAccessorAny f3(&TestVoxel::m_data);
    ProgrammableAccessor<detail::any_c> f4(&TestVoxel::m_data);



    int i=0;
    foreach (TestVoxel &el,v) {
        f1.Set(&el,i++);
        std::cout << " -> " << f2.Get(&el) << " - " << f3.Get<float>(&el) << f4.Get<int>(&el) << f1(&el).Get<float>() << "\n";

    }


    END_TESTING;
}

