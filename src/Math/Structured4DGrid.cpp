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



#include "Structured4DGrid.h"

using namespace uLib;

//_____________________________________________________________
Structured4DGrid::Structured4DGrid()
{
    // reset uni-dim space
    m_Dims = Vector4i(0,0,0,0);
    m_Origin = Vector4f(0.,0.,0.,0.);
    m_Increments = Vector4i(0,0,0,0);
    m_binW = Vector4f(1.,1.,1.,1.);
    m_debug = true;
}


//_____________________________________________________________
void Structured4DGrid::SetDims(const Vector4i &size)
{
    this->m_Dims = size;

    // set increments
    this->m_Increments[0] = 1;
    this->m_Increments[1] = m_Dims[0];
    this->m_Increments[2] = m_Dims[0] * m_Dims[1];
    this->m_Increments[3] = m_Dims[0] * m_Dims[1] * m_Dims[2];

}

//_____________________________________________________________
void Structured4DGrid::SetPhysicalSpace(const Vector4f &origin, const Vector4f &spacing)
{
    m_Origin = origin;
    m_binW = spacing;

    m_uni2phys_T = Translation<float,4>(m_Origin) * Scaling(m_binW);
    m_phys2uni_T = m_uni2phys_T.matrix().inverse();

    return;
}


//_____________________________________________________________
bool Structured4DGrid::IsInsideBounds(const Vector4f &pt) const
{
    Vector4i pLoc = this->PhysicsToUnitSpace(pt);
    return this->IsInsideGrid(pLoc);
}


//_____________________________________________________________
Vector4i Structured4DGrid::UnMap(int index) const
{
    Vector4i v( 0,0,0, 0 );
    Vector4i iv = m_Increments;

    int id = 0;
    for(int k=0; k<4; ++k) {
        int inc = iv.maxCoeff(&id);
        v(id) = index / inc;
        index -= v(id) * inc;
        iv(id) = 0;
    }
    return v;
}

//_____________________________________________________________
bool Structured4DGrid::IsInsideGrid(const Vector4i &v) const
{
    int vok = 1;
    vok *= (v(0) >= 0 && v(0) < m_Dims[0]);
    vok *= (v(1) >= 0 && v(1) < m_Dims[1]);
    vok *= (v(2) >= 0 && v(2) < m_Dims[2]);
    vok *= (v(3) >= 0 && v(3) < m_Dims[3]);
    return vok;
}


//_____________________________________________________________
Vector4i Structured4DGrid::PhysicsToUnitSpace(const Vector4f &pt) const
{
    Vector4i out;
    Vector4f pLoc = m_phys2uni_T * pt;

    out << (int)floor(pLoc(0)),
                (int)floor(pLoc(1)),
                (int)floor(pLoc(2)),
                (int)floor(pLoc(3));

    return out;
}

//_____________________________________________________________
Vector4f Structured4DGrid::UnitToPhysicsSpace(const Vector4i &ind) const
{
    Vector4f p;
    p = m_uni2phys_T * ind.cast<float>();

    return p;
}

//_____________________________________________________________
void Structured4DGrid::PrintSelf(std::ostream &o)
{
    o << "uLib Structured Data 4D: \n"
      << "dim     = " << this->GetDims().transpose() << "\n"
      << "spacing = " << this->GetSpacing().transpose() << "\n";
}

