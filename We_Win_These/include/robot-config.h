using namespace vex;

extern brain Brain;

extern controller umisha;

extern motor lf;
extern motor lm;
extern motor lb;
extern motor_group leftc;

extern motor rf;
extern motor rm;
extern motor rb;
extern motor_group rightc;

extern motor l_cata;
extern motor r_cata;
extern motor_group cata_intake;

extern inertial imu;
extern limit cata_switch;
extern digital_out l_expand;
extern digital_out r_expand;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
