/// \file muCastorMuDetDIGI.cxx 
/// \brief Implementation of the muCastorMuDetDIGI class 
//  This class build the DIGI for the scintillator detectors 
/// \author G. Bonomi, M. Subieta - INFN

#include <iostream>

#include "muCastorMuDetDIGI.h"

/// \cond CLASSIMP
ClassImp(muCastorMuDetDIGI)
/// \endcond

using namespace std;

//_____________________________________________________________________________
muCastorMuDetDIGI::muCastorMuDetDIGI() :
    fDetID(-1),
    fLayID(-1),
    fTubID(-1),
    fDistMC(0.),
    fDriftMC(0.),
    fDist(0.),
    fDrift(0.),
    fEnergy(0.)
{}

//_____________________________________________________________________________
muCastorMuDetDIGI::~muCastorMuDetDIGI() 
{}

//_____________________________________________________________________________
void muCastorMuDetDIGI::Print(const Option_t* /*opt*/) const
{
    cout << "  DetID: " << fDetID
         << "  LayID: " << fLayID
         << "  TubID: " << fTubID
         << "  energy deposit (keV): " << fEnergy
         << endl;
}

