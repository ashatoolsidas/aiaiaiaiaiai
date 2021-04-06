#ifndef ODOM_H
#define ODOM_H

namespace odom {
  extern double x,y,th;
  int track();
  void setPos(double x, double y, double th);
}

#endif