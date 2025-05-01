#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh" // For colors during visualiing

DetectorConstruction::DetectorConstruction():G4VUserDetectorConstruction(){

}

DetectorConstruction::~DetectorConstruction(){

}

G4VPhysicalVolume * DetectorConstruction:: Construct(){
G4cout <<"DetectorConstruction::Construct() starting..." <<G4endl;

//Getting the NIST material manager
G4NistManager* nist = G4NistManager::Instance();

//defining the materials and the vacuum for the world and gold for the foil
G4Material*worldMat = nist->FindOrBuildMaterial("G4_Galactic");
G4Material* foilMat = nist->FindOrBuildMaterial("G4_AU");

//Defining the volumes for both the world and the foil
G4double worldSize = 1.0*m; //the worldis a meter cubes

G4Box* worldSolid = new G4Box ("WorldSolid", 0.5*worldSize, 0.5*worldSize, 0.5*worldSize);
worldLog = new G4LogicalVolume(worldSolid, worldMat, "WorldLog");
G4VPhysicalVolume*worldPhys = new G4PVPlacement(
0, //kein rotation
G4ThreeVector(), //@ (0,0,0)
worldLog,  //the worlds logical volume
"WorldPhys",//the world sname
0,false,0,true //this just shows the mother volume(none), no boolean op, copying he number, checks for overlaps
);

//FOR the foil
G4double foilThick = 1.0*um; //1 micrometer
G4double foilSizeXY = 10.0*cm;

G4Box* foilSolid = new G4Box ("FoilSolid", 0.5*foilSizeXY,0.5*foilSizeXY,0.5*foilThick);
foilLog = new G4LogicalVolume(foilSolid, foilMat, "FoilLog");
new G4PVPlacement (
    0,
    G4ThreeVector(0,0,0),
    foilLog,
    "FoilPhys",
    worldLog,
    false, 0, true
);

//For visualizing
worldLog->SetVisAttributes(G4VisAttributes::GetInvisible()); // Make world invisible
G4VisAttributes* foilVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0)); // Yellow foil
foilLog->SetVisAttributes(foilVisAtt);

G4cout << "DetectorConstruction::Construct() finished." << G4endl;

return worldPhys;

}
