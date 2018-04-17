
#include <TApplication.h>
#include <TObject.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <TClonesArray.h>

#include <TBrowser.h>
#include <TString.h>
#include <TText.h>
#include <TPave.h>


#include "Root/TestTObject.h"
#include "Root/RootMuonScatter.h"

#include "Detectors/MuonScatter.h"

#include "Root/muBlastMCTrack.h"


int main(int argc,char **argv) {

    TFile *file = new TFile(argv[1]);
    TTree *tree = (TTree*) file->Get("muBlastMC");
    if (tree->IsZombie()) {
        std::cerr << "Zombie tree\n";
        exit(1);
    }

    TClonesArray   * track_array = NULL;
    tree->GetBranch("muBlastMCTrack")->SetAutoDelete(kFALSE);
    tree->SetBranchAddress("muBlastMCTrack",&track_array);

    for(int i=0; i<tree->GetEntries(); ++i) {
        tree->GetEntry(i);
        int trn = track_array->GetEntriesFast();
        std::cout << "---- EV " << i << " : " << trn << " tracks ----------\n";
        for(int j=0; j<trn; ++j) {
            /*ROOT::Mutom::*/muBlastMCTrack * track = (/*ROOT::Mutom::*/muBlastMCTrack *) track_array->At(j);
            if(abs(track->fPdgCode) == 13)
                track->Dump();
        }
    }
    return 0;
}
