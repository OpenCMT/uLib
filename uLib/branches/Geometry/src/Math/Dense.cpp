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




#include "Dense.h"
#include "Core/Archives.h"

//ULIB_SERIALIZE(uLib::HPoint3f) {
//    ar & boost::serialization::make_nvp(NULL,boost::serialization::base_object<uLib::HPoint3f::BaseClass,uLib::HPoint3f>(ob));
//}


//ULIB_SERIALIZE(uLib::Vector4f) {
//    ar & boost::serialization::make_nvp(NULL,boost::serialization::base_object<uLib::Vector4f::BaseClass,uLib::Vector4f>(ob));
//}


//ULIB_SERIALIZE(uLib::HLine3f) {
//    ar
//            & "HLine -> ( origin: " & AR(origin) & "; direction: " & AR(direction) & ") ";
//}

//ULIB_SERIALIZE(uLib::HError3f) {
//    ar
//            & "HLine -> ( poserr: " & AR(position_error) & "; direrr: " & AR(direction_error) & ") ";
//}


// NEW //
ULIB_SERIALIZE(uLib::Vector2i) { ar & boost::serialization::make_nvp(NULL,ob); }
ULIB_SERIALIZE(uLib::Vector3i) { ar & boost::serialization::make_nvp(NULL,ob); }
ULIB_SERIALIZE(uLib::Vector4i) { ar & boost::serialization::make_nvp(NULL,ob); }
ULIB_SERIALIZE(uLib::Vector2f) { ar & boost::serialization::make_nvp(NULL,ob); }
ULIB_SERIALIZE(uLib::Vector3f) { ar & boost::serialization::make_nvp(NULL,ob); }
ULIB_SERIALIZE(uLib::Vector4f) { ar & boost::serialization::make_nvp(NULL,ob); }
ULIB_SERIALIZE(uLib::Vector2d) { ar & boost::serialization::make_nvp(NULL,ob); }
ULIB_SERIALIZE(uLib::Vector3d) { ar & boost::serialization::make_nvp(NULL,ob); }
ULIB_SERIALIZE(uLib::Vector4d) { ar & boost::serialization::make_nvp(NULL,ob); }


