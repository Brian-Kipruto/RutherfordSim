#include "DetectorConstruction.hh"
#include "G4ios.hh" // Include for G4cout

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh" // For visualization colors

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction()
{ }

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4cout << "DetectorConstruction::Construct() starting..." << G4endl;
  // Get NIST material manager
  G4NistManager* nist = G4NistManager::Instance();

  // --- Define Materials ---
  // Vacuum for the world
  G4cout << "--> Defining World Material..." << G4endl;
  G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");
  if (!worldMat) {
      G4cerr << "ERROR: Failed to build World material (G4_Galactic)!" << G4endl;
      // Optional: exit or throw exception here if critical
  } else {
      G4cout << "    World Material: " << worldMat->GetName() << G4endl;
  }


  // Gold for the foil
  G4cout << "--> Defining Foil Material..." << G4endl;
  G4Material* foilMat = nist->FindOrBuildMaterial("G4_Au");
  // **** ADD CHECK FOR FOIL MATERIAL ****
  if (!foilMat) {
      G4cerr << "ERROR: Failed to build Foil material (G4_Au)!" << G4endl;
      // Optional: exit or throw exception here if critical, otherwise foilLog creation will fail
  } else {
      G4cout << "    Foil Material: " << foilMat->GetName() << G4endl;
  }

  // --- Define Volumes ---
  // World
  G4cout << "--> Defining World Volume..." << G4endl;
  G4double worldSize = 1.0*m; // Make the world 1 meter cubed
  G4Box* worldSolid = new G4Box("WorldSolid", 0.5*worldSize, 0.5*worldSize, 0.5*worldSize);
  worldLog = new G4LogicalVolume(worldSolid, worldMat, "WorldLog");
  G4VPhysicalVolume* worldPhys = new G4PVPlacement(0,                     // no rotation
                                     G4ThreeVector(),       // at (0,0,0)
                                     worldLog,              // its logical volume
                                     "WorldPhys",           // its name
                                     0,                     // its mother volume (none)
                                     false,                 // no boolean operation
                                     0,                     // copy number
                                     true);                 // check overlaps
   G4cout << "    World Logical Volume created." << G4endl;


  // Foil
  G4cout << "--> Defining Foil Volume..." << G4endl;
  G4double foilThickness = 1.0 * um; // 1 micrometer thick foil
  G4double foilSizeXY = 10.0 * cm;   // 10 cm wide foil
  G4Box* foilSolid = new G4Box("FoilSolid", 0.5*foilSizeXY, 0.5*foilSizeXY, 0.5*foilThickness);

  // **** ADD CHECK BEFORE CREATING FOIL LOGICAL VOLUME ****
  if (foilMat) { // Only proceed if foilMat is valid
      foilLog = new G4LogicalVolume(foilSolid, foilMat, "FoilLog");
      // **** ADD CHECK FOR FOIL LOGICAL VOLUME ****
      if (!foilLog) {
          G4cerr << "ERROR: Failed to create Foil Logical Volume!" << G4endl;
      } else {
           G4cout << "    Foil Logical Volume created." << G4endl;
           new G4PVPlacement(0,                       // no rotation
                             G4ThreeVector(0, 0, 0),  // place foil at the center of the world
                             foilLog,                 // its logical volume
                             "FoilPhys",              // its name
                             worldLog,                // its mother volume (World)
                             false,                   // no boolean operation
                             0,                       // copy number
                             true);                   // check overlaps
           G4cout << "    Foil Physical Volume placed." << G4endl;
      }
  } else {
      G4cerr << "ERROR: Skipping Foil Logical Volume creation because material is invalid." << G4endl;
  }


  // --- Visualization Attributes ---
  G4cout << "--> Setting Vis Attributes..." << G4endl;
  worldLog->SetVisAttributes(G4VisAttributes::GetInvisible()); // Make world invisible
  if (foilLog) { // Only set attributes if foilLog is valid
      G4VisAttributes* foilVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0)); // Yellow foil
      foilLog->SetVisAttributes(foilVisAtt);
      G4cout << "    Foil Vis Attributes set." << G4endl;
  }

  G4cout << "DetectorConstruction::Construct() finished." << G4endl;
  // Always return the physical World
  return worldPhys;
}