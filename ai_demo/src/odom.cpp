#include "vex.h"
#include "odom.h"

#define sL 0.85
#define sR 0.85
#define sB 6.5

#define IN_CONVERT 0.001

namespace odom  {

double x,y,th;

int track () {
  LeftEnc.resetRotation();
  RightEnc.resetRotation();
  BackEnc.resetRotation();

  double L=0,R=0,B=0,
         prevL=0,prevR=0,prevB=0,prevRad=0,
         dL,dR,dB,rad,
         dRad, rotations=0;

  while(true) {
    // current encoder values in inches
    L = LeftEnc.rotation(deg)  * IN_CONVERT;
    R = RightEnc.rotation(deg) * IN_CONVERT;
    B = BackEnc.rotation(deg)  * IN_CONVERT;

    // change in encoder values
    dL = L - prevL;
    dR = R - prevR;
    dB = B - prevB;

    // angle stuff
    //rad = (R-L) / (sR+sL); 
    rad = (360 - Inertial.heading()) * M_PI / 180;
    dRad = rad - prevRad;
    prevRad = rad;

    if(dRad < -1)
      rotations++;
    else if(dRad > 1)
      rotations--;


    // local coords
    // dX_l = 2 * sin(rad/2) * (dB/dRad + sB);
    // dY_l = 2 * sin(rad/2) * (dR/dRad + sR);

    // mapping and adding stuff
    odom::x += (dB * cos(rad) - dR * sin(rad));
		odom::y += (dB * sin(rad) + dR * cos(rad));
    odom::th = (rotations*360) + (360 - Inertial.heading());

    // seting prev values
    prevL = L;
    prevR = R;
    prevB = B;

    // printing woop
    Brain.Screen.printAt(15, 15, "X: %.2f", odom::x);
    Brain.Screen.printAt(15, 30, "Y: %.2f", odom::y);
    Brain.Screen.printAt(15, 45, "heading: %f", odom::th);

    // Brain.Screen.printAt(15, 75, "L: %.2f", LeftEnc.rotation(deg));
    // Brain.Screen.printAt(15, 90, "R: %.2f", RightEnc.rotation(deg));
    // Brain.Screen.printAt(15, 105, "B: %.2f", BackEnc.rotation(deg));
    Brain.Screen.printAt(15, 75, "L: %.2f", L);
    Brain.Screen.printAt(15, 90, "R: %.2f", R);
    Brain.Screen.printAt(15, 105, "B: %.2f", B);

    wait(10,msec);
    Brain.Screen.clearScreen();
  }

  return 0;
}

void setPos(double x, double y, double th) {
  odom::x = x;
  odom::y = y;
  odom::th = th;
}

};