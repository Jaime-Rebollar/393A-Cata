#include "drive.h"
#include "vex.h"
#include "cmath"

using namespace vex;


// PD Constants

//double LINEAR_KP = 0.006;// 0.0142 5 in 2 disc
//double LINEAR_KD = 0;
double LINEAR_STEP = 0.1;

//double TURN_KP = 0.107;//0.07 90 turn with 2 disc 0.107 45 turn two disc
//double TURN_KD = 0;
double TURN_STEP = 10;

double GEAR_RATIO = 36 / 60.0;
double WHEELCIRCUMFRENCE = M_PI * 3.25;





// Helper Functions

void set_drive(double left, double right) 
{
  leftc.spin(fwd, left, volt);
  rightc.spin(fwd, right, volt);
}

void reset_encoders() 
{
  lf.resetPosition();
  lm.resetPosition();
  lb.resetPosition();
  rf.resetPosition();
  rm.resetPosition();
  rb.resetPosition();
  imu.resetRotation();
}

double get_encoder_avg() 
{
  double avg = (fabs(lf.position(rotationUnits::raw)) +
                fabs(lm.position(rotationUnits::raw)) +
                fabs(lb.position(rotationUnits::raw)) +
                fabs(rf.position(rotationUnits::raw)) +
                fabs(rm.position(rotationUnits::raw)) +
                fabs(rb.position(rotationUnits::raw))) /
               6.0;
  return avg;
}


void set_chassis_brake(int type) {
  if (type == 1) {
    leftc.setStopping(coast);
    rightc.setStopping(coast);
  } else if (type == 2) {
    leftc.setStopping(hold);
    rightc.setStopping(hold);
  } else if (type == 3) {
    leftc.setStopping(brake);
    rightc.setStopping(brake);
  }
}

void reset_cata() {
  if (!(cata_switch.pressing()))
   {
     cata_intake.spin(forward, 11.0, volt);
   }
   else {
     cata_intake.stop(brakeType::brake);
   }
  
}

double slew(double target_speed, double step, double current_speed) {
  if(target_speed > (current_speed + step)) {
    current_speed += step;
  }
  else if(target_speed < (current_speed - step)) {
    current_speed -= step;
  }
  else {
    current_speed = target_speed;
  }
  return current_speed;
}

// Driver Control Functions
void set_drive_motors() {
  double turnImportance = 0.5;

  double turnVal = umisha.Axis4.position();
  double forwardVal = umisha.Axis2.position();
  double turnVolts = turnVal * -0.11;
  double forwardVolts = forwardVal * 0.11 * (1 - (std :: abs(turnVolts) / 11.0) * turnImportance);
  set_drive(forwardVolts - turnVolts, forwardVolts + turnVolts);
}

// Autonomous Functons

void pd_forward(float target, int maxSpeed, int minSpeed) {

//auto decides kp and kd

  double kp = 0.0;
  double kd = 0.0;

  if(target <= 5.0) {
    kp = 0.019;
    kd = 0.0;
  }
  else if(target <= 10.0) {
    kp = 0.0123;//
    kd = 0;
  }
  else if(target <= 15.0) {
    kp = 0.0101;//
    kd = 0;
  }
  else if(target <= 20.0) {
    kp = 0.00875;//
    kd = 0;
  }
  else if(target <= 24.0) {
    kp = 0.00803;//
    kd = 0;
  }
  else if(target <= 30.0) {
    kp = 0.0072;//
    kd = 0;
  }
  else if(target <= 35.0) {
    kp = 0.0067;//
    kd = 0;
  }
  else if(target <= 40.0) {
    kp = 0.00625;//
    kd = 0;
  }
  else if(target <= 45.0) {
    kp = 0.00585;//
    kd = 0;
  }

  double error;
  double prevError;
  double prev_rawpower = 0.0;
  double derivative;
  double rawPower;
  double maxVolts = maxSpeed * 12.0;
  double minVolts = minSpeed * 12.0;
  int cappedSpeed = -1;
  double targetValue = (300.0 / (WHEELCIRCUMFRENCE * GEAR_RATIO)) * target;
  int DELAY_TIME = 10;
  int errorTimer;

  reset_encoders();
  set_chassis_brake(1);

  while (targetValue > get_encoder_avg()) {

    error = targetValue - get_encoder_avg();
    derivative = (error - prevError);
    prevError = error;

    rawPower = (error * kp) + (derivative * kd);
    rawPower = slew(rawPower, LINEAR_STEP, prev_rawpower);

    cappedSpeed = error / abs(int(error));

    if (fabs(rawPower) <= fabs(minVolts)) {
      rawPower = minVolts * cappedSpeed;
    }

    if (fabs(rawPower) >= fabs(maxVolts)) {
      rawPower = maxVolts * cappedSpeed;
    }

    if (abs(int((error))) <= (targetValue / 2)) { // && abs(turnError) <= 4
      errorTimer += DELAY_TIME;
      if (errorTimer > 60) {
        errorTimer = 0;
        break;
      }
    } else {
      errorTimer = 0;
    }

    prev_rawpower = rawPower;

    printf("error: %f\n", error);
    set_drive(rawPower, rawPower);
    wait(10, msec);
  }
  leftc.stop(brakeType::coast);
  rightc.stop(brakeType::coast);
}

