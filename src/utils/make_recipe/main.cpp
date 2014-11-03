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



#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

#include "Core/Options.h"


using namespace uLib;

extern "C" {
extern char _binary_recipe_tar_gz_start;
extern char _binary_recipe_tar_gz_end;
extern char _binary_cmake_tar_gz_start;
extern char _binary_cmake_tar_gz_end;
}


namespace {
static struct Parameters : Options
{
    std::string project;
    Parameters(const char *hello = "Program options") : Options(hello) {
        add_options()
                ("help,h", "printout help")
                // GENERAL //
                ("project,p",      &project,     std::string(),    "name of project")
                ("cmake,k",        "cmake recipe project")
                ("cmake-modules,K",  "only builds cmake modules directory")
                ("libs",   "get mutom linker flags")
                ("cflags", "get compiler flags")
                ;
    }
} p;
} // namespace


static std::string system_pipe(std::string cmd) {
    FILE *pipe = popen(cmd.c_str(),"r");
    if(pipe) {
        std::stringstream ss;
        int c = fgetc (pipe);
        while (c != EOF) {
            if(c != '\n') ss << (char)c;
            c = fgetc (pipe);
        }
        return ss.str();
    }
    else return std::string("");
}





int main(int argc, char *argv[])
{
    p.parse_command_line(argc,argv);

    if(p.project != "") {
        char dir[300];
        sprintf(dir,"mkdir %s",p.project.c_str());
        system(dir);
        chdir(p.project.c_str());
    }

    if(p.count("cmake") || p.count("cmake-modules")) {
        std::ofstream file;
        file.open("_cmake.tar.gz", std::ios::out | std::ios::binary );
        char*  ptr = &_binary_cmake_tar_gz_start;
        while ( ptr != &_binary_cmake_tar_gz_end )
            file << *ptr++;
        file.close();

        std::cout << "Deploing CMake files .... \n";
        system("tar -zxvf _cmake.tar.gz");
        system("rm _cmake.tar.gz");
        std::cout << "done ... \n";
    }

    if(p.count("cmake")) {
        std::ofstream file;
        file.open("_recipe.tar.gz", std::ios::out | std::ios::binary );
        char*  ptr = &_binary_recipe_tar_gz_start;
        while ( ptr != &_binary_recipe_tar_gz_end )
            file << *ptr++;
        file.close();

        std::cout << "Deploing recipe files .... \n";
        system("tar -zxvf _recipe.tar.gz");
        system("rm _recipe.tar.gz");
        std::cout << "done ... \n";
    }

    if(p.count("cflags")) {
        std::cout
                << system_pipe("cmake --find-package -DCMAKE_PREFIX_PATH=/usr/local/lib/cmake/mutom-0.2 -DNAME=uLib -DLANGUAGE=C -DCOMPILER_ID=GNU -DMODE=COMPILE")
                << system_pipe("cmake --find-package -DCMAKE_PREFIX_PATH=/usr/local/lib/cmake/mutom-0.2 -DNAME=IB -DLANGUAGE=C -DCOMPILER_ID=GNU -DMODE=COMPILE");
    }

    if(p.count("libs")) {
        std::cout
                << system_pipe("cmake --find-package -DCMAKE_PREFIX_PATH=/usr/local/lib/cmake/mutom-0.2 -DNAME=uLib -DLANGUAGE=C -DCOMPILER_ID=GNU -DMODE=LINK")
                << system_pipe("cmake --find-package -DCMAKE_PREFIX_PATH=/usr/local/lib/cmake/mutom-0.2 -DNAME=IB -DLANGUAGE=C -DCOMPILER_ID=GNU -DMODE=LINK");
    }

    return 0;
}

