#include "SkinDetectorWriter.h"
#include "muCastorSkinHit.h"
#include "TVector3.h"

SkinDetectorWriter::SkinDetectorWriter(string filename) :
    t_file(nullptr),
    t_tree(nullptr),
    t_buffer(nullptr),
    i_status(0)
{
    t_file = new TFile(filename.c_str(), "RECREATE");
    t_tree = new TTree("muCastorMC", "muCastorMC");
    t_buffer = new TClonesArray("muCastorSkinHit");

    t_tree->Branch("CastorSkinHits", "TClonesArray", t_buffer, 32000, 99);

    if (t_file->IsZombie()) i_status = 1;
}

SkinDetectorWriter::~SkinDetectorWriter()
{}

void SkinDetectorWriter::add(int detID, float p_x, float p_y, float p_z,
                             float m_x, float m_y, float m_z)
{
    TClonesArray& ref = *t_buffer;
    int size = ref.GetEntriesFast();

    muCastorSkinHit* new_hit = new(ref[size]) muCastorSkinHit();
    new_hit->SetDetID(detID);
    new_hit->SetPdgCode(13);
    new_hit->SetMotherID(-1);
    new_hit->SetPos (TVector3(p_x, p_y, p_z));
    new_hit->SetMom (TVector3(m_x, m_y, m_z));
}

void SkinDetectorWriter::write()
{
    if (t_tree->Fill() < 0) i_status = 2;
    t_buffer->Delete();   // or t_buffer->Clear() ??
}

void SkinDetectorWriter::close()
{
    if (t_tree->Write() == 0) i_status = 3;
    t_file->Close();
}