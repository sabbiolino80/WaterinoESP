//#include <Stepper.h>

#ifndef SimpleStepper_h
#define SimpleStepper_h

#include "Arduino.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
// Target RPM for X axis motor
#define MOTOR_X_RPM 30
// Target RPM for Y axis motor
#define MOTOR_Y_RPM 90

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 1


class SimpleStepper
{
  public:
    SimpleStepper();
    //~SimpleStepper();
    void setup();
    void loop();
  private:
    BasicStepperDriver *_stepperH;
    BasicStepperDriver *_stepperV;
    SyncDriver *_controller;
};


#endif
