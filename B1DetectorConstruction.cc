//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolumeStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "B1BOptrMultiParticleChangeCrossSection.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
  // fOverlaypVolume(0)
 
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  

   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  //create a new material to simulate space environment
  G4Material* world_mat = new G4Material("Space",1.,1.01*g/mole,1.e-25*g/cm3,kStateGas,0.1*kelvin,1.e-19*pascal);
  G4double world_sizeXY = 15*um;
  G4double world_sizeZ  = 15*um;
  // G4Material* world_mat = nist->FindOrBuildMaterial("G4_Si");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       world_sizeXY/2, world_sizeXY/2, world_sizeZ/2);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                   //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  // 
  // Envelope parameters
  //
  G4double env_sizeX = 10.3315*um;
  G4double env_sizeY=8.9539*um;
  G4double env_sizeZ = 10*um;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_Si");

  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        env_sizeX/2, env_sizeY/2, env_sizeZ/2); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0                      //copy number
                    );          //overlaps checking
 
  //     
  // Overlap
  //  
  // G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_Si");
  // G4ThreeVector pos1 = G4ThreeVector(0,0,0);
        
  // // overlap       
  // G4double shape1_sizeX = 10.3315*um;
  // G4double shape1_sizeY=8.9539*um;
  // G4double shape1_sizeZ = 10*um;
  // G4Box* solidShape1=
  //  new G4Box("Overlap",
  //  shape1_sizeX/2,shape1_sizeY/2,shape1_sizeZ/2 );
                      
  // G4LogicalVolume* logicShape1 =                         
  //   new G4LogicalVolume(solidShape1,         //its solid
  //                       shape1_mat,          //its material
  //                       "Overlap");           //its name
               
  // new G4PVPlacement(0,                       //no rotation
  //                   pos1,                    //at position
  //                   logicShape1,             //its logical volume
  //                   "Overlap",                //its name
  //                   logicEnv,                //its mother  volume
  //                   false,                   //no boolean operation
  //                   0);                     //copy number);
  //                             //overlaps checking

  //     
  // sensitive volume
  //
  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_Si");
  G4ThreeVector pos2 = G4ThreeVector(0,0,0);

  //box
  //SV area equals to    
 G4double shape2_sizeXY=1.5*um; G4double shape2_sizeZ=0.4*um;
  G4Box* solidShape2 =    
    new G4Box("SV",                      //its name
              shape2_sizeXY/2,shape2_sizeXY/2,shape2_sizeZ/2); //its size
                
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "SV");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "SV",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0                     //copy number
                    );          //overlaps checking
                
  // Set Sensitive Volume as scoring volume
  //
  // fOverlaypVolume = logicShape1;
  fScoringVolume = logicShape2;
  //
  //always return the physical World
  //
  return physWorld;
}

void B1DetectorConstruction::ConstructSDandField()
{
  // -- Fetch volume for biasing:
  G4LogicalVolume* logicEnv = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
  
  // ----------------------------------------------
  // -- operator creation and attachment to volume:
  // ----------------------------------------------
B1BOptrMultiParticleChangeCrossSection* testMany = 
    new B1BOptrMultiParticleChangeCrossSection();
  testMany->AddParticle("proton");
  testMany->AttachTo(logicEnv);
  // testMany->AddParticle("neutron");
  testMany->AttachTo(logicEnv);
  G4cout << " Attaching biasing operator " << testMany->GetName()
             << " to logical volume " << logicEnv->GetName()
             << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
