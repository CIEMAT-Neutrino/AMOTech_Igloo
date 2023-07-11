#ifndef CONSRTUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4VisAttributes.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();

	virtual G4VPhysicalVolume *Construct();

private:
	
	virtual void ConstructSDandField();

	G4double wallThick, ceilingThick;

	G4Box *solidWorld, *solidCeiling, *solidIron, *solidDetector;
	G4Box *outerIgloo, *innerIgloo; 
	G4SubtractionSolid *solidWall;
	
	G4LogicalVolume *logicWorld, *logicWall, *logicCeiling, *logicIron, *logicDetector;
	G4VPhysicalVolume *physWorld, *physWall, *physCeiling, *physIron, *physDetector;

	G4Material *worldMat, *Conc, *water, *iron;
	G4double insideS, insideH, insideL;

	G4GenericMessenger *fMessenger;

	void DefineMaterials();

	G4VisAttributes* logicConcVisAtt   = new G4VisAttributes(G4Colour(0.46, 0.53, 0.6, 0.3));
	G4VisAttributes* logicDetectorVisAtt   = new G4VisAttributes(G4Colour(0.0, 0.6, 1.0, 1)); //blue
	G4VisAttributes* logicIronVisAtt   = new G4VisAttributes(G4Colour(1.0, 0.5, 0.0, 1)); //orange
};

#endif
