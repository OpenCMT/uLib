#ifndef CLASSCOMPOSITE_H
#define CLASSCOMPOSITE_H

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#include <boost/mpl/zip_view.hpp>

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/at.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/mpl/same_as.hpp>

#include <Core/Types.h>
#include <Core/Mpl.h>

namespace uLib {
namespace detail {


template < typename _Seq >
struct ClassComposite {
    typedef _Seq Seq;
    
    ////////////////////////////////////////////////////////////////////////////////
    //  TUPLE  /////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    
    
    template<class T, class Tuple>
    struct tuple_push_front;
    
    template<class T, BOOST_PP_ENUM_PARAMS(10, class T)>
    struct tuple_push_front<T, boost::tuple<BOOST_PP_ENUM_PARAMS(10, T)> > {
        typedef boost::tuple<T, BOOST_PP_ENUM_PARAMS(9, T)> type;
    };
    
    // TUPLE //
    typedef typename boost::mpl::reverse_copy< Seq,
                                               boost::mpl::inserter<boost::tuple<>,
                                               tuple_push_front<boost::mpl::_2, boost::mpl::_1> >
                                             >::type 
    Tuple;
        
    
    ////////////////////////////////////////////////////////////////////////////////
    //  COPY  //////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////    
    
    // Copy operator structure //
    template < typename Other >
    struct CopyOp {
        const Other &m_other;
        ClassComposite * const m_this;
        
        CopyOp(const Other &other, ClassComposite * const src) : m_other(other), m_this(src) {}
                
        template < typename U >
        void operator () (U) const {            
            static const int id = mpl::at< U, mpl::int_<2> >::type::value;            
            boost::tuples::get<id>(m_this->m_tuple) = boost::tuples::get<id>(m_other.m_tuple);                        
        }                
    };
                        
    template < class Other >
    inline void copy ( const Other &copy ) throw () { 
        // sequence of type pairs
        typedef typename mpl::zip_view< mpl::vector<Seq, typename Other::Seq> >::type zip; 
        
        // adds position to each element
        typedef typename mpl::range_c<int, 0, mpl::size<zip>::value >::type range;         
        typedef typename mpl::zip_view< mpl::vector<Seq, typename Other::Seq, range> >::type zip_range; 
        
        // filter only elements that match
        typedef typename mpl::filter_view< zip_range, 
                                           boost::is_same< mpl::at< mpl::_ , mpl::int_<0> >, 
                                                           mpl::at< mpl::_ , mpl::int_<1> > 
                                                         >
                                         >::type filtered_zip;         
        // apply copy
        mpl::for_each<filtered_zip>(CopyOp<Other>(copy,this));
    }
        
    
    ClassComposite() {}
    
    template < class Other >
    ClassComposite(const Other &copy) {
        this->copy(copy);
    }

    template < class Other >
    const ClassComposite & operator = (const Other &copy) {
        this->copy(copy);
        return *this;
    }

    template < int n, class A >
    ClassComposite< typename mpl::replace_el<Seq,A,n>::type >
    SetComponent(const A &alg) {
        typedef typename mpl::replace_el<Seq,A,n>::type _seq;
        ClassComposite< _seq > out = *this;
        boost::tuples::get<n>(out) = alg;
        return out;
    }        
    
    
    Tuple m_tuple;
};



} // detail


struct Null {};
template < typename T0 = Null,
           typename T1 = Null,
           typename T2 = Null,
           typename T3 = Null,
           typename T4 = Null,
           typename T5 = Null >
class ClassComposite  : detail::ClassComposite< mpl::vector<> > {
public:
    typedef detail::ClassComposite< mpl::vector<> > BaseClass;

    T0& A0();
    T1& A1();
    T2& A2();
    T3& A3();
    T4& A4();
    T5& A5();    

    using BaseClass::operator =;
    using BaseClass::SetComponent;
    
private:
    // NOT ACCESSIBLE because never reached //
    ClassComposite() {}

    template < class Other >
    ClassComposite(const Other &t) : BaseClass(t) {}
};




template < typename _A0 >
class ClassComposite<_A0> : public detail::ClassComposite< mpl::vector<_A0> >
{
    typedef detail::ClassComposite< mpl::vector<_A0> > BaseClass;
public:
    ClassComposite() {}
    
    ClassComposite(const _A0 &a0) :
        BaseClass::m_tuple(a0) 
    {}
    
    template < typename Other >
    ClassComposite(const Other &copy) : BaseClass(copy) {}
    
    _A0& A0() { return boost::tuples::get<0>(this->m_tuple); }
    const _A0& A0() const { return boost::tuples::get<0>(this->m_tuple); }
    
    using BaseClass::operator =;
    using BaseClass::SetComponent;
};




template < typename _A0, typename _A1 >
class ClassComposite<_A0,_A1> : public detail::ClassComposite< mpl::vector<_A0,_A1> >
{
    typedef detail::ClassComposite< mpl::vector<_A0,_A1> > BaseClass;
public:
    ClassComposite() {}
    
    ClassComposite(const _A0 &a0, const _A1 &a1) :
        BaseClass::m_tuple(a0,a1) 
    {}
    
    template < typename Other >
    ClassComposite(const Other &copy) : BaseClass(copy) {}
    
    _A0& A0() { return boost::tuples::get<0>(this->m_tuple); }
    _A1& A1() { return boost::tuples::get<1>(this->m_tuple); }
    const _A0& A0() const { return boost::tuples::get<0>(this->m_tuple); }
    const _A1& A1() const { return boost::tuples::get<1>(this->m_tuple); }
    
    using BaseClass::operator =;
    using BaseClass::SetComponent;
};




template < typename _A0, typename _A1, typename _A2 >
class ClassComposite<_A0,_A1,_A2> : public detail::ClassComposite< mpl::vector<_A0,_A1,_A2> >
{
    typedef detail::ClassComposite< mpl::vector<_A0,_A1,_A2> > BaseClass;
public:
    ClassComposite() {}
    
    ClassComposite(const _A0 &a0, const _A1 &a1, const _A2 &a2) :
        BaseClass::m_tuple(a0,a1,a2) 
    {}
    
    template < typename Other >
    ClassComposite(const Other &copy) : BaseClass(copy) {}
    
    _A0& A0() { return boost::tuples::get<0>(this->m_tuple); }
    _A1& A1() { return boost::tuples::get<1>(this->m_tuple); }
    _A2& A2() { return boost::tuples::get<2>(this->m_tuple); }
    const _A0& A0() const { return boost::tuples::get<0>(this->m_tuple); }
    const _A1& A1() const { return boost::tuples::get<1>(this->m_tuple); }
    const _A2& A2() const { return boost::tuples::get<2>(this->m_tuple); }
    
    using BaseClass::operator =;
    using BaseClass::SetComponent;
};

// TODO: add more Ax ...


} // uLib



#endif // CLASSCOMPOSITE_H

