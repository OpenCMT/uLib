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




#include <typeinfo>
#include <fstream>

#include "boost/archive/xml_oarchive.hpp"
#include "boost/archive/polymorphic_xml_oarchive.hpp"
#include "boost/archive/polymorphic_xml_iarchive.hpp"
#include "boost/archive/polymorphic_text_oarchive.hpp"
#include "boost/archive/polymorphic_text_iarchive.hpp"

#include "boost/serialization/export.hpp"

#include "Ob.h"
#include "Ob1.h"

#include "boost/archive/detail/basic_pointer_oserializer.hpp"





//template class boost::archive::detail::archive_serializer_map<boost::archive::polymorphic_xml_oarchive>;

int main(int /*argc*/, char* /*argv*/[])
{
    D d;
    A *a = &d;
    a->i = 5552368;

    A *la = NULL;

    D *dla = NULL;

    {
        std::ofstream file;
        file.open("test.xml");
        boost::archive::polymorphic_xml_oarchive oa_implementation(file,0);
        boost::archive::polymorphic_oarchive & opa = oa_implementation;
        opa << BOOST_SERIALIZATION_NVP(a);
        a->Save(opa);
        file.close();
    }

    {
        std::ifstream file;
        file.open("test.xml");
        boost::archive::polymorphic_xml_iarchive ia_implementation(file,0);
        boost::archive::polymorphic_iarchive & ipa = ia_implementation;
        ipa >> BOOST_SERIALIZATION_NVP(la);
        ipa >> BOOST_SERIALIZATION_NVP(dla);
        file.close();
    }

    boost::archive::polymorphic_xml_oarchive xoa(std::cout);
    dla->Save(xoa);



}

























