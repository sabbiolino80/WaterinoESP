
#include <dummy.h>
#include "Definitions.h"
#include "ManualControls.h"

// SKETCH CONFIGURATION
//#define log_touch_levels
//#define log_touch_commands
#define step_delay 5

//#define touch4          13
//#define touch5          12
//#define touch6          14
//#define touch7          27
//#define touch8          33
//#define touch9          32


ManualControls::ManualControls()
{

}


void ManualControls::setup()
{
  //  pinMode(touch4, INPUT);
  //  pinMode(touch5, INPUT);
  //  pinMode(touch6, INPUT);
  //  pinMode(touch7, INPUT);
  //  pinMode(touch8, INPUT);
  //  pinMode(touch9, INPUT);

  //int threshold = 40;
  //touchAttachInterrupt(T0, gotTouch, threshold);
  //void gotTouch(){
  //Serial.println("Touched\n");
  //}


}


void ManualControls::loop()
{
  for (_i = 4; _i < 10; _i++)
  {
    _touchValues[_i] = touchRead(_touchPins[_i]);
#ifdef log_touch_levels
    String log = String("T" + String(_i) + " " + String(_touchValues[_i]) + " - ");
    Serial.println(log);
    //      Serial.print("T");
    //      Serial.print(_i);
    //      Serial.print(" ");
    //      Serial.print(_touchValues[_i]);
    //      Serial.print(" - ");
#endif
  }
  //Serial.println();
  //  t4 = touchRead(T4);
  //  t5 = touchRead(T5);
  //  t6 = touchRead(T6);
  //  t7 = touchRead(T7);
  //  t8 = touchRead(T8);
  //  t9 = touchRead(T9);
  //#ifdef log_touch_levels
  //  Serial.print("T4 ");
  //  Serial.print(t4);
  //  Serial.print(" - T5 ");
  //  Serial.print(t5);
  //  Serial.print(" - T6 ");
  //  Serial.print(t6);
  //  Serial.print(" - T7 ");
  //  Serial.print(t7);
  //  Serial.print(" - T8 ");
  //  Serial.print(t8);
  //  Serial.println(t9);
  //  Serial.print(" - T9 ");
  //#endif


  if (_touchValues[4] < 20 || jogLeft)
  {
    if (_touchCounters[4] > 10 || jogLeft)
    {
      digitalWrite(stepper1_dir, HIGH);
      digitalWrite(stepper1_step, HIGH);
      delay(step_delay);
      digitalWrite(stepper1_step, LOW );
      delay(step_delay);
#ifdef log_touch_commands
      Serial.print("left ");
      Serial.println(_touchValues[4]);
#endif
    }
    else
      _touchCounters[4]++;
  }
  else
    _touchCounters[4] = 0;

  if (_touchValues[5] < 20 || jogRight)
  {
    if (_touchCounters[5] > 10 || jogRight)
    {
      digitalWrite(stepper1_dir, LOW);
      digitalWrite(stepper1_step, HIGH);
      delay(step_delay);
      digitalWrite(stepper1_step, LOW );
      delay(step_delay);
#ifdef log_touch_commands
      Serial.print("right ");
      Serial.println(_touchValues[5]);
#endif
    }
    else
      _touchCounters[5]++;
  }
  else
    _touchCounters[5] = 0;

  if (_touchValues[6] < 20 || jogUp)
  {
    if (_touchCounters[6] > 10 || jogUp)
    {
      digitalWrite(stepper2_dir, HIGH);
      digitalWrite(stepper2_step, HIGH);
      delay(step_delay);
      digitalWrite(stepper2_step, LOW );
      delay(step_delay);
#ifdef log_touch_commands
      Serial.print("up ");
      Serial.println(_touchValues[6]);
#endif
    }
    else
      _touchCounters[6]++;
  }
  else
    _touchCounters[6] = 0;

  if (_touchValues[7] < 20 || jogDown)
  {
    if (_touchCounters[7] > 10 || jogDown)
    {
      digitalWrite(stepper2_dir, LOW);
      digitalWrite(stepper2_step, HIGH);
      delay(step_delay);
      digitalWrite(stepper2_step, LOW );
      delay(step_delay);
#ifdef log_touch_commands
      Serial.print("down ");
      Serial.println(_touchValues[7]);
#endif
    }
    else
      _touchCounters[7]++;
  }
  else
    _touchCounters[7] = 0;

  if (_touchValues[9] < 20)
  {
    if (_touchCounters[9] > 10)
    {
      digitalWrite(ev_out, HIGH);
#ifdef log_touch_commands
      Serial.print("valve on ");
      Serial.println(_touchValues[9]);
#endif
      digitalWrite(stepper1_sleep, HIGH);
    }
    else
      _touchCounters[9]++;
  }
  else
    _touchCounters[9] = 0;

  if (_touchValues[8] < 20)
  {
    if (_touchCounters[8] > 10)
    {
      digitalWrite(ev_out, LOW);
#ifdef log_touch_commands
      Serial.print("valve off ");
      Serial.println(_touchValues[8]);
#endif
      digitalWrite(stepper1_sleep, LOW);
    }
    else
      _touchCounters[8]++;
  }
  else
    _touchCounters[8] = 0;
}
