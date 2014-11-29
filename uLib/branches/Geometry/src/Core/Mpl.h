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



#ifndef U_MPL_H
#define U_MPL_H

#include <boost/preprocessor.hpp>

#include <boost/mpl/fold.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/inherit.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector/vector0.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/vector/vector20.hpp>
#include <boost/mpl/copy.hpp>

#include <boost/mpl/find.hpp>

#include <boost/mpl/transform.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/filter_view.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/string.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/same_as.hpp>

#include <boost/mpl/has_xxx.hpp>

#include <boost/utility/enable_if.hpp>

/**
 * Max size of nofold inerited capability
 */
#ifndef   ULIB_CFG_MPL_INERIT_NOFOLD_MAXSIZE
#  define ULIB_CFG_MPL_INERIT_NOFOLD_MAXSIZE 10
#endif

namespace uLib {

namespace mpl {

using namespace boost::mpl;
using namespace boost::mpl::placeholders;


//using boost::enable_if;

namespace detail {

/**
 * Inerit nofold implementation, set ULIB_CFG_MPL_INERIT_NOFOLD_MAXSIZE to
 * desired max derivation size keeping in mind that total size accounts all
 * mutiple inherited classes.
 */
template <class TypeSeq, unsigned int size>
struct inherit_nofold {};

// Horizontal repetition macro //
#define _INERIT_NOFOLD_H(hz,hn,hdata)                    \
    BOOST_PP_COMMA_IF(hn)                                \
    mpl::at<TypeSeq,mpl::int_<hn> >::type

// Veritical repetition macro //
#define _INERIT_NOFOLD_V(vz,vn,vdata)                    \
    template <class TypeSeq>                             \
    struct inherit_nofold<TypeSeq,BOOST_PP_INC(vn)> :    \
    BOOST_PP_REPEAT(BOOST_PP_INC(vn),_INERIT_NOFOLD_H,~) \
    {};

// Multiple size declaration //
BOOST_PP_REPEAT(ULIB_CFG_MPL_INERIT_NOFOLD_MAXSIZE,_INERIT_NOFOLD_V,~)

#undef  _INERIT_NOFOLD_H
#undef  _INERIT_NOFOLD_V


} // detail

/**
 * Build a derivation tuple from mpl type sequence.
 * The same behavior can be obtained by inherit_linearly but folding derivation
 * results in a hard to read debugging
 */
template <class TypeSeq>
struct inherit_nofold {
    typedef detail::inherit_nofold< TypeSeq, mpl::size<TypeSeq>::type::value > type;
};

/** INHERIT LINEARLY standard utility macro */
#define ULIB_MPL_INHERIT_SEQ(_TypeList)                                        \
    uLib::mpl::inherit_linearly< _TypeList, mpl::inherit< mpl::_1, mpl::_2 > >::type

/** INHERIT NOFOLD   utility macro (see struct inherit_nofold template) */
#define ULIB_MPL_INHERIT_NOFOLD_SEQ(_TypeList)                                 \
    uLib::mpl::inherit_nofold< _TypeList >::type




template< class T>
struct type {

};

template <const char *N, class T>
struct nvp {
    nvp() : name(N) {}
    const char *name;
    typedef T type;
};





} // mpl
} // uLib

#endif // MPL_H
