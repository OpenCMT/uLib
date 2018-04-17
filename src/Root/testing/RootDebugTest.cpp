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




#include <TApplication.h>
#include <TTree.h>
#include <TFile.h>
#include <TBrowser.h>
#include <TString.h>
#include <TText.h>
#include <TPave.h>

#include "Root/TestTObject.h"
#include "Root/RootMuonScatter.h"

#include "Detectors/MuonScatter.h"

TTree * getTree(TFile *m_File, const char *path, const char *name) {
    std::string p = std::string("/") + std::string(path);
    TDirectory *dir = m_File->GetDirectory(p.c_str());
    if(!dir) {
        m_File->mkdir(path);
    }
    m_File->cd(path);
    std::string n = p + std::string("/") + std::string(name);
    TObject *obj = m_File->Get(n.c_str());
    if(!obj) {
        TTree *tree = new TTree();
        tree->SetName(name);
        return tree;
    }
    else {
        return (TTree *)obj;
    }
}


int main(int argc,char **argv) {

    uLib::MuonScatter u_mu;
    ROOT::Mutom::MuonScatter mu;

    TFile *file = new TFile("test_file.root","RECREATE");
    TTree *tree = new TTree("test","Testing MuonScatter dump...");

    tree->Branch("mu",&mu);

//    mu.in.X = 1;
//    mu.in.Y = 2;
//    mu.in.Z = 3;
//    mu.in.dirX = 4;
//    mu.in.dirY = 5;
//    mu.in.dirZ = 6;
//    mu.in.p = 555;
//    mu.out.p = 2368;

    u_mu.LineIn().origin << 3,3,3;
    u_mu.LineIn().direction << 5,5,5;
    u_mu.LineOut().origin << 1,2,3;
    u_mu.LineOut().direction << 4,5,6;
    u_mu.SetMomentum(555);
    u_mu.SetMomentumPrime(2368);

    mu << u_mu;

    tree->Fill();

    file->cd();
    tree->Write();

    gApplication = new TApplication("Application", &argc, argv);
    TBrowser *tbr = new TBrowser("test");
    tbr->Show();
    gApplication->Run();

    return 0;
}
