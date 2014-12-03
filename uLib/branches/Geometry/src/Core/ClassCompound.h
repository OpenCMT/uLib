#ifndef U_CORE_CLASSCOMPOUND_H
#define U_CORE_CLASSCOMPOUND_H


#include "boost/type_traits.hpp"

#include "Core/Mpl.h"


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
            static_cast<T &>(*m_dst) = t;
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
    ClassCompound(const Other &t) {
        typedef typename Other::Seq _seq;
        mpl::for_each<_seq>(CopyOp<Other>(&t,this));
    }

    template < class Other >
    const ClassCompound & operator = (const Other &t) {
        typedef typename Other::Seq _seq;
        mpl::for_each<_seq>(CopyOp<Other>(&t,this));
        return *this;
    }

};


} // detail



struct Null {};
template < class T0 = Null,
           class T1 = Null,
           class T2 = Null,
           class T3 = Null,
           class T4 = Null,
           class T5 = Null >
struct ClassCompound {
    typedef T0 A0;
    typedef T1 A1;
    typedef T2 A2;
    typedef T3 A3;
    typedef T4 A4;
    typedef T5 A5;

    //NEVER REACHED //
};

template < class _A0 >
struct ClassCompound<_A0> : detail::ClassCompound< mpl::vector<_A0> > {

    typedef detail::ClassCompound< mpl::vector<_A0> > BaseClass;
    typedef _A0 A1;

    ClassCompound() {}

    template < class Other >
    ClassCompound(const Other &t) : BaseClass(t) {}

    using BaseClass::operator =;
};

template < class _A0,
           class _A1 >
struct ClassCompound<_A0,_A1> : detail::ClassCompound< mpl::vector<_A0,_A1> > {
    typedef detail::ClassCompound< mpl::vector<_A0,_A1> > BaseClass;
    typedef _A0 A0;
    typedef _A1 A1;

    ClassCompound() {}

    template < class Other >
    ClassCompound(const Other &t) : BaseClass(t) {}

    using BaseClass::operator =;
};

template < class _A0,
           class _A1,
           class _A2 >
struct ClassCompound<_A0,_A1,_A2> : detail::ClassCompound< mpl::vector<_A0,_A1,_A2> > {

    typedef detail::ClassCompound< mpl::vector<_A0,_A1,_A2> > BaseClass;
    typedef _A0 A0;
    typedef _A1 A1;
    typedef _A2 A2;


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
    typedef _A0 A0;
    typedef _A1 A1;
    typedef _A2 A2;
    typedef _A3 A3;

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
    typedef _A0 A0;
    typedef _A1 A1;
    typedef _A2 A2;
    typedef _A3 A3;
    typedef _A4 A4;

    ClassCompound() {}

    template < class Other >
    ClassCompound(const Other &t) : BaseClass(t) {}

    using BaseClass::operator =;
};

} // uLib



#endif // CLASSCOMPOUND_H
