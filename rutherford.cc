#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = nullptr;
  if (argc == 1) { // Interactive mode
    ui = new G4UIExecutive(argc, argv);
  }

  // Construct the appropriate Run Manager
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  // Set mandatory user initialization classes for master thread (optional)
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());

  // Initialize Visualization Manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get pointer to UI manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  if (!ui) {
    // Batch mode
    if (argc != 2) {
        G4cerr << "Usage: " << argv[0] << " <macro_file>" << G4endl;
        return 1;
    }
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  } else {
    // Interactive mode
    // You might want a default macro like vis.mac or init_vis.mac
    // UImanager->ApplyCommand("/control/execute init_vis.mac"); // Uncomment if you create this file
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  delete visManager;
  delete runManager; // Deleting RunManager deletes registered user classes

  return 0;
}