#include "brain_interface.h"

bool auton_on = true;
double start_timer = 0;
double end_timer = 0;
double time_elapsed = 0;

//moveToPosition: 
// if third paramter is true, the position entered will be a global position of the field
// if third parameter is false, the position entered will be relative to the robot

void run_intakes(double mode){
  spin(intake_left, 100*mode);
  spin(intake_right, 100*mode);
  intake_mode = mode;
}

void move_forward(double length, double speed=100){
  spin(front_left, speed);
  spin(front_right, speed);
  spin(back_left, -speed);
  spin(back_right, -speed);
  wait(length);
  spin(front_left, 0);
  spin(front_right, 0);
  spin(back_left, 0);
  spin(back_right, 0);
}

void back_up(double length, double speed=100){
  spin(front_left, -speed);
  spin(front_right, -speed);
  spin(back_left, speed);
  spin(back_right, speed);
  wait(length);
  spin(front_left, 0);
  spin(front_right, 0);
  spin(back_left, 0);
  spin(back_right, 0);
}

void left_right(double left_speed, double right_speed){
  spin(front_left, left_speed);
  spin(back_left, -left_speed);
  spin(front_right, right_speed);
  spin(back_right, -right_speed);
}

void reset_ball_counter(){
  balls_intaked=0;
  balls_shot=0;
}

void testing3(){
  global.theta=90;
  shooting_target=1;
  intaking_target=1;
  disposal_setting=0;
  override_distance=true;
  auton_shooting_mode=1;

  // 4th GOAL
  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
  }

  wait(100);
  left_right(-100, -100);
  wait(200);
  descore_time=200;
  ass_intaking=true;
  auton_shooting_mode=-1;

  moveToPosition(0, -20, 90);
  wait(60000);
}

void testing2(){

  start_timer = vex::timer::system();
  global.theta=157;
  reset_ball_counter();

  run_intakes(1);
  ball_one=true;
  move_forward(300);

  time_out=1000;
  moveToPosition(-41.5, 15, 162); //-41, 15, 162
  moveToPosition(-39.5, 0, -135);
  run_intakes(0);
  
  left_right(20, 20); 
  wait(200);
  reset_ball_counter();

  disposal_setting=0; 
  override_distance=true;
  
  optional_intake_delay=200;

  intaking_target=1;
  shooting_target=2;
  auton_shooting_mode=1;

  // 1st GOAL
  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
  }
  
  wait(200);
  left_right(-100, -100);
  wait(500);

  descore_time=500;
  ass_intaking=true;
  auton_shooting_mode=-1;
  override_distance=false;
  
  moveToPosition(-13, 55, -119); //-13, 55, -117
  run_intakes(1);
  
  moveToPosition(global.pos_x, global.pos_y, 180);
  reset_ball_counter();

  moveToPosition(-38, 55.5, 180);

  left_right(10, 10);
  wait(200);

  shooting_target=2;
  intaking_target=2;
  optional_intake_delay=300;
  auton_shooting_mode=1;

  // 2nd GOAL
  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
  }

  run_intakes(-1);
  wait(200);
  left_right(-100, -100);
  wait(150);

  optional_descore_delay=200;
  descore_time=1700;
  auton_shooting_mode=-1;
  
  moveToPosition(-30, 56, 90);
  run_intakes(0.5);

  moveToPosition(-45, 81.5, 127); //-44, 82, 127
  moveToPosition(-41, 111, 135);

  run_intakes(0);
  reset_ball_counter();
  left_right(20, 20);
  wait(200);

  shooting_target=1;
  intaking_target=2;
  disposal_setting=2;
  auton_shooting_mode=1;
  
  // 3rd GOAL
  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
  }

  wait(100);
  disposal_setting=2;
  reset_ball_counter();
  shooting_target=1;
  wait(100);
  
  ass_intaking=true;
  auton_shooting_mode=-1;
  time_out=800;
  moveToPosition(-30, 103, 165); //-30, 104, 165
  reset_ball_counter();
  intake_early=800;
  //moveToPosition(5, 86, -30); // what diagonal movement would have looked like

  moveToPosition(13, 109, 85);
  left_right(20, 20);
  wait(100);

  shooting_target=1;
  disposal_setting=0;
  override_distance=true;
  intaking_target=1;
  auton_shooting_mode=1;

  // 4th GOAL
  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
  }

  wait(100);
  left_right(-100, -100);
  wait(200);
  descore_time=350;
  ass_intaking=true;
  auton_shooting_mode=-1;

  moveToPosition(14.5, 83, 90);

  end_timer = vex::timer::system();
  cout<<end_timer-start_timer<<endl;
  wait(60000);

  // moveToPosition(-28, 55.5, 180);
  // run_intakes(0.5);

  // descore_time=1500;
  // //optional_descore_delay = 400;
  // auton_shooting_mode=-1;
  // moveToPosition(-45, 83, 120);
  // moveToPosition(-45, 112, 135);
  // reset_ball_counter();
  // run_intakes(0);

  // left_right(20, 20);
  // wait(200);

  // optional_intake_delay=200;

  // shooting_target=1;
  // intaking_target=2;
  // auton_shooting_mode=1;

  // while(auton_shooting_mode!=0 || intaking_target != -1){
  //   wait(5);
  // }

  // wait(200);
  // left_right(-100, -100);
  // wait(100);

  // moveToPosition(-33, 104, 165);

  // wait(60000);


  // left_right(10, 10);
  // wait(100);
  // run_intakes(-1);
  // shooting_target=2;
  // auton_shooting_mode=1;
  // wait(700);
  // back_up(300);
  // left_right(-100,100);
  // auton_shooting_mode=0;
  // ball_one=true;
  // reset_ball_counter();
  // shooting_target=2;
  // intaking_target=4;
  // auton_shooting_mode=1;

  // while(auton_shooting_mode!=0 || intaking_target != -1){
  //   wait(5);
  // }

  wait(60000);
}

// prog run

