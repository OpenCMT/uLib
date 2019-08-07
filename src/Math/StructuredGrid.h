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



#ifndef U_MATH_STRUCTUREDGRID_H
#define U_MATH_STRUCTUREDGRID_H

#include "Math/ContainerBox.h"
#include "Math/StructuredData.h"

namespace uLib {


class StructuredGrid : public ContainerBox, public StructuredData {
    typedef ContainerBox BaseClass;
public:
    StructuredGrid(const Vector3i &size);

    // TODO: Add SetSize of Container .. adjusting spacing //

    using ContainerBox::SetOrigin;

    inline void SetSpacing(const Vector3f &spacing);

    inline Vector3f GetSpacing() const;

    bool IsInsideBounds(const Vector4f &pt) const;

    Vector3i Find(const HPoint3f &pt) const;

    void PrintSelf(std::ostream &o);
};



// --- INLINES -------------------------------------------------------------- //

inline void StructuredGrid::SetSpacing(const Vector3f &spacing)
{
    ContainerBox::SetSize(spacing);
}

inline Vector3f StructuredGrid::GetSpacing() const
{
    return ContainerBox::GetSize();
}


}

#endif // STRUCTUREDGRID_H