void pd_backward(float target, int maxSpeed, int minSpeed) {

  //auto decides kp and kd

  double kp = 0.0;
  double kd = 0.0;

  if(target <= 5.0) {
    kp = 0.019;
    kd = 0.0;
  }
  else if(target <= 10.0) {
    kp = 0.0123;//
    kd = 0;
  }
  else if(target <= 15.0) {
    kp = 0.0101;//
    kd = 0;
  }
  else if(target <= 20.0) {
    kp = 0.00875;//
    kd = 0;
  }
  else if(target <= 24.0) {
    kp = 0.00803;//
    kd = 0;
  }
  else if(target <= 30.0) {
    kp = 0.0072;//
    kd = 0;
  }
  else if(target <= 35.0) {
    kp = 0.0067;//
    kd = 0;
  }
  else if(target <= 40.0) {
    kp = 0.00625;//
    kd = 0;
  }
  else if(target <= 45.0) {
    kp = 0.00585;//
    kd = 0;
  }


  double error;
  double prevError;
  double prev_rawpower = 0.0;
  double derivative;
  double rawPower;
  double maxVolts = maxSpeed * 12.0;
  double minVolts = minSpeed * 12.0;
  int cappedSpeed = -1;
  double targetValue = (300.0 / (WHEELCIRCUMFRENCE * GEAR_RATIO)) * target;
  int DELAY_TIME = 10;
  int errorTimer;

  reset_encoders();
  set_chassis_brake(1);

  while (targetValue > get_encoder_avg()) {

    error = targetValue - get_encoder_avg();
    derivative = (error - prevError);
    prevError = error;

    rawPower = (error * kp) + (derivative * kd);
    rawPower = slew(rawPower, LINEAR_STEP, prev_rawpower);

    cappedSpeed = error / abs(int(error));

    if (fabs(rawPower) <= fabs(minVolts)) {
      rawPower = minVolts * cappedSpeed;
    }

    if (fabs(rawPower) >= fabs(maxVolts)) {
      rawPower = maxVolts * cappedSpeed;
    }

    if (abs(int((error))) <= (targetValue / 5)) { // && abs(turnError) <= 4
      errorTimer += DELAY_TIME;
      if (errorTimer > 60) {
        errorTimer = 0;
        break;
      }
    } else {
      errorTimer = 0;
    }

    prev_rawpower = rawPower;

    printf("error: %f\n", error);
    set_drive(-rawPower, -rawPower);
    wait(10, msec);
  }
  leftc.stop(brakeType::coast);
  rightc.stop(brakeType::coast);
}

