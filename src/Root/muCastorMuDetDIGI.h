#ifndef muCastor_MuDetDIGI_H
#define muCastor_MuDetDIGI_H

/// \file muCastorMuDetDIGI.h
/// \brief Definition of the muCastorMuDetDIGI class 
///
/// \authors G. Bonomi, M. Subieta - INFN

#include <TObject.h>

class muCastorMuDetDIGI : public TObject
{
public:
    muCastorMuDetDIGI();
    virtual ~muCastorMuDetDIGI();

    // -------> PUBLIC FUNCTIONS
    virtual void Print(const Option_t* option = "") const;

    // -------> SET METHODS

    /// Set Det ID (Detector module)
    void SetDetID(Int_t id)  { fDetID = id; };  

    /// Set Layer ID (Layer [0,5])
    void SetLayID(Int_t id)  { fLayID = id; };  

    /// Set Tube ID (Tube inside each layer)
    void SetTubID(Int_t id)  { fTubID = id; };  

    void SetDistMC      (Double_t v)  { fDistMC = v; };
    void SetDriftMC     (Double_t v)  { fDriftMC= v; };
    void SetDist        (Double_t v)  { fDist   = v; };
    void SetDrift       (Double_t v)  { fDrift  = v; };

    // Set energy 
    void SetEnergy(Double_t e)  { fEnergy = e; };

    // -------> GET METHODS

    /// \return The Module number
    Int_t GetDetID() { return fDetID; };

    /// \return The Layer number
    Int_t GetLayID() { return fLayID; };

    /// \return The Tube number
    Int_t GetTubID() { return fTubID; };

    Double_t GetDistMC()    { return fDistMC;   };
    Double_t GetDriftMC()   { return fDriftMC;  };
    Double_t GetDist()      { return fDist;     };
    Double_t GetDrift()     { return fDrift;    };

    /// \return Get energy
    Double_t GetEnergy()   { return fEnergy; };


    // -------> PRIVATE VARIABLES
private:
    Int_t      fDetID;      // Detector module ID 
    Int_t      fLayID;      // Detector layer ID
    Int_t      fTubID;      // Layer tube ID
    Double_t   fDistMC;     // Minimum distance of particle tracks to the wire
    Double_t   fDriftMC;    // Minimum drift time to the wire
    Double_t   fDist;       // Minimum distance of particle tracks to the wire (with smearing)
    Double_t   fDrift;      // Minimum drift time to the wire (with smearing)
    Double_t   fEnergy;     // Energy released in the element

    ClassDef(muCastorMuDetDIGI,1) //muCastorMuDetDIGI  
};

#endif //muCastorMuDetDIGI_H


