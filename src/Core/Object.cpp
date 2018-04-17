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





#include "config.h"

#include "Object.h"
#include "Vector.h"

#include "boost/archive/polymorphic_xml_oarchive.hpp"
#include "boost/archive/polymorphic_xml_iarchive.hpp"
#include "boost/archive/polymorphic_text_oarchive.hpp"
#include "boost/archive/polymorphic_text_iarchive.hpp"
#include "boost/archive/polymorphic_binary_oarchive.hpp"
#include "boost/archive/polymorphic_binary_iarchive.hpp"



namespace uLib {


const char *Version::PackageName   = PACKAGE_NAME;
const char *Version::VersionNumber = PACKAGE_VERSION;
const char *Version::Release       = "x"; //SVN_REVISION;


////////////////////////////////////////////////////////////////////////////////
// Object Private //

class ObjectPrivate {
public:

    struct Signal {
        GenericMFPtr  sigptr;
        std::string   sigstr;
        SignalBase   *signal;
    };

    struct Slot {
        GenericMFPtr sloptr;
        std::string  slostr;
    };


    Vector<Signal> sigv;
    Vector<Slot>   slov;
};




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// OBJECT IMPLEMENTATION



Object::Object() :
    d(new ObjectPrivate)
{}

Object::Object(const Object &copy) :
    ObjectPropable(copy),
    d(new ObjectPrivate(*copy.d))
{}

Object::~Object() {
    delete d;
}

void Object::DeepCopy(const Object &copy)
{
    // should lock to be tread safe //
    memcpy(d,copy.d,sizeof(ObjectPrivate));
    // ERROR! does not copy parameters ...                                      <<<< FIXXXXX
}





void Object::SaveXml(std::ostream &os, Object &ob)
{
    Archive::xml_oarchive ar(os);
    ar << boost::serialization::make_nvp("Object",ob);
}

void Object::LoadXml(std::istream &is, Object &ob)
{
    Archive::xml_iarchive ar(is);
    ar >> boost::serialization::make_nvp("Object",ob);
}


// FINIRE
void Object::SaveConfig(std::ostream &os, int version)
{   
    Archive::xml_oarchive ar(os);
    ObjectPropable::serialize(ar,0);
}

void Object::LoadConfig(std::istream &is, int version)
{
    if(!props()) this->init_properties();
    Archive::xml_iarchive ar(is);
    ObjectPropable::serialize(ar,0);
}





void Object::PrintSelf(std::ostream &o) const
{
    o << "OBJECT signals: ------------------\n";
    Vector<ObjectPrivate::Signal>::Iterator itr;
    for(itr = d->sigv.begin(); itr<d->sigv.end(); itr++)
    {
        o << "  signal:[ " << itr->sigstr << " ]\n";
    }
    o << "--------------------------------------\n\n";
}


bool Object::addSignalImpl(SignalBase *sig, GenericMFPtr fptr, const char *name)
{
    ObjectPrivate::Signal s = {fptr,std::string(name),sig};
    d->sigv.push_back(s);
}

bool Object::addSlotImpl(GenericMFPtr fptr, const char *name)
{
    ObjectPrivate::Slot s = {fptr,std::string(name)};
    d->slov.push_back(s);
}

SignalBase *Object::findSignalImpl(const GenericMFPtr &fptr) const
{
    for(int i=0; i<d->sigv.size(); ++i)
    {
        if(d->sigv[i].sigptr == fptr)
            return d->sigv[i].signal;
    }
    return NULL;
}

SignalBase *Object::findSignalImpl(const char *name) const
{
    std::string in(name);
    for(int i=0; i<d->sigv.size(); ++i)
    {
        if(d->sigv[i].sigstr == in)
            return d->sigv[i].signal;
    }
    return NULL;
}

GenericMFPtr *Object::findSlotImpl(const char *name) const
{
    std::string in(name);
    for(int i=0; i<d->slov.size(); ++i)
    {
        if(d->slov[i].slostr == in)
            return &d->slov[i].sloptr;
    }
    return NULL;
}




// std::ostream &
// operator << (std::ostream &os, uLib::Object &ob)
// {
//     uLib::Object *op = &ob;
//     uLib::Archive::hrt_oarchive (os) << op;
//     return os;
// }

// std::ostream &
// operator << (std::ostream &os, uLib::Object *ob)
// {
//     uLib::Archive::hrt_oarchive(os) << ob;
//     return os;
// }

// std::istream &
// operator >> (std::istream &is, uLib::Object &ob)
// {
// //    uLib::Object *op = &ob;
//     uLib::Archive::hrt_iarchive(is) >> ob;
//     return is;
// }




} // uLib



