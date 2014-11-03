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




#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/signals2/signal.hpp>



#include "Ob.h"
#include "Ob1.h"
#include "Ob2.h"


using namespace uLib;


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//// test boost ETI system //

// used in external plugin construction mechanism //
int test_boost_eti () {

    boost::serialization::extended_type_info_typeid<Ob2> i_eti;

    std::cout << "int eti guid key: " << i_eti.get_key() << "\n";

    Ob2 *test = (Ob2*)i_eti.construct(0);
    test->init();

    std::cout << "int eti typeid name: " << i_eti.get_typeid().name() << "\n";

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// main //






int main()
{

//    ////////////////////////////////////////////////////
//    // serialization tests
{
    Ob1 ob1;
    ob1.init();
    std::cout << "ob1 param: " <<
                 ob1.p().a << " " <<
                 ob1.p().b << "\n";



    Ob2 *ob2 = Ob2::New();
    std::cout << "ob2 param: " <<
                 ob2->p().a << " " <<
                 ob2->p().b << " " <<
                 ob2->p().c << " " <<
                 ob2->p().d << "\n";
    std::cout << "ob2 uuid: " <<
                 to_string(ob2->type_id()->id) << "\n";


//    // serialize ob2 to file //
//    {
//        std::ofstream ofs("_BoostTest.xml");
//        boost::archive::xml_oarchive oa(ofs);
//        oa << BOOST_SERIALIZATION_NVP(ob2);
//    }

     // serialize ob2 to file via objact base cast //
    {
        Ob *ob = Ob2::New();
        sprintf(static_cast<Ob2 *>(ob)->non_serializable_member,
                "deserializzati dati interni attraverso dump binario");
        std::ofstream ofs("_BoostTest.xml");
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(ob);
    }


//    delete ob2;

    // deserialize ob2 from file //
    {
        Ob2 *newob2 = Ob2::New();
        newob2->p().c = 0;
        std::ifstream ifs("_BoostTest.xml");
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(*newob2);
        printf("%s\n",newob2->non_serializable_member);
        std::cout << "deserialized ob2: > " <<
                     newob2->p().a << " " <<
                     newob2->p().b << " " <<
                     newob2->p().c << " " <<
                     newob2->p().d << "\n";
        std::cout << "deserialized ob2 member: " <<
                     "serializable_member = " << newob2->serializzable_member << "\n";
        std::cout << "deserialized ob2 uuid: " <<
                     to_string(newob2->type_id()->id) << "\n";
    }

}







}

























