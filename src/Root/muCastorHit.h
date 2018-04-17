#ifndef muCastor_HIT_H
#define muCastor_HIT_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007, 2008 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \file muCastorHit.h
/// \brief Definition of the muCastorHit class 
///
/// \authors G. Bonomi, M. Subieta - INFN

#include <TObject.h>
#include <TVector3.h>

class muCastorHit : public TObject
{
  public:
    muCastorHit();
    virtual ~muCastorHit();

    // methods
    virtual void Print(const Option_t* option = "") const;

    //
    // set methods
    
    /// Set track Id
    void SetTrackID  (Int_t track)  { fTrackID = track; };

    /// Set particle PDG Code
    void SetPdgCode  (Int_t pdg)  { fPdgCode = pdg; };

    /// Set Mother ID
    void SetMotherID  (Int_t mid)  { fMotherID = mid; };

    /// Set track Id
    void SetEventNumber  (Int_t ievt)  { fEvent = ievt; };
    
    /// Set Element ID (e.g. fiber, strip)
    void SetElemID(Int_t id)  { fElemID = id; };  

    /// Set Section ID (e.g. layer, wafer)
    void SetSectID(Int_t id)  { fSectID = id; };  

    /// Set energy deposit
    void SetEdep     (Double_t de)  { fEdep = de; };

    /// Set hit time 
    void SetTime    (Double_t dt)  { fTime = dt; };
    
    /// Set step length 
    void SetStep    (Double_t dl)  { fStep = dl; };
    
    /// Set momentum
    void SetMom      (TVector3 xyz) { fMom = xyz; };
      
    /// Set hit coordinates
    void SetPos      (TVector3 xyz) { fPos = xyz; };
      
    /// Set last position
    void SetLastPos      (TVector3 xyz) { fLastPos = xyz; };
      
    //
    // get methods
    
    /// \return The track Id
    Int_t GetTrackID()   { return fTrackID; };

    /// \return The event number
    Int_t GetEventNumber()   { return fEvent; };

    /// \return The Module number
    Int_t GetElemID() { return fElemID; };

    /// \return The Layer number
    Int_t GetSectID() { return fSectID; };

    /// \return The energy deposit
    Double_t GetEdep()   { return fEdep; };      

    /// \return The hit time
    Double_t GetTime()   { return fTime; };      

    /// \return The step length
    Double_t GetStep()   { return fStep; };      

    /// \return The track position
    TVector3 GetMom()    { return fMom; };
      
    // return Hit coordinates (at the entrance of the detector)
    TVector3 GetPos()    { return fPos; };

    // return Last position (at the exit of the detector or when decayed)
    TVector3 GetLastPos()    { return fLastPos; };

  public:
    Int_t      fTrackID;   // Track Id
    Int_t      fPdgCode;   // Particle PDG Code
    Int_t      fMotherID;  // Particle mother ID (-1 = primary, 0 = secondary, etc..)
    Int_t      fEvent;     // Event Number
    Int_t      fElemID;    // Detector Element ID (e.g. fiber, strip)
    Int_t      fSectID;    // Detector Section/Sector ID (e.g. layer, wafer) 
    Double_t   fEdep;      // Energy deposit
    Double_t   fTime;      // Hit time
    Double_t   fStep;      // Step Length
    TVector3   fMom;       // Track momentum when releasing the hit
    TVector3   fPos;       // Hit coordinates (at the entrance of the detector)
    // 12/03/2012: for the moment, fLastPos is introduced for gDetSD only
    TVector3   fLastPos;   // Last position (at the exit of the detector or when decayed)
    
  ClassDef(muCastorHit,1) //muCastorHit  
};

#endif //muCastort_HIT_H


