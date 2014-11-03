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





#ifndef OB_H
#define OB_H

#include <fstream>
#include <ostream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/signals2/signal.hpp>

#include <Core/Object.h>

#include "testing-prototype.h"






#include "Core/Vector.h"
#include "Core/Uuid.h"

#include "boost/typeof/typeof.hpp"
#include <boost/serialization/binary_object.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/name_generator.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>


#include <boost/serialization/extended_type_info_typeid.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Mock of serializable object system //

#define default(vlaue)
#define slots
#define signals public
#define emit
# define SLOT(a)     a
# define SIGNAL(a)   a





namespace uLib {









////////////////////////////////////////////////////////////////////////////////
//// OB  ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Ob {

public:

    Ob();
    ~Ob() {
        if(m_p) delete m_p;
    }

    //// init //////////////////////////////////////////////////////////////////
    template <class T>
    void init(){
        if(!m_type_id) {
            m_p = (Parameters *) new typename T::Parameters;
            m_type_id = TypeRegister::Controller()->AddType< T >();
        }
    }

    virtual void PrintSelf(std::ostream &o) const { o << "Base Object PrintSelf\n"; }

protected:
    // parameters //////////////////////////////////////////////////////////////
    struct Parameters { friend class boost::serialization::access; };
    inline Parameters &p() { assert(m_p); return *m_p; }
    inline const Parameters &p() const { assert(m_p); return *m_p; }
    virtual void init() {}


    // serialization access ////////////////////////////////////////////////////
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        //        ar & boost::serialization::make_nvp("instance_size", m_type_id->size);
        //        ar & boost::serialization::make_nvp("instance_data",boost::serialization::make_binary_object(this,m_type_id->size));
    }

    template <class Archive>
    static void serialize(Archive &ar, Ob &ob, const unsigned int version) {}

    template <class Archive>
    static void serialize(Archive &ar, Ob::Parameters &p, const unsigned int version) {}


public:

    TypeRegister::Entry * type_id() const { return m_type_id; }

private:

    // members /////////////////////////////////////////////////////////////////
    struct Parameters *m_p;
    struct Signals    *m_s;

    friend class ObPrivate;
    class ObPrivate   *d;

    TypeRegister::Entry * m_type_id;
};









}

////////////////////////////////////////////////////////////////////////////////





BOOST_CLASS_EXPORT_KEY(uLib::Ob)







#endif
