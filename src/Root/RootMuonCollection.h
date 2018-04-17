#ifndef ROOTMUONCOLLECTION_H
#define ROOTMUONCOLLECTION_H

#include "RootMuonScatter.h"

namespace ROOT {
namespace Mutom {

class RootMuoncollection
{
public:
    RootMuoncollection();
    void addMuon(MuonScatter & mu);

};


} // Mutom
} // ROOT


#endif // ROOTMUONCOLLECTION_H
