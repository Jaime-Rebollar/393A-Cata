/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

int AutonNumber = 1; // Current Autonomous

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // auton selector
  int x1 = 5;
  int y1 = 50;
  int x2 = 50;
  int y2 = 175;
  int spacing = 60;
  int rect_amount = 8;
  color selected = red;
  color unselected = blue;

  // Print 8 rectangles
  for (int i = 0; i < rect_amount; i++) {
    color current_color;
    // Check if i is AutonNumber to change current_color
    if (i + 1 == AutonNumber) {
      current_color = selected;
    } else {
      current_color = unselected;
    }
    Brain.Screen.setPenColor(current_color);
    Brain.Screen.drawRectangle(x1 + (spacing * i), y1, x2, y2, current_color);
  }

  // Set font to monoM
  Brain.Screen.setFont(monoM);

  while (true) {

    // Selected position
    int x = Brain.Screen.xPosition(); // X position of finger
    int y = Brain.Screen.yPosition(); // Y position of finger

    // Check if finger is within vertical selection of the boxes
    if (y1 < y && y < y1 + y2) {
      for (int i = 0; i < rect_amount; i++) {
        // Check which x value the finger is within
        if (x1 + (spacing * i) < x && x < (spacing * (i + 1)) - x1) {
          // Change color of previously selected box to unselected
          Brain.Screen.setPenColor(unselected);
          Brain.Screen.drawRectangle(x1 + (spacing * (AutonNumber - 1)), y1, x2,
                                     y2, unselected);
          AutonNumber = i + 1; // Update AutonNumber
          // Change color of new box to selected
          Brain.Screen.setPenColor(selected);
          Brain.Screen.drawRectangle(x1 + (spacing * (AutonNumber - 1)), y1, x2,
                                     y2, selected);
        }
      }
    }

    // Print AutonNumber to brain
    Brain.Screen.setPenColor(selected);
    Brain.Screen.printAt(5, 30, "Current Auto: %d",
                         AutonNumber); // %d is a formatting character that gets
                                       // replaced with AutonNumber
    wait(20, msec);
    Brain.Screen.clearLine(1);
  }

  imu.calibrate();
  while (imu.isCalibrating()) {
    wait(100, msec);
  }
  cata_intake.setStopping(brakeType::brake);
  leftc.setStopping(brakeType::coast);
  rightc.setStopping(brakeType::coast);

  umisha.rumble(".");
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  imu.calibrate();
  while (imu.isCalibrating()) {
    wait(100, msec);
  }
  cata_intake.setStopping(brakeType::brake);
  set_chassis_brake(1);


  /* pd_forward(5, 100, 0);
  cata_intake.spin(forward, 11, volt);
  wait(200, msec);
  cata_intake.spin(reverse, 0, volt);
  pd_backward(10, 100, 0);
  while(true) {
    if(!cata_switch.pressing()) {
      cata_intake.spin(forward, 11, volt);
    }
    else {
      cata_intake.stop(brakeType::brake);
      break;
    }
    }
  pd_turn_right(90, 100, 0);
  pd_turn_right(45, 100, 0);
  cata_intake.spin(forward, -11, volt);
  pd_forward(10, 100, 0);
  wait(2000, msec);
  cata_intake.spin(forward, 0, volt); */

  pd_forward(20, 100, 0);
  pd_turn_right(95, 100, 0);
  pd_forward(6.5, 100, 0);
  cata_intake.spin(forward, 11, volt);
  wait(275, msec);
  cata_intake.spin(reverse, 0, volt);




  




