#include "intakes.h"
#include "vex.h"

void Intakes::run(int speed) {
  LeftIntake.spin(fwd, speed, pct);
  RightIntake.spin(fwd, speed, pct);
}

Intakes intakes;