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



#ifndef U_GEOMETRY_H
#define U_GEOMETRY_H

#include "Math/Dense.h"
#include "Math/Transform.h"

namespace uLib {

class Geometry : public AffineTransform {
public:

    inline Vector4f GetWorldPoint(const Vector4f &v) const {
        return this->GetWorldMatrix() * v;
    }

    inline Vector4f GetWorldPoint(const float x, const float y, const float z) {
        return this->GetWorldPoint(Vector4f(x,y,z,1));
    }

    inline Vector4f GetLocalPoint(const Vector4f &v) const {
        return this->GetWorldMatrix().inverse() * v;
    }

    inline Vector4f GetLocalPoint(const float x, const float y, const float z) {
         return this->GetLocalPoint(Vector4f(x,y,z,1));
    }
};


}

#endif // GEOMETRY_H
