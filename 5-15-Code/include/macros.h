#include "vex.h"
using namespace std;
using namespace vex;

//Macros to make code simpler to read
#define spin(a,b) a.spin(directionType::fwd,b,velocityUnits::pct)
#define clear(a) a.resetRotation();
#define stop(a) a.stop(brakeType::brake)
#define wait(x) task::sleep(x)
#define press(x) ct.x.pressing() // hold
#define press2(x) pt.x.pressing() // hold
#define release(x,y) ct.x.released(y) // one press
#define release2(x,y) pt.x.released(y) // one press
#define MIN(a,b) ((a)<(b))?(a):(b)
#define MAX(a,b) ((a)>(b))?(a):(b)
#define hold(a) a.setStopping(brakeType::hold)
#define coast(a) a.setStopping(brakeType::coast) 
#define brake(a) a.setStopping(brakeType::brake)

//Macros for indexer sensing
#define triggered(a) a.value()<100;
#define b1_triggered (base_one.value()<100 && base_one.value()!=0);
#define b2_triggered base_two.value()<20; 
#define b3_triggered base_three.value()<100;
#define b4_triggered base_four.value()<100;

//Macros for mathematical operations
#define PI 3.1415926536
#define signum(num) ((num>0)-(num<0)) // returns -1, 1 based on signage 

//PID Constants
#define kp 0.12 // 0.115, 0.075 | 0.085 
#define kd 0.3 //0.8
#define ki 0
#define kpT 0.85 // 0.3, 1,2 | 0.31, 0.1 // 2
#define kdT 0
#define kiT 0
#define kc 0.13

// 0.097, 0.2, 0.005
//.1, 0.3, 0.007 - short turns
//.13, 0, 0.01

// current: 0.1, 0.5, 0.015
// new: 0.1, 0.5, 0.02

// 24 inches - 0.079, 0.013 (worked rlly well)

// .12, 0.001
// .15, 0.002
// .145 0.002

// 0.07, 0.115, 0.08, 0.097 - 48 inches
// 0.5
//0.014 // 0.002, 0.015
// 0.8, 0.85

//Converts int to string
string toString(int x){
  ostringstream ss;
  ss << x;
  return ss.str();
}

/* kp, kpT pairs for old robot */
// 0.25, 1.5
// 0.3, 1.5 --> most tolerance (best for 1 tile+ movements)