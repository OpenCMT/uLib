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




#include "Ob1.h"

namespace uLib {





// created by moc // -------------------------------------------------------- //


void Ob1::init()
{
    Ob::init<Ob1>();
    boost::serialization::void_cast_register<Ob1,BaseClass>();
    BaseClass::init();
    // default parameters value //
    p().a = 1;
    p().b = 2;
}




//// serialization accessor that can be made by moc //

//template <class Archive>
//void Ob1::serialize(Archive &ar, Ob1::Parameters &p, const unsigned int version)
//{
//    Ob1::BaseClass::serialize<Archive>( ar,p,version );
//    ar & boost::serialization::make_nvp("a",p.a);
//    ar & boost::serialization::make_nvp("b",p.b);
//}

//template <class Archive>
//void Ob1::serialize(Archive &ar, Ob1 &ob, const unsigned int version )
//{
//    Ob1::BaseClass::serialize<Archive>(ar,ob,version);
//    // other members to be serialized //
//}



// -------------------------------------------------------------------------- //



}


BOOST_CLASS_EXPORT_IMPLEMENT(uLib::Ob1) // use this in cpp file

