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



#ifndef U_CORE_DEBUGARCHIVES_H
#define U_CORE_DEBUGARCHIVES_H

#include <boost/archive/detail/basic_pointer_iserializer.hpp>
#include <boost/archive/detail/basic_pointer_oserializer.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/archive/detail/register_archive.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

#include <boost/archive/polymorphic_text_oarchive.hpp>

#include "Archives.h"
#include "StringReader.h"



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// FWD DECLARATIONS OF ARCHIVES //


namespace uLib {
namespace Archive {

class Root_debug_archive;

}
}


namespace boost {
namespace archive {
namespace detail {
template<class ArchiveImplementation> class polymorphic_oarchive_route;
template<class ArchiveImplementation> class polymorphic_iarchive_route;
}
}
}

namespace boost {
namespace serialization {
    template <typename T> struct hrp;
}
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// ARCHIVES REGISTRATION //

// in Archives.h



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// ARCHIVES IO INTERFACES //


namespace boost {
namespace archive {
namespace detail {


// DECLARE INTERFACE SPECIALIZATIONS ///////////////////////////////////////////
// With this declarations all uLib archive Implementation will use their own
// extended interface //

template <>
class interface_iarchive        <uLib::Archive::Root_debug_archive> : public
        uLib_interface_iarchive <uLib::Archive::Root_debug_archive> {};


} // detail
} // archive
} // boost













////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// ARCHIVES DEFINITIONS //

namespace boost {
namespace archive {

//template<class Archive>
//inline void load_const_override(Archive & ar, const char *t ){
//    typedef typename mpl::identity<detail::load_non_pointer_type<Archive> >::type typex;
//    typex::invoke(ar, t);
//}

//template<class Archive, class T>
//inline void load(Archive & ar, T &t){
//    // if this assertion trips. It means we're trying to load a
//    // const object with a compiler that doesn't have correct
//    // funtion template ordering.  On other compilers, this is
//    // handled below.
//    //    detail::check_const_loading< T >();
//    typedef
//        BOOST_DEDUCED_TYPENAME mpl::eval_if<is_pointer< T >,
//            mpl::identity<detail::load_pointer_type<Archive> >
//        ,//else
//        BOOST_DEDUCED_TYPENAME mpl::eval_if<is_array< T >,
//            mpl::identity<detail::load_array_type<Archive> >
//        ,//else
//        BOOST_DEDUCED_TYPENAME mpl::eval_if<is_enum< T >,
//            mpl::identity<detail::load_enum_type<Archive> >
//        ,//else
//            mpl::identity<detail::load_non_pointer_type<Archive> >
//        >
//        >
//        >::type typex;
//    typex::invoke(ar, t);
//}



}
}

// ROOT FWD
class TTree;
///////////


namespace uLib {
namespace Archive {

namespace detail {

class basic_Root_Ttree_oprimitive
{
    TTree *m_tree;



public:
    basic_Root_Ttree_oprimitive(const char *tree_name);
    ~basic_Root_Ttree_oprimitive();

};

} // detail



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// XML FOR LOG OUTPUT PURPOUSE //

///////////////////////////////////////////////////////////////////////////
//// log data to an output stream.  This illustrates a simpler implemenation
//// of text output which is useful for getting a formatted display of
//// any serializable class.  Intended to be useful as a debugging aid.
class Root_debug_archive :
    /* protected ? */
    public boost::archive::detail::common_oarchive<Archive>
{
    typedef boost::archive::detail::common_oarchive<Root_debug_archive> base;
    typedef Root_debug_archive Archive;

    // give serialization implementation access to this clas
    friend class boost::archive::detail::interface_oarchive<Root_debug_archive>;
    friend class boost::archive::save_access;

public:

//    void save_override(const char *str, int v) {
//        // Do not save any human decoration string //
//        //        basic_text_oprimitive::save(str);
//    }

//    template<class T>
//    void save_override(T & t, BOOST_PFTO int){
//        base::save_override(boost::serialization::make_nvp(NULL, t), 0);
//    }

//    // activate this if you want to trap non nvp objects //
//    //    template<class T>
//    //    void save_override(T & t, BOOST_PFTO int)
//    //    {
//    //        BOOST_MPL_ASSERT((boost::serialization::is_wrapper< T >));
//    //        //        this->detail_common_oarchive::save_override(t, 0);
//    //    }

//    template<class T>
//    void save_override(const boost::serialization::nvp<T> & t, int){
//        base::save_override(t, 0);
//    }


//    // specific overrides for attributes - not name value pairs so we
//    // want to trap them before the above "fall through"
//    // since we don't want to see these in the output - make them no-ops.
//    void save_override(const boost::archive::object_id_type & t, int)         {}
//    void save_override(const boost::archive::object_reference_type & t, int)  {}
//    void save_override(const boost::archive::version_type & t, int)           {}
//    void save_override(const boost::archive::class_id_type & t, int)          {}
//    void save_override(const boost::archive::class_id_optional_type & t, int) {}
//    void save_override(const boost::archive::class_id_reference_type & t, int){}
//    void save_override(const boost::archive::class_name_type & t, int)        {}
//    void save_override(const boost::archive::tracking_type & t, int)          {}


//public:
//    Root_debug_archive(std::ostream & os, unsigned int flags = 0) :
//        boost::archive::xml_oarchive_impl<log_archive>(
//            os,
//            flags | boost::archive::no_header
//        )
//    {}
};





} // Archive
} // uLib



ULIB_SERIALIZATION_REGISTER_ARCHIVE(uLib::Archive::Root_debug_archive)






#endif // U_CORE_DEBUGARCHIVES_H
