//----------------------------------------------------------
// Class : CastorSkinHit 
// Date: October 2020
// Author: Germano Bonomi   germano.bonomi@unibs.it
//----------------------------------------------------------

#include <iostream>

#include "muCastorSkinHit.h"

/// \cond CLASSIMP
ClassImp(muCastorSkinHit)
/// \endcond

using namespace std;

//_____________________________________________________________________________
muCastorSkinHit::muCastorSkinHit() :
    fDetID(-1),
    fPdgCode(-1),
    fMotherID(-1),
    fMomX(0.),
    fMomY(0.),
    fMomZ(0.),
    fPosX(0.),
    fPosY(0.),
    fPosZ(0.)
{}

//_____________________________________________________________________________
muCastorSkinHit::~muCastorSkinHit() 
{}
//_____________________________________________________________________________
void muCastorSkinHit::Print(const Option_t* /*opt*/) const
{
    cout << "  detID: " << fDetID 
         << "  position (cm): (" 
         << fPosX << ", " << fPosY << ", " << fPosZ << ")"
         << "  momentum (MeV/c): (" 
         << fMomX << ", " << fMomY << ", " << fMomZ << ")"
         << endl;
}

