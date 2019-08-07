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



#ifndef VTKTRIANGLEMESH_H
#define VTKTRIANGLEMESH_H


#include "uLibVtkInterface.h"
#include "Math/TriangleMesh.h"

class vtkPolyData;

namespace uLib {


class vtkTriangleMesh : public Abstract::uLibVtkPolydata {
    typedef TriangleMesh Content;
public:
    vtkTriangleMesh(Content &content);
    ~vtkTriangleMesh();

    void ReadFromFile(const char *filename);

    void ReadFromXMLFile(const char *filename);

    void ReadFromObjFile(const char *filename);

    void ReadFromStlFile(const char *filename);

    virtual class vtkProp *GetProp();

    virtual class vtkPolyData *GetPolyData() const;

    void Update();

private:
    void vtk2uLib_update();
    void uLib2vtk_update();

    TriangleMesh &m_content;
    vtkPolyData  *m_Poly;
    vtkActor     *m_Actor;
};



}

#endif // VTKTRIANGLEMESH_H