void prog_run(){
  start_timer = vex::timer::system();
  global.theta=135;
  reset_ball_counter();
  double time_elapsed=0;
  wait(25);

  run_intakes(1);
  move_forward(500);
  moveToPosition(-35, 28, 165);

  moveToPosition(-30, 9, -135);
  move_forward(500);

  shooting_target=3;
  intaking_target=4;
  auton_shooting_mode=1;
  time_elapsed=0;
  optional_shooting_delay = 100;

  // SHOOTING AT 1ST GOAL
  
  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>100){
      left_right(10, 10); 
    }
  }

  // wait(200);
  // reset_ball_counter();
  // shooting_target=2;
  // intaking_target=1;
  // auton_shooting_mode=1;
  
  // while(auton_shooting_mode!=0 || intaking_target != -1){
  //   wait(5);
  // }

  run_intakes(-1);
  wait(250);

  descore_time=700;
  auton_shooting_mode=-1;
  back_up(650);
  reset_ball_counter();

  moveToPosition(-2, 61, 90, false, false, 0.065);
  moveToPosition(-11, 61, -180);
  time_out=1000;
  moveToPosition(-32, 61, -180, false, false, 0.075);
  time_out=99999;
  move_forward(300);

  shooting_target=1;
  intaking_target=0;
  auton_shooting_mode=1;

  // SHOOTING AT 2ND GOAL

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    left_right(10, 10); 
  }

  wait(250);
  shooting_target=1;
  intaking_target=3;
  auton_shooting_mode=1;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
  }

  run_intakes(-1);
  wait(250);

  optional_descore_delay=150;
  descore_time=650;
  auton_shooting_mode=-1;
  moveToPosition(-27, 62, -135);

  time_out=1800;
  moveToPosition(-37.5, 92, 135, false, false, 0.075); //-37, 91.5
  time_out=99999;

  moveToPosition(-16.5, 102.75, 45, false, false, 0.075); //-18, 102.75
  move_forward(150);
  moveToPosition(-31, 116, 135);
  move_forward(400);

  shooting_target=1;
  intaking_target=4;
  auton_shooting_mode=2;

  // SHOOTING AT 3RD GOAL

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    left_right(10, 10);
  }

  wait(250);

  back_up(150);
  optional_descore_delay=150;
  // no_intake=true; //stop intake really quickly when descoring
  descore_time=1400;
  auton_shooting_mode=-1;

  moveToPosition(26, 106, 90, false, false, 0.075);
  reset_ball_counter();

  move_forward(350);
  shooting_target=1;
  intaking_target=1;
  auton_shooting_mode=2;

  // SHOOTING at 4TH GOAL

  while(auton_shooting_mode!=0 || intaking_target != -1){
    left_right(0, 0);
    wait(5);
  }

  run_intakes(-1);
  wait(250); 

  optional_shooting_delay=200; //start descoring 200 ms into the next movement
  descore_time=500;
  auton_shooting_mode=-1;
  back_up(200);
  left_right(-100, 100);
  wait(150);
  balls_shot=0;

  moveToPosition(24, 100, -90);
  move_forward(400);
  moveToPosition(50, 101.75, 37);
  move_forward(250);
  moveToPosition(84, 98, 0);
  moveToPosition(81, 119, 45);

  move_forward(350);
  shooting_target=1;
  intaking_target=4;
  auton_shooting_mode=1;
  time_elapsed=0;

  // SHOOTING AT 5TH GOAL
  
  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>100){
      left_right(10, 10); 
    }
  }

  wait(200);
  reset_ball_counter();
  shooting_target=2;
  intaking_target=1;
  auton_shooting_mode=1;
  
  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
  }
  
  run_intakes(-1);
  wait(250);

  descore_time=700;
  auton_shooting_mode=-1;
  back_up(500);

  moveToPosition(51, 65, -90, false, false, 0.065);
  moveToPosition(61, 65, 0);
  time_out=1000;
  moveToPosition(92, 65, 0, false, false, 0.075);
  time_out=99999;


  /* new time-out syntax

  time_out = 1000; //change accordingly (maximum time that the method can run for)
  moveToPosition/movement
  time_out = 99999; 

  */

  end_timer = vex::timer::system();
  cout<<end_timer-start_timer<<endl;

  wait(60000);
}

// home row auton

void homerow(){
  start_timer = vex::timer::system();
  global.theta=0;
  reset_ball_counter();
  wait(25);

  run_intakes(1);
  left_right(50, 35);
  wait(550);

  intaking_target=3;
  shooting_target=3;
  auton_shooting_mode=1;
  optional_shooting_delay = 250;

  double time_elapsed=0;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>200){
      left_right(0, 0); 
    }
    if (time_elapsed>6000){
      auton_shooting_mode=0;
    }
  }
  wait(250);

  back_up(150);
  descore_time=1000;
  auton_shooting_mode=-1;
  time_out=3000;
  moveToPosition(-43, 14, -90, false, false, 0.09);
  time_out=999999;
  
  reset_ball_counter();
  run_intakes(1);
  move_forward(400);

  intaking_target=2;
  shooting_target=1;
  time_elapsed=0;
  auton_shooting_mode=2;
  optional_shooting_delay = 0;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>300){
      left_right(0, 0); 
    }
  }

  wait(250);
  back_up(400);
  descore_time=1500;
  auton_shooting_mode=-1;
  moveToPosition(-42, 29, -45, false, false, 0.13);

  intaking_target=3;
  shooting_target=2;
  time_elapsed=0;

  reset_ball_counter();
  //moveToPosition(-94.5, 7, -135); 
  moveToPosition(-92, 30, -145);
  //moveToPosition(-99, 26, -135); //-95.5 --> -97.5
  run_intakes(1);
  move_forward(600); //450
  auton_shooting_mode=1;
  optional_shooting_delay=75;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
  }

  wait(250);
  back_up(400);
  run_intakes(0);

  moveToPosition(-51, 54.5, 70, false, false, 0.07);
  run_intakes(-0.2);
  moveToPosition(-42, 54.5, 60, false, false, 0.07);

  // moveToPosition(-56, 46, 90);
  // moveToPosition(-56, 46, -90, 0, 0, 0, 0, 10);
  // moveToPosition(-56, 46, 90, 0, 0, 0, 0, 10);
  // moveToPosition(-56, 46, -90, 0, 0, 0, 0, 10);
  // moveToPosition(-56, 46, 120);
  wait(60000);
}

// auton with ryan (917m coordinated)

void coordinated_1(){
  start_timer = vex::timer::system();
  global.theta=0;
  reset_ball_counter();
  wait(25);

  run_intakes(1);
  left_right(50, 35);
  wait(550);

  intaking_target=3;
  shooting_target=3;
  auton_shooting_mode=1;
  optional_shooting_delay = 250;

  double time_elapsed=0;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>200){
      left_right(0, 0); 
    }
    if (time_elapsed>6000){
      auton_shooting_mode=0;
    }
  }
  wait(250);

  back_up(150);
  descore_time=1000;
  auton_shooting_mode=-1;
  time_out=3000;
  moveToPosition(-43, 14.5, -90, false, false, 0.09);
  time_out=999999;
  
  reset_ball_counter();
  run_intakes(1);
  move_forward(400);

  intaking_target=2;
  shooting_target=1;
  time_elapsed=0;
  auton_shooting_mode=2;
  optional_shooting_delay = 0;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>300){
      left_right(0, 0); 
    }
  }

  wait(250);
  back_up(400);
  descore_time=1500;
  auton_shooting_mode=-1;
  moveToPosition(-20, 31, -90, false, false, 0.11);
  wait(250);

  moveToPosition(27.5, 25, 32);
  reset_ball_counter();

  left_right(9, 9);

  intaking_target=1;
  shooting_target=1;
  time_elapsed=0;
  auton_shooting_mode=1;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    if(intaking_target==-1){
      left_right(0, 0);
    }
  }  
  
  left_right(0, 0);
  run_intakes(0);
  wait(350);
  reset_ball_counter();

  //left_right(5, 5);
  intaking_target=3;
  auton_shooting_mode=1;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
  }  

  run_intakes(-1);
  back_up(400);

  end_timer = vex::timer::system();
  cout<<end_timer-start_timer<<endl;

  wait(60000);
}

