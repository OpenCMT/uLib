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

#ifndef Structured4DGrid_H
#define Structured4DGrid_H

#include "Math/Dense.h"

#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace Eigen;

namespace uLib {

class Structured4DGrid {
public:

    Structured4DGrid();

    /// unit-space
    void SetDims(const Vector4i &size);
    inline Vector4i GetDims() {return m_Dims; }
    bool IsInsideGrid(const Vector4i &v) const;
    inline int Map(Vector4i index) const  { return (m_Increments.transpose() * index);}
    Vector4i UnMap(int index) const;

    /// physics-space
    void SetPhysicalSpace(const Vector4f &origin, const Vector4f &spacing);
    inline Vector4f GetSpacing() const {    return m_binW; }
    inline Vector4f GetOrigin() const {    return m_Origin; }
    bool IsInsideBounds(const Vector4f &pt) const;

    /// operations
    Vector4i PhysicsToUnitSpace(const Vector4f &pt) const;
    Vector4f UnitToPhysicsSpace(const Vector4i &ind) const;
    void PrintSelf(std::ostream &o);
    void SetDebug(bool debug){ m_debug = debug; };

private:
    Vector4i m_Dims;
    Vector4i m_Increments;
    Vector4f m_binW;
    Vector4f m_Origin;
    bool m_debug;

     Transform<float, 4, Eigen::Affine>  m_uni2phys_T;
     Transform<float, 4, Eigen::Affine>  m_phys2uni_T;
};
}

#endif // Structured4DGrid_H
