
#include <Geant4/G4RunManager.hh>

#include <Geant4/G4Material.hh>
#include <Geant4/G4NistManager.hh>

#include <Geant4/G4Box.hh>
#include <Geant4/G4TessellatedSolid.hh>
#include <Geant4/G4LogicalVolume.hh>

#include <Geant4/G4GDMLParser.hh>
//#include <Geant4/G4GDMLRead.hh>
//#include <Geant4/G4GDMLReadSolids.hh>



#include "Math/TriangleMesh.h"
#include "Vtk/vtkTriangleMesh.h"

#include "Detectors/Solid.h"

using namespace uLib;



namespace Material {

G4Material *StainlessSteel(float dens = 8.06) { // <- g/cm3
    G4NistManager* man = G4NistManager::Instance();
    man->SetVerbose(1);

    // Define elements from NIST
    G4Element* C  = man->FindOrBuildElement("C");
    G4Element* Si = man->FindOrBuildElement("Si");
    G4Element* Cr = man->FindOrBuildElement("Cr");
    G4Element* Mn = man->FindOrBuildElement("Mn");
    G4Element* Fe = man->FindOrBuildElement("Fe");
    G4Element* Ni = man->FindOrBuildElement("Ni");


    // Define materials not in NIST
    G4double density = dens*g/cm3;
    G4int ncomponents;
    G4double fractionmass;
    G4Material* StainlessSteel = new G4Material("StainlessSteel", density, ncomponents=6);
    StainlessSteel->AddElement(C, fractionmass=0.001);
    StainlessSteel->AddElement(Si, fractionmass=0.007);
    StainlessSteel->AddElement(Cr, fractionmass=0.18);
    StainlessSteel->AddElement(Mn, fractionmass=0.01);
    StainlessSteel->AddElement(Fe, fractionmass=0.712);
    StainlessSteel->AddElement(Ni, fractionmass=0.09);
    return StainlessSteel;
}

//G4Material *ASTM_A710(float dens = 7.85) { // <- g/cm3
//    G4NistManager* man = G4NistManager::Instance();
//    man->SetVerbose(1);

//    // Define elements from NIST
//    G4Element* C  = man->FindOrBuildElement("C");
//    G4Element* Cr = man->FindOrBuildElement("Cr");
//    G4Element* Cu = man->FindOrBuildElement("Cu");
//    G4Element* Fe = man->FindOrBuildElement("Fe");
//    G4Element* Mn = man->FindOrBuildElement("Mn");
//    G4Element* Mo = man->FindOrBuildElement("Mo");
//    G4Element* Ni = man->FindOrBuildElement("Ni");
//    G4Element* Nb = man->FindOrBuildElement("Nb");
//    G4Element* P  = man->FindOrBuildElement("P");
//    G4Element* Si = man->FindOrBuildElement("Si");
//    G4Element* S  = man->FindOrBuildElement("S");


//    // Define materials not in NIST
//    G4double density = dens*g/cm3;
//    G4int ncomponents;
//    G4double fractionmass;
//    G4Material* StainlessSteel = new G4Material("StainlessSteel", density, ncomponents=6);
//    StainlessSteel->AddElement(C, fractionmass=0.0007);
//    StainlessSteel->AddElement(Cr, fractionmass=0.18);
//    StainlessSteel->AddElement(Cr, fractionmass=0.18);
//    StainlessSteel->AddElement(Cr, fractionmass=0.18);
//    StainlessSteel->AddElement(Si, fractionmass=0.007);
//    StainlessSteel->AddElement(Mn, fractionmass=0.01);
//    StainlessSteel->AddElement(Fe, fractionmass=0.712);
//    StainlessSteel->AddElement(Ni, fractionmass=0.09);
//    return StainlessSteel;
//}


G4Material *Tungsten(float dens = 19.25) { // <- g/cm3
    G4NistManager* man = G4NistManager::Instance();
    man->SetVerbose(1);

    G4Element* Wf  = man->FindOrBuildElement("W");

    G4double density = dens*g/cm3;
    G4int ncomponents;
    G4double fractionmass;
    G4Material* Tungsten = new G4Material("Tungsten", density, ncomponents=1);
    Tungsten->AddElement(Wf, fractionmass=1);
    return Tungsten;
}


}



#include <Geant4/G4PVPlacement.hh>

int main()
{

    G4GDMLParser parser;
    G4Material *steel = Material::StainlessSteel();

    // Acciaio1 //
    {
        TriangleMesh mesh;
        vtkTriangleMesh v_mesh(mesh);
        v_mesh.ReadFromObjFile("objects/ByMaterial/Acciaio1.obj");
        mesh.PrintSelf(std::cout);
        TessellatedSolid solid("telaio1");
        solid.SetMaterial(steel);
        solid.SetMesh(mesh);
        parser.Write("telaio1.gdml",solid.GetLogical());
    }

    // Acciaio2 //
    {
        TriangleMesh mesh;
        vtkTriangleMesh v_mesh(mesh);
        v_mesh.ReadFromObjFile("objects/ByMaterial/Acciaio2.obj");
        mesh.PrintSelf(std::cout);
        TessellatedSolid solid("telaio2");
        solid.SetMaterial(steel);
        solid.SetMesh(mesh);
        parser.Write("telaio2.gdml",solid.GetLogical());
    }

    // Assali //
    {
        TriangleMesh mesh;
        vtkTriangleMesh v_mesh(mesh);
        v_mesh.ReadFromObjFile("objects/ByMaterial/Assali.obj");
        mesh.PrintSelf(std::cout);
        TessellatedSolid solid("assali");
        solid.SetMaterial(steel);
        solid.SetMesh(mesh);
        parser.Write("assali.gdml",solid.GetLogical());
    }


}
