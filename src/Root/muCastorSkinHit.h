//----------------------------------------------------------
// Class : CastorSkinHit 
// Date: October 2020
// Author: Germano Bonomi   germano.bonomi@unibs.it
//----------------------------------------------------------

#ifndef muCastor_SKINHIT_H
#define muCastor_SKINHIT_H


#include <TObject.h>
#include <TVector3.h>

class muCastorSkinHit : public TObject
{
public:
    muCastorSkinHit();
    virtual ~muCastorSkinHit();

    // methods
    virtual void Print(const Option_t* option = "") const;

    // set methods
    void SetDetID(Int_t id)         { fDetID = id; };  
    void SetPdgCode(Int_t pdg)      { fPdgCode = pdg; };
    void SetMotherID(Int_t mid)     { fMotherID = mid; };
    void SetMom(TVector3 xyz)       { fMomX = xyz.X(); fMomY = xyz.Y(); fMomZ = xyz.Z(); };
    void SetPos(TVector3 xyz)       { fPosX = xyz.X(); fPosY = xyz.Y(); fPosZ = xyz.Z(); };
      
private:
    Int_t      fDetID;      // Detector module ID 
    Int_t      fPdgCode;    // Particle PDG Code
    Int_t      fMotherID;   // Particle mother ID (-1 = primary, 0 = secondary, etc..)
    Double_t   fMomX;       // Track momentum when releasing the hit (X)
    Double_t   fMomY;       // Track momentum when releasing the hit (Y)
    Double_t   fMomZ;       // Track momentum when releasing the hit (Z)
    Double_t   fPosX;       // Hit coordinates (at the entrance of the detector) (X)
    Double_t   fPosY;       // Hit coordinates (at the entrance of the detector) (Y)
    Double_t   fPosZ;       // Hit coordinates (at the entrance of the detector) (Z)
    
    ClassDef(muCastorSkinHit,1) //muCastorSkinHit  
};

#endif //muCastort_SKINHIT_H


