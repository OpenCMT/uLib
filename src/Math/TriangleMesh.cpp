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




#include "TriangleMesh.h"


namespace uLib {

void TriangleMesh::PrintSelf(std::ostream &o)
{
    o << " // ------- TRIANGLE MESH ------- // \n" ;
    o << "    #Points : " << m_Points.size() << "\n";
    o << "    #Triang : " << m_Triangles.size() << "\n";
    for(int i=0; i < m_Triangles.size(); ++i ) {
        o << "     - triangle[" << i << "]" <<
             " " << m_Triangles[i](0) <<
             "->(" << m_Points[m_Triangles[i](0)].transpose() << ") " <<
             " " << m_Triangles[i](1) <<
             "->(" << m_Points[m_Triangles[i](1)].transpose() << ") " <<
             " " << m_Triangles[i](2) <<
             "->(" << m_Points[m_Triangles[i](2)].transpose() << ") " <<
             " \n";
    }
    o << " // ----------------------------- // \n";
}

void TriangleMesh::AddPoint(const Vector3f &pt)
{
    this->m_Points.push_back(pt);
}

void TriangleMesh::AddTriangle(const Id_t *id)
{
    Vector3i triangle(id[0],id[1],id[2]);
    this->m_Triangles.push_back(triangle);
}

void TriangleMesh::AddTriangle(const Vector3i &id)
{
    this->m_Triangles.push_back(id);
}


}
