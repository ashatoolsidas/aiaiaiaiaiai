#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "odom.h"

class Drivetrain{
public:
  void move( double frwd, double side, double turn );
  void stop();
  void moveTo( double x, double y, double heading );
  void moveTo_rel( double x, double y, double heading=odom::th );
  void toGoal(int goal);
  void findBall(int id);
};

extern Drivetrain xdrive;

#endif