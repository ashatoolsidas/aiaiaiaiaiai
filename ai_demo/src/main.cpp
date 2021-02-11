/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       james                                                     */
/*    Created:      Mon Aug 31 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Left1                motor         16              
// Left2                motor         18              
// Left3                motor         12              
// Right1               motor         15              
// Right2               motor         14              
// Right3               motor         4               
// Middle1              motor         20              
// Middle2              motor         13              
// Inertial             inertial      3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "PID.h"
#include <cmath>

#define PI 3.14159265

using namespace vex;
float x=1,y=1,heading=1;
double degr;
int lim; 
char dir;



// create instance of jetson class to receive location and other
// data from the Jetson nano
//
ai::jetson  jetson_comms;

/*----------------------------------------------------------------------------*/
// Create a robot_link on PORT1 using the unique name robot_32456_1
// The unique name should probably incorporate the team number
// and be at least 12 characters so as to generate a good hash
//
// The Demo is symetrical, we send the same data and display the same status on both
// manager and worker robots
// Comment out the following definition to build for the worker robot
#define  MANAGER_ROBOT    1

#if defined(MANAGER_ROBOT)
//#pragma message("building for the manager")
ai::robot_link       link( PORT21, "robot_32456_1", linkType::manager );
#else
//#pragma message("building for the worker")
ai::robot_link       link( PORT21, "robot_32456_1", linkType::worker );
#endif


void drive (int frwd, int turn) {
  Left1.spin(fwd, (frwd+turn)*0.3, rpm);
  Right1.spin(fwd,(frwd-turn)*0.3, rpm);
}

//spinny
void turn( double targ, PD pd ) {
  double speed;
  pd.reset( targ-heading );

  int count = 0;

  while( std::abs(targ - heading) > 0.1 ) {
    // hello robot buddy please do what i want u to do!
    link.get_local_location(x, y, heading);
    Brain.Screen.printAt(15,15,"h: %.2f",heading);

    if( pd.getKp() == 0 && pd.getKd() == 0 )
      speed = 30; // default - be careful
    else
      // literally dont know if d works but that's okay
      speed = -pd.speed(heading, targ, 200);

    //dont do stupid turns
    if(std::abs(targ-heading) > 180)
      speed *= -1;

    Left1.spin(fwd, speed, rpm);
    Right1.spin(fwd, -speed, rpm);

    count++;
    task::sleep(10);
    if(count > 300)
      break;
  }
  Left1.stop();
  Right1.stop();
}

// zoom zoom
void forwards(char coord, int lim, PD pd){
  double speed;

  if(coord == 'y') { //this is so jank but okay
    pd.reset( lim-y );
    while( std::abs(y - lim) > 50) {
      speed = pd.speed(y,lim,200);
      link.get_local_location(x, y, heading);
      Brain.Screen.printAt(15,15,"y=%.2f",y);
      Left1.spin(fwd, -speed, rpm);
      Right1.spin(fwd, -speed, rpm);
    }
  }else{
    pd.reset( lim-x );
    while( std::abs(x - lim) > 50)
      speed = pd.speed(x,lim,200);
      link.get_local_location(x, y, heading);
      Brain.Screen.printAt(15,15,"x=%.2f",x);
      Left1.spin(fwd, -speed, rpm);
      Right1.spin(fwd, -speed, rpm);
  }

  Left1.stop();
  Right1.stop();
};

int turnTask() {
  turn(degr,{20,0});
  return 0;
}

int forwardsTask() {
  forwards(dir,lim, {0.5,0});
  return 0;
}
/*----------------------------------------------------------------------------*/


competition Competition;

// define your global instances of motors and other devices here

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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void autonomous(void) {
  Left1.spin(fwd, 200, rpm);
  Right1.spin(fwd, -200, rpm);
}

void usercontrol(void) {

    Left1.spin(fwd, -200, rpm);
    Right1.spin(fwd, -200, rpm);
  
//     thread t1(dashboardTask);

//     lim = 700;
//     dir = 'y';
//     thread t2(forwardsTask);  
//     t2.join();

//     degr = PI/2;
//     thread t3(turnTask);
//     t3.join();

//     task::sleep(10000);
//     t2.interrupt();

//     lim = -700;
//     dir = 'x';
//     thread t4(forwardsTask);
//     t4.join();

//     degr = 0;
//     thread t5(turnTask);
//     t5.join();

//     dir = 'y';
//     thread t6(forwardsTask);
//     t6.join();
// //t5.interrupt();

}


int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    Inertial.calibrate();
    
        // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // local storage for latest data from the Jetson Nano
    static MAP_RECORD       local_map;

    // RUn at about 15Hz
    int32_t loop_time = 66;


    // start the status update display


    
    // print through the controller to the terminal (vexos 1.0.12 is needed)
    // As USB is tied up with Jetson communications we cannot use
    // printf for debug.  If the controller is connected
    // then this can be used as a direct connection to USB on the controller
    // when using VEXcode.
    //
    //FILE *fp = fopen("/dev/serial2","wb");
    
    while(1) {

      // int turn = (x-960)/3;
      // if(std::abs(960-x) < 20)
      //   turn = 0;

      // drive(-150,turn);


      // int leftspd = Controller.Axis3.value();
      // int rightspd = Controller.Axis2.value();

      // Left1.spin(fwd, leftspd, rpm);
      // Left2.spin(fwd, leftspd, rpm);
      // Left3.spin(fwd, leftspd, rpm);
      // Right1.spin(fwd,rightspd, rpm);
      // Right2.spin(fwd, rightspd, rpm);
      // Right3.spin(fwd, rightspd, rpm);
      

        //get last map data
        jetson_comms.get_data( &local_map );

        // set our location to be sent to partner robot
        link.set_remote_location( local_map.pos.x, local_map.pos.y, local_map.pos.az );

        //fprintf(fp, "%.2f %.2f %.2f\n", local_map.pos.x, local_map.pos.y, local_map.pos.az  );

        // request new data        
        jetson_comms.request_map();

        // Allow other tasks to run
        this_thread::sleep_for(loop_time);
    }
}