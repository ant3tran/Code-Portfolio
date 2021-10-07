//BAD PORTS: 5, 6, 13
using namespace vex;
using signature = vision::signature;
using code = vision::code;
vex::inertial Gyro(vex::PORT2);
brain Brain;
motor front_right = motor(PORT7);
motor front_left = motor(PORT2,true);
motor back_right = motor(PORT8,true); 
motor back_left = motor(PORT3);

motor shooter = motor(PORT4);
motor indexer = motor(PORT21, true);

motor intake_left = motor(PORT1, true);
motor intake_right = motor(PORT9);

encoder L_ODOM = encoder(Brain.ThreeWirePort.C);
encoder R_ODOM = encoder(Brain.ThreeWirePort.A);
encoder B_ODOM = encoder(Brain.ThreeWirePort.E);

// vex::distance base_one = vex::distance(PORT12);
// vex::distance base_two = vex::distance(PORT4);
vex::distance intaking_sensor = vex::distance(PORT19);
vex::distance shooting_sensor = vex::distance(PORT11);//17
vex::distance bottom_indexer = vex::distance(PORT15); //15 - bad port
vex::distance upper_indexer = vex::distance(PORT20);

vex::distance forward_wall_align = vex::distance(PORT22);
vex::distance backward_wall_align = vex::distance(PORT7);

rotation odom_l = rotation(PORT6, true);
rotation odom_b = rotation(PORT16);
rotation odom_r = rotation(PORT10);
//optical color_detector = optical(PORT6);

controller ct = controller();
controller pt = controller(controllerType::partner);

//motor indexer = motor(PORT5, vex::gearSetting::ratio6_1);
//motor sorter = motor(PORT11, vex::gearSetting::ratio6_1); //4
//triport EXPANDA = triport(PORT8);
//pot pot_left = pot(Brain.ThreeWirePort.G);
// pot pot_right = pot(Brain.ThreeWirePort.H);
// line I = line(EXPANDA.A);
// line M  = line(EXPANDA.A);
// line B = line(EXPANDA.A);
//optical opt_sense = optical(PORT3);