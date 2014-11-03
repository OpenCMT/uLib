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

#ifndef U_MATH_IMAGESPACE_H
#define U_MATH_IMAGESPACE_H

#include "Core/Object.h"
#include "Math/ContainerBox.h"


namespace uLib {

class ImageSpace : public ContainerBox {
    typedef ContainerBox BaseClass;
public:
    ImageSpace(const Vector3i size);

    using ContainerBox::SetOrigin;

//    void SetSize(const Vector3f v);

//    Vector3f GetSize() const;

    void SetSpacing(const Vector3f spacing);

    Vector3f GetSpacing() const;

//    bool IsInsideBounds(const Vector4f pt) const;

    Vector3i Find(const Vector4f pt) const;

    void PrintSelf(std::ostream &o);

private:
    using ContainerBox::GetSize;
    using ContainerBox::SetSize;
};


} // uLib




#endif // IMAGESPACE_H
