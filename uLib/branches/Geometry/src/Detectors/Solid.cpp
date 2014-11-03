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



// G4 Solid //
#include <Geant4/G4Material.hh>
#include <Geant4/G4NistManager.hh>
#include <Geant4/G4LogicalVolume.hh>

// Tessellated solid //
#include <Geant4/G4TessellatedSolid.hh>
#include <Geant4/G4TriangularFacet.hh>
#include <Geant4/G4ThreeVector.hh>


#include "Math/Dense.h"

#include "Solid.h"

namespace uLib {

class DetectorsSolidPimpl {
public:
    static G4ThreeVector getG4Vector3f(const Vector3f &vector) {
        return G4ThreeVector( vector(0), vector(1), vector(2) );
    }
};



Solid::Solid() :
    m_Logical (new G4LogicalVolume(NULL,NULL,"unnamed_solid")),
    m_Material(NULL)
{}

Solid::Solid(const char *name) :
    m_Logical(new G4LogicalVolume(NULL,NULL,name)),
    m_Material(NULL)
{}



void Solid::SetNistMaterial(const char *name)
{
    G4NistManager *nist = G4NistManager::Instance();
    if (m_Material) delete m_Material;
    m_Material = nist->FindOrBuildMaterial(name);
    m_Logical->SetMaterial(m_Material);
}

void Solid::SetMaterial(G4Material *material)
{
    if(material)
    {
        m_Material = material;
        m_Logical->SetMaterial(material);
    }
}










TessellatedSolid::TessellatedSolid(const char *name) :
    BaseClass(name),
    m_Solid(new G4TessellatedSolid(name))
{}


void TessellatedSolid::SetMesh(TriangleMesh &mesh)
{
    G4TessellatedSolid *ts = this->m_Solid;
    for (int i=0; i<mesh.Triangles().size(); ++i) {
        const Vector3i &trg = mesh.Triangles().at(i);
        G4TriangularFacet *facet = new G4TriangularFacet(
                    DetectorsSolidPimpl::getG4Vector3f(mesh.Points().at(trg(0))),
                    DetectorsSolidPimpl::getG4Vector3f(mesh.Points().at(trg(1))),
                    DetectorsSolidPimpl::getG4Vector3f(mesh.Points().at(trg(2))),
                    ABSOLUTE);
        ts->AddFacet((G4VFacet *)facet);
    }
    this->m_Logical->SetSolid(ts);
}


}
