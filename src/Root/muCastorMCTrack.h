#ifndef muCastor_MCTRACK_H
#define muCastor_MCTRACK_H

//########################################
// muCastorMCTrack class
// Created at the University of Brescia, Italy
// Date: December 2011
// Autors: Germano Bonomi   germano.bonomi@ing.unibs.it 
//         Martin Subieta   martin.subieta@ing.unibs.it
//########################################

#include <iostream>
#include "vector"
#include "TObject.h"
#include "TParticle.h"
#include "Detectors/MuonScatter.h"

class TClonesArray;

class muCastorMCTrack : public TObject
{

 public:

  /**  Default constructor  **/
  muCastorMCTrack();

  /**  Constructor from TParticle  **/
  muCastorMCTrack(TParticle* particle);

  /**  Destructor  **/
  virtual ~muCastorMCTrack();
  void Reset();   


  /**  Accessors  **/
   Int_t          GetFirstDaughter()  const { return fDaughter[0];}
   Int_t          GetMother()  const { return fMother[0];}

  /**  Modifiers  **/
   virtual void        AddPoint(TLorentzVector pos, TLorentzVector mom);
   virtual void           SetFirstDaughter(Int_t trkid)      { fDaughter[0] = trkid; }
   virtual void           SetLastDaughter(Int_t trkid)       { fDaughter[1] = trkid; }

   inline void Dump() {
       std::cout << "muCastorMCTrack\n"
                 << "PDG code: " << fPdgCode << "\n"
                 << "Momentum: " << fPx << ", " << fPy << ", " << fPz << "\n"
                 << "Position: " << fVx << ", " << fVy << ", " << fVz << "\n"
                 << "Npoints: " << fNpoints << "\n";
       return;
   }

public:

/* Private variables - copying private variables of TParticle */

  Int_t          fPdgCode;              // PDG code of the particle
  Int_t          fMother[2];            // Indices of the mother particles
  Int_t          fDaughter[2];          // Indices of the daughter particles

  Double_t       fPx;                   // x component of momentum
  Double_t       fPy;                   // y component of momentum
  Double_t       fPz;                   // z component of momentum
  Double_t       fE;                    // Energy

  Double_t       fVx;                   // x of production vertex
  Double_t       fVy;                   // y of production vertex
  Double_t       fVz;                   // z of production vertex
  Double_t       fVt;                   // t of production vertex

  Int_t          fPointsSize; // capacity of points array
  Int_t          fNpoints;    // number of stored points
  Double_t      *fPntPosX;     //[fNpoints] array of points (x) belonging to this track
  Double_t      *fPntPosY;     //[fNpoints] array of points (y) belonging to this track
  Double_t      *fPntPosZ;     //[fNpoints] array of points (z) belonging to this track
  Double_t      *fPntT;        //[fNpoints] array of points (t) belonging to this track
  Double_t      *fPntMomX;     //[fNpoints] array of points (px) belonging to this track
  Double_t      *fPntMomY;     //[fNpoints] array of points (py) belonging to this track
  Double_t      *fPntMomZ;     //[fNpoints] array of points (pz) belonging to this track
  Double_t      *fPntE;        //[fNpoints] array of points (E) belonging to this track

  ClassDef(muCastorMCTrack,1);

};

uLib::MuonScatter &operator << (uLib::MuonScatter &mu, const muCastorMCTrack &bsmu);
#endif //muCastor_MCTRACK_H   
