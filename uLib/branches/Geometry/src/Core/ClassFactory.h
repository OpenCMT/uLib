#ifndef U_CORE_CLASSFACTORY_H
#define U_CORE_CLASSFACTORY_H


#include <map>
#include <vector>

#include <boost/mpl/unpack_args.hpp>

#include "Core/Mpl.h"
#include "Core/MplSequenceCombiner.h"
#include "Core/Types.h"


namespace uLib {


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// generator //

template <class T>
static void * newClass() { return new T; }

template <class T>
static void * newClass2(void *a1,void *a2) { return new T(a1,a2); }



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Run time named class factory //

template <class BaseType>
class NamedClassFactory {
    typedef void * (*_newClassfn)();
    typedef std::map<const char*,_newClassfn> MapType;

public:
    template<typename Type>
    void AddType(const char* name) {
        m_map.insert(std::make_pair(name, &newClass<Type>));
    }

    BaseType *Create(const char *type) {
        typename MapType::iterator itr = m_map.find(type);
        return static_cast<BaseType*>(itr->second());
    }

    void List(std::ostream &o) {
        for(typename MapType::iterator itr = m_map.begin(); itr!=m_map.end(); itr++ )
            o << itr->first << "\n";
    }

private:
    MapType m_map;
};




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// MPL sequence registered class factory //


template <class BaseType, typename RegSeqT>
class RegisteredClassFactory {
    typedef void *(*_newClassfn)();
    typedef std::vector<_newClassfn> TypeVectorType;

    struct AddTypeOp {
        AddTypeOp( RegisteredClassFactory *_p) : m_parent(_p) {}
        template <typename U> void operator ()(U x) {
            m_parent->addType<U>();
        }
        RegisteredClassFactory *m_parent;
    };

    template < typename T >
    void addType() { m_map.push_back(&newClass<T>); }

public:

    RegisteredClassFactory() {
        mpl::for_each<RegSeqT>(AddTypeOp(this));
    }

    template < typename T >
    int Find() {
        typedef typename mpl::find<RegSeqT,T>::type iter;
        return iter::pos::value;
    }

    template < typename T >
    BaseType *Create() {
        int id = Find<T>();
        typename TypeVectorType::iterator itr = m_map.begin() + id;
        return (BaseType *)(*itr)();
    }

private:
    TypeVectorType m_map;
};



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <
        class BaseType,
        template <class T1> class DerivedType,
        typename S1
        >
class RegisteredClassFactory1 {
    typedef void*(*_newClassfn)();
    typedef std::vector<_newClassfn> TypeVectorType;

    template < typename U >
    void addType() { m_map.push_back(&newClass<
//                                               BaseType,
                                               DerivedType<U>
                                              >); }

    struct AddTypeSeqOp {
        AddTypeSeqOp( RegisteredClassFactory1 *_p) : m_parent(_p) {}
        template < typename Seq >
        void operator()(Seq) {
            m_parent->addType<
                    typename mpl::at<Seq, mpl::int_<0> >::type
                    > ();
        }
        RegisteredClassFactory1 *m_parent;
    };

    typedef mpl::combine_view< mpl::vector<S1> > AlgView;
public:

    RegisteredClassFactory1() {
        mpl::for_each< AlgView >(AddTypeSeqOp(this));
    }

    template < typename T >
    static inline int FindS1() {
        typedef typename mpl::find<S1,T>::type iter;
        return iter::pos::value;
    }

    BaseType *Create(int id1) {
        typename TypeVectorType::iterator itr = m_map.begin() + id1;
        return (BaseType *)(*itr)();
    }

private:
    TypeVectorType m_map;
    static const int m_size1 = mpl::size<S1>::type::value;
};




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template <
        class BaseType,
        template <class T1, class T2> class DerivedType,
        typename S1,
        typename S2
        >
class RegisteredClassFactory2 {
    typedef void*(*_newClassfn)();
    typedef std::vector<_newClassfn> TypeVectorType;

