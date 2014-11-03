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





#ifndef OB_H
#define OB_H


/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// test_polymorphic2.hpp

// (C) Copyright 2009 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <ostream>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp>

#include <boost/preprocessor/seq.hpp>

#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>



#define _SERIALIZE_IMPL_SEQ \
    (boost::archive::polymorphic_iarchive) \
    (boost::archive::polymorphic_oarchive) \
    (boost::archive::xml_iarchive) \
    (boost::archive::xml_oarchive)

#define _SERIALIZE_IMPL(Class,Archive) \
    template void Class::serialize(Archive &ar,const unsigned int);

#define _SERIALIZE_IMPL_OP(r,data,elem) _SERIALIZE_IMPL(data,elem)

#define SERILIZE_IMPL(Class) BOOST_PP_SEQ_FOR_EACH(_SERIALIZE_IMPL_OP,Class,_SERIALIZE_IMPL_SEQ)

#define _SPECIALIZE_IS_VIRTUAL_BASE(Base,Derived) namespace boost{ template<> struct is_virtual_base_of<Base,Derived>: public boost::mpl::true_ {}; }
#define _SPECIALIZE_IS_VIRTUAL_BASE_OP(r,data,elem) _SPECIALIZE_IS_VIRTUAL_BASE(data,elem)




// should pass compilation and execution
namespace boost {
namespace archive {
    class polymorphic_oarchive;
    class polymorphic_iarchive;
}
}


struct A {
    virtual ~A() {}

    template <class Archive> void serialize(Archive &ar, unsigned int v);
    virtual void Save(boost::archive::polymorphic_oarchive &ar);

    int i;
};


struct B : virtual A {

    template <class Ar> void serialize(Ar &ar, unsigned int v);
    virtual void Save(boost::archive::polymorphic_oarchive &ar);

};

BOOST_CLASS_EXPORT_KEY(B)

struct C : virtual A {

    template <class Ar> void serialize(Ar &ar, unsigned int v);
    virtual void Save(boost::archive::polymorphic_oarchive &ar);
};

BOOST_CLASS_EXPORT_KEY(C)



#endif
