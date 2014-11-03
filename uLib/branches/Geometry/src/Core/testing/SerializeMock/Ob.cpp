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






/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_base.cpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

//#include <boost/archive/polymorphic_oarchive.hpp>
//#include <boost/archive/polymorphic_iarchive.hpp>
//#include <boost/archive/xml_oarchive.hpp>
//#include <boost/archive/xml_iarchive.hpp>

#include "Ob.h"


//// A /////////////////////////////////////////////////////////////////////////

template <class Archive>
void A::serialize(Archive &ar, unsigned int v) {
    ar & BOOST_SERIALIZATION_NVP(i);
}

//_SERIALIZE_IMPL(A,boost::archive::polymorphic_oarchive)
SERILIZE_IMPL(A)

void A::Save(boost::archive::polymorphic_oarchive &ar)
{ ar << boost::serialization::make_nvp(boost::serialization::guid<A>(),this); }

// note: only the most derived classes need be exported
// BOOST_CLASS_EXPORT(A)




//// B /////////////////////////////////////////////////////////////////////////

template <class Ar>
void B::serialize(Ar &ar, unsigned int v) {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(A);
}

SERILIZE_IMPL(B)

void B::Save(boost::archive::polymorphic_oarchive &ar)
{ ar << boost::serialization::make_nvp(boost::serialization::guid<B>(),this); }

_SPECIALIZE_IS_VIRTUAL_BASE(A,B)
BOOST_CLASS_EXPORT_IMPLEMENT(B)




//// C /////////////////////////////////////////////////////////////////////////

template <class Ar>
void C::serialize(Ar &ar, unsigned int v) {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(A);
}

SERILIZE_IMPL(C)

void C::Save(boost::archive::polymorphic_oarchive &ar)
{ ar << boost::serialization::make_nvp(boost::serialization::guid<C>(),this); }

_SPECIALIZE_IS_VIRTUAL_BASE(A,C)
BOOST_CLASS_EXPORT_IMPLEMENT(C)




