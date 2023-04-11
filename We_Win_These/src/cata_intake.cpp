#include "drive.h"
#include "vex.h"

using namespace vex;


//Helper Functions



//Driver Control Functions
void set_cata_motors() {
 if (!(cata_switch.pressing()))
   {
     cata_intake.spin(forward, 11.0, volt);
   }
 else if ((umisha.ButtonL2.pressing() == true) && (cata_switch.pressing() == true))
 {
   cata_intake.spin(reverse, 11.0, volt);
 }
 else if ((umisha.ButtonR2.pressing() == true) && (cata_switch.pressing() == true))
 {
   cata_intake.spin(forward, 11.0, volt);
 }
 else
   {
     cata_intake.stop(brakeType::brake);
   }
}

    


//Autonomous Functons

void reset() {
  while(true) {
    if(!cata_switch.pressing()) {
      cata_intake.spin(forward, 11, volt);
    }
    else {
      cata_intake.stop(brakeType::brake);
      break;
    }
  }
}

void shoot(){
  cata_intake.spinFor(forward, 180, degrees);
}
