//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007, 2008 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \file muCastorHit.cxx 
/// \brief Implementation of the muCastorHit class 
///
/// \author G. Bonomi, F. Zenoni, M. Subieta - INFN

#include <iostream>

#include "muCastorHit.h"

/// \cond CLASSIMP
ClassImp(muCastorHit)
/// \endcond

using namespace std;

//_____________________________________________________________________________
muCastorHit::muCastorHit() 
  : fTrackID(-1),
    fPdgCode(-1),
    fMotherID(-1),
    fEvent(-1),
    fElemID(-1),
    fSectID(-1),
    fEdep(0.),
    fTime(0.),
    fStep(0.),
    fMom(),
    fPos(),
    fLastPos()
{
/// Default constructor
}
//_____________________________________________________________________________
muCastorHit::~muCastorHit() 
{
/// Destructor
}
//_____________________________________________________________________________
void muCastorHit::Print(const Option_t* /*opt*/) const
{
/// Printing

  cout << "  trackID: " << fTrackID 
       << "  ElementID: " << fElemID
       << "  SectionID: " << fSectID
       << "  energy deposit (keV): " << fEdep * 1.0e06
       << "  position (cm): (" 
       << fPos[0] << ", " << fPos[1] << ", " << fPos[2] << ")"
       << endl;
}

