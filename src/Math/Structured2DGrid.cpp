/*//////////////////////////////////////////////////////////////////////////////
// CMT Cosmic Muon Tomography project //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  Copyright (c) 2014, Universita' degli Studi di Padova, INFN sez. di Padova
  All rights reserved

  Authors: Sara Vanini < sara.vanini@pd.infn.it >

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



#include "Structured2DGrid.h"

using namespace uLib;

//_____________________________________________________________
Structured2DGrid::Structured2DGrid()
{
    // reset uni-dim space
    m_Dims = Vector2i(0,0);
    m_Origin = Vector2f(0.,0.);
    m_Increments = Vector2i(0,0);
    m_binW = Vector2f(1.,1.);
    m_debug = true;
}


//_____________________________________________________________
void Structured2DGrid::SetDims(const Vector2i &size)
{
    this->m_Dims = size;

    // set increments
    this->m_Increments[0] = 1;
    this->m_Increments[1] = m_Dims[0];
   }

//_____________________________________________________________
void Structured2DGrid::SetPhysicalSpace(const Vector2f &origin, const Vector2f &spacing)
{
    m_Origin = origin;
    m_binW = spacing;

    m_uni2phys_T = Translation<float,2>(m_Origin) * Scaling(m_binW);
    m_phys2uni_T = m_uni2phys_T.matrix().inverse();

    return;
}


//_____________________________________________________________
bool Structured2DGrid::IsInsideBounds(const Vector2f &pt) const
{
    Vector2i pLoc = this->PhysicsToUnitSpace(pt);
    return this->IsInsideGrid(pLoc);
}


//_____________________________________________________________
Vector2i Structured2DGrid::UnMap(int index) const
{
    Vector2i v( 0,0 );
    Vector2i iv = m_Increments;

    int id = 0;
    for(int k=0; k<2; ++k) {
        int inc = iv.maxCoeff(&id);
        v(id) = index / inc;
        index -= v(id) * inc;
        iv(id) = 0;
    }
    return v;
}

//_____________________________________________________________
bool Structured2DGrid::IsInsideGrid(const Vector2i &v) const
{
    int vok = 1;
    vok *= (v(0) >= 0 && v(0) < m_Dims[0]);
    vok *= (v(1) >= 0 && v(1) < m_Dims[1]);

    return vok;
}


//_____________________________________________________________
Vector2i Structured2DGrid::PhysicsToUnitSpace(const Vector2f &pt) const
{
    Vector2i out;
    Vector2f pLoc = m_phys2uni_T * pt;

    out << (int)floor(pLoc(0)),
                (int)floor(pLoc(1));

    return out;
}

//_____________________________________________________________
Vector2f Structured2DGrid::UnitToPhysicsSpace(const Vector2i &ind) const
{
    Vector2f p;
    p = m_uni2phys_T * ind.cast<float>();

    return p;
}

//_____________________________________________________________
void Structured2DGrid::PrintSelf(std::ostream &o)
{
    o << "uLib Structured Data 2D: \n"
      << "dim     = " << this->GetDims().transpose() << "\n"
      << "spacing = " << this->GetSpacing().transpose() << "\n";
}

