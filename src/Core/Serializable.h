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



#ifndef U_SERIALIZABLE_H
#define U_SERIALIZABLE_H

/* Serialization:



TODO:
* Problema nella serializzazione delle properties in test_archive
* implementare human readable make_hrp ... non riesco..

*/




#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/serialization/nvp.hpp>

//#include <boost/archive/xml_iarchive.hpp>
//#include <boost/archive/xml_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include "boost/archive/polymorphic_iarchive.hpp"
//#include "boost/archive/polymorphic_oarchive.hpp"

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>


#include "Core/Mpl.h"
#include "Core/ObjectProps.h"
#include "Core/Archives.h"
#include "Core/Export.h"



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// BOOST SERIALIZATION ADD-ON

namespace boost {
namespace serialization {

// ACCESS 2 //
template <class T> struct access2 {};


// NON FUNZIONA ... SISTEMARE !!!! // ------------------------------------------
template<class T>
class hrp :
        public wrapper_traits<const hrp< T > >
{
    const char *m_name;
    T *m_value;
    std::string *m_str;

public:
    explicit hrp(const char * name_, T &t) :
        m_str(new std::string),
        m_name(name_), m_value(&t) {}

    const char * name() const {
        return this->m_name;
    }


    template<class Archivex>
    void save( Archivex & ar, const unsigned int /* file_version */) const {
        ////        ar.operator<<(const_value());
        //        std::stringstream ss;
        //        uLib::Archive::hrt_oarchive har(ss);
        //        har << make_nvp(m_name,*m_value);
        //        //        (*m_str) = ss.str();
        ////        ar.operator << (make_nvp(m_name, ss.str());
    }
    template<class Archivex>
    void load( Archivex & ar, const unsigned int /* file_version */) {
//        ar.operator>>(value());
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
};


template<class T>
inline
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
hrp< T > make_hrp(const char * name, T & t){
    return hrp< T >(name, t);
}

#define HRP(name) \
    boost::serialization::make_hrp(BOOST_PP_STRINGIZE(name), name)


} // serialization
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
// ULIB SERIALIZATION

namespace uLib {



#define _AR_OP(r,data,elem) data&BOOST_SERIALIZATION_BASE_OBJECT_NVP(elem);

#define NVP(data) BOOST_SERIALIZATION_NVP(data)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// SERIALIZTION MACROS //

// !!! WARNING !!! INTRUSIVE SERIALIZATION IS ACTUALLY NOT WORKING FEATURE
// SO LEAVE ULIB_CFG_INTRUSIVE_SERIALIZATION NOT DEFINED

#ifdef ULIB_CFG_INTRUSIVE_SERIALIZATION_OBJECT
#  define ULIB_SERIALIZABLE_OBJECT        _ULIB_DETAIL_INTRUSIVE_SERIALIZABLE_OBJECT
#  define ULIB_SERIALIZE_OBJECT(_Ob,...)  _ULIB_DETAIL_INTRUSIVE_SERIALIZE_OBJECT(_Ob,__VA_ARGS__)
#  define _AR_(_name)                     _ULIB_DETAIL_INTRUSIVE_AR_(_name)
#else
#  define ULIB_SERIALIZABLE(_Ob)           _ULIB_DETAIL_UNINTRUSIVE_SERIALIZABLE(_Ob) \
                                            ULIB_CLASS_EXPORT_KEY(_Ob)
#  define ULIB_SERIALIZE(_Ob,...)          _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE(_Ob)
#  define ULIB_SERIALIZE_DERIVED(_Ob,...)  _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_DERIVED(_Ob,__VA_ARGS__)
#  define ULIB_SERIALIZABLE_OBJECT(_Ob)    _ULIB_DETAIL_UNINTRUSIVE_SERIALIZABLE_OBJECT(_Ob) \
                                            ULIB_CLASS_EXPORT_OBJECT_KEY(_Ob)
#  define ULIB_SERIALIZE_OBJECT(_Ob,...)   _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_OBJECT(_Ob,__VA_ARGS__)
#  define ULIB_SERIALIZE_OBJECT_PROPS(_Ob) _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_PROPS(_Ob)
#  define AR(_name)                        _ULIB_DETAIL_UNINTRUSIVE_AR_(_name)
#  define HR(_name)                        _ULIB_DETAIL_UNINTRUSIVE_AR_(_name)
#endif


#define ULIB_SERIALIZE_ACCESS                                        \
    friend class boost::serialization::access;                       \
    template <class T> friend class boost::serialization::access2;

#define ULIB_CLASS_EXPORT_KEY(_FullNamespaceClass)                   \
    BOOST_CLASS_EXPORT_KEY(_FullNamespaceClass)

#define ULIB_CLASS_EXPORT_OBJECT_KEY(_FullNamespaceClass)            \
    BOOST_CLASS_EXPORT_KEY(_FullNamespaceClass)                      \
    BOOST_CLASS_EXPORT_KEY(_FullNamespaceClass::ObjectProps)         \
    BOOST_CLASS_EXPORT_KEY(uLib::ObjectPropsImpl<_FullNamespaceClass>)


#define _SERIALIZE_IMPL_SEQ  \
    (uLib::Archive::text_iarchive) \
    (uLib::Archive::text_oarchive) \
    (uLib::Archive::hrt_iarchive)  \
    (uLib::Archive::hrt_oarchive)  \
    (uLib::Archive::xml_iarchive)  \
    (uLib::Archive::xml_oarchive)  \
    (uLib::Archive::log_archive)


/** Solving virtual class check problem */
#define _ULIB_DETAIL_SPECIALIZE_IS_VIRTUAL_BASE(_Base,_Derived)    namespace boost{ template<> struct is_virtual_base_of<_Base,_Derived>: public boost::mpl::true_ {}; }
#define _ULIB_DETAIL_SPECIALIZE_IS_VIRTUAL_BASE_OP(r,data,elem) _ULIB_DETAIL_SPECIALIZE_IS_VIRTUAL_BASE(elem,data)



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// INTRUSIVE SERIALIZATION ( NOT WORKING YET !! ) //

#define _ULIB_DETAIL_INTRUSIVE_AR_(name) ar & BOOST_SERIALIZATION_NVP(name);

#define _ULIB_DETAIL_INTRUSIVE_SERIALIZE_FUNC(Class,Archive) \
    template void Class::serialize(Archive &ar,const unsigned int);

#define _ULIB_DETAIL_INTRUSIVE_SERIALIZE_FUNC_OP(r,data,elem) _ULIB_DETAIL_INTRUSIVE_SERIALIZE_FUNC(data,elem);

#define _ULIB_DETAIL_INTRUSIVE_SERIALIZABLE_OBJECT \
    typedef boost::mpl::bool_<true> serializable;                                                \
    typedef boost::mpl::remove_if< TypeList, IsUnSerializable >::type SerilizableTypeList;       \
    void PrintSerializableListId() { boost::mpl::for_each<SerilizableTypeList>(PrintTypeId()); } \
    template <class ArchiveT> void serialize(ArchiveT &ar,const unsigned int version);           \
    template <class ArchiveT> void serialize_parents(ArchiveT &ar,const unsigned int version);   \
    template <class ArchiveT> void save_override(ArchiveT &ar,const unsigned int version);

#define _ULIB_DETAIL_INTRUSIVE_SERIALIZE_OBJECT(_Ob,...) \
    template <class ArchiveT> void _Ob::serialize(ArchiveT &ar, const unsigned int version) { \
    boost::serialization::void_cast_register<_Ob,_Ob::BaseClass>(static_cast<_Ob *>(NULL),static_cast<_Ob::BaseClass *>(NULL));   \
    _Ob::serialize_parents(ar,version); \
    _Ob::save_override(ar,version); }\
    template <class ArchiveT> void _Ob::serialize_parents(ArchiveT &ar, const unsigned int v) { \
    BOOST_PP_SEQ_FOR_EACH(_AR_OP,ar,BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))); } \
    BOOST_PP_SEQ_FOR_EACH(_ULIB_DETAIL_INTRUSIVE_SERIALIZE_FUNC_OP,_Ob,_SERIALIZE_IMPL_SEQ)\
    BOOST_PP_SEQ_FOR_EACH(_ULIB_DETAIL_SPECIALIZE_IS_VIRTUAL_BASE_OP,_Ob,BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))) \
    ULIB_CLASS_EXPORT_IMPLEMENT(_Ob) \
    namespace boost { \
    namespace serialization { \
    template<class ArchiveT> inline void load_construct_data(ArchiveT & ar, _Ob *o, const unsigned int file_version) \
    { ::new(o)_Ob(); o->init_parameters(); } }}\
    template <class ArchiveT> void _Ob::save_override(ArchiveT &ar, const unsigned int version)



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// UNINTRUSIVE SERIALIZATION

