#ifndef SkinDetectorWriter_h
#define SkinDetectorWriter_h

#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"

using std::string;

class SkinDetectorWriter
{
public:
    SkinDetectorWriter(string filename);
    virtual ~SkinDetectorWriter();

    void add(int detID, float p_x, float p_y, float p_z, float m_x, float m_y, float m_z);
    int status() { return i_status; }
    void write();
    void close();

private:
    TFile* t_file;
    TTree* t_tree;
    TClonesArray* t_buffer;
    int i_status;
};



#endif //SkinDetectorWriter_h