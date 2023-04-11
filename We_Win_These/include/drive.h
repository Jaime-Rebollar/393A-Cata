#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
 
 
#include "v5.h"
#include "v5_vcs.h"
 
#include "robot-config.h"
 
 
 
//Helper Functions
void set_drive(double left, double right);
 
void reset_encoders();
 
double get_encoder_avg();
 
void set_chassis_brake(int type);

void reset_cata();

double slew(double target_speed, double step, double current_speed);
 
//Driver Control Functions
void set_drive_motors();
 
//Autonomous Functons
 
void pd_forward(float target, int maxSpeed, int minSpeed); //target in inches
 
void pd_backward(float target, int maxSpeed, int minSpeed); //target in inches
 
void pd_turn_right(float target, int maxSpeed, int minSpeed); //target in degrees
 
void pd_turn_left(float target, int maxSpeed, int minSpeed); //target in degrees