#ifndef muCastor_RUN_H
#define muCastor_RUN_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007, 2008 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \file muCastorInfo.h
/// \brief Definition of the muCastorInfo class 
///
/// \authors G. Bonomi, A. Donzella - INFN

#include <TObject.h>
#include <TVector3.h>

class muCastorInfo : public TObject
{
  public:
    muCastorInfo();
    virtual ~muCastorInfo();

    // methods
    virtual void Print(const Option_t* option = "") const;

    void SetMuGen  (Int_t muGen)  { fMuGen = muGen; };
    void SetMuTrk  (Int_t muTrk)  { fMuTrk = muTrk; };

    Int_t GetMuGen()   { return fMuGen; };

  private:
    Int_t      fMuGen;   // Generated muons
    Int_t      fMuTrk;   // Tracked muons
    
  ClassDef(muCastorInfo,1) //muCastorInfo  
};

#endif //muCastor_RUN_H


