/*//////////////////////////////////////////////////////////////////////////////
// CMT Cosmic Muon Tomography project //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  Copyright (c) 2014, Universita' degli Studi di Padova, INFN sez. di Padova
  All rights reserved

  Authors: Andrea Rigoni Garola < andrea.rigoni@pd.infn.it >

  ------------------------------------------------------------------
  This library is free software;  you  can  redistribute  it  and/or
  modify it  under the  terms  of  the  GNU  Lesser  General  Public
  License as published  by  the  Free  Software  Foundation;  either
  version 3.0 of the License, or (at your option) any later version.

  This library is  distributed in  the hope that it will  be useful,
  but  WITHOUT ANY WARRANTY;  without  even  the implied warranty of
  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of  the GNU Lesser General  Public
  License along with this library.

//////////////////////////////////////////////////////////////////////////////*/



#ifndef U_LINEARFIT_H
#define U_LINEARFIT_H

#include "Core/Macros.h"
#include "Math/Dense.h"
#include "ChamberDetector.h"


namespace uLib {

class LinearFitData {
public:
    uLibConstRefMacro(Position,Vector2f)
    uLibConstRefMacro(Slope,Vector2f)
    uLibConstRefMacro(PositionError,Vector2f)
    uLibConstRefMacro(SlopeError,Vector2f)
    uLibGetMacro(HitsNumber,int)
    uLibGetMacro(Idv,ChamberDetector::ID)

private:
        friend class LinearFit;
    Vector2f m_Position;
    Vector2f m_Slope;
    Vector2f m_PositionError;
    Vector2f m_SlopeError;
    int      m_HitsNumber;
    DetectorChamber::ID m_Idv;
};


class LinearFit : public LinearFitData {
public:
    uLibRefMacro(Position,Vector2f)
    uLibRefMacro(Slope,Vector2f)
    uLibRefMacro(PositionError,Vector2f)
    uLibRefMacro(SlopeError,Vector2f)
    uLibSetMacro(HitsNumber,int)
    uLibSetMacro(Idv,ChamberDetector::ID)
};



}


#endif // LINEARFIT_H
