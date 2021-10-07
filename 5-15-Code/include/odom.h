#include "driver.h"

using namespace vex;

// #define get_left  L_ODOM.rotation(rotationUnits::raw)
// #define get_right R_ODOM.rotation(rotationUnits::raw)
// #define get_back  B_ODOM.rotation(rotationUnits::raw)

#define get_left  odom_l.position(degrees)
#define get_right odom_r.position(degrees)
#define get_back  odom_b.position(degrees)

// all measurements in inches 
#define omni_wheels_diameter  3.25 
#define center_to_left_wheel  6.17 //5.17 new, 5.1 old
#define center_to_right_wheel 6.17 //5.17
#define center_to_back_wheel  5 //6.25 

// scales to convert encoder ticks and specific arcs into inches
double side_scale = 360 / (PI * omni_wheels_diameter);
double back_scale = 360 / (PI * omni_wheels_diameter);
double back_arc = 2 * PI * center_to_back_wheel / 360;
double turn_scale = PI/180 * (center_to_left_wheel + center_to_right_wheel);
//double turn_scale = 0.01316236;
// error for translational movement (PID)
double error;
double last_error;
double total_error;

double angle_to_destination = 0;

// error for turning (P loop only)
double error_theta;

// wheel indices: 0,1,2,3 (clockwise starting from back right) where -1 means unassigned
int c_index = -1; // current wheel index with max velocity
int p_index = -1; // previous wheel index with max velocity
bool wheel_indices[] = {0,0,0,0}; // keeps track of wheel indices with max velocity for overshooting

double movement_velocity = 0; // controlled by movement error and movement PID
double turning_velocity = 0; // controlled by turning error and turning P-loop
double auton_slew_control = 10; // for smoother acceleration during auton/prog

double speeds[] = {0,0,0,0}; // motor speeds for 4 wheels (calculated using odom)
double previous_speeds[] = {0,0,0,0}; // previous motor speeds for 4 wheels (calculated using odom)
double momentum_speeds[] = {0,0,0,0}; // initial motor speeds at start of movement for testing purposes

const double auton_slew = 5;//0.59;
double time_out = 99999;
double intake_early = 99999;

typedef 
   struct odom_tracking {
      double pos_x;
      double pos_y;
      double theta;
   } odom;

odom global = {0, 0, 157}; // global position and theta
odom delta = {0, 0, 0}; // change in position and theta after every odom call

bool end_movement = false;
bool odom_ended = true;

/* Functions */

// wraps theta within range of (-180, 180] degrees
double wrap(double theta){
   if(theta > 180)  
      return wrap(theta - 360);
   else if(theta <= -180) 
      return wrap(theta + 360);
   return theta;
}

double getGyro(){
   return wrap(90.0-Gyro.heading(rotationUnits::deg));
}

void reset_theta(){
   global.theta=getGyro();
}

// odom tracking task (runs in background)
int trackOdometry(){
   long prev_left = 0, prev_right = 0, prev_back = 0;
   long cur_left, cur_right, cur_back;
   double left_delta, right_delta;

   while (true)
   {
      // Updates current odom values
      cur_left = get_left;
      cur_right = get_right;
      cur_back = get_back;
   
      // Calculates left and right wheel movements in inches
      left_delta = (double)(cur_left - prev_left) / side_scale;
      right_delta = (double)(cur_right - prev_right) / side_scale;
   
      // Calculates theta in degrees 
      delta.theta = (double)(left_delta - right_delta) / turn_scale;
   
      // Calculates back wheel strafing in inches, accounting for arc correction
      delta.pos_x = (double)(cur_back - prev_back) / back_scale; // + (double)(back_arc * delta.theta); 
   
      // Updates previous odom values
      prev_left = cur_left;
      prev_right = cur_right;
      prev_back = cur_back;
   
      // Calculates position delta based on left and right wheels in inches
      delta.pos_y = (left_delta + right_delta) / 2;
   
      // Updates robot position based on odom calculations
      if (abs(delta.pos_y) < 200 && abs(delta.pos_x) < 200) // prevents updating of nonsensical encoder values around auton launch
      { 
         double angle_to_position = global.theta - delta.theta / 2; 
         global.pos_x += delta.pos_y * cos(angle_to_position * PI/180) + delta.pos_x * cos((angle_to_position-90) * PI/180);
         global.pos_y += delta.pos_y * sin(angle_to_position * PI/180) + delta.pos_x * sin((angle_to_position-90) * PI/180);
      }
   
      // Update theta in degrees
      global.theta -= delta.theta;
      global.theta = wrap(global.theta);
      wait(2);
   }
   return 0;
}

// run XDrive (via odom)
void motorSpeeds(double speeds[], bool slew_control=false){
   if (slew_control) {
      for (int i = 0; i < 4; i++) {
         if (abs(speeds[i] - previous_speeds[i]) > auton_slew)
            previous_speeds[i] += auton_slew * signum(speeds[i] - previous_speeds[i]);
         else
            previous_speeds[i] = speeds[i];
      }
   } 
   else {
      for (int i = 0; i < 4; i++) 
         previous_speeds[i] = speeds[i];
   }
   
    spin(back_right, previous_speeds[0]);
    spin(back_left, previous_speeds[1]);
    spin(front_left, previous_speeds[2]);
    spin(front_right, previous_speeds[3]);
}

void movementPID2(double final_pos_x, double final_pos_y, bool keep_momentum, double k_p, double k_i, double k_pt = kpT){
   //delta to final position (scale to inches)
   double delta_x = (final_pos_x - global.pos_x) * side_scale; 
   double delta_y = (final_pos_y - global.pos_y) * side_scale;

   double angle_error = atan2(delta_y, delta_x) * 180/PI;
   double movement_error = sqrt(delta_x * delta_x + delta_y * delta_y);
  
   double curve_theta = 180 - 2 * angle_error;
   double robot_width = center_to_left_wheel + center_to_right_wheel;
   double curve_radius = movement_error * sin(angle_error) / sin(curve_theta) + robot_width/2;

   double left_right_velocity_ratio = (curve_radius - robot_width) / (curve_radius + robot_width);
   
}

