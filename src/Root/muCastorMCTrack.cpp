//*****************************************************************************************
// muCastorMCTrack class
// Created at the University of Brescia, Italy
// Date: December 2011
// Autors: Germano Bonomi   germano.bonomi@ing.unibs.it 
//         Martin Subieta   martin.subieta@ing.unibs.it
//******************************************************************************************

#include <iostream>

#include "Detectors/MuonScatter.h"
#include <Root/muCastorMCTrack.h>
#include <TClonesArray.h>

using namespace std;

ClassImp(muCastorMCTrack)
uLib::MuonScatter &operator << (uLib::MuonScatter &mu, const muCastorMCTrack &bsmu) {

  /// store muons only if at least two points are stored in track
  if(bsmu.fNpoints >= 2)  {
    mu.LineIn().origin << bsmu.fPntPosX[0], bsmu.fPntPosY[0], bsmu.fPntPosZ[0];
    mu.LineIn().direction << bsmu.fPntMomX[0], bsmu.fPntMomY[0], bsmu.fPntMomZ[0];

    mu.LineOut().origin << bsmu.fPntPosX[bsmu.fNpoints-1], bsmu.fPntPosY[bsmu.fNpoints-1], bsmu.fPntPosZ[bsmu.fNpoints-1];
    mu.LineOut().direction << bsmu.fPntMomX[bsmu.fNpoints-1], bsmu.fPntMomY[bsmu.fNpoints-1], bsmu.fPntMomZ[bsmu.fNpoints-1];

    mu.SetMomentum(mu.LineIn().direction.norm());
    mu.SetMomentumPrime(mu.LineOut().direction.norm());
    }

    return mu;
}

//namespace ROOT {
//namespace Mutom {
// -----   Default constructor   -------------------------------------------
muCastorMCTrack::muCastorMCTrack()
{
  fPdgCode = 0;	 // PDG code of the particle
  fMother[0] = 0; 	  // Indices of the mother particles
  fDaughter[0] = -1;  // Indices of the daughter particles
  fMother[1] = 0; 	  // Indices of the mother particles
  fDaughter[1] = -1;  // Indices of the daughter particles
  fPx = 0.; 		 // x component of momentum
  fPy = 0.; 		 // y component of momentum
  fPz = 0.; 		 // z component of momentum
  fE  = 0.;  		 // Energy
  fVx = 0.; 		 // x of production vertex
  fVy = 0.; 		 // y of production vertex
  fVz = 0.; 		 // z of production vertex
  fVt = 0.; 		 // t of production vertex
   
  fPointsSize = 0;       // Maximum number of points associated to the tracks
  fNpoints    = 0;       // Number of points associated to this track 
  fPntPosX    = 0;       // Array of points X
  fPntPosY    = 0;       // Array of points Y
  fPntPosZ    = 0;       // Array of points Z
  fPntT       = 0;       // Array of points Time 
  fPntMomX    = 0;       // Array of points Mom X 
  fPntMomY    = 0;       // Array of points Mom Y 
  fPntMomZ    = 0;       // Array of points Mom Z 
  fPntE       = 0;       // Array of points Energy 

}
// -------------------------------------------------------------------------



