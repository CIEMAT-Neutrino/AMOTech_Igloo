#include "run.hh"

MyRunAction::MyRunAction(){

	G4AnalysisManager *man = G4AnalysisManager::Instance();	
	
	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");	
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->CreateNtupleDColumn("fPx");
	man->CreateNtupleDColumn("fPy");
	man->CreateNtupleDColumn("fPz");
	man->CreateNtupleDColumn("fMomentum");
	man->CreateNtupleDColumn("fTotalEnergy");
	man->CreateNtupleDColumn("fKineticEnergy");
	man->CreateNtupleDColumn("fMass");
	man->CreateNtupleIColumn("fParticleID");
	man->CreateNtupleSColumn("fParticleName");
	man->FinishNtuple(0);
}

MyRunAction::~MyRunAction(){}

void MyRunAction::BeginOfRunAction(const G4Run* run){
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	G4int runID = run->GetRunID();

	G4cout << "************** Run ID: " << runID << "*******************" << G4endl;

	std::stringstream strRunID;
	strRunID << runID ;

	man->OpenFile("output"+strRunID.str()+".root");
	

}

void MyRunAction::EndOfRunAction(const G4Run*){
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man->Write();
	man->CloseFile();
	G4cout << "************** end of run *******************" << G4endl;

}
