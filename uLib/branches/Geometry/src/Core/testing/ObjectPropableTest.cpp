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



#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>


#include "Core/Types.h"
#include "Core/Object.h"
#include "Core/ObjectProps.h"
#include "Core/StringReader.h"
#include "Math/Dense.h"

#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"


#include "testing-prototype.h"




using namespace uLib;



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// STRUCTURES //


struct A : virtual Object {

    uLibTypeMacro(A, Object)

    properties() {
        int      p_a;
        Vector3f p_3f;
    };

    int m_a;
};

void A::init_properties() {
    $_init();
    $$.p_a   = 0;
    $$.p_3f << 1,2,3;
}

ULIB_SERIALIZABLE_OBJECT(A)
ULIB_SERIALIZE_OBJECT(A, Object) { ar & AR(m_a); }
ULIB_SERIALIZE_OBJECT_PROPS(A)   { ar & AR(p_a) & AR(p_3f); }




struct B : A {
    uLibTypeMacro(B,A)

    properties() {
        std::string p;
    };

    B() : m_b(324) {}

    int m_b;
};


void B::init_properties() {
    $_init();
    $$.p = "ciao";
}

ULIB_SERIALIZABLE_OBJECT(B)
ULIB_SERIALIZE_OBJECT(B,A)     { ar & AR(m_b); }
ULIB_SERIALIZE_OBJECT_PROPS(B) { ar & AR(p);   }



struct C {
    int m_c;    
    std::string m_str;
};

ULIB_SERIALIZABLE(C)
ULIB_SERIALIZE(C) { ar & AR(m_c) & AR(m_str); }



struct D : virtual Object, B {
    uLibTypeMacro(D,Object,B)

    properties() {
        C p_c;
    };
};

void D::init_properties() {
    $_init();
    $$.p_c.m_c = 1234;
}

ULIB_SERIALIZABLE_OBJECT(D)
ULIB_SERIALIZE_OBJECT(D,Object) {}
ULIB_SERIALIZE_OBJECT_PROPS(D) {
 ar & AR(p_c);
}



class E : public C, public D {
    uLibTypeMacro(E,D,C)
public:
        E() : m_Ea(5552368) {}
        int m_Ea;
};

ULIB_SERIALIZABLE_OBJECT(E)
ULIB_SERIALIZE_OBJECT(E,C,D) {
    ar & AR(m_Ea);
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// TESTS //


int test_xml_direct() {
    // TEST ARCHIVE SAVE AND LOAD direct //
    E o; o.init_properties();
    o.$$.p_c.m_str = "works";
    {
        std::ofstream file("test.xml");
        Archive::xml_oarchive ar(file);
        ar << NVP(o);
    }
    o.$$.p_c.m_str = "hola";
    {
        std::ifstream file("test.xml");
        Archive::xml_iarchive ar(file);
        ar >> NVP(o);
    }
    std::cout << o.$$.p_c.m_str << "\n";
    return ( o.$$.p_c.m_str == "works" );
}


int test_xml_pointer() {
    // TEST ARCHIVE SAVE AND LOAD from pointer //
    E *o = new E; o->init_properties();
    o->$$.p_c.m_str = "works";
    {
        std::ofstream file("test.xml");
        Archive::xml_oarchive ar(file);
        ar << NVP(o);
    }
    o->$$.p_c.m_str = "hola";
    {
        std::ifstream file("test.xml");
        Archive::xml_iarchive ar(file);
        ar >> NVP(o);
    }
    std::cout << o->$$.p_c.m_str << "\n";
    return ( o->$$.p_c.m_str == "works" );
}


int test_xml_objsave() {
    // TEST SELF SAVE
    E o; o.init_properties();
    o.$(B).p = "works";
    {
        std::ofstream file("test.xml");
        Object::SaveXml(file,o);
    }
    o.$(B).p = "hola";
    {
        std::ifstream file("test.xml");
        Object::LoadXml(file,o);
    }

    std::cout << o.$(B).p << "\n";
    return ( o.$(B).p == "works" );
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// MAIN //

int main()
{
    BEGIN_TESTING(PropableTest);

    TEST1( test_xml_direct()  );
    TEST1( test_xml_pointer() );
    TEST1( test_xml_objsave() );

    END_TESTING;
}