// mjs coordianted auton? not finished

void coordinated_2(){
  start_timer = vex::timer::system();

  end_timer = vex::timer::system();
  cout<<end_timer-start_timer<<endl;

  run_intakes(1);

  moveToPosition(-26, 11, -145);
  move_forward(700);

  double time_elapsed=0;

  intaking_target=3;
  shooting_target=3;
  auton_shooting_mode=1;
  optional_shooting_delay = 300;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>100){
      left_right(10, 10); 
    }
    if (time_elapsed>6000){
      auton_shooting_mode=0;
    }
  }
  wait(250);

 
  descore_time=900;
  auton_shooting_mode=-1;
  back_up(600);
  wait(500);

  moveToPosition(7.5, 47.5, 79);
  run_intakes(-0.2);
  auton_shooting_mode=0;
  moveToPosition(13.5, 47.5, 65); //12, 50.5, 67
  // back_up(300);


  // moveToPosition(80, 20, 25.5); 

  // left_right(9, 9);

  // intaking_target=1;
  // shooting_target=1;
  // time_elapsed=0;
  // auton_shooting_mode=1;

  // while(auton_shooting_mode!=0 || intaking_target != -1){
  //   wait(5);
  //   if(intaking_target==-1){
  //     left_right(0, 0);
  //   }
  // }  
  
  // left_right(0, 0);
  // run_intakes(0);
  // wait(350);
  // reset_ball_counter();

  // //left_right(5, 5);
  // intaking_target=3;
  // auton_shooting_mode=1;

  // while(auton_shooting_mode!=0 || intaking_target != -1){
  //   wait(5);
  // }  

  // run_intakes(-1);
  // moveToPosition(50, 30, 90);

  wait(60000);
}

void testing(){
  start_timer = vex::timer::system();
  global.theta=0;
  reset_ball_counter();
  wait(25);

  run_intakes(1);
  left_right(50, 20);
  wait(500);

  intaking_target=3;
  shooting_target=3;
  auton_shooting_mode=1;

  double time_elapsed=0;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>200){
      left_right(0, 0); 
    }
  }
  wait(250);

  back_up(150);
  descore_time=1000;
  auton_shooting_mode=-1;
  moveToPosition(-43, 6.5, -90);
  
  reset_ball_counter();
  run_intakes(1);
  move_forward(200);

  intaking_target=2;
  shooting_target=1;
  time_elapsed=0;
  auton_shooting_mode=1;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>300){
      left_right(0, 0); 
    }
  }

  wait(250);
  back_up(400);
  descore_time=1500;
  auton_shooting_mode=-1;
  moveToPosition(-42, 31, -45, false, false, 0.11);

  intaking_target=3;
  shooting_target=2;
  time_elapsed=0;

  moveToPosition(-95.5, 7, -135);
  moveToPosition(-98.5, 4, -135); //-86, 7 //-92, 2
  reset_ball_counter();
  run_intakes(1);
  move_forward(250); //450
  auton_shooting_mode=1;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>100){
      left_right(0, 0); 
    }
  }

  run_intakes(0);
  wait(250);
  back_up(400);

  moveToPosition(-61, 50, 90, false, false, 0.07);
  run_intakes(-0.2);
  moveToPosition(-51, 49, 90, false, false, 0.06);

  moveToPosition(-56, 46, 120);

  // move_forward(350);
  // moveToPosition(50.5, 9, -90);
  // move_forward(400);
  // wait(500);
  // back_up(400);
  // moveToPosition(97, 7, -45);
  // run_intakes(1);
  // move_forward(350);
  // override_distance=true;
  // spin(shooter, 100);
  // spin(indexer, 100);
  // //moveToPosition(0, 72, 90);
  // moveToPosition(0, 0, 135);
  // moveToPosition(0, 0, -90);
  // moveToPosition(0, 0, 0); 
  // wait(60000);
  
  
  // global.theta=90;
  // run_intakes(1);
  // left_right(10, 10);
  // cout<<"working"<<endl;

  // balls_intaked=0;
  // balls_shot=0;
  // intaking_target=1;
  // shooting_target=2;
  // auton_shooting_mode=1;

  // while(auton_intaking_mode!=0 || intaking_target != -1){
  //   wait(5);
  // }
  // wait(200);

  // left_right(-100, 10);
  // wait(300);

  // intaking_target=0;
  // shooting_target=3;
  // auton_shooting_mode=1;

  // while(auton_intaking_mode!=0 || intaking_target != -1){
  //   wait(5);
  // }

  // wait(400);

  // moveToPosition(global.pos_x, global.pos_y, 20);
  // move_forward(300);
  end_timer = vex::timer::system();
  cout<<end_timer-start_timer<<endl;
  wait(60000);
}

// Auton without 7
void no_7(){
  start_timer = vex::timer::system();
  global.theta=0;
  reset_ball_counter();
  wait(25);

  run_intakes(1);
  left_right(50, 35);
  wait(550);

  intaking_target=3;
  shooting_target=3;
  auton_shooting_mode=1;
  optional_shooting_delay = 250;

  double time_elapsed=0;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>200){
      left_right(0, 0); 
    }
    if (time_elapsed>6000){
      auton_shooting_mode=0;
    }
  }
  wait(250);

  back_up(150);
  descore_time=1000;
  auton_shooting_mode=-1;
  time_out=3000;
  moveToPosition(-43, 14, -90, false, false, 0.09);
  time_out=999999;
  
  reset_ball_counter();
  run_intakes(1);
  move_forward(400);

  intaking_target=2;
  shooting_target=1;
  time_elapsed=0;
  auton_shooting_mode=2;
  optional_shooting_delay = 0;

  while(auton_shooting_mode!=0 || intaking_target != -1){
    wait(5);
    time_elapsed+=5;
    if(time_elapsed>300){
      left_right(0, 0); 
    }
  }

  wait(250);
  back_up(400);
  descore_time=1500;
  auton_shooting_mode=-1;
  moveToPosition(-42, 29, -45, false, false, 0.13);

  // intaking_target=3;
  // shooting_target=2;
  // time_elapsed=0;

  // reset_ball_counter();
  //moveToPosition(-94.5, 7, -135); 
  moveToPosition(-58, 30, 70); //ALIGN FOR MIDDLE MOVEMENT
  // run_intakes(1);
  // move_forward(500); //450
  // auton_shooting_mode=1;
  // optional_shooting_delay=75;

  // while(auton_shooting_mode!=0 || intaking_target != -1){
  //   wait(5);
  //   time_elapsed+=5;
  // }

  // wait(250);
  // back_up(400);
  // run_intakes(0);

  moveToPosition(-49, 63, 70, false, false, 0.07);
  run_intakes(-0.2);
  moveToPosition(-41, 61, 60, false, false, 0.07);

  // moveToPosition(-56, 46, 90);
  // moveToPosition(-56, 46, -90, 0, 0, 0, 0, 10);
  // moveToPosition(-56, 46, 90, 0, 0, 0, 0, 10);
  // moveToPosition(-56, 46, -90, 0, 0, 0, 0, 10);
  // moveToPosition(-56, 46, 120);
  wait(60000);
}

