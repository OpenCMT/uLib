#ifndef U_CORE_CLASSCOMPOUND_H
#define U_CORE_CLASSCOMPOUND_H


#include "boost/type_traits.hpp"

#include "Core/Mpl.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// COMPOUND DETAIL //

namespace uLib {
namespace detail {

template < class _Seq >
struct ClassCompound : ULIB_MPL_INHERIT_SEQ(_Seq) {
    typedef _Seq Seq;

    ClassCompound() {}

    template < class S >
    struct CopyOp {
        CopyOp(const S * src, ClassCompound * const dst) : m_src(src), m_dst(dst) {}

        template < class T, bool b >
        void copy(const T &t, const boost::integral_constant<bool,b>&) const {
        }

        template < class T >
        void copy(const T &t, const boost::true_type&) const {
            // this must be defined not throwing //
            static_cast<T &>(*m_dst) = t;
            // TODO: constness should removed to use swap ... (think!)
            //  std::swap(static_cast<T &>(*m_dst),t);
        }

        template < class A >
        void operator()(A) const {
            const A &t = *m_src;
            copy(t, boost::is_base_of<A,ClassCompound>());
        }

        ClassCompound * const m_dst;
        const S *m_src;
    };

    template < class Other >
    ClassCompound(const Other &copy) {
        typedef typename Other::Seq _seq;
        mpl::for_each<_seq>(CopyOp<Other>(&copy,this));
    }

    template < class Other >
    inline void copy ( const Other &copy ) throw () {
        typedef typename Other::Seq _seq;
        mpl::for_each<_seq>(CopyOp<Other>(&copy,this));
    }

    template < class Other >
    const ClassCompound & operator = (const Other &copy) {
        this->copy(copy);
        return *this;
    }

    template < int n, class A >
    ClassCompound< typename mpl::replace_el<Seq,A,n>::type >
    SetComponent(const A &alg) {
        typedef typename mpl::replace_el<Seq,A,n>::type _seq;
        ClassCompound< _seq > out = *this;
        static_cast< A& >(out) = alg;
        return out;
    }
};
} // detail




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// COMPOUND SPECIALIZATIONS //

struct Null {};
template < class T0 = Null,
           class T1 = Null,
           class T2 = Null,
           class T3 = Null,
           class T4 = Null,
           class T5 = Null >
class ClassCompound  : detail::ClassCompound< mpl::vector<> > {
public:
    typedef detail::ClassCompound< mpl::vector<> > BaseClass;

    T0& A0();
    T1& A1();
    T2& A2();
    T3& A3();
    T4& A4();
    T5& A5();    


    using BaseClass::operator =;


private:
    // NOT ACCESSIBLE because never reached //

    ClassCompound() {}

    template < class Other >
    ClassCompound(const Other &t) : BaseClass(t) {}
};



template < class _A0 >
struct ClassCompound<_A0> : detail::ClassCompound< mpl::vector<_A0> > {

    typedef detail::ClassCompound< mpl::vector<_A0> > BaseClass;
    _A0& A0() { return (_A0&)*this; }
    const _A0& A0() const { return (const _A0&)*this; }

    ClassCompound() {}

    template < class Other >
    ClassCompound(const Other &t) : BaseClass(t) {}

    using BaseClass::operator =;
};

template < class _A0,
           class _A1 >
struct ClassCompound<_A0,_A1> : detail::ClassCompound< mpl::vector<_A0,_A1> > {
    typedef detail::ClassCompound< mpl::vector<_A0,_A1> > BaseClass;
    _A0& A0() { return (_A0&)*this; }
    _A1& A1() { return (_A1&)*this; }
    const _A0& A0() const { return (const _A0&)*this; }
    const _A1& A1() const { return (const _A1&)*this; }

    ClassCompound() {}    

    template < class Other >
    ClassCompound(const Other &t) : BaseClass(t) {}

    using BaseClass::operator =;
    using BaseClass::SetComponent;
};

template < class _A0,
           class _A1,
           class _A2 >
struct ClassCompound<_A0,_A1,_A2> : detail::ClassCompound< mpl::vector<_A0,_A1,_A2> > {

    typedef detail::ClassCompound< mpl::vector<_A0,_A1,_A2> > BaseClass;
    _A0& A0() { return (_A0&)*this; }
    _A1& A1() { return (_A1&)*this; }
    _A2& A2() { return (_A2&)*this; }
    const _A0& A0() const { return (const _A0&)*this; }
    const _A1& A1() const { return (const _A1&)*this; }
    const _A2& A2() const { return (const _A2&)*this; }


    ClassCompound() {}

    template < class Other >
    ClassCompound(const Other &t) : BaseClass(t) {}

    using BaseClass::operator =;
};

template < class _A0,
           class _A1,
           class _A2,
           class _A3 >
struct ClassCompound<_A0,_A1,_A2,_A3> : detail::ClassCompound< mpl::vector<_A0,_A1,_A2,_A3> > {

    typedef detail::ClassCompound< mpl::vector<_A0,_A1,_A2,_A3> > BaseClass;
    _A0& A0() { return (_A0&)*this; }
    _A1& A1() { return (_A1&)*this; }
    _A2& A2() { return (_A2&)*this; }
    _A3& A3() { return (_A3&)*this; }
    const _A0& A0() const { return (const _A0&)*this; }
    const _A1& A1() const { return (const _A1&)*this; }
    const _A2& A2() const { return (const _A2&)*this; }
    const _A3& A3() const { return (const _A3&)*this; }

    ClassCompound() {}

    template < class Other >
    ClassCompound(const Other &t) : BaseClass(t) {}

    using BaseClass::operator =;
};

template < class _A0,
           class _A1,
           class _A2,
           class _A3,
           class _A4 >
struct ClassCompound<_A0,_A1,_A2,_A3,_A4> : detail::ClassCompound< mpl::vector<_A0,_A1,_A2,_A3,_A4> > {

    typedef detail::ClassCompound< mpl::vector<_A0,_A1,_A2,_A3,_A4> > BaseClass;
    _A0& A0() { return (_A0&)*this; }
    _A1& A1() { return (_A1&)*this; }
    _A2& A2() { return (_A2&)*this; }
    _A3& A3() { return (_A3&)*this; }
    _A4& A4() { return (_A4&)*this; }
    const _A0& A0() const { return (const _A0&)*this; }
    const _A1& A1() const { return (const _A1&)*this; }
    const _A2& A2() const { return (const _A2&)*this; }
    const _A3& A3() const { return (const _A3&)*this; }
    const _A4& A4() const { return (const _A4&)*this; }

    ClassCompound() {}

    template < class Other >
    ClassCompound(const Other &t) : BaseClass(t) {}

    using BaseClass::operator =;
};

} // uLib



#endif // CLASSCOMPOUND_H
