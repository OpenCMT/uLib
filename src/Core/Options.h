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



#ifndef U_CORE_OPTIONS_H
#define U_CORE_OPTIONS_H

#include <boost/program_options.hpp>

namespace uLib {

namespace detail {

struct Options {

    /**
     * Wrapper for boost program_options easy init syntax
     */
    class options_description_easy_init  {
        typedef boost::program_options::options_description_easy_init InitClass;
        InitClass m_init;
    public:
        options_description_easy_init(InitClass init) :
            m_init(init) {}


        options_description_easy_init&
        operator()(const char* name,
                   const char* description)
        {
            m_init(name,description);
            return *this;
        }

        options_description_easy_init&
        operator()(const char* name,
                   const boost::program_options::value_semantic* s)
        {
            m_init(name,s);
            return *this;
        }


        options_description_easy_init&
        operator()(const char* name,
                   const boost::program_options::value_semantic* s,
                   const char* description)
        {
            m_init(name,s,description);
            return *this;
        }


        template <typename T>
        options_description_easy_init&
        operator()(const char* name,
                   T * value,
                   const T default_value,
                   const char* description)
        {
            m_init(name,
                   boost::program_options::value<T>(value)->default_value(default_value),
                   description);
            return *this;
        }

        template <typename T>
        options_description_easy_init&
        operator()(const char* name,
                   T * value,
                   const char* description)
        {
            assert(value);
            m_init(name,
                   boost::program_options::value<T>(value)->default_value(*value),
                   description);
            return *this;
        }

        template <typename T>
        options_description_easy_init&
        operator()(const char* name,
                   T * value,
                   const T default_value)
        {
            m_init(name,
                   boost::program_options::value<T>(value)->default_value(default_value));
            return *this;
        }

        template <typename T>
        options_description_easy_init&
        operator()(const char* name,
                   T * value)
        {
            assert(value);
            m_init(name,
                   boost::program_options::value<T>(value)->default_value(*value));
            return *this;
        }

    };

}; // Options

} // detail



class Options {
    boost::program_options::options_description m_global;
    boost::program_options::options_description m_configuration;
    boost::program_options::positional_options_description m_posdesc;
    boost::program_options::variables_map m_vm;

public:
    typedef detail::Options::options_description_easy_init initType;

    Options(const char *str = "Program options");

    initType add_options() {        
        return initType(m_global.add_options());
    }

    initType add_config_options() {
        return initType(m_configuration.add_options());
    }

    void add_positional_option(const char *name, int max_count) {
        // TODO:
        //        m_posdesc(name,max_count);
    }

    void parse_command_line(int argc, char *argv[]);

    void parse_config_file(std::string &str);

    void parse_config_file(const char *fname);

    template <typename T>
    static inline boost::program_options::typed_value<T>* value(T *v, T dvalue) {
        boost::program_options::typed_value<T> *r = boost::program_options::value<T>(v);
        r->default_value(dvalue);
        return r;
    }

    bool count(const char *str) const;

};


} // uLib



#endif // U_CORE_OPTIONS_H
