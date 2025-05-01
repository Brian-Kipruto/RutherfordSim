#ifndef DetectorConstruction_HH
#define DetectorConstruction_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4PhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct(); // this is the main method for building geometry

private:
G4LogicalVolume*worldLog = nullptr;
G4LogicalVolume*foilLog = nullptr;

//remember to add incase i will need other private members
};
#endif

