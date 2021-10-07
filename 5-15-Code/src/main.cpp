// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// S                    distance      18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "auton_selector.h"

// using namespace std;
using namespace vex;

int auton_num = -3;
bool run_auton_plz = 0;
competition Competition;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  //Initializing Robot Configuration. DO NOT REMOVE!, vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  Gyro.calibrate();
  while(Gyro.isCalibrating()) wait(20);
}

void running_auton(){
  if(!run_auton_plz)
    run_auton_plz=true;
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
  switch(auton_num){
    case -4: testing3();
    case -3: testing2();
    case -2: Black2(); 
    case -1: testing();
    case 0: Black1(); 
    case 1: no_7(); 
    case 2: Blue2();
    case 3: Blue3();
    case 4: Blue4();
    case 5: Red1();
    case 6: Red2();
    case 7: Red3();
    case 8: Red4();
    case 9: Red5();
    case 10: homerow();
    case 11: coordinated_1(); //917m coordinated (i.e. start on right side)
    case 12: coordinated_2(); //mjs coordinated (i.e. start on left side)
    case 13: prog_run();
  }
  wait(60000);
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
  // all these buttons are single release (not hold)
  // Gyro.calibrate();
  // while(Gyro.isCalibrating())wait(20);
  //release(ButtonB, kill_indexing);
  // release(ButtonB, forwardonly);
  // release(ButtonA, stoponly);
  //release(ButtonRight, running_auton);
  // release(ButtonA, kill_indexing);
  // release(ButtonRight, auto_shoot);
  task* Drive;
  Drive=new task(driveControls);
  Drive->resume();
  // wait(100);
  // while (1) {
  //   if(!run_auton_plz)
  //     driveControls();
  //   else{
  //     Blue1();
  //     run_auton_plz=false;
  //   }
  //   wait(5); 
  // }
}


// L1 - hold - shooting (shooting over pooping)
// R1 - hold - pooping 
// L2 - button - indexer 

task* T = new task(trackOdometry);
task* T2 = new task(distance_detection);
task* T3 = new task(ball_detection_intaking);
task* T4 = new task(ball_detection_shooting);
task* T5 = new task(intaking_detection);
task* T6 = new task(shooterControls);

int main() {
  // Set up callbacks for autonomous and driver control periods.
  //auton_num = drawButtons();
  //Gyro.setHeading(315,rotationUnits::deg);
  odom_l.resetPosition();
  odom_b.resetPosition();
  odom_r.resetPosition();
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  wait(400);

  int min_value = 1000;
  
  // Prevent main from exiting with an infinite loop.
  while (true) { 

    //cout<<"Odom Theta"<<global.theta<<endl;
    //cout<<"Position: ("<<global.pos_x<<", "<<global.pos_y<<")\n";

    //cout<<color_detector.hue()<<endl; 

    // cout<<"\nShot: "<<balls_shot<<endl;
    // cout<<"Intook: "<<balls_intaked<<endl;
    // cout<<spike<<endl;

    // cout<<"Auton shooting mode: "<<auton_shooting_mode<<endl;
    // cout<<override_distance<<endl;
    
    //cout<<wheel_indices[0]<<wheel_indices[1]<<wheel_indices[2]<<wheel_indices[3]<<endl;
    //cout<<speeds[0]<<" "<<speeds[1]<<" "<<speeds[2]<<" "<<speeds[3]<<" "<<error<<endl;
    
    // min_value = MIN(min_value, intaking_sensor.value());
    // cout<<min_value<<endl;

    drawButtons();
    Brain.Screen.render();
    // wait(5);
  }
}