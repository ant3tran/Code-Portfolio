#include "wall_aligning.h"
//#include "motor_display.h"

typedef struct _button {
  int xpos;
  int ypos;
  int width;
  int height;
  bool state;
  vex::color offColor;
  vex::color onColor;
  const char *label;
  bool visible;
} button;

button red_screen[] = {
  {0, 0, 500, 250, false, 0xFF0000, 0xFF0000, "HOT_BABY", true}
};

//Create Buttons
// {x-pos, y-pos, x_size, y-size, state, offColor, onColor, "description", visible}
button main_menu[] = {
  {50, 50, 75, 75, false, 0x000000, 0xFFFFFF, "Auton_Mode", true},    //0
  {50, 150, 75, 75, false, 0x000000, 0xFFFFFF, "Debug_Mode", true},   //1
  {200, 50, 75, 75, false, 0x000000, 0xFFFFFF, "Global_Setup", true}, //2
  {200, 150, 75, 75, false, 0x00000, 0xFFFFFF, "Motor_info", true},
  {350, 50, 75, 75, false, 0x00000, 0xFFFFFF, "ART :D", true}
};

button motor_info_display[] {
  {225, 120, 30, 30, false, 0x000000, 0xFFFFFF, "<--", false},         //15
  {50, 25, 75, 75, false, 0x000000, 0xFFFFFF, "Drive", false},
  {200, 25, 75, 75, false, 0x000000, 0xFFFFFF, "Intake", false},    
  {350, 25, 75, 75, false, 0x000000, 0xFFFFFF, "Shooter", false}
};

button art_display[] {
  {225, 120, 30, 30, false, 0x000000, 0xFFFFFF, "<--", false}
};

button auton[] = {
  {225, 120, 30, 30, false, 0x000000, 0xFFFFFF, "<--", false },       //11
  {30, 40, 60, 60, false, 0x000000, 0x3BDDFF, "Blue 1", false},       //3
  {150, 40, 60, 60, false, 0x000000, 0x3BDDFF, "Blue 2", false },     //4
  {270, 40, 60, 60, false, 0x000000, 0x3BDDFF, "Blue 3", false },     //5
  {390, 40, 60, 60, false, 0x000000, 0x3BDDFF, "Blue 4", false },     //6
  {30, 160, 60, 60, false, 0x000000, 0xFF59B6, "Red 1", false },      //7
  {150, 160, 60, 60, false, 0x000000, 0xFF59B6, "Red 2", false },     //8
  {270, 160, 60, 60, false, 0x000000, 0xFF59B6, "Red 3", false },     //9
  {390, 160, 60, 60, false, 0x000000, 0xFF59B6, "Red 4", false },     //10
};

button odom_display[] = {
  {200, 165, 30, 30, false, 0x000000, 0xFFFFFF, "<--", false},        //14
  {105, 165, 75, 70, false, 0x000000, 0xFFFFFF, "Reset", false},      //13
  {30, 165, 75, 70, false, 0x000000, 0xFFFFFF, "Global/Local", false},//12
};

button compass[] = {
  {200, 165, 40, 40, false, 0x000000, 0xFFFFFF, "<--", false},        
  {140, 100, 40, 40, false, 0x000000, 0xFFFFFF, "E", false },    
  {140, 40, 40, 40, false, 0x000000, 0xFFFFFF, "NE", false },    
  {80, 40, 40, 40, true, 0x000000, 0xFFFFFF, "N", false},   
  {20, 40, 40, 40, false, 0x000000, 0xFFFFFF, "NW", false },     
  {20, 100, 40, 40, false, 0x000000, 0xFFFFFF, "W", false },     
  {20, 160, 40, 40, false, 0x000000, 0xFFFFFF, "SW", false },     
  {80, 160, 40, 40, false, 0x000000, 0xFFFFFF, "S", false },      
  {140, 160, 40, 40, false, 0x000000, 0xFFFFFF, "SE", false }
};

#define global_odom odom_display[2].state

//Variable Definitions
int red_screen_length = sizeof(red_screen)/sizeof(red_screen[0]);;
int main_menu_length = sizeof(main_menu)/sizeof(main_menu[0]);;
int auton_length = sizeof(auton)/sizeof(auton[0]);;
int odom_display_length = sizeof(odom_display)/sizeof(odom_display[0]);;
int compass_length = sizeof(compass)/sizeof(compass[0]);;
int motor_info_length = sizeof(motor_info_display)/sizeof(motor_info_display[0]);;
int art_display_length = sizeof(art_display)/sizeof(art_display[0]);;

