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



#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <vector>

#include "Core/Object.h"
#include "Math/Dense.h"

namespace uLib {

class TriangleMesh : public Object {

public:
    void PrintSelf(std::ostream &o);

    void AddPoint(const Vector3f &pt);

    void AddTriangle(const Id_t *id);
    void AddTriangle(const Vector3i &id);

    inline std::vector<Vector3f> & Points() { return this->m_Points; }
    inline std::vector<Vector3i> & Triangles() { return this->m_Triangles; }

private:
    std::vector<Vector3f> m_Points;
    std::vector<Vector3i> m_Triangles;

};

}


#endif // TRIANGLEMESH_H
