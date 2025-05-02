#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"


ActionInitialization::ActionInitialization():G4VUserActionInitialization(){

};

ActionInitialization::~ActionInitialization(){

};

void ActionInitialization::BuildForMaster()const{

} //called for master thread not needed now bu required

void ActionInitialization::Build()const{
SetUserAction(new PrimaryGeneratorAction());
//SetUserAction(new RunAction());
//SetUserAction(new EventAction());
//SetUserAction(new SteppingAction());
}