void Blue2(){
  start_timer = vex::timer::system();
  global.theta = 0;  
  balls_intaked = 0;
  balls_shot = 0;

  override_distance=true;

  spin(indexer,-100);
  run_intakes(-1);
  left_right(50, 18);

  wait(100);
  spin(indexer, 0); 
  run_intakes(1);
  override_distance=false;


  intaking_target=3;
  shooting_target=3;
  wait(750);

  auton_shooting_mode=1;
  int movement_timer=0;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
    movement_timer+=5;
    if(movement_timer>500)
      left_right(0, 0);
  }

  run_intakes(-1);
  back_up(100);
  descore_time=2000;
  auton_shooting_mode=-1;

  moveToPosition(-23, 7, 0, true);
  moveToPosition(-40, 8.5, -90);

  balls_intaked=0;
  balls_shot=0;
  run_intakes(1);
  move_forward(380);

  balls_shot=0;
  intaking_target=2;
  shooting_target=1;
  auton_shooting_mode=1;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }

  run_intakes(-1);
  wait(150);

  descore_time=2500;
  balls_shot=0;
  shooting_target=1;
  auton_shooting_mode=-1;

  optional_descore_delay=200;
  descore_time=1500;
  auton_shooting_mode=-1;

  moveToPosition(-28, 28, -90);

  moveToPosition(-33.5, 48, 130); //45.5 y
  back_up(300);

  moveToPosition(4, 43.5, 70); // 11 45 67

  wait(60000);
  balls_intaked=0;
  balls_shot=0;

  run_intakes(1);
  left_right(20, 20);
  movement_timer=0;

  while(movement_timer<1000 && balls_intaked!=1){
    wait(5);
  }

  run_intakes(0);
  back_up(500);
  wait(60000);

  //wait(60000); // kill auton (for debugging purposes)
  
  balls_intaked=0;
  balls_shot=0;

  moveToPosition(-72, 48.5, 90, false, false, 0.08, 0.005);
  run_intakes(0);
  moveToPosition(-54, 47, 85);

  //wait(60000);
  left_right(10, 40);

  intaking_target=3;
  shooting_target=2;

  wait(200);
  auton_shooting_mode=1;
  
  movement_timer=0;
  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
    movement_timer+=5;
    if(movement_timer>100)
      left_right(10, 10);
  }

  wait(100);
  run_intakes(-1);
  back_up(800);
  run_intakes(1);

  moveToPosition(-64, 49, 90, false, false, 0.08, 0.005);
  moveToPosition(-54, 47, 85);

  end_timer = vex::timer::system();
  time_elapsed = start_timer - end_timer;
  cout<<time_elapsed<<endl;

  shooting_call=true;
  wait(60000);
}

// AUTON
void Black2(){
  start_timer = vex::timer::system();
  global.theta = 0;  
  balls_intaked = 0;
  balls_shot = 0;

  override_distance=true;

  spin(indexer,-100);
  run_intakes(-1);
  left_right(50, 18);

  wait(100);
  spin(indexer, 0); 
  run_intakes(1);
  override_distance=false;


  intaking_target=3;
  shooting_target=3;
  wait(750);

  auton_shooting_mode=1;
  int movement_timer=0;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
    movement_timer+=5;
    if(movement_timer>500)
      left_right(0, 0);
  }

  run_intakes(-1);
  back_up(100);
  descore_time=2000;
  auton_shooting_mode=-1;

  moveToPosition(-23, 7, 0, true);
  moveToPosition(-40, 8, -90);

  balls_intaked=0;
  balls_shot=0;
  run_intakes(1);
  move_forward(350);

  balls_shot=0;
  intaking_target=2;
  shooting_target=1;
  auton_shooting_mode=1;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }

  run_intakes(-1);
  wait(150);
  // descore_time=2500;
  // descore_auto_intake=true;
  //balls_shot=0;
  //shooting_target=1;
  //auton_shooting_mode=-1;

  back_up(600);
  moveToPosition(-68, 28, -170);
  run_intakes(-1);

  descore_time=1300;
  auton_shooting_mode=-1;
  wait(1200);
  
  //wait(60000); // kill auton (for debugging purposes)
  
  balls_intaked=0;
  balls_shot=0;

  moveToPosition(-72, 48.5, 90, false, false, 0.08, 0.005);
  run_intakes(0);
  moveToPosition(-54, 47, 85);

  wait(60000);
  left_right(10, 40);

  intaking_target=3;
  shooting_target=2;

  wait(200);
  auton_shooting_mode=1;
  
  movement_timer=0;
  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
    movement_timer+=5;
    if(movement_timer>100)
      left_right(10, 10);
  }

  wait(100);
  run_intakes(-1);
  back_up(800);
  run_intakes(1);

  moveToPosition(-64, 49, 90, false, false, 0.08, 0.005);
  moveToPosition(-54, 47, 85);

  end_timer = vex::timer::system();
  time_elapsed = start_timer - end_timer;
  cout<<time_elapsed<<endl;

  shooting_call=true;
  wait(60000);
}

void Black1(){
  global.theta = 159;
  
    // run intakes and don't move for 750 sec, allows time for flipout 
  wait(50);
  run_intakes(1);
  balls_intaked = 0;

  // consecutive movements to corner goal
  moveToPosition(-27.5, -0.5, -160, true);
  left_right(20, 60);
  // moveToPosition(-44.4, 1, -135, false);

  // spin(front_left, 20);
  // spin(front_right, 20);
  // spin(back_left, -20);
  // spin(back_right, -20);

  // shoot upon reaching goal for 700 ms (note: shooting time doesn't affect robo waiting time)

  //descore_time=700;
  auton_shooting_mode=1;
  intaking_target=1;
  shooting_target=1;
  
  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }
  
  // wait 300 ms upon reaching goal, stop intakes, wait another 400 ms until shooting finishes 

  run_intakes(-1);
  back_up(200);
  run_intakes(1);

  moveToPosition(-25.5, 51, 90, false, false, 0.08, 0.004);
  moveToPosition(-5, 53, 79);

  //back up
  back_up(300);
  spin(front_left, 100);
  spin(front_right, -100);
  spin(back_left, -100);
  spin(back_right, 100);
  wait(150);
  moveToPosition(40, 46, 13, true);

  balls_intaked=0;
  run_intakes(1);
  moveToPosition(64.7, 59.4, 62, false, false); //65.4, 62.7
  move_forward(300);

  intaking_target=1;
  shooting_target=1;
  auton_shooting_mode=1;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }

  wait(200);
  run_intakes(-0.5);
  back_up(200);
  descore_time=1000;
  auton_shooting_mode=-1;

  spin(front_left, 100);
  spin(front_right, -100);
  spin(back_left, -100);
  spin(back_right, 100);
  wait(150);

  //moveToPosition(65.2, 30.4, -72.3, true, false, kp, ki, kpT, 6);
  left_right(20, 60);

  intaking_target=1;
  shooting_target=1;
  auton_shooting_mode=1;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }

  //back_up(200);

  // going clockwise
  // spin(front_left, 100);
  // spin(front_right, -100);
  // spin(back_left, -100);
  // spin(back_right, 100);
  // wait(100);

  // moveToPosition(62.5, 20, -42);
  // wait(10);
  // move_forward(250);

  // auton_intaking_mode=-1;
  // hold(intake_left);
  // hold(intake_right);
  // spin(indexer,-50); 
  // wait(1000);
  // descore_time=300;
  // run_intakes(-1);
  // auton_shooting_mode=-1;
  // wait(300);
  // auton_intaking_mode=1;
  // descore_time=300;
  // auton_intaking_mode=-1;

  // back_up(300);
  // run_intakes(1);
  // auton_intaking_mode=0;
  
  // balls_intaked = 0;
  // moveToPosition(61.8, 9, -44);
  // auton_shooting_mode=1;
  // move_forward(320);

  // intaking_target=1;
  // shooting_target=1;
  
  // while(auton_shooting_mode != 0 || intaking_target != -1){
  //   wait(5);
  // }
  // back_up(200);

  wait(60000);
}

