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




#include <boost/serialization/export.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "Ob.h"
#include "Ob1.h"


template <class Ar>
void D::serialize(Ar &ar, unsigned int v) {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(B);
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(C);
}

SERILIZE_IMPL(D)

void D::Save(boost::archive::polymorphic_oarchive &ar)
{ ar << boost::serialization::make_nvp(boost::serialization::guid<D>(),this); }

_SPECIALIZE_IS_VIRTUAL_BASE(B,D)
_SPECIALIZE_IS_VIRTUAL_BASE(C,D)
BOOST_CLASS_EXPORT_IMPLEMENT(D)
