#ifndef muCastor_PVTX_H
#define muCastor_PVTX_H

/// \brief Definition of the muCastorPrimaryVertex class 
///
/// \authors G. Bonomi (04/02/2020)

#include <TObject.h>

class muCastorPrimaryVertex : public TObject
{
    public:
        muCastorPrimaryVertex();
        virtual ~muCastorPrimaryVertex();

        // -------> PUBLIC FUNCTIONS
        virtual void Print(const Option_t* option = "") const;

        // -------> SET METHODS

		void SetPdgCode(Int_t code) { fPdgCode = code; };

        void SetVx(Double_t Vx)   { fVx = Vx; };  
        void SetVy(Double_t Vy)   { fVy = Vy; };  
        void SetVz(Double_t Vz)   { fVz = Vz; };  

        void SetPx(Double_t Px)   { fPx = Px; };  
        void SetPy(Double_t Py)   { fPy = Py; };  
        void SetPz(Double_t Pz)   { fPz = Pz; };  

        void SetE(Double_t E)  { fE = E; };

        void Reset();
    private:
        // -------> PRIVATE VARIABLES
		Int_t          fPdgCode;              // PDG code of the particle

  		Double_t       fVx;                   // x of production vertex
  		Double_t       fVy;                   // y of production vertex
  		Double_t       fVz;                   // z of production vertex

 		Double_t       fPx;                   // x component of momentum
  		Double_t       fPy;                   // y component of momentum
  		Double_t       fPz;                   // z component of momentum
  		Double_t       fE;                    // Energy


        ClassDef(muCastorPrimaryVertex,1) //muCastorPrimaryVertex  
};

#endif //muCastor_PVTX_H


