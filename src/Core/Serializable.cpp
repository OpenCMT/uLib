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



#include "boost/archive/polymorphic_xml_oarchive.hpp"
#include "boost/archive/polymorphic_xml_iarchive.hpp"
#include "boost/archive/polymorphic_text_oarchive.hpp"
#include "boost/archive/polymorphic_text_iarchive.hpp"
#include "boost/archive/polymorphic_binary_oarchive.hpp"
#include "boost/archive/polymorphic_binary_iarchive.hpp"

#include "Serializable.h"


using namespace uLib;



//void Serializable::SaveXml(std::ostream &os, const char *name)
//{
//    boost::archive::polymorphic_oarchive *xoa = new boost::archive::polymorphic_xml_oarchive(os);
//    this->Save(*xoa);
//    delete xoa;
//}

//void Serializable::LoadXml(std::istream &is, const char *name)
//{
//    boost::archive::polymorphic_iarchive *xia = new boost::archive::polymorphic_xml_iarchive(is);
//    this->Load(*xia,this);
//    delete xia;
//}

//void Serializable::SaveText(std::ostream &os, const char *name)
//{
//    boost::archive::polymorphic_oarchive *xoa = new boost::archive::polymorphic_text_oarchive(os);
//    this->Save(*xoa);
//    delete xoa;
//}

//void Serializable::LoadText(std::istream &is, const char *name)
//{
//    boost::archive::polymorphic_iarchive *xia = new boost::archive::polymorphic_text_iarchive(is);
//    this->Load(*xia,this);
//    delete xia;
//}

//void Serializable::SaveBin(std::ostream &os, const char *name)
//{
//    boost::archive::polymorphic_oarchive *xoa = new boost::archive::polymorphic_binary_oarchive(os);
//    this->Save(*xoa);
//    delete xoa;
//}

//void Serializable::LoadBin(std::istream &is, const char *name)
//{
//    boost::archive::polymorphic_iarchive *xia = new boost::archive::polymorphic_binary_iarchive(is);
//    Serializable::Load(*xia,this);
//    delete xia;
//}


//void Serializable::Save(boost::archive::polymorphic_oarchive &ar, Serializable *ob)
//{
//    ar << boost::serialization::make_nvp("Object",ob);
//}

//void Serializable::Load(boost::archive::polymorphic_iarchive &ar, Serializable *ob)
//{
//    ar >> boost::serialization::make_nvp("Object",ob);
//}


