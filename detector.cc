#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) :  G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
	G4Track *track = aStep->GetTrack();

	track->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

	//Particles paramaters
	const G4ParticleDefinition *particle = track->GetParticleDefinition();

	G4int particleID = particle->GetPDGEncoding();
	G4String particleName[10] = {particle->GetParticleName()};
	G4ThreeVector posParticle = preStepPoint->GetPosition();
	G4ThreeVector momParticle = preStepPoint->GetMomentum();
	momentum = sqrt(momParticle[0]*momParticle[0]+momParticle[1]*momParticle[1]+momParticle[2]*momParticle[2]);
	G4double TotEnergyParticle = preStepPoint->GetTotalEnergy();
	G4double kinEnergy = preStepPoint->GetKineticEnergy();
	G4double mass = preStepPoint->GetMass();


	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	//if(evt%1000==0){
	//	G4cout << "Event: " << evt << " \n" << G4endl;
	//}
	

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0, evt);
	man->FillNtupleDColumn(1, posParticle[0]);
	man->FillNtupleDColumn(2, posParticle[1]);
	man->FillNtupleDColumn(3, posParticle[2]);
	man->FillNtupleDColumn(4, momParticle[0]);
	man->FillNtupleDColumn(5, momParticle[1]);
	man->FillNtupleDColumn(6, momParticle[2]);
	man->FillNtupleDColumn(7, momentum);
	man->FillNtupleDColumn(8, TotEnergyParticle);
	man->FillNtupleDColumn(9, kinEnergy);
	man->FillNtupleDColumn(10, mass);
	man->FillNtupleIColumn(11, particleID);
	man->AddNtupleRow(0);
	

	return true;
}
