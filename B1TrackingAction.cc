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
// -------------------------------------------------------------------
// -------------------------------------------------------------------
//*The B1TrackingAtion.cc is from B1TrackingAction.hh, and this step is used*
//*to calculate energy deposition of a track, the formula is Ed=sigma(wi*Ei)*

#include "B1TrackingAction.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "B1EventAction.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include <iomanip>
#include "G4ios.hh"
using namespace std;


B1TrackingAction::B1TrackingAction(B1EventAction* eventAction)
: G4UserTrackingAction(),
  fEventAction(eventAction),
  TdepWithWeight(0.),
  fTdep(0.),
  weight(0.),
  TrackingProcessName{{}}
{}


void B1TrackingAction::PreUserTrackingAction(const G4Track*)
{    
    TdepWithWeight=0;
    fTdep=0;
    // G4cout<<G4endl
    //            <<"The deposited energy in this track is: "
    //            <<G4BestUnit(fTdep,"Energy")
    //            <<G4endl;
   weight = 1;
   TrackingProcessName.clear();
}


void B1TrackingAction::PostUserTrackingAction(const G4Track*)
{
    // G4cout<<G4endl
    //            <<"The deposited energy in this track is: "
    //            <<G4BestUnit(fTdep,"Energy")
    //            <<G4endl;
    // weight = track->GetWeight();
    weight = 1;
    // G4cout
    //          <<G4endl
    //          <<"The weight is: "
    //          <<weight
    //          <<G4endl;
    TdepWithWeight = fTdep*weight;
    // G4cout<<G4endl
    //        <<"The deposited energy with weight in this track is: "
    //        <<G4BestUnit(TdepWithWeight,"Energy")
    //        <<G4endl;

    fEventAction->AddEdep(TdepWithWeight );
    fEventAction->GetProcName(TrackingProcessName);
}

