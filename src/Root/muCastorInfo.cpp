//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007, 2008 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \file muCastorInfo.cxx 
/// \brief Implementation of the muCastorInfo class 
///
/// \author G. Bonomi, A. Donzella - INFN

#include <iostream>

#include "muCastorInfo.h"

/// \cond CLASSIMP
ClassImp(muCastorInfo)
/// \endcond

using namespace std;

//_____________________________________________________________________________
muCastorInfo::muCastorInfo() 
  : fMuGen(-1)
{
/// Default constructor
}
//_____________________________________________________________________________
muCastorInfo::~muCastorInfo() 
{
/// Destructor
}
//_____________________________________________________________________________
void muCastorInfo::Print(const Option_t* /*opt*/) const
{
/// Printing

  cout << "  Generated muons: " << fMuGen 
       << endl;
}