#define _UNAR_OP(r,data,elem) ar&boost::serialization::make_nvp(BOOST_PP_STRINGIZE(elem),boost::serialization::base_object<elem>(ob));

#define _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_FUNC(Class,Archive) \
    template void boost::serialization::serialize(Archive &ar, Class &ob, const unsigned int i);

#define _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_FUNC_OP(r,data,elem) _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_FUNC(data,elem)


// NOTE: becouse of BOOST_PP_VARIADIC_SIZE issue of some boost macro has two
// different implementation

#define _ULIB_DETAIL_UNINTRUSIVE_SERIALIZABLE(_Ob) \
    namespace boost { namespace serialization { \
    template <class ArchiveT> void serialize         (ArchiveT &ar, _Ob &ob, const unsigned int version); \
    template <class ArchiveT> void serialize_parents (ArchiveT &ar, _Ob &ob, const unsigned int version); \
    template <> struct access2< _Ob > { template <class ArchiveT> static void save_override (ArchiveT &ar, _Ob &ob, const unsigned int version); }; }}

#define _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE(_Ob) \
    namespace boost { namespace serialization { \
    template <class ArchiveT> void serialize_parents(ArchiveT &ar, _Ob &ob, const unsigned int v) {} \
    template <class ArchiveT> void serialize  (ArchiveT &ar, _Ob &ob, const unsigned int version) { \
    serialize_parents(ar,ob,version);  \
    access2< _Ob >::save_override(ar,ob,version); } }}\
    ULIB_CLASS_EXPORT_IMPLEMENT(_Ob) \
    BOOST_PP_SEQ_FOR_EACH(_ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_FUNC_OP,_Ob,_SERIALIZE_IMPL_SEQ)\
    template <class ArchiveT> void boost::serialization::access2< _Ob >::save_override(ArchiveT &ar, _Ob &ob, const unsigned int version)