/*     cata_intake.spin(forward, -11, volt);
    wait(2000, msec);
    cata_intake.spin(forward, 0, volt);
    pd_backward(5, 100, 0);
    cata_intake.spin(forward, 11, volt);
    wait(500, msec);
    cata_intake.spin(reverse, 0, volt);
    while(true) {
    if(!cata_switch.pressing()) {
      cata_intake.spin(forward, 11, volt);
    }
    else {
      cata_intake.stop(brakeType::brake);
      break;
    }
    }
    pd_forward(5, 100, 0);

    cata_intake.spin(forward, -11, volt);
    wait(4000, msec);
    cata_intake.spin(forward, 0, volt);
    pd_backward(5, 100, 0);
    cata_intake.spin(forward, 11, volt);
    wait(500, msec);
    cata_intake.spin(reverse, 0, volt);
    while(true) {
    if(!cata_switch.pressing()) {
      cata_intake.spin(forward, 11, volt);
    }
    else {
      cata_intake.stop(brakeType::brake);
      break;
    }
    }
    pd_forward(5, 100, 0);

    cata_intake.spin(forward, -11, volt);
    wait(4000, msec);
    cata_intake.spin(forward, 0, volt);
    pd_backward(5, 100, 0);
    cata_intake.spin(forward, 11, volt);
    wait(500, msec);
    cata_intake.spin(reverse, 0, volt);
    while(true) {
    if(!cata_switch.pressing()) {
      cata_intake.spin(forward, 11, volt);
    }
    else {
      cata_intake.stop(brakeType::brake);
      break;
    }
    }  */
    /* 
    pd_backward(18, 100, 0);
    pd_turn_right(50, 100, 0);
    pd_forward(43, 100, 0);
    cata_intake.spin(forward, -11, volt);
    pd_forward(5, 100, 0);
    wait(300, msec);
    pd_forward(5, 100, 0);
    wait(300, msec);
    pd_forward(10, 100, 0);
    wait(1000, msec);
    cata_intake.spin(forward, 0, volt);
    pd_backward(45, 100, 0);
    pd_turn_left(28, 100, 0);
    cata_intake.spin(forward, 11, volt);
    wait(500, msec);
    cata_intake.spin(reverse, 0, volt);
    while(true) {
    if(!cata_switch.pressing()) {
      cata_intake.spin(forward, 11, volt);
    }
    else {
      cata_intake.stop(brakeType::brake);
      break;
    }
    }

    pd_turn_right(90, 100, 0);
    pd_turn_right(10, 100, 0);
    cata_intake.spin(forward, -11, volt);
    pd_forward(32, 100, 0);
    pd_turn_right(40, 100, 0);
    pd_forward(35, 100, 0);
    pd_turn_left(60, 100, 0);
    wait(500, msec);
    cata_intake.spin(reverse, 0, volt);
    pd_backward(18, 100, 0);
    cata_intake.spin(forward, 11, volt);
    wait(500, msec);
    cata_intake.spin(reverse, 0, volt);
    while(true) {
    if(!cata_switch.pressing()) {
      cata_intake.spin(forward, 11, volt);
    }
    else {
      cata_intake.stop(brakeType::brake);
      break;
    }
    }  */


    





    

    //cata_intake.spin(forward, -11, volt); // intake
    //pd_forward(43, 100, 0);
    //wait(500, msec);
    //pd_turn_left(30, 100, 0);


/* 
    
    cata_intake.spin(forward, -11, volt); // intake
    pd_forward(43, 100, 0);
    pd_turn_left(30, 100, 0);
    cata_intake.spin(forward, 0, volt);
    pd_backward(50, 100, 0);
    cata_intake.spin(forward, 11, volt);
    wait(500, msec);
    cata_intake.spin(reverse, 0, volt);
    while(true) {
    if(!cata_switch.pressing()) {
      cata_intake.spin(forward, 11, volt);
    }
    else {
      cata_intake.stop(brakeType::brake);
      break;
    }
    }

    pd_turn_right(60, 100, 0);
    cata_intake.spin(forward, -11, volt); // intake
    pd_forward(30, 100, 0);
    pd_turn_right(45, 100, 0);
    pd_forward(34, 100, 0);
    pd_turn_left(60, 100, 0);
    cata_intake.spin(forward, 0, volt);
    pd_backward(38, 100, 0);
    cata_intake.spin(forward, 11, volt);
    wait(500, msec);
    cata_intake.spin(reverse, 0, volt);
    while(true) {
    if(!cata_switch.pressing()) {
      cata_intake.spin(forward, 11, volt);
    }
    else {
      cata_intake.stop(brakeType::brake);
      break;
    }
    }

    pd_turn_right(30, 100, 0);
    cata_intake.spin(forward, -11, volt); // intake and roller
    pd_forward(84, 100, 0);
    wait(500, msec);
    cata_intake.spin(forward, 0, volt);
    pd_backward(24, 100, 0);
    pd_turn_right(90, 100, 0);
    cata_intake.spin(forward, -11, volt); // intake and roller
    pd_forward(24, 100, 0);
    wait(500, msec);
    cata_intake.spin(forward, 0, volt);
  */








    //pd_forward(5, 100, 0);
    //cata_intake.spin(reverse, 11, volt);
    //pd_turn_right(45, 100, 0);
    //expand.set(true);
    //wait(1000, msec);
    //expand.set(false);

    
    //pd_backward(24, 100, 0);
    //wait(2000, msec);
    //cata_intake.spin(forward, 11, volt);
    //wait(1000, msec);
    //cata_intake.spin(forward, 0, volt);
    //pd_turn_right(90, 100, 0);
    //pd_backward(5, 100, 0);
    //cata_intake.spin(forward, -11, volt);
    //wait(200, msec);
    //cata_intake.spin(forward, 0, volt);
  // pd_backward(5, 100, 0);
  // cata_intake.spin(forward, -11, volt);
  // wait(200, msec);
  // cata_intake.spin(forward, 0, volt);
    //pd_forward(5, 100, 0);
  //pd_turn_right(90, 100, 0);
 // wait(1000, msec);
  //cata_intake.spin(forward, 11, volt);



  if (AutonNumber == 1) {


    //pd_backward(5, 100, 0);
    //cata_intake.spin(forward, 11, volt);
    //wait(250, msec);
    //cata_intake.spin(forward, 0, volt);
    //pd_forward(5, 100, 0);
    //pd_turn_right(95, 100, 0);
    //wait(500, msec);
    //cata_intake.spin(forward, 11, volt);
    //wait(1000, msec);
    //cata_intake.spin(forward, 0, volt);
    //cata_intake.spin(forward, 11, volt);
    //wait(1000, msec);
    //cata_intake.spin(forward, 0, volt);
    //pd_turn_right(30, 100, 0);
    //expand.set(true);
    //wait(500, msec);
    //expand.set(false);
    //pd_backward(5, 100, 0);
    //pd_forward(5, 100, 0, true);
    //pd_turn_right(45, 100, 0, true);
    //pd_forward(84, 100, 0, true);
    //pd_turn_left(90, 100, 0, true);
    //shoot();
    //pd_turn_left(90, 100, 0, false);
    //pd_backward(84, 100, 0, false);

  } else if (AutonNumber == 2) {

  } else if (AutonNumber == 3) {
    // Skills

  } else if (AutonNumber == 4) {
    // Call Auton
  } else if (AutonNumber == 5) {
    // Call Auton
  } else if (AutonNumber == 6) {
    // Call Auton
  } else if (AutonNumber == 7) {
    // Call Auton
  } else if (AutonNumber == 8) {
    // Call Auton
  }

  // I love men
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  bool l_expandToggle = false;
  bool l_expandLatch = false;
  bool r_expandToggle = false;
  bool r_expandLatch = false;
  bool expandToggle = false;
  bool expandLatch = false;
  bool l_fire_expansion = false;
  bool r_fire_expansion = false;
  bool fire_expansion = false;


  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    l_fire_expansion = umisha.ButtonLeft.pressing();
    r_fire_expansion = umisha.ButtonRight.pressing();
    fire_expansion = umisha.ButtonUp.pressing();
