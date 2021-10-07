#include "odom.h"

vex::color rectangleColor = 0xDDDDDD;
vex::color outlineColor = 0xFFFFFF;

double x_Display = 0;
double y_Display = 0;
double theta_Display = 0;

bool global_positioning = false;

void drawField(){
  for (int i=0; i<6; i++) {
    for (int j=0; j<6; j++){
      Brain.Screen.setPenColor(outlineColor);
      Brain.Screen.drawRectangle(30*i+255, 30*j+30, 30, 30, rectangleColor);
    }
  }
  Brain.Screen.printAt(210, 230, ("(0,0)"));
  Brain.Screen.printAt(325, 25, ("wall"));
  Brain.Screen.printAt(210, 122, ("blue"));
  Brain.Screen.printAt(440, 122, ("red"));
}

void updateTouch(){
  double x = Brain.Screen.xPosition(), y = Brain.Screen.yPosition();
  double min_magnitude = INT8_MAX;
  int point = 0;
  if(x > 250){
    for (int i=0; i<5; i++) {
      for (int j=0; j<5; j++){
        int x_value = 30*i+285-x;
        int y_value = 30*j+60-y;
        double magnitude = sqrt(x_value*x_value+y_value*y_value);
        if(magnitude < min_magnitude){
          min_magnitude = magnitude;
          point = 5*i+j;
        }
      }
    }
    Brain.Screen.drawRectangle(30*floor(point/5)+285-5, 30*(point%5)+60-5, 10, 10, color::black);
    global.pos_x = 24*floor(point/5)+24;
    global.pos_y = 24*(4-(point%5))+24;
  }
}

void displayOdomInfo(bool global_odom){
  double pos_x = (global_odom) ? global.pos_x : global.pos_x;
  double pos_y = (global_odom) ? global.pos_y : global.pos_y;
  double theta = (global_odom) ? global.theta : global.theta;

  Brain.Screen.printAt(25,25,("left: " + toString(get_left)).c_str());
  Brain.Screen.printAt(25,47,("right: " + toString(get_right)).c_str());
  Brain.Screen.printAt(25,69,("back: " + toString(get_back)).c_str());
  Brain.Screen.printAt(25,91,("posX: " + toString(1000*pos_x)).c_str());
  Brain.Screen.printAt(25,113,("posY: " + toString(1000*pos_y)).c_str());
  Brain.Screen.printAt(25,135,("theta: " + toString(1000*theta)).c_str());
}

void updateRobotPosition(){
  x_Display = global.pos_x;
  y_Display = global.pos_y;
  theta_Display = global.theta;
  
  x_Display = x_Display * 30.0/24.0 + 255;
  y_Display = 210 - (y_Display * 30.0/24.0);

  Brain.Screen.drawCircle(x_Display, y_Display, 3, vex::color::black);

  Brain.Screen.setPenColor(vex::color::black);
  Brain.Screen.drawLine(x_Display, y_Display, x_Display + 15 * cos(theta_Display*PI/180), y_Display - 15 * sin(theta_Display*PI/180));
  //Brain.Screen.drawLine(x_Display + 15 * cos(theta_Display*PI/180), y_Display - 15 * sin(theta_Display*PI/180), x_Display + 15 * cos(theta_Display*PI/180) + , y_Display - 15 * sin(theta_Display*PI/180));

  Brain.Screen.setPenColor(outlineColor);
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
        x_Display = 82.5 * i + 262.5; 
        y_Display = 202.5 - 82.5 * j;
        Brain.Screen.drawCircle(x_Display, y_Display, 7.5, vex::color::black);
    }
  }
}

void debugMode(bool global_odom){
  displayOdomInfo(global_odom);
  if(global_odom){
    drawField();
    updateRobotPosition();
  }
}

void globalPositioning(){
  drawField();
  updateTouch();
}