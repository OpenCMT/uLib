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



#ifndef SOLID_H
#define SOLID_H

#include "Core/Object.h"
#include "Math/Dense.h"
#include "Math/TriangleMesh.h"
#include "Detectors/Matter.h"

class G4Material;
class G4LogicalVolume;
class G4TessellatedSolid;


namespace uLib {

class Solid : public Object {
public:

    Solid();
    Solid(const char *name);

    void SetNistMaterial(const char *name);

    void SetMaterial(G4Material *material);

    uLibGetMacro(Material,G4Material *)
    uLibGetMacro(Logical,G4LogicalVolume *)

protected:                
    G4Material         *m_Material;
    G4LogicalVolume    *m_Logical;
};





class TessellatedSolid : public Solid {
    typedef Solid BaseClass;

public:
    TessellatedSolid(const char *name);

    void SetMesh(TriangleMesh &mesh);

    uLibGetMacro(Solid,G4TessellatedSolid *)
private:
    G4TessellatedSolid *m_Solid;
};




}




#endif // SOLID_H
