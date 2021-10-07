#include "odom_display.h"

double border_align_distance = 100;

void calculate_angle(double forward_angle=0){
  double count=200;
  double total=0;

  for(int i=0; i<count; i++){
    double final_angle = forward_angle + (atan2((backward_wall_align.value()-forward_wall_align.value()), border_align_distance) * 180/PI);
    total+=final_angle;
    wait(5);
  }

  total/=count;
  cout<<total<<endl;
}