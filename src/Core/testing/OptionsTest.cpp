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
#include "Core/Options.h"
#include "testing-prototype.h"


using namespace uLib;




int main(int argc, char **argv)
{
    BEGIN_TESTING(Boost ProgramOptions);


    std::string optfile("configuration.ini");
    int a = 0;
    int b = 0;
    Options opt;

    opt.add_options()
            ("help", "printout help")
            ("value",&a,"value")
            ("config",&optfile,"config_file");

    opt.add_config_options()
            ("B.value",&b,"b vlaue");

    opt.parse_command_line(argc,argv);
    opt.parse_config_file(optfile.c_str());

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";


    END_TESTING;
}