#define _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_DERIVED(_Ob,...) \
    namespace boost { namespace serialization { \
    template <class ArchiveT> void serialize_parents(ArchiveT &ar, _Ob &ob, const unsigned int v) { \
    BOOST_PP_IF(BOOST_PP_VARIADIC_SIZE((__VA_ARGS__)),BOOST_PP_SEQ_FOR_EACH(_UNAR_OP,ob,BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)));,) } \
    template <class ArchiveT> void serialize  (ArchiveT &ar, _Ob &ob, const unsigned int version) { \
    serialize_parents(ar,ob,version);  \
    access2< _Ob >::save_override    (ar,ob,version); } }}\
    ULIB_CLASS_EXPORT_IMPLEMENT(_Ob) \
    BOOST_PP_SEQ_FOR_EACH(_ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_FUNC_OP,_Ob,_SERIALIZE_IMPL_SEQ) \
    BOOST_PP_SEQ_FOR_EACH(_ULIB_DETAIL_SPECIALIZE_IS_VIRTUAL_BASE_OP,_Ob,BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))) \
    template <class ArchiveT> void boost::serialization::access2< _Ob >::save_override(ArchiveT &ar, _Ob &ob, const unsigned int version)


#define _ULIB_DETAIL_UNINTRUSIVE_SERIALIZABLE_OBJECT(_Ob) \
    namespace boost { namespace serialization { \
    template <class ArchiveT> void serialize         (ArchiveT &ar, _Ob &ob, const unsigned int version); \
    template <class ArchiveT> void serialize_parents (ArchiveT &ar, _Ob &ob, const unsigned int version); \
    template <> struct access2< _Ob > { template <class ArchiveT> static void save_override (ArchiveT &ar, _Ob &ob, const unsigned int version); }; \
    template <class ArchiveT> void serialize         (ArchiveT &ar, class _Ob::ObjectProps &ob, const unsigned int version); \
    template <class ArchiveT> void save_override     (ArchiveT &ar, class _Ob::ObjectProps &ob, const unsigned int version); }}