int auton_selected = 1;
int global_angle_selected = 1; 

bool buttonSelected = false;
bool debugging = false;
bool global_setup = false;
bool motor_info = false;
bool art_info = false;

bool overheat = false;
int motorTemp [3][8];
int motor_temp_max = 40;

button* reference = main_menu;
int reference_length = main_menu_length;


//Create the main menu
void mainMenu(){
  bool too_hot_baby = false;
  for(int i=0; i<=7; i++){
    if(motorTemp[1][i]>motor_temp_max)
      too_hot_baby=true;
  }

  if(too_hot_baby){
    for(int i = 0; i < main_menu_length; i++) 
      main_menu[i].visible = false;
    
    for(int i = 0; i < red_screen_length; i++) 
      red_screen[i].visible = true;

    reference = red_screen;
    reference_length = red_screen_length;
  } 
  
  // enter auton_mode from main menu
  else if(main_menu[0].state == true){
    for(int i = 0; i < main_menu_length; i++) 
      main_menu[i].visible = false;
    
    for(int i = 0; i < auton_length; i++) 
      auton[i].visible = true;
    
    auton[auton_selected].state = true;
    reference = auton;
    reference_length = auton_length;
  }

  // enter debug_mode from main menu
  else if(main_menu[1].state == true){
    for(int i = 0; i < main_menu_length; i++) 
      main_menu[i].visible = false;

    for(int i = 0; i < odom_display_length; i++) 
      odom_display[i].visible = true;

    debugging = true;
    reference = odom_display;
    reference_length = odom_display_length;
  }
 
  // enter global_setup_mode from main menu
  else if(main_menu[2].state == true){
    for(int i = 0; i < main_menu_length; i++) 
      main_menu[i].visible = false;

    for(int i = 0; i < compass_length; i++) 
      compass[i].visible = true;

    compass[global_angle_selected].state = true;

    global_setup = true;
    reference = compass;
    reference_length = compass_length;
  }
  
  // enter motor_info from main menu
  else if(main_menu[3].state == true){
    for(int i = 0; i < main_menu_length; i++)
      main_menu[i].visible = false;

    for(int i = 0; i < compass_length; i++) 
      motor_info_display[i].visible = true;

    motor_info = true;
    reference = motor_info_display;
    reference_length = motor_info_length;
  }

  //enter art from main menu
  
  else if(main_menu[4].state == true){
    for(int i = 0; i < main_menu_length; i++)
      main_menu[i].visible = false;

    for(int i = 0; i < art_display_length; i++) 
      art_display[i].visible = true;

    art_info = true;
    reference = art_display;
    reference_length = art_display_length;
  }
  
  // go back to main menu
  else if(auton[0].state == true || odom_display[0].state == true || compass[0].state == true || motor_info_display[0].state == true || art_display[0].state == true){
    auton[0].state = false;
    odom_display[0].state = false;
    compass[0].state = false;
    motor_info_display[0].state = false;
    art_display[0].state = false;
    
    for(int i = 0; i < main_menu_length; i++) 
      main_menu[i].visible = true;

    debugging = false;
    global_setup = false;
    motor_info = false;
    art_info = false;

    reference = main_menu;
    reference_length = main_menu_length;
  }
}

//Create Buttons
void createButtons(){
  Brain.Screen.clearScreen();

  if(global_odom) odom_display[2].label = "Global";
  else odom_display[2].label = "Local";

  for(int i=0; i<reference_length; i++){
    if(reference[i].visible){

      //Brain.Screen.setFillColor(transparent);
      Brain.Screen.printAt(reference[i].xpos, reference[i].ypos - 5, false, (reference[i].label));

      //Create button fill
      if(reference[i].state == true){
        Brain.Screen.drawRectangle(reference[i].xpos, reference[i].ypos, reference[i].width, reference[i].height, reference[i].onColor);
      } else {
        Brain.Screen.drawRectangle(reference[i].xpos, reference[i].ypos, reference[i].width, reference[i].height, reference[i].offColor);
      }
    }
  }
}

//Get which button is pressed
int findButtonPressed(double x, double y){
  for (int i = 0; i < reference_length; i++){
    if(reference[i].visible){
      if(x>reference[i].xpos && x<reference[i].xpos + reference[i].width){
        if(y>reference[i].ypos && y<reference[i].ypos + reference[i].height){
          return i;
        }
      }
    }
  }
  return -1;
}

