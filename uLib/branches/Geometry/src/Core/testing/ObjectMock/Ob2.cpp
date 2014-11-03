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





#include "Ob2.h"

namespace uLib {


// created by moc // -------------------------------------------------------- //




void Ob2::init()
{
    Ob::init<Ob2>();
    boost::serialization::void_cast_register<Ob2,BaseClass>();
    BaseClass::init();
    p().c = 3;
    p().d = 4;
}

//template <class Archive>
//void Ob2::serialize(Archive &ar, Parameters &p, const unsigned int version)
//{
//    Ob2::BaseClass::serialize<Archive>( ar,p,version );
//    ar & boost::serialization::make_nvp("c",p.c);
//    ar & boost::serialization::make_nvp("d",p.d);
//}

//template <class Archive>
//void Ob2::serialize(Archive &ar, Ob2 &o, const unsigned int version )
//{
//    Ob2::BaseClass::serialize<Archive>(ar,o,version);
//    ar & boost::serialization::make_nvp("serializzable_member",o.serializzable_member);
//    // other members //
//}



// -------------------------------------------------------------------------- //

}



BOOST_CLASS_EXPORT_IMPLEMENT(uLib::Ob2) // use this in cpp file
