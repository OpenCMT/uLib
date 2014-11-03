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

#ifndef U_MATH_IMAGEMAP_H
#define U_MATH_IMAGEMAP_H

#include "Core/Macros.h"
#include "Core/Object.h"
#include "Math/Dense.h"
#include "Math/DataSet.h"

namespace uLib {

class ImageMap {
public:
    typedef enum {
        CustomOrder = 0,
        XYZ = 0 | 1 << 2 | 2 << 4,
        XZY = 0 | 2 << 2 | 1 << 4,
        YXZ = 1 | 0 << 2 | 2 << 4,
        YZX = 2 | 0 << 2 | 1 << 4,
        ZXY = 1 | 2 << 2 | 0 << 4,
        ZYX = 2 | 1 << 2 | 0 << 4
    } Order;

    ImageMap(const Vector3i &size);

    ImageMap(const ImageMap &copy) :
        m_DataOrder(copy.m_DataOrder),
        m_Dims(copy.m_Dims),
        m_Increments(copy.m_Increments)
    {}

    uLibGetMacro(Dims,Vector3i)

    void SetDims(const Vector3i &size);

    uLibGetSetMacro(Increments,Vector3i)

    void SetDataOrder(Order order = YXZ);

    uLibGetMacro(DataOrder,Order)

    bool IsInsideGrid(const Vector3i &v) const;

    inline int Map(Vector3i index) const;

    Vector3i UnMap(int index) const;

private:
    Order m_DataOrder;
    Vector3i m_Dims;
    Vector3i m_Increments; //TODO: make this line matrix //
};


// --- INLINES -------------------------------------------------------------- //


inline int ImageMap::Map(Vector3i index) const
{
    return (m_Increments.transpose() * index);
}





} // uLib



#endif // IMAGEMAP_H
