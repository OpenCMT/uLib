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



#ifndef U_CORE_UUID_H
#define U_CORE_UUID_H

#include <iostream>
#include <vector>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/name_generator.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "Core/Mpl.h"
#include "Core/Object.h"


namespace uLib {



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Object Registration //


typedef boost::uuids::uuid uuid_t;

extern uuid_t uLib_dns_uuid;

template < typename T >
class type_id : public boost::uuids::uuid {
public:
    type_id() :
        m_size(sizeof(T)),
        uuid(boost::uuids::name_generator(uLib_dns_uuid)(typeid(T).name()))
    {
        std::cout << "Request for register new type\n" <<
                     "name: " << typeid(T).name() << "\n" <<
                     "uuid: " << to_string(*this) << "\n";
    }

    explicit type_id(boost::uuids::uuid const& u)
            : boost::uuids::uuid(u) {}

    operator boost::uuids::uuid() {
        return static_cast<boost::uuids::uuid&>(*this);
    }

    operator boost::uuids::uuid() const {
        return static_cast<boost::uuids::uuid const&>(*this);
    }

    unsigned int size() const { return m_size; }

private:
    unsigned int m_size;
};




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// TYPE REGISTER //

namespace detail {

class TypeRegister {
    typedef boost::uuids::name_generator IDGen_t;
public:
    struct RegisterEntry {
        uuid_t id;
        int size;
    };

    TypeRegister(uuid_t const &dns) :
        gen(dns) {}


    template< typename T >
    RegisterEntry * AddType(T *t = NULL) {
        RegisterEntry en = { gen(typeid(T).name()), sizeof(T) };
        for(int i=0; i < m_registry.size(); ++i)
            if(en.id == m_registry[i].id) return &(m_registry[i]);
        m_registry.push_back(en);
        return &m_registry.back();
    }

    void PrintSelf(std::ostream &o) {
        std::cout << "RegisterController: \n";
        for (int i=0; i<m_registry.size(); ++i)
            o << "type [" << i << "]: "
              << to_string(m_registry[i].id) << " "
              << m_registry[i].size << "\n";
        o << "\n";
    }



private:
    IDGen_t gen;
    std::vector<RegisterEntry> m_registry;

};

} // detail




class TypeRegister : public detail::TypeRegister {
public:
    typedef detail::TypeRegister                BaseClass;
    typedef detail::TypeRegister::RegisterEntry Entry;

    static TypeRegister* Controller();

private:
    TypeRegister();                  // Blocks constructor
    static TypeRegister *s_Instance; // Singleton instance
};




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// OBJECT REGISTER //



} // uLib

#endif // UUID_H
