#include "drivetrain.h"
#include "intakes.h"
#include "vex.h"
#include "odom.h"
#include <cmath>

void Drivetrain::move( double frwd, double side, double turn ) {
  int mult = 0;
  while ( std::abs(frwd +side +turn) * mult < 100 &&
          std::abs(frwd -side -turn) * mult < 100 &&
          std::abs(frwd -side +turn) * mult < 100 &&
          std::abs(frwd +side -turn) * mult < 100) {
    mult ++;
  }
  FrontLeft.spin  ( fwd, (frwd +side +turn) * mult, pct );
  FrontRight.spin ( fwd, (frwd -side -turn) * mult, pct );
  BackLeft.spin   ( fwd, (frwd -side +turn) * mult, pct );
  BackRight.spin  ( fwd, (frwd +side -turn) * mult, pct );
}

void Drivetrain::stop() {
  FrontLeft.stop();
  FrontRight.stop();
  BackLeft.stop();
  BackRight.stop();
}

void Drivetrain::moveTo(double x, double y, double heading) {
  double dx,dy,dth;
  while( std::abs(x-odom::x) > 0.05 || std::abs(y-odom::y) > 0.05 || std::abs(heading-odom::th) > 1 ) {
    double rad = Inertial.heading() * M_PI / 180;
    dx = (x-odom::x) * cos(rad) - (y-odom::y) * sin(rad);
	  dy = (x-odom::x) * sin(rad) + (y-odom::y) * cos(rad);
    dth = odom::th - heading;

    Brain.Screen.printAt(15,135,"dx:%.2f", dx);
    Brain.Screen.printAt(15,150,"dy:%.2f", dy);
    Brain.Screen.printAt(15,165,"dh:%.2f", dth);
    Brain.Screen.printAt(15,180,"rad:%.2f", rad);

    move(dy,dx,dth*0.01);
  } 
  stop();
}

void Drivetrain::moveTo_rel(double dx, double dy, double th) {
  double x = (dx * cos(-th) - dy * sin(-th)) + odom::x,
	       y = (dx * sin(-th) + dy * cos(-th)) + odom::y;
  
  moveTo(x,y,th);
}

void Drivetrain::toGoal(int goal) {
  
}

void Drivetrain::findBall(int id) { // 0=red, 1=blue, 2=goal
  intakes.run(100);
  for(fifo_object_box obj : local_map.boxobj) {
    if(obj.classID == id) {
      double ball_x = (obj.x-150) / 100,
             ball_y = (obj.y-70) / 20; 
      
      moveTo(ball_x,ball_y,0);
      break;
    }
  }
}

Drivetrain xdrive;