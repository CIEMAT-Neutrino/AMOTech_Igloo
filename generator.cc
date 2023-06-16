#include "generator.hh"

//using namespace CLHEP;

MyPrimaryGenerator::MyPrimaryGenerator(){
	fParticleGun = new G4ParticleGun(1);

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "neutron";
	G4ParticleDefinition *particle = particleTable->FindParticle("neutron");
	
	fParticleGun->SetParticleEnergy(100.*MeV);
	fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator(){
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent){

	rc = sqlite3_open("Data/p_showers_210200.db", &db);

	if(rc){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		defaultGenerator = true;
	}else{
		fprintf(stderr, "Opened database successfully\n");
	}
	sqlite3_close(db);

	if(defaultGenerator){
		/* Another default generation
		G4double Srand = (G4UniformRand()*2-1)*(2.4);
		G4double Lrand = (G4UniformRand()*2-1)*(4.0);
		G4double H = 7.;
		G4ThreeVector pos(Srand*m, H*m, Lrand*m); //Horizonal axes are x and z, vertical is y
		*/

		phi = G4UniformRand()*2.0*pi;
		cosTheta = G4UniformRand();
		sinTheta = sqrt(1.0 - cosTheta*cosTheta);
		G4ThreeVector pos(rad*TMath::Cos(phi)*sinTheta, rad*cosTheta ,rad*TMath::Sin(phi)*sinTheta); //Horizonal axes are x and z, vertical is y

		G4ThreeVector down = G4ThreeVector(0., -1., 0.);
		G4ThreeVector mom = -1.0*pos;

		fParticleGun->SetParticlePosition(pos);
		fParticleGun->SetParticleMomentumDirection(mom);

		fParticleGun->GeneratePrimaryVertex(anEvent);
	}
}
