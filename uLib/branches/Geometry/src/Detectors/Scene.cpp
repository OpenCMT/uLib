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





#include <Geant4/G4Material.hh>
#include <Geant4/G4NistManager.hh>
#include <Geant4/G4LogicalVolume.hh>
#include <Geant4/G4GDMLParser.hh>

#include "Core/Vector.h"
#include "Matter.h"
#include "Solid.h"

#include "Scene.h"


namespace uLib {


class DetectorsScenePimpl {

public:


    // members //
    //Vector<Solid> m_Solids;
};




DetectorsScene::DetectorsScene() :
    d(new DetectorsScenePimpl())
{}

DetectorsScene::~DetectorsScene()
{
    delete d;
}

void DetectorsScene::AddSolid(const Solid &solid)
{
//    d->m_Solids.push_back(solid);
}





}
