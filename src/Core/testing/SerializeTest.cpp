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

#include "Core/Object.h"
#include "Core/Archives.h"
#include "ParticlePhysics/MuonTomography/MuonScatter.h"

#include "testing-prototype.h"

using namespace uLib;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// MANUAL SERIALIZATION //

struct V3f {

    float x,y,z;
    V3f()
    { x = y = z =0; }

    V3f(float x, float y, float z) :
        x(x), y(y), z(z) {}

    template <class Archive>
    void serialize (Archive &ar,unsigned int v) {
        ar
                & "<" & NVP(x) & NVP(y) & NVP(z) & ">";
    }
};

ULIB_CLASS_EXPORT_KEY(V3f);
ULIB_CLASS_EXPORT_IMPLEMENT(V3f);


inline std::ostream &
operator <<(std::ostream &o, const V3f &v) {
    Archive::hrt_oarchive(o) << v;
    return o;
}

inline std::istream &
operator >>(std::istream &is, V3f &v) {
    Archive::hrt_iarchive(is) >> v;
    return is;
}




int test_V3f() {
    // testing human readble archive with simple serializable structure //

    V3f v1(1,2,3),v2,v3,v4;
    std::cout << "v    --> " << v1 << "\n";

    std::stringstream ss; ss << v1;
    std::cout << "ss.v --> " << ss.str() << "\n";

    Archive::hrt_iarchive ar(ss); ar >> v2;
    std::cout << "v2   --> " << v2 << "\n";

    std::stringstream("<2 3 4>") >> v3;
    std::cout << "v3   --> " << v3 << "\n";

    //    std::cout << "insert V3f string to parse: "; std::cin >> v4;
    //    std::cout << "v4   --> " << v4 << "\n";
    return (1);
}





////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// OBJECT SERIALIZATION //

class A : public virtual Object {
    uLibTypeMacro(A,Object)
    ULIB_SERIALIZE_ACCESS
public:
    A() : m_a(5552368) {}

    properties() {
        std::string p_a;
    };

    uLibRefMacro (a,int);
private:
    int m_a;
};

void A::init_properties() {
    $_init();
    $$.p_a = "A property string";
}

ULIB_SERIALIZABLE_OBJECT(A)
ULIB_SERIALIZE_OBJECT(A,Object) {
    ar
            & "Object A : "
            & "--> m_a = " & AR(m_a)
            & "\n";
}

ULIB_SERIALIZE_OBJECT_PROPS(A) {
    ar
            & "Object A properties: "
            & "---> p_a = " & AR(p_a) & "\n";
}



int testing_xml_class() {

    A a; a.init_properties();

    {
        std::ofstream file("test.xml");
        Archive::xml_oarchive(file) << NVP(a);
    }
    a.a() = 0;
    a.$$.p_a = "zero string";
    {
        std::ifstream file("test.xml");
        Archive::xml_iarchive(file) >> NVP(a);
    }

    Archive::xml_oarchive(std::cout) << NVP(a);
    return ( a.a() == 5552368 && a.$$.p_a == "A property string" );
}

int testing_hrt_class() {

    A a; a.init_properties();

    {
        std::ofstream file("test.xml");
        Archive::hrt_oarchive(file) << NVP(a);
    }
    a.a() = 0;
    a.$$.p_a = "zero string";
    {
        // ERRORE FIX !
        //        std::ifstream file("test.xml");
        //        Archive::hrt_iarchive(file) >> NVP(a);
    }

    Archive::hrt_oarchive(std::cout) << NVP(a);
    return ( a.a() == 5552368 && a.$$.p_a == "A property string" );
}






////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// MUON SCATTER EXAMPLE //

int testing_mu()
{     
     std::stringstream ss;

     MuonScatter mu;
     mu.SetMomentumIn(555);
     mu.SetMomentumOut(2368);
     {
         std::ofstream file("test.txt");
         file << mu;
     }

     mu.SetMomentumIn(0);
     mu.SetMomentumOut(0);
     {
         std::ifstream file("test.txt");
         file >> mu;
     }

     std::cout << mu << "\n";


}






int main() {
    BEGIN_TESTING(Serialize Test);

    TEST1( test_V3f() );
    TEST1( testing_xml_class() );
    //    testing_hrt_class(); ///// << ERRORE in HRT with properties
    TEST1( testing_mu() );

    END_TESTING;
}