void pd_turn_left(float target, int maxSpeed, int minSpeed) {

  //auto decides kp and kd

  double kp = 0.0;
  double kd = 0.0;

  if(target <= 15.0) {
    kp = 0.265;
    kd = 0.0;
  }
  else if(target <= 30.0) {
    kp = 0.155;//
    kd = 0;
  }
  else if(target <= 45.0) {
    kp = 0.115;//
    kd = 0;
  }
  else if(target <= 60.0) {
    kp = 0.094;//
    kd = 0;
  }
  else if(target <= 75.0) {
    kp = 0;//
    kd = 0;
  }
  else if(target <= 90.0) {
    kp = 0.075;//
    kd = 0;
  }
  else if(target <= 105.0) {
    kp = 0;//
    kd = 0;
  }
  else if(target <= 120.0) {
    kp = 0;//
    kd = 0;
  }
  else if(target <= 135.0) {
    kp = 0;//
    kd = 0;
  }
  else if(target <= 180.0) {
    kp = 0.0501;//
    kd = 0;
  }

  double error;
  double prevError;
  double prev_rawpower;
  double derivative;
  double rawPower;
  double maxVolts = maxSpeed * 12.0;
  double minVolts = minSpeed * 12.0;
  int cappedSpeed = -1;
  int DELAY_TIME = 10;
  int errorTimer;

  reset_encoders();
  set_chassis_brake(2);
  while (target > imu.rotation(deg)) {

    error = target + imu.rotation(deg);
    derivative = (error - prevError);
    prevError = error;
    rawPower = (error * kp) + (derivative * kd);
    rawPower = slew(rawPower, TURN_STEP, prev_rawpower);

    cappedSpeed = error / abs(int(error));

    if (fabs(rawPower) <= fabs(minVolts)) {
      rawPower = minVolts * cappedSpeed;
    }

    if (fabs(rawPower) >= fabs(maxVolts)) {
      rawPower = maxVolts * cappedSpeed;
    }

    if (abs(int((error))) <= (target / 5)) { // && abs(turnError) <= 4
      errorTimer += DELAY_TIME;
      if (errorTimer > 60) {
        errorTimer = 0;
        break;
      }
    } else {
      errorTimer = 0;
    }

    prev_rawpower = rawPower;

    printf("error: %f\n", error);
    set_drive(-rawPower, rawPower);
    wait(10, msec);
  }
}

void pd_turn_right(float target, int maxSpeed, int minSpeed) {

    //auto decides kp and kd

  double kp = 0.0;
  double kd = 0.0;

  if(target <= 15.0) {
    kp = 0.265;
    kd = 0.0;
  }
  else if(target <= 30.0) {
    kp = 0.155;//
    kd = 0;
  }
  else if(target <= 45.0) {
    kp = 0.115;//
    kd = 0;
  }
  else if(target <= 60.0) {
    kp = 0.094;//
    kd = 0;
  }
  else if(target <= 75.0) {
    kp = 0;//
    kd = 0;
  }
  else if(target <= 90.0) {
    kp = 0.075;//
    kd = 0;
  }
  else if(target <= 105.0) {
    kp = 0.075;;//
    kd = 0;
  }
  else if(target <= 120.0) {
    kp = 0;//
    kd = 0;
  }
  else if(target <= 135.0) {
    kp = 0;//
    kd = 0;
  }
  else if(target <= 180.0) {
    kp = 0.0501;//
    kd = 0;
  }

  double error;
  double prevError;
  double prev_rawpower;
  double derivative;
  double rawPower;
  double maxVolts = maxSpeed * 12.0;
  double minVolts = minSpeed * 12.0;
  int cappedSpeed = -1;
  int DELAY_TIME = 10;
  int errorTimer;

  reset_encoders();
  set_chassis_brake(2);

  while (target > imu.rotation(deg)) {

    error = target - imu.rotation(deg);
    derivative = (error - prevError);
    prevError = error;
    rawPower = (error * kp) + (derivative * kd);
    rawPower = slew(rawPower, TURN_STEP, prev_rawpower);

    cappedSpeed = error / abs(int(error));

    if (fabs(rawPower) <= fabs(minVolts)) {
      rawPower = minVolts * cappedSpeed;
    }

    if (fabs(rawPower) >= fabs(maxVolts)) {
      rawPower = maxVolts * cappedSpeed;
    }

    if (abs(int((error))) <= (target / 5)) { // && abs(turnError) <= 4
      errorTimer += DELAY_TIME;
      if (errorTimer > 60) {
        errorTimer = 0;
        break;
      }
    } else {
      errorTimer = 0;
    }

    prev_rawpower = rawPower;

    printf("error: %f\n", error);
    set_drive(rawPower, -rawPower);
    wait(10, msec);
  }
}
