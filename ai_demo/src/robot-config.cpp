#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain    Brain;
motor    FrontLeft     (PORT19, true);
motor    FrontRight    (PORT17);
motor    BackLeft      (PORT20, true);
motor    BackRight     (PORT18);
motor    LowerIndexer  (PORT11);
motor    UpperIndexer  (PORT1);
motor    Launcher      (PORT9);
motor    LeftIntake    (PORT12);
motor    RightIntake   (PORT13);

triport  Expander      (PORT16);
encoder  LeftEnc       (Expander.G);
encoder  RightEnc      (Expander.C);
encoder  BackEnc       (Expander.A);
inertial Inertial      (PORT5);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}