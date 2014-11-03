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




#ifndef OB2_H
#define OB2_H


#include "Ob.h"
#include "Ob1.h"

////////////////////////////////////////////////////////////////////////////////
//  OB2  ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace uLib {

class Ob2 : public Ob1 {
public:
    typedef Ob1 BaseClass;

    struct Parameters : public BaseClass::Parameters {
        int c default(3),d default(4);
    };

    Ob2() {
        serializzable_member = 0;
        memset(non_serializable_member,0,sizeof(char[250]));
    }

    virtual ~Ob2() {}

    // created by macro ////////////////////////////////////////////
    void init();
    inline Parameters &p() { return (Parameters &)Ob::p(); }
    inline const Parameters &p() const { return (Parameters &)Ob::p(); }
    static Ob2 *New() { Ob2 *o = new Ob2; o->init(); return o; }

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version);
    template <class Archive>
    static void serialize(Archive & ar, Parameters & p, const unsigned int version );
    template <class Archive>
    static void serialize(Archive &ar, Ob2 &o, const unsigned int version );

    ////////////////////////////////////////////////////////////////

    virtual void PrintSelf(std::ostream &o) const { o << "Object Ob2 PrintSelf\n"; }

    int  serializzable_member;
    char non_serializable_member[250];
private:

};



template <class Archive>
void serialize(Archive &ar, Ob2::Parameters &p, const unsigned int version )
{
    Ob2::serialize<Archive>(ar,p,version);
}



template<class Archive>
void Ob2::serialize(Archive & ar, const unsigned int version)
{
//    boost::serialization::split_member(ar, *this, version);
    ar & boost::serialization::make_nvp("parameters",p());
    this->serialize<Archive>(ar,*this,version);
    Ob::serialize(ar,version);
}






template <class Archive>
void Ob2::serialize(Archive &ar, Parameters &p, const unsigned int version)
{
    Ob2::BaseClass::serialize<Archive>( ar,p,version );
    ar & boost::serialization::make_nvp("c",p.c);
    ar & boost::serialization::make_nvp("d",p.d);
}

template <class Archive>
void Ob2::serialize(Archive &ar, Ob2 &o, const unsigned int version )
{
    Ob2::BaseClass::serialize<Archive>(ar,o,version);
    ar & boost::serialization::make_nvp("serializzable_member",o.serializzable_member);
    // other members //
}





}


BOOST_CLASS_EXPORT_KEY(uLib::Ob2)          // use this in header
//BOOST_SERIALIZATION_FACTORY_0(uLib::Ob2) // use this for plugin construction





#endif