//Changes all button states to false
void resetAll(){
  for(int i = 0; i < main_menu_length; i++) 
      main_menu[i].state = false;

  for(int i = 0; i < auton_length; i++) 
      auton[i].state = false;

  for(int i = 0; i < odom_display_length-1; i++) 
      odom_display[i].state = false;

  for(int i = 0; i < compass_length; i++) 
      compass[i].state = false;

  for(int i = 0; i < motor_info_length; i++) 
      motor_info_display[i].state = false;

  for(int i = 0; i < art_display_length; i++)
    art_display[i].state = false;
}

//Detects which button is pressed and changes state
void selectButton(){
  double x = Brain.Screen.xPosition(), y = Brain.Screen.yPosition();
  int buttonNum = findButtonPressed(x,y);

  // odom global/local settings button (alternates between the two)
  if(reference == odom_display && buttonNum == 2)
    odom_display[2].state = !odom_display[2].state;

  // odom reset button
  else if(reference == odom_display && buttonNum == 1){
    global.pos_x = 0;
    global.pos_y = 0;
    global.theta = 90;
    Gyro.calibrate();
    while(Gyro.isCalibrating())wait(20);
    Gyro.setHeading(90,rotationUnits::deg);
  }

  else if(buttonNum >= 0){
    resetAll();
    reference[buttonNum].state = true;
  }

  // saving variables
  if(reference==auton && buttonNum>=1 && buttonNum<=8) 
    auton_selected=buttonNum;

  if(reference==compass && buttonNum>=1 && buttonNum<=8){ 
    string label = reference[buttonNum].label;
    global_angle_selected = buttonNum;

    int theta = (global_angle_selected-1)*45;
    global.theta = (theta>180)?(theta-360):theta;
  }
}

int counter = 0;

void autonDebugMenu(){
  if(motorTemp[0][0] + motorTemp[0][1] + 
     motorTemp[0][2] + motorTemp[0][3] > 0) {
    motor_info_display[1].offColor = 0xFF0000;
  } else motor_info_display[1].offColor = 0x000000;

  if(motorTemp[0][4] + motorTemp[0][5]  > 0) {
    motor_info_display[2].offColor = 0xFF0000;
  } else motor_info_display[1].offColor = 0x000000;

  if(motorTemp[0][6] + motorTemp[0][7] > 0) {
    motor_info_display[3].offColor = 0xFF0000;
  } else motor_info_display[1].offColor = 0x000000;


  if(motor_info_display[1].state == true) {
    Brain.Screen.printAt(25,150,("FL C: " + toString(motorTemp[1][0])).c_str());
    Brain.Screen.printAt(25,175,("FR C: " + toString(motorTemp[1][1])).c_str());
    Brain.Screen.printAt(25,200,("BL C: " + toString(motorTemp[1][2])).c_str());
    Brain.Screen.printAt(25,225,("BR C: " + toString(motorTemp[1][3])).c_str());
    Brain.Screen.printAt(125,150,("FL F: " + toString(motorTemp[2][0])).c_str());
    Brain.Screen.printAt(125,175,("FR F: " + toString(motorTemp[2][1])).c_str());
    Brain.Screen.printAt(125,200,("BL F: " + toString(motorTemp[2][2])).c_str());
    Brain.Screen.printAt(125,225,("BR F: " + toString(motorTemp[2][3])).c_str());
  }
  
  if(motor_info_display[2].state == true){
    Brain.Screen.printAt(25,150,("Intake Left C: " + toString(motorTemp[1][4])).c_str());
    Brain.Screen.printAt(25,175,("Intake Right C: " + toString(motorTemp[1][5])).c_str());
    Brain.Screen.printAt(25,200,("Intake Left F: " + toString(motorTemp[2][4])).c_str());
    Brain.Screen.printAt(25,225,("Intake Right F: " + toString(motorTemp[2][5])).c_str());
  }

  if(motor_info_display[3].state == true){
    Brain.Screen.printAt(25,150,("Shooter C: " + toString(motorTemp[1][6])).c_str());
    Brain.Screen.printAt(25,175,("Indexer C: " + toString(motorTemp[1][7])).c_str());
    Brain.Screen.printAt(25,200,("Shooter F: " + toString(motorTemp[2][6])).c_str());
    Brain.Screen.printAt(25,225,("Indexer F: " + toString(motorTemp[2][7])).c_str());
  }
  //Brain.Screen.printAt(25,25,("front left: " + toString(front_left.temperature(temperatureUnits::fahrenheit))).c_str());
  //Brain.Screen.printAt(25,47,("front right: " + toString(front_right.temperature(temperatureUnits::fahrenheit))).c_str());
  //Brain.Screen.printAt(25,69,("back left: " + toString(back_left.temperature(temperatureUnits::fahrenheit))).c_str());
  //Brain.Screen.printAt(25,91,("back right: " + toString(back_right.temperature(temperatureUnits::fahrenheit))).c_str());
}

