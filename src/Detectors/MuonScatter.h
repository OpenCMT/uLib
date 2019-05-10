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




#ifndef U_MUONSCATTER_H
#define U_MUONSCATTER_H

#include "Math/Dense.h"

namespace uLib {


class MuonScatter {
public:
    inline const HLine3f & LineIn() const { return this->m_LineIn; }
    inline const HError3f & ErrorIn() const { return this->m_ErrorIn; }
    inline const HLine3f & LineOut() const { return this->m_LineOut; }
    inline const HError3f & ErrorOut() const { return this->m_ErrorOut; }

    inline HLine3f & LineIn() { return this->m_LineIn; }
    inline HError3f & ErrorIn() { return this->m_ErrorIn; }
    inline HLine3f & LineOut() { return this->m_LineOut; }
    inline HError3f & ErrorOut() { return this->m_ErrorOut; }

    inline void SetMomentum(Scalarf name) { this->m_Momentum = name; }
    inline void SetMomentumPrime(Scalarf name) { this->m_MomentumPrime = name; }

    inline Scalarf GetMomentum() const { return this->m_Momentum; }
    inline Scalarf GetMomentumPrime() const { return this->m_MomentumPrime; }

protected:
    HLine3f  m_LineIn;
    HLine3f  m_LineOut;
    HError3f m_ErrorIn;
    HError3f m_ErrorOut;
    Scalarf  m_Momentum;
    Scalarf  m_MomentumPrime;
};

typedef MuonScatter MuonScatterData;

inline std::ostream&
operator<< (std::ostream& stream, const MuonScatterData &mu) {
    stream << " MuonScatterData: ------------- \n"
           << " P: " << mu.GetMomentum() << "  Pprim: " << mu.GetMomentumPrime() << "\n"
           << " IN:  " << mu.LineIn() << "\n"
           << "      " << mu.ErrorIn() << "\n"
           << " OUT: " << mu.LineOut() << "\n"
           << "      " << mu.ErrorOut() <<"\n"
           << " ------------------------------ \n";
    return stream;
}

}

#endif // U_MUONSCATTER_H