#define _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_OBJECT(_Ob,...) \
    namespace boost { namespace serialization { \
    template <class ArchiveT> void serialize_parents(ArchiveT &ar, _Ob &ob, const unsigned int v) { \
    /* PP  serialize */ BOOST_PP_SEQ_FOR_EACH(_UNAR_OP,ob,BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))); \
    /* MPL serialize */ /*uLib::mpl::for_each<_Ob::BaseList>(uLib::detail::Serializable::serialize_baseobject<_Ob,ArchiveT>(ob,ar) );*/ } \
    template<class ArchiveT> inline void load_construct_data(ArchiveT & ar, _Ob *ob, const unsigned int file_version) { \
    ::new(ob)_Ob(); uLib::detail::ObjectProps::initializer::init_object(ob); } \
    template <class ArchiveT> void serialize  (ArchiveT &ar, _Ob &ob, const unsigned int version) { \
    void_cast_register<_Ob,_Ob::BaseClass>(static_cast<_Ob *>(NULL),static_cast<_Ob::BaseClass *>(NULL)); /*fix*/  \
    serialize_parents(ar,ob,version);  \
    access2< _Ob >::save_override    (ar,ob,version); } }}\
    ULIB_CLASS_EXPORT_IMPLEMENT(_Ob) \
    BOOST_PP_SEQ_FOR_EACH(_ULIB_DETAIL_SPECIALIZE_IS_VIRTUAL_BASE_OP,_Ob,BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))) \
    BOOST_PP_SEQ_FOR_EACH(_ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_FUNC_OP,_Ob,_SERIALIZE_IMPL_SEQ)\
    template <class ArchiveT> void boost::serialization::access2< _Ob >::save_override(ArchiveT &ar, _Ob &ob, const unsigned int version)

#define _ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_PROPS(_Ob) \
    namespace boost { namespace serialization { \
    template <class ArchiveT> void serialize  (ArchiveT &ar, _Ob::ObjectProps &ob, const unsigned int version) { \
    save_override    (ar,ob,version); } }}\
    BOOST_PP_SEQ_FOR_EACH(_ULIB_DETAIL_UNINTRUSIVE_SERIALIZE_FUNC_OP,_Ob::ObjectProps,_SERIALIZE_IMPL_SEQ)\
    ULIB_CLASS_EXPORT_IMPLEMENT(_Ob::ObjectProps) \
    ULIB_CLASS_EXPORT_IMPLEMENT(uLib::ObjectPropsImpl<_Ob>) \
    template <class ArchiveT> void boost::serialization::save_override(ArchiveT &ar, _Ob::ObjectProps &ob, const unsigned int version)


#define _ULIB_DETAIL_UNINTRUSIVE_AR_(name) boost::serialization::make_nvp(BOOST_PP_STRINGIZE(name),ob.name)









////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



namespace detail {

struct Serializable {

    /**
     * Serializable trait to check if an object type is serializable.
     * This only works if UNINTRUSIVE SERIALIZATION is applyed; in intrusive
     * cases a has_serialize trait should be implemented
     */
    template <class T>
    struct serializable_trait : mpl::bool_<false> {};

    /**
     * IsA Serializable Implementation Template
     */
    template <class T>
    struct IsA : serializable_trait<T> {};

    template <class ThisClass, class Archive>
    struct serialize_baseobject {
        ThisClass & m_object;
        Archive   & m_ar;
        serialize_baseobject(ThisClass &o, Archive &ar) : m_object(o), m_ar(ar) {}
        template <class T> void operator()(T &o) {
            m_ar & boost::serialization::make_nvp(
                        typeid(T).name() ,
                        boost::serialization::base_object<T>(m_object));
        }
    };


};


} // detail





struct Serializable {
    friend class boost::serialization::access;
    template <class T> friend class boost::serialization::access2;
    virtual ~Serializable() {}
protected:
};





} // uLib






#endif // U_SERIALIZABLE_H