//left
    if (l_expandToggle){
      l_expand.set(true);
    }
    else {
      l_expand.set(false);
    }
    if (l_fire_expansion) {
      if(!l_expandLatch){
      l_expandToggle = !l_expandToggle;
      l_expandLatch = true;
      }
    }
    else {
      l_expandLatch = false;
    }

//right

    if (r_expandToggle){
      r_expand.set(true);
    }
    else {
      r_expand.set(false);
    }
    if (r_fire_expansion) {
      if(!r_expandLatch){
      r_expandToggle = !r_expandToggle;
      r_expandLatch = true;
      }
    }
    else {
      r_expandLatch = false;
    }
//both

    if (expandToggle){
      l_expand.set(true);
      r_expand.set(true);
    }
    else {
      l_expand.set(false);
      r_expand.set(true);
    }
    if (fire_expansion) {
      if(!expandLatch){
      expandToggle = !expandToggle;
      expandLatch = true;
      }
    }
    else {
      expandLatch = false;
    }

    // if(cata_switch.pressing() == false){
    //    cata_intake.spin(forward, 11.0, voltageUnits::volt);
    //  }
     
    // else{
    //     Intaking = umisha.ButtonL2.pressing();
    //     Shooting  = umisha.ButtonR2.pressing();
    //  }

    // if(Intaking){
    //    cata_intake.spin(forward, -11.0, voltageUnits::volt);


    //  }
    // else if(Shooting){
    //    cata_intake.spin(forward, 11.0, voltageUnits::volt);


    //  }
    // else{
    //    cata_intake.stop(vex::brakeType::brake);
    //  }
    // if (limitswitchtoggle){
    //   allow = true;
    // }
    // else {
    //   allow = false;
    // }
    // if (cata_switch.pressing()) {
    //   if(!limitswitchlatch){
    //   limitswitchtoggle = !limitswitchtoggle;
    //   limitswitchlatch = true;
    //   }
    // }
    // else {
    //   limitswitchlatch = false;
    // }



    // if (shoottoggle){
    //   limitswitchtoggle = !limitswitchtoggle;
    // }
    // else {
    //   limitswitchtoggle = limitswitchtoggle;
    // }
    // if (umisha.ButtonR2.pressing()) {
    //   if(!shootlatch){
    //   shoottoggle = !shoottoggle;
    //   shootlatch = true;
    //   }
    // }
    // else {
    //   shootlatch = false;
    // }
    



    if (umisha.ButtonL1.pressing() == true) {
      cata_intake.spin(reverse, 11.0, volt);
    }
    else if (!(cata_switch.pressing()))
   {
     cata_intake.spin(forward, 11.0, volt);
   }
    else if ((umisha.ButtonL2.pressing() == true) && (cata_switch.pressing()))
   {
   cata_intake.spin(reverse, 11.0, volt);
   }
    else if ((umisha.ButtonR2.pressing() == true) && (cata_switch.pressing()))
   {
    cata_intake.spin(forward, 9.0, volt);
   }
   else
   {
     cata_intake.stop(brakeType::brake);
   }

    set_drive_motors();
    //set_cata_motors();

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
