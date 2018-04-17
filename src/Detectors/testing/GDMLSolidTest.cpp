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




#include <Geant4/G4RunManager.hh>

#include <Geant4/G4Material.hh>
#include <Geant4/G4NistManager.hh>

#include <Geant4/G4Box.hh>
#include <Geant4/G4TessellatedSolid.hh>
#include <Geant4/G4LogicalVolume.hh>
#include <Geant4/G4PVPlacement.hh>

#include <Geant4/G4GDMLParser.hh>
//#include <Geant4/G4GDMLRead.hh>
//#include <Geant4/G4GDMLReadSolids.hh>


#include "Detectors/Solid.h"
#include "testing-prototype.h"




int main()
{

//    G4RunManager* runManager = new G4RunManager;

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *air = nist->FindOrBuildMaterial("G4_AIR");



    G4Box *box = new G4Box("box",5,5,5);

    G4LogicalVolume box_lv(NULL,NULL,"box test");
    box_lv.SetSolid(box);
    box_lv.SetMaterial(air);
    G4PVPlacement  box_pl(0,G4ThreeVector(),&box_lv,"box test",0,0,0);

    G4GDMLParser parser;

    parser.Write("test_out.gdml",&box_lv);


}
