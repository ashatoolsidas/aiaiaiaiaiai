#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
controller Controller;

// VEXcode device constructors
motor Left1 = motor(PORT16, ratio18_1, true);
motor Left2 = motor(PORT18, ratio18_1, false);
motor Left3 = motor(PORT12, ratio18_1, true);
motor Right1 = motor(PORT13, ratio18_1, false);
motor Right2 = motor(PORT14, ratio18_1, false);
motor Right3 = motor(PORT4, ratio18_1, false);
motor Middle1 = motor(PORT20, ratio18_1, false);
//motor Middle2 = motor(PORT13, ratio18_1, false);
inertial Inertial = inertial(PORT3);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}