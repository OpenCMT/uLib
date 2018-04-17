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



#ifndef U_CORE_EXPORT_H
#define U_CORE_EXPORT_H

#include <utility>
#include <cstddef> // NULL
#include <iostream>

#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/type_traits/is_polymorphic.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/serialization/extended_type_info.hpp> // for guid_defined only
#include <boost/serialization/static_warning.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/force_include.hpp>
#include <boost/serialization/singleton.hpp>

#include <boost/archive/detail/register_archive.hpp>


#include "Core/Archives.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



namespace uLib {
namespace Archive {
namespace detail {
namespace extra_detail {

template<class T>
struct guid_initializer
{
    void export_guid(mpl::false_) const {
        // generates the statically-initialized objects whose constructors
        // register the information allowing serialization of T objects
        // through pointers to their base classes.
        boost::archive::detail::
                instantiate_ptr_serialization((T*)0, 0,
                                              uLib::Archive::detail::adl_tag());
    }
    void export_guid(mpl::true_) const {
    }
    guid_initializer const & export_guid() const {
        BOOST_STATIC_WARNING(boost::is_polymorphic< T >::value);
        // note: exporting an abstract base class will have no effect
        // and cannot be used to instantitiate serialization code
        // (one might be using this in a DLL to instantiate code)
        //BOOST_STATIC_WARNING(! boost::serialization::is_abstract< T >::value);
        export_guid(boost::serialization::is_abstract< T >());
        return *this;
    }
};

template<typename T>
struct init_guid;

} // anonymous
} // namespace detail
} // namespace Archive
} // namespace uLib



#define  ULIB_CLASS_EXPORT_IMPLEMENT(T)                      \
    namespace uLib  {                                        \
    namespace Archive {                                      \
    namespace detail {                                       \
    namespace extra_detail {                                 \
    template<>                                               \
    struct init_guid< T > {                                  \
        static guid_initializer< T > const & g;              \
    };                                                       \
    guid_initializer< T > const & init_guid< T >::g =        \
        ::boost::serialization::singleton<                   \
            guid_initializer< T >                            \
        >::get_mutable_instance().export_guid();             \
    }}}}                                                     \
/**/

#endif // EXPORT_H
