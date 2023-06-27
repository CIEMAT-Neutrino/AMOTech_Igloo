#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "Randomize.hh"

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

#include "TMath.h"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction{

public:
	MyPrimaryGenerator();
	~MyPrimaryGenerator();

	virtual void GeneratePrimaries(G4Event*);

	G4double DifferentialFlux(double energy);


private:
	G4ParticleGun *fParticleGun;

	G4double rad = 8*m;
	G4double phi, cosTheta, sinTheta; 
	/*
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	*/
	bool defaultGenerator = true;

};

#endif
