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

#include "Math/Dense.h"
#include "ChamberDetector.h"


namespace uLib {

class LinearFitData {
public:
    inline const Vector2f & Position() const { return this->m_Position; }
    inline const Vector2f & Slope() const { return this->m_Slope; }
    inline const Vector2f & PositionError() const { return this->m_PositionError; }
    inline const Vector2f & SlopeError() const { return this->m_SlopeError; }
    inline int GetHitsNumber() const { return this->m_HitsNumber; }
    inline ChamberDetector::ID GetIdv() const { return this->m_Idv; }

protected:
    Vector2f            m_Position;
    Vector2f            m_Slope;
    Vector2f            m_PositionError;
    Vector2f            m_SlopeError;
    int                 m_HitsNumber;
    DetectorChamber::ID m_Idv;
};


class LinearFit : public LinearFitData {
public:
    inline Vector2f & Position() { return this->m_Position; }
    inline Vector2f & Slope() { return this->m_Slope; }
    inline Vector2f & PositionError() { return this->m_PositionError; }
    inline Vector2f & SlopeError() { return this->m_SlopeError; }
    inline void SetHitsNumber(int name) { this->m_HitsNumber = name; }
    inline void SetIdv(ChamberDetector::ID name) { this->m_Idv = name; }
};



}


#endif // LINEARFIT_H
