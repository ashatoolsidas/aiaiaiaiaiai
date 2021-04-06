#ifndef CONFIG_H
#define CONFIG_H

using namespace vex;

extern brain    Brain;
extern motor    FrontLeft;
extern motor    FrontRight;
extern motor    BackLeft;
extern motor    BackRight;
extern motor    LowerIndexer;
extern motor    UpperIndexer;
extern motor    Launcher;
extern motor    LeftIntake;
extern motor    RightIntake;

extern encoder  LeftEnc;
extern encoder  RightEnc;
extern encoder  BackEnc;
extern inertial Inertial;

extern triport Expander;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);

#endif