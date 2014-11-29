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



#ifndef U_OBJECTPROPS_H
#define U_OBJECTPROPS_H



#include <boost/algorithm/string/replace.hpp>

#include <Core/Mpl.h>
#include <Core/Types.h>



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// MACROS //


#define ULIB_props() \
    public: struct ObjectProps;		                               \
    virtual void init_properties();                                \
    inline struct ObjectProps &p() { /* static const unsigned int offset = props_offset(this); */ \
    /* NON FUNZIA!  return * (struct ObjectProps *)(reinterpret_cast<char*>(props())+offset);  */ \
    return *props()->ptr<ObjectProps>(); }                                                        \
    typedef uLib::mpl::bool_<true>::type propable_trait;                                          \
    public: struct DLL_PUBLIC ObjectProps

#define uLib_properties() ULIB_props()

#define default(vlaue)

#define $$ p()

#define $(_name) props_ref<_name>()

#define $_init()                                                               \
    if(props(this)) return;                                                    \
    props_new(this);                                                           \
    uLib::detail::ObjectProps::initializer::init_object_baselist(this);



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace boost {
namespace serialization {
class access;
}
}


namespace uLib {

namespace detail {

struct ObjectProps {

    /** Define a trait has_member to find if an Object is Propable*/
    BOOST_MPL_HAS_XXX_TRAIT_DEF(propable_trait)

    /** IsA ProbapleObject Implementation Template */
    template <class T>
    struct IsA : has_propable_trait<T> {};

    /** Lambda to get Props member type */
    template <class T>
    struct props_type {
        typedef typename T::ObjectProps type;
    };

    template <typename T>
    struct get_props {

        /** CFList has result but this method check for has BaseList */
        typedef typename detail::TypeIntrospection::child_first<T>::type CFTypeList;

        /** Filter List items that have not Propable feature */
        typedef typename mpl::filter_view< CFTypeList, IsA<mpl::_> >::type FilteredCFTypeList;

        /** Get Props from each Parent in Seq */
        typedef typename mpl::transform_view< FilteredCFTypeList, props_type<mpl::_> >::type type;


        // qui sotto ho un problema che ho temporaneamente tamponato          //
        // ovvero ho usato child_first_impl per ottenere la lista delle basi  //
        // vorrei farlo facendo un pop_back ma non va forse perche il tipo    //
        // non e' corretto. //

        /** Get Parent list from CFTypeList */
        typedef typename detail::TypeIntrospection::child_first_impl<T>::Childs CFBaseList;

        /** Filter Parents that have not Propable feature */
        typedef typename mpl::filter_view< CFBaseList, IsA<mpl::_> >::type FilteredCFBaseList;
    };



    // TODO: convert to pp const value,
    // (non so se sia possibile con il dinamic casting intanto funziona cosi' )
    template <typename T1, typename T2>
    static unsigned int measure_offset(T1 base, T2 derived) {
        return reinterpret_cast<char*>(derived) - reinterpret_cast<char*>(base);
    }

    struct initializer {

        template <class _ObjectT>
        struct lambda_init_object {
            _ObjectT *o;
            lambda_init_object(_ObjectT *o) : o(o) {}
            template<class T> void operator()(T) {
                o->T::init_properties();
            }
        };


        /**
         * This calls the internal init_properties() virtual function for each
         * object parent defined in BaseList only if it is propable
         */
        template <class T>
        static void init_object_baselist(T *o) {
            typedef typename uLib::detail::ObjectProps::get_props<T>::FilteredCFBaseList CFBaseList;
            mpl::for_each<CFBaseList>(lambda_init_object<T>(o));
        }

        /**
         * This calls the internal init_properties() virtual function only if
         * object is propable ( implementation if not propable )
         */
        template <class T>
        static
        typename boost::enable_if<mpl::not_<IsA<T> >,void>::type
        init_object(T *o) {
            ; // do nothing //
        }