// updates motor speeds for translational movement
bool movementPID(double final_pos_x, double final_pos_y, bool keep_momentum, double k_p, double k_i){
   //delta to final position (scale to inches)
   double delta_x = (final_pos_x - global.pos_x) * side_scale; 
   double delta_y = (final_pos_y - global.pos_y) * side_scale;

   // Update PID integral 
   if (abs(total_error) < 1000) total_error += error;
   else total_error = 0;

   // update PID derivative 
   double deriv_error = error - last_error;
   last_error = error;

   // calculate voltage output for motors using PID constants + bounding
   if (keep_momentum){
      movement_velocity = 100;
   }
   else {
      movement_velocity = error * k_p + deriv_error * kd + total_error * k_i;
      if(abs(movement_velocity)>100) movement_velocity = signum(movement_velocity) * 100;
   }

   // calculate angle from current to desired position relative to robot's angle
   double angle_to_destination = atan2(delta_y, delta_x) * 180 / PI;
   angle_to_destination = wrap(angle_to_destination + 90 - global.theta);

   // calculate wheel index (0,1,2,3) w/ velocity dir closest to theta 
   c_index = ceil(angle_to_destination / 90) + 1; 
   wheel_indices[c_index] = 1;
   
   // Set integral to 0 if we overshoot (overshoot measured by change in wheel index)
   if (p_index != c_index && p_index != -1){
      total_error = 0;
   }
   p_index = c_index;

   // calculate ratio of wheel velocities between two sets of wheels
   int angle_of_reference = 90 * c_index - 135;
   double velocity_scale = tan((angle_to_destination - angle_of_reference) * PI/180);

   // assign motor speeds to move toward final position
   speeds[c_index] = movement_velocity; 
   speeds[(c_index+1)%4] = movement_velocity * velocity_scale;
   speeds[(c_index+2)%4] = -movement_velocity;
   speeds[(c_index+3)%4] = -movement_velocity * velocity_scale;

   //return (wheel_indices[0] && wheel_indices[2]) || (wheel_indices[1] && wheel_indices[3]);
   return abs(error)/side_scale < 3;
}

// updates motor speeds for turning
void turningPLoop(double k_pT=kpT) {
   turning_velocity = error_theta * k_pT;
   //cout<<turning_velocity<<endl;
   speeds[0] -= turning_velocity;
   speeds[1] += turning_velocity;
   speeds[2] -= turning_velocity;
   speeds[3] += turning_velocity;
}

// updates odom error based on final position and theta
void error_update(double final_pos_x, double final_pos_y, double final_theta){

   // delta to final position 
   double delta_x = (final_pos_x - global.pos_x) * side_scale; 
   double delta_y = (final_pos_y - global.pos_y) * side_scale;

   // calculate error for distance and theta
   error = sqrt(delta_x * delta_x + delta_y * delta_y);
   error_theta = wrap(final_theta - global.theta);
}

void moveToPosition(double final_pos_x, double final_pos_y, double final_theta, double error_move=2, double error_turn=2, double k_p=kp, double k_pT=kpT, bool keep_momentum=false){
   error = 144.0; // for movement
   error_theta = 360.0; // for turning

   double movement_error_bound = error_move; //in inches
   double turning_error_bound = error_turn; //in degrees
   bool movement_ended = false;
   bool slew_control = false;

   double time_elapsed = 0;

   for(int i=0; i<4; i++)
      wheel_indices[i] = 0;

   while ((abs(error)/side_scale > movement_error_bound || abs(error_theta) > turning_error_bound)){
      for(int i = 0; i < 4; i++)
         speeds[i] = 0;
    
      //cout<<"debugging"<<endl;
      error_update(final_pos_x, final_pos_y, final_theta);
        
      // when movement reaches final position, don't restart movement
      
      if(!keep_momentum){
         movementPID(final_pos_x, final_pos_y, keep_momentum, k_p, ki);
      } 
      else {
         if(movementPID(final_pos_x, final_pos_y, keep_momentum, k_p, ki))
            break;
      }
      
      turningPLoop(k_pT);
   
      //cout<<"Speeds: "<<speeds[0]<<","<<speeds[1]<<","<<speeds[2]<<","<<speeds[3]<<endl;
      //cout<<"Theta: "<<local.theta<<endl;
      //cout<<"Pos: ("<<local.pos_x<<", "<<local.pos_y<<")"<<endl;
      
      motorSpeeds(speeds, slew_control);
   
      time_elapsed+=5;
      if(time_elapsed>time_out){
         time_out=99999;
         break;
      }
   
      if(time_elapsed>intake_early){
         intake_early=99999;
         balls_shot=0;
         balls_intaked=0;
          spin(intake_left, 100);
          spin(intake_right, 100);
      }
   
      wait(5);
   } 
   
   if(!keep_momentum){
      double arr[] = {0,0,0,0};
      motorSpeeds(arr);
   }

}

/* BACKUP ODOM CODE: */

//double center_arc_length, center_to_rotation_point;
//center_arc_length = (left_delta * center_to_right_wheel + right_delta * center_to_left_wheel) / (center_to_left_wheel + center_to_right_wheel);
//center_to_rotation_point = center_arc_length / (theta_delta * PI/180);
//side_delta = sqrt(2 * center_to_rotation_point * center_to_rotation_point * (1 - cos(theta_delta * PI/180))) * signum(left_delta + right_delta);