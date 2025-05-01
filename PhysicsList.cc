#include "PhysicsList.hh"

#include "G4EmStandardPhysics_option4.hh" //option 4 for best accuracy during scattering
#include "G4OpticalPhysics.hh" // often needed for G4EmstandardPhysics constructor
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
  SetVerboseLevel(1);

  // Standard EM physics _option4 for higher accuracy scattering
  RegisterPhysics(new G4EmStandardPhysics_option4());

  // Standard Decay Physics
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // Set default cuts
  SetDefaultCutValue(0.7*mm); // Example cut value
}

PhysicsList::~PhysicsList()
{}