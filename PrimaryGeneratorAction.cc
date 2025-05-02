#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4Alpha.hh" // Include for alpha particle

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1; // Shoot one particle per event
  fParticleGun = new G4ParticleGun(n_particle);

  // Get particle table
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  // Set particle type to alpha
  G4ParticleDefinition* particle = G4Alpha::AlphaDefinition();
  fParticleGun->SetParticleDefinition(particle);

  // Set particle energy
  fParticleGun->SetParticleEnergy(5.0*MeV); // Rutherford used ~5 MeV alphas

  // Set particle position (start just before the foil)
  // World is 1m, foil is at z=0. Start at z = -10 cm.
  fParticleGun->SetParticlePosition(G4ThreeVector(0.*cm, 0.*cm, -10.*cm));

  // Set particle momentum direction (towards positive Z, hitting the foil)
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

// This method is called at the beginning of each event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}