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



#include "StructuredData.h"

using namespace uLib;

StructuredData::StructuredData(const Vector3i &size) :
    m_Dims(size)
{
    SetDataOrder();
}

void StructuredData::SetDims(const Vector3i &size)
{
    this->m_Dims = size;
    SetDataOrder();
}

void StructuredData::SetDataOrder(StructuredData::Order order)
{
    int i = order & 0x3;
    int j = (order >> 2) & 0x3;
    int k = (order >> 4) & 0x3;
    this->m_Increments[i] = 1;
    this->m_Increments[j] = m_Dims[i];
    this->m_Increments[k] = m_Dims[i] * m_Dims[j];
    this->m_DataOrder = order;
}

bool StructuredData::IsInsideGrid(const Vector3i &v) const
{
    int vok = 1;
    vok *= (v(0) >= 0 && v(0) < m_Dims[0]);
    vok *= (v(1) >= 0 && v(1) < m_Dims[1]);
    vok *= (v(2) >= 0 && v(2) < m_Dims[2]);
    return vok;
}



Vector3i StructuredData::UnMap(int index) const
{
    Vector3i v( 0,0,0 );
    Vector3i iv = m_Increments;
    int id = 0;
    for(int k=0; k<3; ++k) {
        int inc = iv.maxCoeff(&id);
        v(id) = index / inc;
        index -= v(id) * inc;
        iv(id) = 0;
    }
    return v;
}


