#include <iostream>
#include <limits>

#include "muCastorPrimaryVertex.h"

/// \cond CLASSIMP
ClassImp(muCastorPrimaryVertex)
/// \endcond

using namespace std;

//_____________________________________________________________________________
muCastorPrimaryVertex::muCastorPrimaryVertex() {
/// Default constructor
    Reset();
}

//_____________________________________________________________________________
muCastorPrimaryVertex::~muCastorPrimaryVertex()
{
/// Destructor
}

//_____________________________________________________________________________
void muCastorPrimaryVertex::Reset()
{
    fPdgCode    = 0;
    fVx         = std::numeric_limits<double>::quiet_NaN();
    fVy         = std::numeric_limits<double>::quiet_NaN();
    fVz         = std::numeric_limits<double>::quiet_NaN();
    fPx         = std::numeric_limits<double>::quiet_NaN();
    fPy         = std::numeric_limits<double>::quiet_NaN();
    fPz         = std::numeric_limits<double>::quiet_NaN();
    fE          = std::numeric_limits<double>::quiet_NaN();
}

//_____________________________________________________________________________
void muCastorPrimaryVertex::Print(const Option_t* /*opt*/) const
{
/// Printing

  	cout << "  Primary particle PDG Code " << fPdgCode << endl; 
	cout << "  Vertex: (" << fVx << ", " << fVy << ", " << fVz << ") cm" << endl;
	cout << "  Mom: (" << fPx << ", " << fPy << ", " << fPz << ")  MeV/c" << endl;

}

