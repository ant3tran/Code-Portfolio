#include "macros.h"
#include "robot_config.h"

// distance sensor override and settings
bool override_distance = false;
bool override_distance2 = false;
bool indexer_spinning = false;
bool shooting_call=false;
int intake_mode = 0;

int b1, b2, b1_reset;
int intake_sense, shooting_sense, intake_sense2;
bool first_ball_detected=false, second_ball_detected=false, third_ball_detected=false, fourth_ball_detected=false;

// auton shooting variables
int auton_shooting_mode = 0; // 0 = nothing, 1 = shoot, -1 = dump/poop
int auton_intaking_mode = 0; // 0 = off, 1 = intake, -1 = outtake

int balls_intaked = 0; // measured by sensors
int balls_shot = 0; // measured by sensors
int intaking_target = 0; // target
int shooting_target = 0; // target

int optional_shooting_delay = 0; // kill shooting x seconds after shooting target reached
int optional_descore_delay = 0; // start dumping/pooping x seconds after method call
int optional_intake_delay = 0; // start intaking x seconds after shooting begins at goal

int descore_time = 1000; // start descoring for x seconds 
int disposal_setting = 1; // 0 = dumping, 1 = pooping (default)

// miscellaneous 
bool shooting_fast=false; // synchs driver shooting with smooth acceleration to 0
bool ball_one = false;  // detects if bot has 1+ ball - autoindexing logic
bool ass_intaking=false; // detects if bot is assintaking - autoindexing logic
bool shooting_while_moving=false; // for 
// // [25, 35] - current

bool spike=false;
int ball_detection_intaking() {
   spike=false;
   while(true){
          // upper_indexer = y.value()>=1 && base_one.value()<=40;
          // b1_reset = base_one.value()>=150;
          // b2 = base_two.value()>=1 && base_two.value()<70;
   
      intake_sense = intaking_sensor.value()<=50 && intaking_sensor.value()>0; //27, 24
          //intake_sense2 = intaking_sensor.value()<=100 && intaking_sensor.value()>0;
      int intake_sense_reset = intaking_sensor.value()>100; //35, 40
   
          // if(intake_sense2 && auton_shooting_mode==0)
          //   ball_one=true;
   
      if(intake_sense && !spike){
         spike=true;
         balls_intaked++;
      } 
      else if(intake_sense_reset && spike){
         spike=false;
      }
      wait(2);
   }
}

// // 25 - current
// // 30 - best
int ball_detection_shooting() {
   int spike=false;
   while(true){
      shooting_sense = shooting_sensor.value()<=35 && shooting_sensor.value()>=1; //30, 30
      bool shooting_sense_reset = shooting_sensor.value()>70;
   
      // for weird shooting angles (for higher tolerance if shooting ball gets stuck at top)
      // if(shooting_sensitive) shooting_sense_reset = base_two.value()>100;
   
      if(shooting_sense && !spike)
         spike=true;
      else if(shooting_sense_reset && spike){
         spike=false;
         balls_shot++;
         //cout<<"Ball shot"<<endl;
      }
      
      wait(2);
   }
}

int intaking_detection() {
   intaking_target=-1;
   while(true){
      if(intaking_target>=0){
         wait(optional_intake_delay);
          spin(intake_left, 100);
          spin(intake_right, 100);
         optional_intake_delay=0;
      
         if(balls_intaked>=intaking_target){
            if (disposal_setting==0){
                spin(intake_left, 10);
                spin(intake_right, 10);
               wait(160);
                spin(intake_left, 0);
                spin(intake_right, 0);
                hold(intake_left);
                hold(intake_right);
            } 
            else if(disposal_setting==1) {
                spin(intake_left, -100);
                spin(intake_right, -100);
            } 
            else if(disposal_setting==2){
                spin(intake_left, -100);
                spin(intake_right, -100);
            }
         
            intaking_target=-1;
         } 
         else {
            if(disposal_setting==0){
                spin(intake_left, 25);
                spin(intake_right, 25);
            } 
            else if(disposal_setting==1) {
                spin(intake_left, 100);
                spin(intake_right, 100);
            } 
            else if(disposal_setting==2) {
                spin(intake_left, 50);
                spin(intake_right, 50);
            }
         }
      }
      wait(5);
   }
}

