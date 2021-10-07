#include "stdlib.h"
#include "distance_sensing.h"

double motor_speeds[] = {0, 0, 0, 0}; // motor speeds array for slew control

const int slew_error_bound = 10; // smoothens acceleration curve using slew control
float turning_constant = 0.6, turning_constant_2 = 1.2; // for slowing down turn sensitivity

int drive_mode = 1; // 0 = arcade, 1 = tank
bool run_auton = 0;

double indexer_mode = 0;
double shooter_mode = 0;
double intaking_mode = 0;
bool force_intake = false;
bool auto_outtake = false;

bool partner_override = false;

void spin_motors(double speeds[]){
    spin(front_left, speeds[0]);
    spin(front_right, speeds[1]);
    spin(back_left, speeds[2]);
    spin(back_right, speeds[3]);
}

// determines wheel speeds based on forward, sideways, and turning axes
void set_speed(double axis_input_1, double axis_input_2, double axis_input_3, bool slew_control, string mode = "tank") {
   double speeds[] = {0, 0, 0, 0};

   double cutoff = 0; 
   bool sqrt_curve = abs(axis_input_2) > cutoff || abs(axis_input_3) > cutoff;
   
   if(mode=="arcade"){
   
      if (axis_input_1 == 0 && axis_input_2 == 0){
         axis_input_3 = (MIN(abs(axis_input_3*turning_constant_2), 80)) * signum(axis_input_3);
      }
   
      speeds[0] = axis_input_1 + axis_input_2 + axis_input_3;
      speeds[1] = axis_input_1 - axis_input_2 - axis_input_3;
      speeds[2] = -axis_input_1 + axis_input_2 - axis_input_3;
      speeds[3] = -axis_input_1 - axis_input_2 + axis_input_3;
   }
   
   else if(mode=="tank"){
      double difference_capping = 150;
   
      // 30, 50, 150, 0, 100, 125, 200, 70
   
      // -100, 40 --> -60, 40, d=140, d2=40, 
      // -80, 50 --> -50, 50, d=130, d2=30, 
      // -50, 80 --> -50, 50, d=130, d2=30, 
   
      // if(abs(axis_input_1-axis_input_2)>difference_capping){
      //   double difference = abs(axis_input_1-axis_input_2);
      //   difference -= difference_capping;
      //   if(abs(axis_input_1)>=abs(axis_input_2)){
      //     axis_input_1 += signum(axis_input_1) * -1 * difference;
      //   } else {
      //     axis_input_2 += signum(axis_input_2) * -1 * difference;
      //   }
      // } 
   
      if(abs(axis_input_1-axis_input_2)>difference_capping){
         double difference = 100/abs(axis_input_1-axis_input_2);
         axis_input_1 *= difference;
         axis_input_2 *= difference;
      } 
   
      //cout<<axis_input_1<<endl;
      //cout<<axis_input_2<<endl;
   
   
      speeds[0] = axis_input_1 + axis_input_3;
      speeds[1] = axis_input_2 - axis_input_3;
      speeds[2] = -axis_input_1 + axis_input_3;
      speeds[3] = -axis_input_2 - axis_input_3;
   }

   // slew_control --> adds acceleration curve;

   double piecewise_break = 0.4;
   double piecwise_speed = piecewise_break * 100;
   double piecewise_speed_cube = piecwise_speed * piecwise_speed * piecwise_speed / 10000;

   if (slew_control) {
      for(int i = 0; i < 4; i++) {
         if(sqrt_curve) 
            speeds[i] = sqrt(abs(speeds[i])) * 10 * signum(speeds[i]); 
         // speeds[i] = speeds[i] * speeds[i] / 100 * signum(speeds[i]);  
      }
   
      for (int i = 0; i < 4; i++) {
         if (abs(speeds[i] - motor_speeds[i]) > slew_error_bound)
            motor_speeds[i] += slew_error_bound * signum(speeds[i] - motor_speeds[i]);
         else
            motor_speeds[i] = speeds[i];
      }
   
      // INSTA ACCELERATION KILL WHEN SPEED = 0
      for(int i=0; i<4; i++){
         if(speeds[i]==0)
            motor_speeds[i]=0;
      }
      
   
   } 
   else {
      for(int i = 0; i < 4; i++)
         motor_speeds[i] = speeds[i];
   }
   
   spin_motors(motor_speeds);
}

// xDrive controls (involves three axes: forward/backward, left/right, turning)
void arcade_mode() {
   double f_speed = abs(ct.Axis2.value()) > 30 ? ct.Axis2.value() : 0;
   double s_speed = abs(ct.Axis1.value()) > 30 ? ct.Axis1.value() : 0;
   double t_speed = abs(ct.Axis4.value()) > 30 ? ct.Axis4.value() : 0;
   set_speed(f_speed, s_speed, t_speed * turning_constant, true, "arcade");
}

