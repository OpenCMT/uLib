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



#ifndef U_CORE_TYPES_H
#define U_CORE_TYPES_H

#include <iostream>
#include <typeinfo>

#include <boost/preprocessor.hpp>

//#include <ltk/ltktypes.h>

#include "Core/Macros.h"
#include "Core/Mpl.h"







namespace uLib {


////////////////////////////////////////////////////////////////////////////////

namespace detail {

struct TypeIntrospection {

    // BOOST IMPL  //
    BOOST_MPL_HAS_XXX_TRAIT_DEF(type_info)

    // SFINAE IMPL //
    /*
    template <typename T>
    struct has_type_info {
        typedef char yes[1];
        typedef char no[2];
        template <typename U> static yes& test(typename U::type_info::BaseList*);
        template <typename   > static no&  test(...);
        //        struct apply {
        static const bool value = sizeof(test<T>(0)) == sizeof(yes);
        typedef boost::mpl::bool_<value> type;
        //        };
    };
    */

    /** IsA Introspectable Object Implementation Template */
    template <class T>
    struct IsIntrospectable : has_type_info<T> {};

    template <typename T> struct access {
        typedef typename T::type_info type_info;
    };

    template <typename T>
    struct child_first_impl {

        template <class T1, bool cond>
        struct lambda_CFList_f {
            typedef mpl::vector<T1> type;
        };

        template <class T1>
        struct lambda_CFList_f<T1,true> {
            //            typedef typename T1::type_info::CFList type;
            typedef typename access<T1>::type_info::CFList type;
        };

        template <class T1>
        struct lambda_CFList : lambda_CFList_f<T1, has_type_info<T1>::value> {};

        /** Transforms all Base Type into proper CFList */
        typedef typename mpl::transform_view < typename access<T>::type_info::BaseList
                                             , lambda_CFList<mpl::_>
                                             >::type CFListSeq;

        /** Folds each CFList into a new sequence */
        typedef typename mpl::fold< CFListSeq
                                  , mpl::vector<>
                                  , mpl::copy< mpl::_1
                                             , mpl::back_inserter<mpl::_2>
                                             >
                                  >::type Childs;

        /** Add This Class to final CFList sequence */
        typedef typename mpl::copy< Childs
                                  , mpl::back_inserter< mpl::vector<T> >
                                  >::type type;
    };


    /**
     * Tests if T has a member called type_info then compile type CFList
     */
    template <typename T>
    struct child_first : mpl::if_< has_type_info<T>
                                 , child_first_impl<T>
                                 , mpl::vector<>
                                 >::type {};


};



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// TYPE ADAPTERS // FINIRE !!!

//#define _REPETITION_V(vz,vn,vdata)


//template < class TypeList >
//class TypeAdapterInputInterface {
//    virtual ~TypeAdapterInputInterface() {}
//public:



//    virtual void operator()(int val)         {}
//    virtual void operator()(std::string val) {}
//};







} // detail ////////////////////////////////////////////////////////////////////


#define CONSTEXPR BOOST_CONSTEXPR


//typedef ltk::Real_t      Real_t;
#ifndef LTK_DOUBLE_PRECISION
typedef float      Real_t;
#else
typedef double     Real_t;
#endif
//typedef ltk::Id_t        Id_t;
typedef id_t       Id_t;
////typedef ltk::Size_t      Size_t;
//typedef ltk::Pointer_t   Pointer_t;
typedef void *     Pointer_t;
typedef bool             Bool_t;      //Boolean (0=false, 1=true) (bool)



//--- bit manipulation ---------------------------------------------------------
#ifndef BIT
#define BIT(n)       (1ULL << (n))
#endif

#ifndef SETBIT
#define SETBIT(n,i)  ((n) |= BIT(i))
#endif

#ifndef CLRBIT
#define CLRBIT(n,i)  ((n) &= ~BIT(i))
#endif

#ifndef TESTBIT
#define TESTBIT(n,i) ((Bool_t)(((n) & BIT(i)) != 0))
#endif


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// TYPE INTROSPECTION FOR OBJECTS //



#define uLibTypeMacro(thisClass,...) \
    \
    /* Friendship detail for accessing introspection */ \
    template <typename> friend class uLib::detail::TypeIntrospection::access;       \
    \
    /* type info structure*/ public: \
    /* in GCC 4.8 must be public or dynamic_cast wont work */ \
    struct type_info { \
      /*WARNING: -std=c++0x required for this! */ \
      constexpr static const char *name = BOOST_PP_STRINGIZE(thisClass);            \
      typedef BOOST_PP_VARIADIC_ELEM(0,__VA_ARGS__) BaseClass;                      \
      typedef thisClass ThisClass;                                                  \
      typedef uLib::mpl::vector<__VA_ARGS__,thisClass> TypeList;                    \
      typedef uLib::mpl::vector<__VA_ARGS__>           BaseList;                    \
      typedef uLib::detail::TypeIntrospection::child_first<ThisClass>::type CFList; \
    }; \
    \
    public: \
    typedef type_info::BaseClass BaseClass; \
    virtual const char *type_name() const { return type_info::name; } \
    /* Object Props fwd declaration*/ \
    struct ObjectProps; \
    /**/


/**
 * TypeList inheritance introspection
 */
struct TypeIntrospection {
    template <typename T>
    struct child_first : detail::TypeIntrospection::child_first<T> {};

};






// SISTEMARE //
struct PrintTypeId {
    template <class T>
    void operator()(T) const
    { std::cout << typeid(T).name() << std::endl; }

    template <typename SeqT>
    static void PrintMplSeq(SeqT *p = NULL) { boost::mpl::for_each<SeqT>(PrintTypeId()); }

    template <typename Class>
    static void PrintType(Class *p = NULL) { std::cout << typeid(Class).name() << std::endl; }
};







} // uLib

#endif // U_CORE_TYPES_H





















