/*
   Multi-motor control (experimental)

   Move two or three motors at the same time.
   This module is still work in progress and may not work well or at all.

   Copyright (C)2017 Laurentiu Badea

   This file may be redistributed under the terms of the MIT license.
   A copy of this license has been included with this distribution in the file LICENSE.
*/

#ifdef FALSE

#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#include "SimpleStepper.h"
#include "Definitions.h"




SimpleStepper::SimpleStepper()
{
  // 2-wire basic config, microstepping is hardwired on the driver
  // Other drivers can be mixed and matched but must be configured individually
  BasicStepperDriver stepperH((short)MOTOR_STEPS, (short)stepper1_dir, (short)stepper1_step);
  BasicStepperDriver stepperV((short)MOTOR_STEPS, (short)stepper2_dir, (short)stepper2_step);

  _stepperH = &stepperH;
  _stepperV = &stepperV;

  // Pick one of the two controllers below
  // each motor moves independently, trajectory is a hockey stick
  // MultiDriver controller(stepperX, stepperY);
  // OR
  // synchronized move, trajectory is a straight line
  SyncDriver controller(stepperH, stepperV);
  _controller = &controller;
}


void SimpleStepper::setup() {
  /*
     Set target motors RPM.
  */
  _stepperH->begin(MOTOR_X_RPM, MICROSTEPS);
  _stepperV->begin(MOTOR_Y_RPM, MICROSTEPS);
}

void SimpleStepper::loop() {

  while(_controller->nextAction() > 0);

  _controller->rotate(90 * 5, 60 * 15);
  delay(1000);
  _controller->rotate(-90 * 5, -30 * 15);
  delay(1000);
  _controller->rotate(0, -30 * 15);
  delay(30000);
}

#endif