void Blue3(){
  global.theta = 152;
  spin(indexer,40);
  spin(intake_left, -100);
  spin(intake_right, -100);
  intake_mode = 1;

  wait(300); // distance sensor trigger duration for flipout

  spin(indexer, 0);
  spin(intake_left, 0);
  spin(intake_right, 0);
  intake_mode = 0;

  wait(200); // wait before movement

  //moveToPosition(35, 9, -16, false);
  run_intakes(1);
  moveToPosition(-36.25, 6, 180, false);

  /*
  spin(front_left, 8);
  spin(back_left, -8);
  spin(front_right, 100);
  spin(back_right, -100);
  wait(450);
  spin(front_left, 0);
  spin(back_left, 0);
  spin(front_right, 0);
  spin(back_right, 0);

  auton_shooting_mode=1;
  intaking_target=1;
  shooting_target=1;
  
  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }

  //wait(60000);

  back_up(200);
  
  // Going to center
  run_intakes(1);
  //moveToPosition(-24.5, 52.3, 72.6, false, 0.083, 0.013); //0.083, 0.013
  moveToPosition(-19.9, 52, 85.2, false, 0.083, 0.013); //0.083, 0.013
  //-23.4, 52.5, 81.2
  wait(50);
  moveToPosition(0.5, 52.3, 72.6);
  run_intakes(0);

  moveToPosition(2, 33, 9, true);
  moveToPosition(67, 45.5, 9);
  auton_intaking_mode=-1;
  hold(intake_left);
  hold(intake_right);
  spin(indexer,-50); 
  moveToPosition(68, 45.5, 56);
  run_intakes(-1);
  wait(10);
  spin(front_right, 100);
  spin(back_right, -100);
  spin(front_left, 100);
  spin(back_left, -100);
  wait(200);
  spin(front_right, 0);
  spin(back_right, 0);
  spin(front_left, 0);
  spin(back_left, 0);

  // auton_intaking_mode=-1;
  // hold(intake_left);
  // hold(intake_right);
  // spin(indexer,-50); 
  // wait(1000);
  // descore_time=300;
  // run_intakes(-1);
  // auton_shooting_mode=-1;
  // wait(300);
  // auton_intaking_mode=1;
  // descore_time=300;
  // auton_intaking_mode=-1;

  back_up(300);
  run_intakes(1);
  auton_intaking_mode=0;
  
  balls_intaked = 0;
  moveToPosition(61.8, 9, -44);
  auton_shooting_mode=1;
  move_forward(320);

  intaking_target=1;
  shooting_target=1;
  
  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }
  back_up(200);
  */

  wait(60000);
  
}          

void Blue4(){
  wait(1000);
//   run_intake(0);
//   moveToPosition(0, 0, 135, false);
//   momentum_speeds[0]=-100, momentum_speeds[1]=-100, momentum_speeds[2]=100, momentum_speeds[3]=100;
//   moveToPosition(-19, 22, 135, true);
//   moveToPosition(-29, 31, 180, false);
//   moveToPosition(-32, 17.5, -135, false); // 1st post

//   run_intake(1);
//   balls_shot = 0;
//   shoot_until_x_balls=1;
//   auton_shooting_many=true;
//   while(balls_shot!=1){
//     wait(5);
//   }
//   wait(200);
//   run_intake(2);

//   //moveToPosition(-20, 30, 0, false);
//   //override_line = 2;
//   moveToPosition(4, 21, -45, false);
  
//   auton_shooting_one=true;
//   hold(intake_left);
//   hold(intake_right);
//   wait(750);

//   moveToPosition(12, 30, 0, false);
//   run_intake(0);
//   moveToPosition(60, 30, 0, false);
//   moveToPosition(96, 6, -45, false);
//   auton_shooting_one=true;
//   run_intake(1);
//   wait(500);
//   run_intake(2);
//   wait(250);

//   back_up(500);
//   run_intake(0);
//   moveToPosition(72, 60, 90, false);
    spin(indexer, -100);
  wait(60000);
}

void Red1(){  
  global.theta = 90;
  wait(60000);

  moveToPosition(-24, 0, -135, true);
}

// AUTON
void Red2(){
  // 1) B -> A transition 1: strafing, move fprward

  start_timer = vex::timer::system();
  global.theta = 90;
  balls_intaked=0;
  moveToPosition(-8, -8, 135, true);
  move_forward(450);

  intaking_target=3;
  shooting_target=2;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }
  // 2) B -> A transition 1: strafing completely

  // start = vex::timer::system();
  // global.theta = 90;
  // moveToPosition(-18, -3, 135, false);
  // move_forward(200);

  end_timer = vex::timer::system();
  time_elapsed = end_timer-start_timer;
  cout<<time_elapsed<<endl;
  wait(60000);
  
}

