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

#include "testing-prototype.h"
#include "Core/Debug.h"

#include <boost/any.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/include/sequence.hpp>

#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/include/push_back.hpp>


#include <Rtypes.h>
#include <TFile.h>
#include <TObject.h>
#include <TTree.h>
#include <TApplication.h>
#include <TBrowser.h>

using namespace uLib;



class DebugAdapterTTree : public detail::DebugAdapterInterface {
    TTree *m_tree;
public:

    DebugAdapterTTree(const char *name) : m_tree(new TTree(name,name)) {}
    ~DebugAdapterTTree() { delete m_tree; }

    void operator()(int val) {
        std::cout << "debugger 2 prints: " << val << "\n";
    }
};




int main(int argc, char **argv)
{

    {
        Debug debug;
        DebugAdapterText adapter(std::cout);
        DebugAdapterTTree treead("test");

        debug.AddAdapter(adapter);
        debug.AddAdapter(treead);

        int a = 5552368;
        debug("a",a);

        std::string str = "ciao";
        debug("str",str);

        debug.Update();
    }


    // TestTObject *test = new TestTObject;


    TFile *file = new TFile("test_file.root","RECREATE");
    file->cd();
    TTree *tree = new TTree;
//    tree->Branch("test",&test);

//    for(int i=0;i<10;++i) {
//        test->a = i;
//        test->b = -i;
//        tree->Fill();
//    }
    tree->Write();

    gApplication = new TApplication("My ROOT Application", &argc, argv);
    TBrowser *tbr = new TBrowser("test");
    tbr->Show();


    gApplication->Run();

    return 0;
}