// -----   Constructor from TParticle   ------------------------------------
muCastorMCTrack::muCastorMCTrack(TParticle* part)
{

  fPdgCode     = part->GetPdgCode();
  fMother[0]   = part->GetFirstMother();
  fMother[1]   = part->GetSecondMother();
  fDaughter[0] = part->GetFirstDaughter();
  fDaughter[1] = part->GetLastDaughter();
  fPx          = part->Px();
  fPy          = part->Py();
  fPz          = part->Pz();
  fE           = part->Energy();

  fVx          = part->Vx();
  fVy          = part->Vy();
  fVz          = part->Vz();
  fVt          = part->T();

  fPointsSize = 0;       // Maximum number of points associated to the tracks
  fNpoints    = 0;       // Number of points associated to this track 
  fPntPosX    = 0;       // Array of points X
  fPntPosY    = 0;       // Array of points Y
  fPntPosZ    = 0;       // Array of points Z
  fPntT       = 0;       // Array of points Time 
  fPntMomX    = 0;       // Array of points Mom X 
  fPntMomY    = 0;       // Array of points Mom Y 
  fPntMomZ    = 0;       // Array of points Mom Z 
  fPntE       = 0;       // Array of points Energy 
}
// -------------------------------------------------------------------------


  
// -----   Destructor   ----------------------------------------------------
muCastorMCTrack::~muCastorMCTrack()
{
   if (fPntPosX) delete [] fPntPosX;
   if (fPntPosY) delete [] fPntPosY;
   if (fPntPosZ) delete [] fPntPosZ;
   if (fPntT)    delete [] fPntT;
   if (fPntMomX) delete [] fPntMomX;
   if (fPntMomY) delete [] fPntMomY;
   if (fPntMomZ) delete [] fPntMomZ;
   if (fPntE)    delete [] fPntE;
}
// -------------------------------------------------------------------------
//______________________________________________________________________________
void muCastorMCTrack::AddPoint(TLorentzVector pos, TLorentzVector mom)
{

// Add a point to the track (copied from TGeoTrack::AddPoint)
   if (!fPntPosX) {
      fPointsSize = 12; // The first time create the array with fPointsSize size
      fPntPosX = new Double_t[fPointsSize];
      fPntPosY = new Double_t[fPointsSize];
      fPntPosZ = new Double_t[fPointsSize];
      fPntT    = new Double_t[fPointsSize];
      fPntMomX = new Double_t[fPointsSize];
      fPntMomY = new Double_t[fPointsSize];
      fPntMomZ = new Double_t[fPointsSize];
      fPntE    = new Double_t[fPointsSize];
   } else {
      if (fNpoints>=fPointsSize) { // when needed increase the arrays size by 4
         Int_t newSize = fPointsSize + 4;
         // Pos (X, Y, Z) & Time 
         Double_t *tPosX = new Double_t[newSize];
         memcpy(tPosX, fPntPosX, fNpoints*sizeof(Double_t));
         fPointsSize *= 2;
         delete [] fPntPosX;
         fPntPosX = tPosX;

         Double_t *tPosY = new Double_t[newSize];
         memcpy(tPosY, fPntPosY, fNpoints*sizeof(Double_t));
         fPointsSize *= 2;
         delete [] fPntPosY;
         fPntPosY = tPosY;

         Double_t *tPosZ = new Double_t[newSize];
         memcpy(tPosZ, fPntPosZ, fNpoints*sizeof(Double_t));
         fPointsSize *= 2;
         delete [] fPntPosZ;
         fPntPosZ = tPosZ;

         Double_t *tT = new Double_t[newSize];
         memcpy(tT, fPntT, fNpoints*sizeof(Double_t));
         fPointsSize *= 2;
         delete [] fPntT;
         fPntT = tT;

         // Mom (X, Y, Z) & Energy 
         Double_t *tMomX = new Double_t[newSize];
         memcpy(tMomX, fPntMomX, fNpoints*sizeof(Double_t));
         fPointsSize *= 2;
         delete [] fPntMomX;
         fPntMomX = tMomX;

         Double_t *tMomY = new Double_t[newSize];
         memcpy(tMomY, fPntMomY, fNpoints*sizeof(Double_t));
         fPointsSize *= 2;
         delete [] fPntMomY;
         fPntMomY = tMomY;

         Double_t *tMomZ = new Double_t[newSize];
         memcpy(tMomZ, fPntMomZ, fNpoints*sizeof(Double_t));
         fPointsSize *= 2;
         delete [] fPntMomZ;
         fPntMomZ = tMomZ;

         Double_t *tE = new Double_t[newSize];
         memcpy(tE, fPntE, fNpoints*sizeof(Double_t));
         fPointsSize = newSize;
         delete [] fPntE;
         fPntE = tE;
      }
   }
  
  // Storing the info
  fPntPosX[fNpoints] = pos[0];
  fPntPosY[fNpoints] = pos[1];
  fPntPosZ[fNpoints] = pos[2];
  fPntT[fNpoints]    = pos[3];

  fPntMomX[fNpoints] = mom[0];
  fPntMomY[fNpoints] = mom[1];
  fPntMomZ[fNpoints] = mom[2];
  fPntE   [fNpoints] = mom[3];

  fNpoints++; // One more point
}

//_____________________________________________________________________________
void muCastorMCTrack::Reset()
{
/// Delete contained particles, reset particles array and stack.

   fNpoints    = 0;   
   fPointsSize = 0;
   if (fPntPosX) delete [] fPntPosX;
   if (fPntPosY) delete [] fPntPosY;
   if (fPntPosZ) delete [] fPntPosZ;
   if (fPntT)    delete [] fPntT;
   if (fPntMomX) delete [] fPntMomX;
   if (fPntMomY) delete [] fPntMomY;
   if (fPntMomZ) delete [] fPntMomZ;
   if (fPntE)    delete [] fPntE;
   fPntPosX    = 0;
   fPntPosY    = 0;
   fPntPosZ    = 0;
   fPntT       = 0;
   fPntMomX    = 0;
   fPntMomY    = 0;
   fPntMomZ    = 0;
   fPntE       = 0;

}
//} // Mutom
//} // ROOT
