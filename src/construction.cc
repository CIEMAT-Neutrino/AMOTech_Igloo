
#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction(){
	fMessenger = new G4GenericMessenger(this, "/shield/","Shielding construction");

	fMessenger->DeclareProperty("wallThick", wallThick, "Thickness of the walls (meters)");
	wallThick = 1.6; //Set thickness of the walls (meters)

	fMessenger->DeclareProperty("ceilingThick", ceilingThick, "Thickness of the ceiling (meters)");
	ceilingThick = 0.8; //Set thickness of the ceiling (meters)

	DefineMaterials();
	
	insideH = 2.4; //Set half height of the inside (meters) 
	insideL = 4.0; //Set half length of the inside (meters)
	insideS = insideH; //Set half side of the inside (meters)
}

MyDetectorConstruction::~MyDetectorConstruction(){}

void MyDetectorConstruction::DefineMaterials(){
	G4NistManager *nist = G4NistManager::Instance();

	water = nist->FindOrBuildMaterial("G4_WATER");
	Conc = nist->FindOrBuildMaterial("G4_CONCRETE");
	iron = nist->FindOrBuildMaterial("G4_Fe");

	worldMat = nist->FindOrBuildMaterial("G4_AIR");

}

G4VPhysicalVolume *MyDetectorConstruction::Construct(){

	solidWorld = new G4Box("solidWorld", 25*m, 25*m, 25*m);
	logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
	logicWorld->SetVisAttributes(new G4VisAttributes(G4Colour(0., 0., 0.)));

	outerIgloo = new G4Box("outerIgloo", (insideS + wallThick)*m, insideH*m, (insideL + wallThick)*m);
	innerIgloo = new G4Box("innerIgloo", insideS*m, insideH*m, insideL*m);
	solidWall = new G4SubtractionSolid("solidWall", outerIgloo, innerIgloo);
	logicWall = new G4LogicalVolume(solidWall, Conc, "logicConc");
	physWall = new G4PVPlacement(0, G4ThreeVector(0., insideH*m, 0.), logicWall, "physWall", logicWorld, false, 0, true);
	logicWall->SetVisAttributes(logicConcVisAtt);

	solidIron = new G4Box("solidIron", 3.7*m, 0.085*m, 0.2*22*m);
	logicIron = new G4LogicalVolume(solidIron, iron, "logicIron");
	physIron = new G4PVPlacement(0, G4ThreeVector(0., (insideH*2+ceilingThick+0.085)*m, 0.), logicIron, "physIron", logicWorld, false, 0, true);
	logicIron->SetVisAttributes(logicIronVisAtt);

	solidCeiling = new G4Box("solidCeiling", (insideS+wallThick)*m, ceilingThick/2*m, (insideL+wallThick)*m);
	logicCeiling = new G4LogicalVolume(solidCeiling, Conc, "logicCeiling");
	physCeiling =	new G4PVPlacement(0, G4ThreeVector(0., (insideH*2+ceilingThick/2)*m, 0.), logicCeiling, "physCeiling", logicWorld, false, 0, true);
	logicCeiling->SetVisAttributes(logicConcVisAtt);
	
	//Only one detector
	solidDetector = new G4Box("solidDetector", insideS*m, insideH*m, insideL*m);
	logicDetector = new G4LogicalVolume(solidDetector, worldMat,"logicDetector");
	physDetector = new G4PVPlacement(0,G4ThreeVector(0., insideH*m, 0.),logicDetector, "physDetector", logicWorld, false, 0, true);
	logicDetector->SetVisAttributes(logicDetectorVisAtt);

	return physWorld;
}


void MyDetectorConstruction::ConstructSDandField(){

	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicDetector->SetSensitiveDetector(sensDet);

}