        /**
         * This calls the internal init_properties() virtual function only if
         * object is propable ( implementation if propable )
         */
        template <class T>
        static
        typename boost::enable_if<IsA<T>,void>::type
        init_object(T *o) {
            o->init_properties();
        }

    };

    template <class ThisClass, class Archive>
    struct serialize_baselist {
        ThisClass & m_object;
        Archive   & m_ar;
        serialize_baselist(ThisClass &o, Archive &ar) : m_object(o), m_ar(ar) {}
        template <class T> void operator()(T &o) {
            // T is taken fron get_props<BaseList>::FilteredPList types to get
            // type_info_name that is the type name defined by Type macro
            typedef typename props_type<T>::type PType;
            std::string name(TypeIntrospection::access<T>::type_info::name);
            boost::algorithm::replace_all(name,"::","_");
            m_ar & boost::serialization::make_nvp(
                        name.c_str() ,
                        boost::serialization::base_object<PType>(m_object));
        }
    };

};

} // detail





struct ObjectPropsBase {
    virtual ~ObjectPropsBase() {}
    virtual ObjectPropsBase *copy() = 0;

    template <class T> inline T *ptr() { return dynamic_cast<T*>(this); }

    template<class ArchiveT> void serialize(ArchiveT &ar, const unsigned int version) {}
};



template <class T>
struct ObjectPropsImpl :
        ObjectPropsBase,
        ULIB_MPL_INHERIT_NOFOLD_SEQ(typename uLib::detail::ObjectProps::get_props<T>::type)
{    
    typedef ObjectPropsImpl<T> ThisClass;
    typedef typename uLib::detail::ObjectProps::get_props<T>::type CFList;
    typedef typename uLib::detail::ObjectProps::get_props<T>::FilteredCFTypeList FilteredCFTypeList;
    ObjectPropsBase *copy() { return new ThisClass(*this); }

    template<class ArchiveT> void serialize(ArchiveT &ar, const unsigned int version) {
        boost::serialization::void_cast_register<ThisClass,ObjectPropsBase>();
        mpl::for_each<FilteredCFTypeList>(detail::ObjectProps::serialize_baselist<ThisClass,ArchiveT>(*this,ar));
    }
};


class ObjectPropable {

    ObjectPropsBase *m_props;
    friend class uLib::detail::ObjectProps;
    friend class boost::serialization::access;
public:
    ObjectPropable() : m_props(NULL) {}
    ObjectPropable(const ObjectPropable &c) { if(c.m_props) m_props = c.m_props->copy(); else m_props = NULL; }
    ~ObjectPropable() { if(m_props) delete m_props; }


    template <class T> inline typename T::ObjectProps&  props_ref() const { if(m_props) return *m_props->ptr<typename T::ObjectProps>(); else exit(1); }
    template <class T> inline typename T::ObjectProps*  props(T *ptr = NULL) const { if(m_props) return m_props->ptr<typename T::ObjectProps>(); else return NULL; }
protected:
    ObjectPropsBase *props() const { return m_props; }
    template <class T> inline void props_new(T* ptr = NULL) { if(!m_props) m_props = new ObjectPropsImpl<T>; }

    /** NOT working dynamic cache casting */
    template <class T> inline unsigned int props_offset(T *ptr) const
    { if(m_props) return detail::ObjectProps::measure_offset(m_props,m_props->ptr<T>()); else return -1; }


    template<class ArchiveT> void serialize(ArchiveT &ar, const unsigned int version) {
        if(m_props) ar & boost::serialization::make_nvp("properties",m_props);
    }

public:
    /**
     * ObjectPropable is not directly propable itself to prevent Basclass
     * duplication in inherit_nofold. And for the same reason ANY VIRTUAL BASE
     * SHOULD NOT BE PROPABLE
     */
    virtual void init_properties() {}

};

} // uLib







#endif // U_OBJECTPROPS_H