void tank_mode() {
   double l_speed = abs(ct.Axis3.value()) > 2 ? ct.Axis3.value() : 0;
   double r_speed = abs(ct.Axis2.value()) > 2 ? ct.Axis2.value() : 0;

   // if(abs(l_speed)>50)
   //   l_speed=50*signum(l_speed);
   // if(abs(r_speed)>50)
   //   r_speed=50*signum(r_speed);
   if (l_speed < 0 && r_speed , 0) {
      auto_outtake = true;
   }

   double strafe_deadzone = 1000;
   //double l_strafe = ct.Axis1.value() > strafe_deadzone ? ct.Axis1.value() : 0;
   //double r_strafe = ct.Axis4.value() < -strafe_deadzone ? ct.Axis4.value() : 0;
   
   double s_speed = abs(ct.Axis4.value())>strafe_deadzone ? ct.Axis4.value() : 0;

   //double s_speed = abs(ct.Axis1.value()) > abs(ct.Axis4.value()) ? ct.Axis1.value() : ct.Axis4.value();
   //double s_speed = abs(ct.Axis4.value()) > 5 ? ct.Axis4.value() : 0;
   //if (abs(s_speed) < 15) s_speed = 0;
   //MAX(ct.Axis1.value(), 0) + MIN(ct.Axis4.value(), 0);
   //abs(ct.Axis1.value()) > 30 ? ct.Axis1.value() : 0;
   set_speed(l_speed, r_speed, s_speed, true, "tank");
}

void reset(){
    spin(intake_left, 0);
    spin(intake_right, 0);
    spin(shooter, 0);
    spin(indexer, 0);
}

void change_drive_mode(){
   drive_mode = 1-drive_mode;
}

void change_indexer_mode(){
   if(indexer_mode != 0)
      indexer_mode = 0;
   else
      indexer_mode = -0.3;
}

void kill_indexing(){
   // auton_intaking_mode = 10 - auton_intaking_mode;
   override_distance2 = !override_distance2;
}

void auto_shoot(){
   shooting_target=1;
   auton_shooting_mode=2;
}

void reset_shooting(){
   balls_shot=0;
   shooting_target=0;
}
// calls the major methods on loop
int shooterControls(){
   int time_pooping=0;
   int time_since_press=0;
   bool pause=false;
   while(true){
      if(press(ButtonY)) {
         override_distance=true;
         force_intake=true;
          spin(shooter, -100);
          spin(indexer, -100);
      } 
      else if (press(ButtonL1)) {
         force_intake=false;
         override_distance=true;
         shooting_fast=true;
          spin(shooter, 100);
          spin(indexer, 100);
         time_since_press=0;
      } 
      else if (press(ButtonL2)) {
         override_distance=true;
      
         if(!pause){
             spin(shooter, -50);
             spin(indexer, -50);
         } 
         else {
             spin(shooter, 0);
             spin(indexer, 0);
            time_pooping+=5;
            if(time_pooping>600){
               pause=false;
               time_pooping=0;
            }
         }
      
         bool sense = upper_indexer.value()<=40 && upper_indexer.value()>=1; // detect if upper indexer triggered
      
         if(sense && time_since_press>280){ // if upper indexer triggered for 280 ms when dumping, stop indexer
            pause=true;
            time_since_press=0;
         } 
      
         force_intake=false;
         ball_one=false;
         time_since_press+=5;
      } 
      else if (press(ButtonA)){
         force_intake=false;
         override_distance=true;
          spin(shooter, 50);
          spin(indexer, 50);
         shooting_fast=true;
         time_since_press=0;
      } 
      else if (override_distance){
         ball_one=false;
         time_since_press=0;
         // override_distance=false;
      }
      
      if(force_intake) {
         intaking_mode = -1;
         force_intake = false;
      } 
      else if (press(ButtonR1)) {
         intaking_mode = 1;
      } 
      else if (press(ButtonR2)) {
         intaking_mode = -1;
      } 
      else if (auto_outtake) {
         intaking_mode = -0.5;
         auto_outtake = false;
      } 
      else {
         intaking_mode = 0;
      }
      
      wait(2);
   }
   return 0;
}

int driveControls() {
   while(true){
      if(drive_mode==0)
         arcade_mode();
      else
         tank_mode();
      
       spin(intake_left, intaking_mode * 100);
       spin(intake_right, intaking_mode * 100);
      wait(2);
   }
   return 0;
}

/* backup distance sensor code */

// else if(!(b4 && b3 && b2) && !(b4 && b3) && !(b3)){
//   if(b2 && !b3 && !b4){
//     spin(shooter_left, 10);
//     spin(shooter_right, 10);
//   }

//   if(b4 && !b3){
//     spin(shooter_left, -40);
//     spin(shooter_right, -40);
//   }
// }

/* backup accleration code */

// SQUARE CURVE
// for(int i = 0; i < 4; i++)
//   speeds[i] = speeds[i] * speeds[i] / 100 * signum(speeds[i]);

// SQUARE ROOT CURVE
// for(int i = 0; i < 4; i++)
//  speeds[i] = sqrt(speeds[i]) * 10 * signum(speeds[i]);

/* backup variables */

// bool auton_shooting_many = false;
// bool auton_shooting_one = false;
// int num_balls = 0;

//   // if(abs(speeds[i]) < piecewise_break * 100){
      //   speeds[i] = speeds[i] * speeds[i] * speeds[i] / 10000;
      // }

      // else if(speeds[i] > 0){ 
      //   speeds[i] = piecewise_speed_cube + (speeds[i]-piecwise_speed)/(100-piecwise_speed) * (100 - piecewise_speed_cube);
      // } else {
      //   speeds[i] = -100 + (speeds[i]+100)/(piecwise_speed+100) * (piecewise_speed_cube + 100);
      // }

      // (40, 100) --> (0.064, 100)
      // (-100, -40) --> (-100, -0.064)