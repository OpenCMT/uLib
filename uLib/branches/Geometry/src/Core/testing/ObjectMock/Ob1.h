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



#ifndef OB1_H
#define OB1_H

#include <string>
#include "Ob.h"


////////////////////////////////////////////////////////////////////////////////
//  OB1  ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace uLib {

class Ob1 : public Ob {
public:

    typedef Ob BaseClass;
    struct Parameters : public BaseClass::Parameters {
        int a default(1);
        int b default(2);
    };
    virtual ~Ob1() {}

    // created by macro ////////////////////////////////////////////////////////
    void init();
    inline Parameters &p() { return (Parameters &)Ob::p(); }
    inline const Parameters &p() const { return (Parameters &)Ob::p(); }
    static Ob1 *New() { Ob1 *o = new Ob1; o->init(); return o; }


    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version);

    template <class Archive>
    static void serialize(Archive & ar,
                          Ob1::Parameters & p,
                          const unsigned int version );

    template <class Archive>
    static void serialize(Archive &ar,
                          Ob1 &ob,
                          const unsigned int version );
    ////////////////////////////////////////////////////////////////////////////

    virtual void PrintSelf(std::ostream &o) const { o << "Object Ob1 PrintSelf\n"; }


};

// serialize accessors in macro // ------------------------------------------ //
template <class Archive>
void serialize(Archive &ar, Ob1::Parameters &p, const unsigned int version )
{
    Ob1::serialize<Archive>(ar,p,version);
}


template<class Archive>
void Ob1::serialize(Archive & ar, const unsigned int version)
{
    ar & boost::serialization::make_nvp("parameters",p());
    this->serialize<Archive>(ar,*this,version);
    Ob::serialize(ar,version);
}
// -------------------------------------------------------------------------- //


// serialization accessor that can be made by moc //

template <class Archive>
void Ob1::serialize(Archive &ar, Ob1::Parameters &p, const unsigned int version)
{
    Ob1::BaseClass::serialize<Archive>( ar,p,version );
    ar & boost::serialization::make_nvp("a",p.a);
    ar & boost::serialization::make_nvp("b",p.b);
}

template <class Archive>
void Ob1::serialize(Archive &ar, Ob1 &ob, const unsigned int version )
{
    Ob1::BaseClass::serialize<Archive>(ar,ob,version);
    // other members to be serialized //
}




} // namespace

BOOST_CLASS_EXPORT_KEY(uLib::Ob1) // use this in header


#endif
