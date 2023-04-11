#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller umisha;
//cata side back
motor lf = motor(PORT5, ratio6_1, true);
motor lm = motor(PORT3, ratio6_1, false);
motor lb = motor(PORT4, ratio6_1, true);
motor_group leftc = motor_group(lf, lm, lb);

motor rf = motor(PORT8, ratio6_1, false);
motor rm = motor(PORT7, ratio6_1, true);
motor rb = motor(PORT9, ratio6_1, false);
motor_group rightc = motor_group(rf, rm, rb);

motor l_cata = motor(PORT1, ratio6_1, true);
motor r_cata = motor(PORT10, ratio6_1, false);
motor_group cata_intake = motor_group(l_cata, r_cata);

inertial imu = inertial(PORT6);
limit cata_switch = limit(Brain.ThreeWirePort.A);
digital_out l_expand = digital_out(Brain.ThreeWirePort.H);
digital_out r_expand = digital_out(Brain.ThreeWirePort.C);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}