void Red3(){
  //Gyro.calibrate();
  //while(Gyro.isCalibrating())wait(20);

  cout<<vex::timer::system()<<endl;
  spin(intake_left, -50);
  spin(intake_right, -50);
  spin(shooter, 100);

  wait(250); 

  spin(shooter, 0);
  balls_intaked = 0;
  balls_shot = 0;

  Gyro.setHeading(315, rotationUnits::deg);
  global.theta = 135;
  run_intakes(1);

   // start --> 1st pole
  moveToPosition(-10, 10, 135, true);
  moveToPosition(-31.5, 28, -180, false, 0.12);
  moveToPosition(-32, 8, -135, false);
  move_forward(300);
  //cout<<global.pos_x<<endl;
  //cout<<global.pos_y<<endl;

  // shooting at 1st pole
  run_intakes(1);
  balls_intaked=0;
  intaking_target=2;
  shooting_target=3;
  auton_shooting_mode=1;
  optional_shooting_delay=25;
  run_intakes(1);
  wait(185);
  run_intakes(0);

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }
  wait(250);

  // 1st --> 2nd transition
  back_up(100);
  descore_time=1000;
  run_intakes(-1);
  auton_shooting_mode=-1;
  back_up(700);

  moveToPosition(14, 48.5, 135, false, 0.13);
  balls_intaked=0;
  run_intakes(1);
  move_forward(350);///
  //moveToPosition(3.25, 59.25, 135, false);
  //moveToPosition(10, 65, 178, false);
  //moveToPosition(3.25, 63, 135, false);//***FIX Y
  moveToPosition(-19.5, 65, 178, false);
  move_forward(400);

  // shooting at 2nd pole
  run_intakes(1);
  intaking_target=3;
  shooting_target=2;
  optional_shooting_delay=70;
  auton_shooting_mode=1;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }
  reset_theta();
  wait(300);
  

  // 2nd --> 3rd transition
  run_intakes(-1);//
  moveToPosition(-16.5, 65, -160, false);
  descore_time=600;
  run_intakes(-1);
  auton_shooting_mode=-1;
  wait(600);
  run_intakes(1);
  balls_intaked=0;
  
  moveToPosition(-31, 87.5, 135, false);
  move_forward(200);
  moveToPosition(-22, 118, 135, false);
  move_forward(500);
  
  // shooting at 3rd pole
  
  intaking_target=3;
  shooting_target=1;
  optional_shooting_delay=75;
  auton_shooting_mode=1;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }
  reset_theta();
  
  wait(100);
  back_up(200); 
  // // cout<<global.theta<<endl;
  // // reset_theta();
  // // cout<<global.theta<<endl;

  // // 3rd --> 4th transition
  // optional_descore_delay=50;//500
  // run_intakes(-1);
  // descore_time=850;
  // auton_shooting_mode=-1;
  // moveToPosition(-28, 114, -140, false);
  // wait(100);
  // moveToPosition(-30, 115, -7, false, 0.12, 0.001, 0.8);
  // run_intakes(1);

  // moveToPosition(-12, 115, -7, false);
  // balls_intaked=0;
  // moveToPosition(2.5, 115, -51, false);
  // move_forward(1000);
  // //moveToPosition(26, 80.5, -51, false);
  // reset_theta();
  // wait(10);
  // moveToPosition(26.6, 108, 90, false);
  // move_forward(400);

  // // shooting at 4th pole
  // intaking_target=-1;
  // shooting_target=2;
  // optional_shooting_delay=60;
  // auton_shooting_mode=1;
  // run_intakes(1);
  // wait(250);
  // run_intakes(0);

  // while(auton_shooting_mode != 0 || intaking_target != -1){
  //   wait(5);
  // }
  // reset_theta();
  // wait(300);

  // // 4th --> 5th transition
  // // run_intakes(1);
  // // wait(300);//
  // moveToPosition(29, 104, 120, false);
  // descore_time=800;
  // run_intakes(-0.75);
  // auton_shooting_mode=-1;
  // wait(600);
  // run_intakes(1);

  // moveToPosition(28, 111, 3, false, 0.12, 0.001, 1);
  // reset_theta();
  // balls_intaked=0;
  // moveToPosition(64, 111, 0, false);
  // moveToPosition(72, 111, -35, false); //
  // move_forward(300);

  // moveToPosition(78, 116.5, 45, false); //
  // run_intakes(1);
  // move_forward(550);  

  // // start --> 1st pole
  // moveToPosition(-10, 10, 135, true);
  // moveToPosition(-31.5, 28, -180, false, 0.12);
  // moveToPosition(-32, 8, -135, false);
  // move_forward(300);
  // //cout<<global.pos_x<<endl;
  // //cout<<global.pos_y<<endl;

  // // shooting at 1st pole
  // run_intakes(1);
  // balls_intaked=0;
  // intaking_target=2;
  // shooting_target=3;
  // auton_shooting_mode=1;
  // optional_shooting_delay=25;
  // run_intakes(1);
  // wait(185);
  // run_intakes(0);

  // while(auton_shooting_mode != 0 || intaking_target != -1){
  //   wait(5);
  // }
  // wait(250);

  // // 1st --> 2nd transition
  // back_up(100);
  // descore_time=1000;
  // run_intakes(-1);
  // auton_shooting_mode=-1;
  // back_up(700);

  // moveToPosition(14, 48.5, 135, false, 0.13);
  // balls_intaked=0;
  // run_intakes(1);
  // move_forward(400);///
  // //moveToPosition(3.25, 59.25, 135, false);
  // //moveToPosition(10, 65, 178, false);
  // //moveToPosition(3.25, 63, 135, false);//***FIX Y
  // moveToPosition(-19.5, 65, 178, false);
  // move_forward(400);

  // // shooting at 2nd pole
  // run_intakes(1);
  // intaking_target=3;
  // shooting_target=2;
  // optional_shooting_delay=70;
  // auton_shooting_mode=1;

  // while(auton_shooting_mode != 0 || intaking_target != -1){
  //   wait(5);
  // }
  // reset_theta();
  // wait(300);
  

  // // 2nd --> 3rd transition
  // run_intakes(-1);//
  // moveToPosition(-16.5, 65, -160, false);
  // descore_time=600;
  // run_intakes(-1);
  // auton_shooting_mode=-1;
  // wait(600);
  // run_intakes(1);
  // balls_intaked=0;
  
  // moveToPosition(-31, 87.5, 135, false);
  // move_forward(200);
  // moveToPosition(-22, 116.25, 135, false);
  // move_forward(550);
  
  // // shooting at 3rd pole
  
  // intaking_target=3;
  // shooting_target=1;
  // optional_shooting_delay=75;
  // auton_shooting_mode=1;

  // while(auton_shooting_mode != 0 || intaking_target != -1){
  //   wait(5);
  // }
  // reset_theta();
  
  // wait(100);
  // back_up(200); 
  // // cout<<global.theta<<endl;
  // // reset_theta();
  // // cout<<global.theta<<endl;

  // 3rd --> 4th transition
  optional_descore_delay=50;//500
  run_intakes(-1);
  descore_time=850;
  auton_shooting_mode=-1;
  moveToPosition(-28, 114, -140, false);
  wait(100);
  moveToPosition(-30, 115, -7, false, 0.12, 0.001, 0.8);
  run_intakes(1);

  moveToPosition(-12, 115, -7, false);
  balls_intaked=0;
  moveToPosition(2.5, 115, -51, false);
  move_forward(1000);
  //moveToPosition(26, 80.5, -51, false);
  reset_theta();
  wait(10);
  moveToPosition(26.6, 108, 90, false);
  move_forward(400);

  // shooting at 4th pole
  intaking_target=-1;
  shooting_target=2;
  optional_shooting_delay=60;
  auton_shooting_mode=1;
  run_intakes(1);
  wait(250);
  run_intakes(0);

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }
  reset_theta();
  wait(300);

  // 4th --> 5th transition
  // run_intakes(1);
  // wait(300);//
  moveToPosition(29, 104, 120, false);
  descore_time=800;
  run_intakes(-0.75);
  auton_shooting_mode=-1;
  wait(600);
  run_intakes(1);

  moveToPosition(28, 111, 3, false, 0.12, 0.001, 1);
  reset_theta();
  balls_intaked=0;
  moveToPosition(64, 111, 0, false);
  moveToPosition(72, 111, -35, false); //
  move_forward(300);

  moveToPosition(78.25, 116.5, 45, false); //
  move_forward(550); 

  // shooting at 5th pole
  run_intakes(1);
  //balls_intaked=0;
  intaking_target=4;
  shooting_target=2;
  optional_shooting_delay=5;
  auton_shooting_mode=1;
  run_intakes(1);
  wait(250);
  run_intakes(0);
  
  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }
  run_intakes(-1);
  
  // goal 5 reset
  global.pos_x = -32.55; //-32.5
  global.pos_y = 7.5; //7.5 //
  reset_theta();
  global.theta = wrap(global.theta+180);

  wait(150);

  // 5th --> 6th transition
  back_up(100);
  descore_time=1200;
  run_intakes(-1);
  auton_shooting_mode=-1;
  back_up(700);

  moveToPosition(16, 48, 135, false, 0.13);
  balls_intaked=0;
  run_intakes(1);
  moveToPosition(6, 56, 135, false);
  //moveToPosition(10, 65.5, 178, false, 0.16, 0.002, 1);
  moveToPosition(-20.5, 66, 178, false);
  move_forward(450);

  // shooting at 6th pole
  run_intakes(1);
  intaking_target=3;
  shooting_target=2;
  optional_shooting_delay=60;
  auton_shooting_mode=1;
  run_intakes(1);
  wait(200);
  run_intakes(0);

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }
  reset_theta();
  global.theta+=180;
  wrap(global.theta);
  wait(300);

  // 6th --> 7th transition
  run_intakes(-1);//
  moveToPosition(-17, 65, -160, false);
  descore_time=600;
  run_intakes(-1);
  auton_shooting_mode=-1;
  wait(600);
  run_intakes(1);
  balls_intaked=0;
  
  moveToPosition(-35.5, 89, 135, false);
  move_forward(115);
  moveToPosition(-28, 121.25, 135, false);
  move_forward(500);
     
  // shooting at 7th pole
  
  intaking_target=3;
  shooting_target=1;
  optional_shooting_delay=75;
  auton_shooting_mode=1;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }

  reset_theta();
  global.theta+=180;
  wrap(global.theta);

  wait(100);
  back_up(200);

  // 7th --> 8th transition
  //optional_descore_delay=500;
  run_intakes(-1);
  descore_time=850;
  auton_shooting_mode=-1;
  moveToPosition(-32, 113, -140, false);
  wait(100);
  moveToPosition(-32.5, 115, -7, false, 0.12, 0.001, 0.8);
  run_intakes(1);
  balls_intaked=0;

  //back_up(700);

  //global.theta=0;
  //reset_theta();
  //global.pos_x=-9;
  //global.pos_y=0;
  //run_intakes(1);

  moveToPosition(-12, 113, -2, true);
  moveToPosition(25, 103.5, 87, false);
  run_intakes(-1);
  move_forward(400);

  // shooting at 8th pole 

  balls_intaked=0;
  intaking_target=0;
  shooting_target=1;
  optional_shooting_delay=50;
  auton_shooting_mode=1;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }

  reset_theta();
  global.theta+=180;
  wrap(global.theta);
  wait(200);  

  // 8th --> center transition

  moveToPosition(25, 104, -90);
  run_intakes(1);
  moveToPosition(24, 90, -90);
  moveToPosition(21, 82, -90);
  moveToPosition(19.25, 76.5, -90);
  run_intakes(-1);
  move_forward(500);
  wait(100);
  reset_theta();
  global.theta+=180;
  wrap(global.theta);
  global.pos_x=0;
  global.pos_y=0;
  wait(100);
  back_up(200);
  moveToPosition(0,1,-90);
  moveToPosition(0, 4, -90);
  // moveToPosition(0, 1, -90);
  // moveToPosition(0, 4, -90);
  moveToPosition(0, 1, -90);
  moveToPosition(0.5, 4, -90);
  moveToPosition(1, 1, -90);

  // moveToPosition(22.25, 78, -90);
  // moveToPosition(22.25, 74, -90);
  // moveToPosition(22.25, 78, -90);
  // moveToPosition(22.25, 74, -90);
  // moveToPosition(22.25, 78, -90);
  // moveToPosition(22.25, 74, -90);

  override_distance=true;

  // shootign at center pole
  spin(back_right, -100);
  spin(front_right, 100);
  spin(shooter, 100);
  wait(500);
  spin(back_right, 0);
  spin(front_right, 0);
  wait(400);

  back_up(300);
  cout<<vex::timer::system()<<endl;

  // moveToPosition(-12, 110, 0, false);
  // moveToPosition(3, 110, -45, false);
  // moveToPosition(22, 88, -40, false);

  // moveToPosition(29, 110, 90, false);
  // move_forward(450);

  // // shooting at 4th pole
  // run_intakes(1);
  // intaking_target=3;
  // shooting_target=2;
  // optional_shooting_delay=50;
  // auton_shooting_mode=1;

  // while(auton_shooting_mode != 0 || intaking_target != -1){
  //   wait(5);
  // }
  // wait(300);

  // // 4th --> 5th transition
  // moveToPosition(29, 101, 70, false);
  // descore_time=500;
  // run_intakes(-0.7);
  // auton_shooting_mode=-1;
  // wait(500);
  // run_intakes(1);

  wait(60000);
}

