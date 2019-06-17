#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SubtractionSolid.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4AssemblyVolume.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "DetectionSystemPlastics.hh"

#include "G4SystemOfUnits.hh"

#include <string>

//DetectionSystemPlastics::DetectionSystemPlastics(G4double length, G4double height, G4double width, G4int material):
DetectionSystemPlastics::DetectionSystemPlastics(G4double thickness, G4int material):
    // LogicalVolumes
    fPlasticLog(0)
 //   fTestcanAlumCasingLog(0),
   // fTestcanScintillatorLog(0),
   // fTestcanQuartzWindowLog(0)
{
    // can properties
    fScintillatorLength        = 6.*cm;
    fScintillatorHeight        = 6.*cm;
    fScintillatorWidth         = thickness;
   
   if(material == 1)  fPlasticMaterial = "BC408";
	else if (material == 2) fPlasticMaterial = "Deuterium";
	else if (material == 3) fPlasticMaterial = "H";
	else if (material == 4) fPlasticMaterial = "C";
	else G4cout<< "Material Unknown" << G4endl;


/*    fScintillatorLength        = length;
    fAlumCanThickness          = 1.0*mm;
    fScintillatorInnerRadius   = 0.0*mm;
    fScintillatorOuterRadius   = radius;
    fQuartzThickness           = 6.35*mm;
    fQuartzRadius              = radius + fAlumCanThickness;
    fCanMaterial               = "G4_Al";
    fLiquidMaterial            = "Deuterated Scintillator";
    fQuartzMaterial            = "G4_SILICON_DIOXIDE";

    fStartPhi               = 0.0*deg;
    fEndPhi                 = 360.0*deg;
   
    fLiquidColour           = G4Colour(0.0/255.0,255.0/255.0,225.0/255.0);
    fGreyColour             = G4Colour(0.5, 0.5, 0.5); 
    fQuartzColour           = G4Colour(1.0, 0.0, 1.0);   
*/ 
G4cout << "Calling Constructor" << G4endl;
}


DetectionSystemPlastics::~DetectionSystemPlastics() {
    // LogicalVolumes
 /*   delete fTestcanAlumCasingLog;
    delete fTestcanScintillatorLog;
    delete fTestcanQuartzWindowLog;
*/
delete fPlasticLog;
G4cout << "Calling Destructor" << G4endl;

}


G4int DetectionSystemPlastics::Build() {
    fAssemblyPlastics = new G4AssemblyVolume(); 
G4cout << "Calling Build function" << G4endl;
    BuildPlastics();

    return 1;
}

G4int DetectionSystemPlastics::PlaceDetector(G4LogicalVolume* expHallLog) {
    G4RotationMatrix * rotate = new G4RotationMatrix;
    G4ThreeVector move = G4ThreeVector(0., 0., 0.);

    fAssemblyPlastics->MakeImprint(expHallLog, move, rotate);
G4cout << "Calling place detector" << G4endl;
    return 1;
}

G4int DetectionSystemPlastics::BuildPlastics() {
 
G4cout << "Calling Build PLastics" << G4endl;


    G4ThreeVector move, direction;
    G4RotationMatrix* rotate;

    G4Material* plasticG4material = G4Material::GetMaterial(fPlasticMaterial);
    if( !plasticG4material ) {
        G4cout << " ----> Material " << fPlasticMaterial << " not found, cannot build! " << G4endl;
        return 0;
    }
      else {
G4cout << plasticG4material->GetName() << "is the name of the detector material" << G4endl;
}

G4Box * box = new G4Box("Plastic Detector", fScintillatorLength, fScintillatorHeight, fScintillatorWidth);
   move = G4ThreeVector(50., 50., 50.);
    rotate = new G4RotationMatrix;
    direction 	  = G4ThreeVector(1., 1., 1.);
   
    
    //logical volume for scintillator can
    if(fPlasticLog == NULL ) {
        fPlasticLog = new G4LogicalVolume(box, plasticG4material, "test", 0, 0, 0);
        //fTestcanAlumCasingLog->SetVisAttributes(canVisAtt);
    }
    fAssemblyPlastics->AddPlacedVolume(fPlasticLog, move, rotate);

////////Scintillation Properties ////////
// Havent included appropriate libraries yet...

G4MaterialPropertiesTable * MPT1 = new G4MaterialPropertiesTable();
//Based on BC408 data
G4double photonEnergy[4] = {1.*keV, 0.1*MeV, 1.*MeV, 10.*MeV};
G4double RIndex1[4] = {1.58, 1.58, 1.58, 1.58};

const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);
assert(sizeof(RIndex1) == sizeof(photonEnergy));


//G4double absorption[4] = 


 
    return 1;
}

