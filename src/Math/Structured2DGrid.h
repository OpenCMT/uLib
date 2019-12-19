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

#ifndef Structured2DGrid_H
#define Structured2DGrid_H

#include "Math/Dense.h"

#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace Eigen;

namespace uLib {

class Structured2DGrid {
public:

    Structured2DGrid();

    /// unit-space
    void SetDims(const Vector2i &size);
    inline Vector2i GetDims() {return m_Dims; }
    bool IsInsideGrid(const Vector2i &v) const;
    inline int Map(Vector2i index) const  { return (m_Increments.transpose() * index);}
    Vector2i UnMap(int index) const;

    /// physics-space
    void SetPhysicalSpace(const Vector2f &origin, const Vector2f &spacing);
    inline Vector2f GetSpacing() const {    return m_binW; }
    inline Vector2f GetOrigin() const {    return m_Origin; }
    bool IsInsideBounds(const Vector2f &pt) const;

    /// operations
    Vector2i PhysicsToUnitSpace(const Vector2f &pt) const;
    Vector2f UnitToPhysicsSpace(const Vector2i &ind) const;
    void PrintSelf(std::ostream &o);
    void SetDebug(bool debug){ m_debug = debug; };

private:
    Vector2i m_Dims;
    Vector2i m_Increments;
    Vector2f m_binW;
    Vector2f m_Origin;
    bool m_debug;

     Transform<float, 2, Eigen::Affine>  m_uni2phys_T;
     Transform<float, 2, Eigen::Affine>  m_phys2uni_T;
};
}

#endif // Structured2DGrid_H