void Red4(){
  global.theta=0;
  wait(400);
  run_intakes(1);

  moveToPosition(19, 0, 0, true);
  run_intakes(-1);
  moveToPosition(54, -1, 90, false);

  balls_intaked=0;
  intaking_target=0;
  shooting_target=1;
  optional_shooting_delay=50;
  auton_shooting_mode=1;

  while(auton_shooting_mode != 0 || intaking_target != -1){
    wait(5);
  }
  wait(200);  

  moveToPosition(54, -1, -90);
  run_intakes(1);
  moveToPosition(47, -33, -90);
  run_intakes(-1);
  moveToPosition(47, -36, -90);
  moveToPosition(47, -33, -90);
  moveToPosition(47, -36, -90);
  moveToPosition(47, -33, -90);
  moveToPosition(47, -36, -90);
  moveToPosition(47, -33, -90);
  moveToPosition(47, -36, -90);

  override_distance=true;

  spin(back_right, -100);
  spin(front_right, 100);
  wait(300);
  spin(back_right, 0);
  spin(front_right, 0);

  spin(shooter, 100);
  wait(500);

  back_up(500);


  // moveToPosition(0, 6, 90);
  // moveToPosition(0, 0, 90);
  // moveToPosition(0, 6, 90);
  // moveToPosition(0, 0, 90);
  // moveToPosition(0, 6, 90);
  // moveToPosition(0, 0, 90);

  wait(60000);
  // moveToPosition(-37, 20, -135, true);
  //  moveToPosition(-43, 9, -135, false);
  //moveToPosition(0, 24, 90, false);
  // moveToPosition(-31, 24, 180, false);
  // moveToPosition(-29, 7, -135, false);
  // move_forward(true, 200);
  // wait(1000);

  // moveToPosition(13, 48, 135, false);
  // momentum_speeds[0] = -100; 
  // momentum_speeds[1] = -100; 
  // momentum_speeds[2] = 100; 
  // momentum_speeds[3] = 100; 
  // moveToPosition(0, 63, 180, false);
  // moveToPosition(-29, 63, 180, false);
  // move_forward(true, 200);
  // moveToPosition(24,24,-45,false);
  // moveToPosition(0,48,135,false);
  // moveToPosition(24,72,-45,false);
  // momentum_speeds[0] = -100; 
  // momentum_speeds[1] = -100; 
  // momentum_speeds[2] = 100; 
  // momentum_speeds[3] = 100; 
  // moveToPosition(-12,12,135,true);
  // wait(60000);
}