// // distance sensing code
int distance_detection() {
//   bool correcting = false;
//   int color_bounds[] = {0,0};
//   bool intake_count_reached=false, shot_count_reached=false

   bool reset=false;

   while (true) {
    
      // shooting in programming skills/auton only
      if(auton_shooting_mode == 1){
         balls_shot=0;
      
         //spin(shooter, 100);
         //spin(indexer, 100);
        
         while(true){
            if(balls_shot < shooting_target){
                spin(shooter, 100);
                spin(indexer, 100);
            }
            
            else if(balls_shot >= shooting_target){
               wait(optional_shooting_delay);
            
                spin(shooter, 0);
                spin(indexer, 0);
                brake(indexer);
                brake(shooter);
               optional_shooting_delay=0;
               break;
            }
         }
      
         auton_shooting_mode = 0;
         indexer_spinning=false;
      }
      
       // descoring in progamming skills/auton only
      else if(auton_shooting_mode == -1) {
         balls_intaked=0;
         wait(50);
      
         int time_passed = 0, time_pooping = 0;
         bool pause = false;
      
         wait(optional_descore_delay);
      
         if(disposal_setting==0){ //intaking for dumping or overshooting
             spin(intake_left, -100);
             spin(intake_right, -100);
         } 
         else if(disposal_setting==1) { //intaking for pooping
             spin(intake_left, 100);
             spin(intake_right, 100);
         } 
         else if(disposal_setting==2) {
             spin(intake_left, 0);
             spin(intake_right, 0);
         }
      
         if(disposal_setting==0){ //indexing logic for dumping
             spin(shooter, -50);
             spin(indexer, -50);
            wait(descore_time);
         } 
         else if(disposal_setting==1) { //indexing logic for pooping
            for (int i=0; i<descore_time/2; i++){
               if(!pause){
                   spin(shooter, -40);
                   spin(indexer, -40);
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
            
               if(sense && time_passed%280==0){ // if upper indexer triggered for 280 ms when dumping, stop indexer
                  pause=true;
               } 
            
               ball_one=false;
               time_passed+=5;
               wait(2);
            }
         } 
         else if(disposal_setting==2) { //indexing logic for overshooting
            balls_shot=0;
            shooting_target=2;
            wait(50);
         
            while(true){
               if(balls_shot < shooting_target){
                   spin(shooter, 100);
                   spin(indexer, 100);
               }
               
               else if(balls_shot >= shooting_target){
                  wait(optional_shooting_delay);
               
                   spin(shooter, 0);
                   spin(indexer, 0);
               
                  optional_shooting_delay=0;
                  break;
               }
            }
         }
      
          spin(shooter, 0);
          spin(indexer, 0);
      
         if(disposal_setting==2){
             hold(shooter);
             hold(indexer);
         }
       
         if(disposal_setting == 0 || disposal_setting == 1) {
             spin(intake_left, 100);
             spin(intake_right, 100);
         } 
         else {
             spin(intake_left, -100);
             spin(intake_right, -100);
         }
      
         auton_shooting_mode = 0;
         disposal_setting = 1;
         optional_descore_delay = 0;
         indexer_spinning=false;
         balls_shot=0;
         balls_intaked=0;
      
         if(disposal_setting!=2)
            wait(200);
      
         if(ass_intaking){
            ball_one=true;
            override_distance=false;
            ass_intaking=false;
         }
      }
      
       // regular indexing logic (for driver and programming/auton)
      else if (auton_intaking_mode == 0 && !override_distance) {
      
         if(upper_indexer.value() < 60 || shooting_sensor.value() < 60){ // if a top ball detected, never run indexer
            ball_one = false;
            //cout<<upper_indexer.value()<<endl;
            //cout<<shooting_sensor.value()<<endl;
         } 
         else if(intaking_sensor.value() < 50 && upper_indexer.value() > 30){ // else run indexer if one ball detected
            ball_one = true;
         } 
      
         // note: for ass intaking auton logic, just set ball_one=true manually and it will automatically run indexer at slow speed
      
         if(ball_one){
             spin(shooter, 25);
             spin(indexer, 25);
         } 
         else if (shooting_fast){ // use brake type right after shooting for 300 ms, then go back to hold
             spin(shooter, 0);
             spin(indexer, 0);
             brake(indexer);
             brake(shooter);
            wait(300);
            shooting_fast=false;
         } 
         else if(!indexer_spinning) { // hold type for normal indexing
             spin(shooter, 0);
             spin(indexer, 0);
             hold(indexer);
             hold(shooter);
         }
      } 
   
      wait(5);
   }

   return -1;
}

// /* optical sensor code */

// string auton_shooting_color = "red";

// // if(auton_shooting_color=="red"){
// //   color_bounds[0]=220;
// //   color_bounds[1]=250;
// // } else{
// //   color_bounds[0]=0;
// //   color_bounds[1]=25;
// // }

// // while(color_detector.hue()<color_bounds[0] || color_detector.hue()>color_bounds[1]){
// //   spin(shooter_left, 100 * auton_shooting_mode);
// //   spin(shooter_right, 100 * auton_shooting_mode);
// // }

// /* auton shooting code: time based */

// // if(auton_shooting_mode != 0){
// //   spin(shooter_left, 100 * auton_shooting_mode);
// //   spin(shooter_right, 100 * auton_shooting_mode);
// //   wait(shoot_time);
// //   spin(shooter_left, 0);
// //   spin(shooter_right, 0);
// //   auton_shooting_mode = 0;
// // }