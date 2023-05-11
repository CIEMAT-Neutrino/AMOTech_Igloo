//source /cvmfs/sft.cern.ch/lcg/views/LCG_100/x86_64-centos7-gcc8-opt/setup.sh
//source /cvmfs/sft.cern.ch/lcg/views/LCG_100/x86_64-centos7-gcc8-opt/bin/geant4.sh

//source /cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc12-opt/setup.sh
//source /cvmfs/sft.cern.ch/lcg/views/LCG_103/x86_64-centos7-gcc12-opt/bin/geant4.sh

//cmake -DGeant4_DIR=/cvmfs/sft.cern.ch/lcg/releases/Geant4/10.07.p01-daa34/x86_64-centos7-gcc8-opt ../
//cmake -DGeant4_DIR=/cvmfs/sft.cern.ch/lcg/releases/Geant4/11.1.1-be329/x86_64-centos7-gcc12-opt/ ../

# include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "QGSP_INCLXX_HP.hh"
//#include "Shielding.hh"
#include "physics.hh"
#include "action.hh"


int main(int argc, char** argv){
	
	G4RunManager *runManager = new G4RunManager();

	runManager->SetUserInitialization(new MyDetectorConstruction());
	//Physics lists:
	//runManager->SetUserInitialization(new Shielding); 
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new QGSP_INCLXX_HP);
	//
	runManager->SetUserInitialization(new MyActionInitialization());

	runManager->Initialize();

	G4UIExecutive *ui = 0;

	if(argc == 1){	
		ui = new G4UIExecutive(argc, argv);
	}


	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	if(ui){
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
	}else{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
    
	return 0;
}
