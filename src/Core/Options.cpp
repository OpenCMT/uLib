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
#include "Core/Options.h"

#include <boost/program_options.hpp>


//class boost::program_options::error_with_option_name;
//template<> boost::program_options::typed_value<int> boost::program_options::value<int>();
//template<> boost::program_options::typed_value<int> boost::program_options::value<int>(int *);


namespace uLib {

Options::Options(const char *str) :
    m_global(str),
    m_configuration("Configuration")
{}

void Options::parse_command_line(int argc, char *argv[]) {
    boost::program_options::store(boost::program_options::parse_command_line(argc,argv,m_global),m_vm);
    boost::program_options::notify(m_vm);

    if(m_vm.count("help")) {
        std::cout << "\n" << m_global << "\n";
        if(m_configuration.options().size()) {
            std::cout << "\n" << m_configuration << "\n\n";
        }
        exit(1);
    }
}

void Options::parse_config_file(std::string &str)
{
    this->parse_config_file(str.c_str());
}

void Options::parse_config_file(const char *fname)
{
    std::ifstream is;
    is.open(fname);
    boost::program_options::options_description fileopt;
    fileopt.add(m_global).add(m_configuration);
    if(is.is_open()) {
        boost::program_options::store(boost::program_options::parse_config_file(is,fileopt,true),m_vm);
        boost::program_options::notify(m_vm);
    }
}

bool Options::count(const char *str) const
{
    return (m_vm.count(str));
}


} // uLib




