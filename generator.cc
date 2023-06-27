#include "generator.hh"

using namespace CLHEP;

MyPrimaryGenerator::MyPrimaryGenerator(){
	fParticleGun = new G4ParticleGun(1);

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "neutron";
	G4ParticleDefinition *particle = particleTable->FindParticle("neutron");
	
	fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator(){
	delete fParticleGun;
}

G4double MyPrimaryGenerator::DifferentialFlux(double energy){
	double b[] = {0.35, 0.4106};
	double g[] = {2.1451, -0.667};
	double c[] = {1.006e-6, 1.011e-3};

	G4double flux = 0.0;
	for(int i = 0; i < 2; i++){
		flux += c[i]*exp(-b[i]*log(energy)*log(energy) + g[i]*log(energy));
	}
	return flux;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent){


	//Another default generation
	G4double Srand = (G4UniformRand()*2-1)*(2.4);
	G4double Lrand = (G4UniformRand()*2-1)*(4.0);
	G4double H = 7.;
	G4ThreeVector pos(Srand*m, H*m, Lrand*m); //Horizonal axes are x and z, vertical is y

	G4double energy_rand, prob, rand;
	while(true){
		energy_rand = G4UniformRand()*999.0+1.0;
		
		rand = G4UniformRand();
		prob = DifferentialFlux(energy_rand)/DifferentialFlux(1.0);
		if(rand < prob){
			break;
		}

	}
	fParticleGun->SetParticleEnergy(energy_rand*MeV);

	/*
	phi = G4UniformRand()*2.0*pi;
	cosTheta = G4UniformRand();
	sinTheta = sqrt(1.0 - cosTheta*cosTheta);
	G4ThreeVector pos(rad*TMath::Cos(phi)*sinTheta, rad*cosTheta ,rad*TMath::Sin(phi)*sinTheta); //Horizonal axes are x and z, vertical is y
	*/
	G4ThreeVector down = G4ThreeVector(0., -1., 0.);
	G4ThreeVector mom = -1.0*pos;

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(down);

	fParticleGun->GeneratePrimaryVertex(anEvent);
}