    template < typename U, typename V >
    void addType() { m_map.push_back(&newClass<
//                                               BaseType,
                                               DerivedType<U,V>
                                              >); }

    struct AddTypeSeqOp {
        AddTypeSeqOp( RegisteredClassFactory2 *_p) : m_parent(_p) {}
        template < typename Seq >
        void operator()(Seq) {
            m_parent->addType<
                    typename mpl::at<Seq, mpl::int_<0> >::type,
                    typename mpl::at<Seq, mpl::int_<1> >::type
                    > ();
        }
        RegisteredClassFactory2 *m_parent;
    };

    typedef mpl::combine_view< mpl::vector<S1,S2> > AlgView;

//    template < typename _T, class _Seq >
//    static inline int find() {
//        typedef typename mpl::find<_Seq,_T>::type iter;
//        return iter::pos::value;
//    }

public:

    RegisteredClassFactory2() {
        mpl::for_each< AlgView >(AddTypeSeqOp(this));
    }


    template < typename T >
    static inline int FindS1() {
        typedef typename mpl::find<S1,T>::type iter;
        return iter::pos::value;
    }

    template < typename T >
    static inline int FindS2() {
        typedef typename mpl::find<S2,T>::type iter;
        return iter::pos::value;
    }


    BaseType * Create(int id1, int id2) {
        typename TypeVectorType::iterator itr = m_map.begin() + id1 + m_size1 * id2;
        return (BaseType *)(*itr)();
    }

private:
    TypeVectorType m_map;
    static const int m_size1 = mpl::size<S1>::type::value;
    static const int m_size2 = mpl::size<S2>::type::value;
};




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



template <
        class BaseType,
        template <class T1, class T2, class T3> class DerivedType,
        typename S1,
        typename S2,
        typename S3
        >
class RegisteredClassFactory3 {
    typedef void*(*_newClassfn)();
    typedef std::vector<_newClassfn> TypeVectorType;

    template < typename T1, typename T2, typename T3 >
    void addType() { m_map.push_back(&newClass<
//                                               BaseType,
                                               DerivedType<T1,T2,T3>
                                              >); }

    struct AddTypeSeqOp {
        AddTypeSeqOp( RegisteredClassFactory3 *_p) : m_parent(_p) {}
        template < typename Seq >
        void operator()(Seq) {
            m_parent->addType<
                    typename mpl::at<Seq, mpl::int_<0> >::type,
                    typename mpl::at<Seq, mpl::int_<1> >::type,
                    typename mpl::at<Seq, mpl::int_<2> >::type
                    > ();
        }
        RegisteredClassFactory3 *m_parent;
    };

    typedef mpl::combine_view< mpl::vector<S1,S2,S3> > AlgView;
public:

    RegisteredClassFactory3() {
        mpl::for_each< AlgView >(AddTypeSeqOp(this));
    }

    template < typename T >
    static inline int FindS1() {
        typedef typename mpl::find<S1,T>::type iter;
        return iter::pos::value;
    }

    template < typename T >
    static inline int FindS2() {
        typedef typename mpl::find<S2,T>::type iter;
        return iter::pos::value;
    }

    template < typename T >
    static inline int FindS3() {
        typedef typename mpl::find<S3,T>::type iter;
        return iter::pos::value;
    }


    BaseType *Create(int id1, int id2, int id3) {
        typename TypeVectorType::iterator itr = m_map.begin() + id1 + m_size1 * id2 + m_size1 * m_size3 * id3;
        return (BaseType *)(*itr)();
    }

private:
    TypeVectorType m_map;
    static const int m_size1 = mpl::size<S1>::type::value;
    static const int m_size2 = mpl::size<S2>::type::value;
    static const int m_size3 = mpl::size<S3>::type::value;
};











////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


} // uLib




#endif // CLASSFACTORY_H