void Red5() {
  // run intakes and don't move for 750 sec, allows time for flipout
  run_intakes(1); 
  wait(750);

  // consecutive movements to corner goal
  moveToPosition(-35, 4, 175, false);
  moveToPosition(-43, 9, -135, false);

  // shoot upon reaching goal for 700 ms (note: shooting time doesn't affect robo waiting time)
  descore_time=700;
  auton_shooting_mode=1;
  
  // wait 300 ms upon reaching goal, stop intakes, wait another 400 ms until shooting finishes 
  wait(300);
  run_intakes(0);
  wait(700);

  run_intakes(-1);
  descore_time=1200;
  auton_shooting_mode=-1;
  back_up(600);
  run_intakes(1);
  moveToPosition(-24, 55, 90, false);


  moveToPosition(6, 53, 45, false);

  descore_time=1000;
  auton_shooting_mode=1;
  wait(300);
  run_intakes(0);
  wait(1700);
  back_up(500);

  wait(60000);
}

/* extra auton code */

// double shoot_length = 1000;
// double shooting_detecting = true;
// double ball_detecting = true;
// int balls_intook = 0;
// int balls_shot = 0;
// int shoot_until_x_balls = 0;

// void shoot(int sec){
//   spin(shooter_left, 100);
//   spin(shooter_right, 100);
//   wait(sec);
//   spin(shooter_left, 0);
//   spin(shooter_right, 0);
//   override_distance=false;
// }

// int auton_shooting_once(){
//   wait(1000);
//   while(true){
//     wait(5);
//   }
//   return -1;
// }

// int detect_balls_intaking(){
//   wait(1000);
//   while(true){
//     wait(5);
//   }
//   return -1;
// }

// int detect_balls_shooting(){
//   wait(1000);
//   while(true){
//     wait(5);
//   }
//   return -1;
// }

// int auton_shooting_all(){
//   wait(1000);
//   while(true){
//     wait(5);
//   }
//   return -1;
// }

// void run_intake(int option){
//   if(option==0){
//     spin(intake_left, -100);
//     spin(intake_right, 100);
//   } else if (option==1) {
//     spin(intake_left, 0);
//     spin(intake_right, 0);
//   } else {
//     spin(intake_left, 100);
//     spin(intake_right, -100);
//   }

/* odom momentum testing code */

// global.theta = 90;
// moveToPosition(0, 36, 90, true, true);
// moveToPosition(20, 56, 45, false);
// wait(60000);

/* old prog code */
 // balls_shot=0;
  
  // moveToPosition(-41, -1, -123, false); 
  // run_intake(0);
  // moveToPosition(0, 0, 135, false);
  // momentum_speeds[0]=-100, momentum_speeds[1]=-100, momentum_speeds[2]=100, momentum_speeds[3]=100;
  // moveToPosition(-19, 22, 135, true);
  // moveToPosition(-29, 31, 180, false);
  // moveToPosition(-32, 17.5, -135, false); // 1st post

  // balls_intook = 0;
  // balls_shot = 0;
  // shoot_until_x_balls=4;
  // auton_shooting_many=true;
  // while(balls_intook!=2){
  //   wait(5);
  // }
  // wait(200);
  // override_line = 1;
  // run_intake(2);

  // moveToPosition(14, 53, 130, false);
  // run_intake(0);
  // moveToPosition(8, 74, 173, false);
  // moveToPosition(-24, 74, 173, false); // 2nd post

  // balls_shot = 0;
  // shoot_until_x_balls=2;
  // run_intake(0);
  // auton_shooting_many=true;
  // while(balls_shot!=2){
  //   wait(5);
  // }
  // wait(200);

  // moveToPosition(-15, 74, 173, false);
  // override_line = 2;
  // moveToPosition(-30, 94, 125, false);
  // moveToPosition(-22, 130, 135, false); //3rd post

  // momentum_speeds[0]=-100, momentum_speeds[1]=-100, momentum_speeds[2]=100, momentum_speeds[3]=100;
  // moveToPosition(-20, 118, 0, true);
  // run_intake(0);
  // wait(500);
  // override_line=2;
  // moveToPosition(24, 118, 45, false);

  // balls_shot = 0;
  // shoot_until_x_balls=1;
  // auton_shooting_one=true;
  // while(balls_shot!=1){
  //   wait(5);
  // }

  //

  // moveToPosition(0, 32, 90, true);
  // moveToPosition(-24, 48, 135, false);
  // final_pos_x = 0;
  // final_pos_y = 0;
  // f_theta = 90;
  //spin(intake_left, -100);
  //spin(intake_right, 100);
  // moveToPosition(0, 24, 90, true);
  // moveToPosition(-24, 96, 90, false);
  //  moveToPosition(5, 20, -45, false);

  // moveToPosition(48, 24, 0, false);
  // moveToPosition(24, 24, -45, false);
  // moveToPosition(0, 0, 90, false);
  //moveToPosition(48,24,0, false);
  //moveToPosition(48, -48, 90,false);
  //moveToPosition(0, -48, 90,false);
  //moveToPosition(0, 0, 90, false);
  //moveToPosition(0, 0, 90, false);
  // moveToPosition(0, 0, 90, false);

  // moveToPosition(0, 48, 0, false);
  // moveToPosition(24, 24, -45, false);

  // moveToPosition(0, 12, 90, false);
  // moveToPosition(13, 30, 0, false);
  // moveToPosition(19, 0, -45, false);
 
  // moveToPosition(0, 14, 90, false);
  // moveToPosition(17, 21, -45, false);
  // wait(250);
  // moveToPosition(9, 19, -45, false);
  // moveToPosition(-21, 15, -140, false);
  // wait(250);
  // moveToPosition(-21, 30, -160, false);
  // moveToPosition(-78, 12, -155, false);
  // wait(250);
  // moveToPosition(-76, 48, 90, false);
  // moveToPosition(-82, 49, 160, false);
  // wait(250);

  // moveToPosition(-81, 52, 180, false);
  // moveToPosition(-81, 56, 135, false);