void getMotorTemps(){
  motorTemp[1][0] = front_left.temperature(temperatureUnits::celsius);
  motorTemp[1][1] = front_right.temperature(temperatureUnits::celsius);
  motorTemp[1][2] = back_left.temperature(temperatureUnits::celsius);
  motorTemp[1][3] = front_right.temperature(temperatureUnits::celsius);
  motorTemp[1][4] = intake_left.temperature(temperatureUnits::celsius);
  motorTemp[1][5] = intake_right.temperature(temperatureUnits::celsius);
  motorTemp[1][6] = shooter.temperature(temperatureUnits::celsius);
  motorTemp[1][7] = indexer.temperature(temperatureUnits::celsius);
  
  motorTemp[2][0] = front_left.temperature(temperatureUnits::fahrenheit);
  motorTemp[2][1] = front_right.temperature(temperatureUnits::fahrenheit);
  motorTemp[2][2] = back_left.temperature(temperatureUnits::fahrenheit);
  motorTemp[2][3] = front_right.temperature(temperatureUnits::fahrenheit);
  motorTemp[2][4] = intake_left.temperature(temperatureUnits::fahrenheit);
  motorTemp[2][5] = intake_right.temperature(temperatureUnits::fahrenheit);
  motorTemp[2][6] = shooter.temperature(temperatureUnits::fahrenheit);
  motorTemp[2][7] = indexer.temperature(temperatureUnits::fahrenheit);
  //1 for overheating, 0 for not
  motorTemp[0][0] = motorTemp[1][0]/45;
  motorTemp[0][1] = motorTemp[1][1]/45;
  motorTemp[0][2] = motorTemp[1][2]/45;
  motorTemp[0][3] = motorTemp[1][3]/45;
  motorTemp[0][4] = motorTemp[1][4]/45;
  motorTemp[0][5] = motorTemp[1][5]/45;
  motorTemp[0][6] = motorTemp[1][6]/45;
  motorTemp[0][7] = motorTemp[1][7]/45;

  if(motorTemp[0][0] + motorTemp[0][1]
   + motorTemp[0][2] + motorTemp[0][3]
   + motorTemp[0][4] + motorTemp[0][5]
   + motorTemp[0][6] + motorTemp[0][6] > 0) overheat = true;
   else overheat = false;
}

void status(){
  if(overheat == true){
    Brain.Screen.drawRectangle(100, 0, 75, 20, 0xFF0000);
  }
}
  //if(brain::battery::capacity(percentUnits::pct	)

void art_showcase(){
  //Brain.Screen.printAt(25,150,(("Left Align (cm): " + toString(position_left.objectDistance(distanceUnits::cm))).c_str()));
  // Brain.Screen.printAt(25,175,(("Right Align (cm): " + toString(position_back.objectDistance(distanceUnits::cm))).c_str()));
  // Brain.Screen.printAt(25,200,(("Left Align (mm): " + toString(position_left.objectDistance(distanceUnits::mm))).c_str()));
  // Brain.Screen.printAt(25,225,(("Right Align (mm): " + toString(position_back.objectDistance(distanceUnits::mm))).c_str()));
  // Brain.Screen.drawRectangle(50, 50, 200, 200, 0xFF0000);
  // for(int i = 0; i < 20; i++){
  //   Brain.Screen.drawLine(50, 10 * i + 50, 10 * i + 50, 250);
  //   Brain.Screen.drawLine(250, 250 - 10 * i, 250 - 10 * i, 50);
  // }
  //Brain.Screen.drawLine(50, 50, 200, 200);
}


//Call in main
int drawButtons() {
  mainMenu();
  getMotorTemps();
  status();
  createButtons();
  if(debugging) {
    debugMode(global_odom);
  }
  if(global_setup) {
    globalPositioning();
  }
  if(motor_info){
    autonDebugMenu();
  }
  if(art_info){
    art_showcase();
  }
  Brain.Screen.pressed(selectButton);
  //return auton_selected;
  return 7;
}