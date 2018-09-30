#ifndef ManualControl_h
#define ManualControls_h

#include "Arduino.h"

class ManualControls
{
  public:
    ManualControls();
    //~ManualControls();
    void setup();
    void loop();
  private:
    unsigned char _touchPins[10] = {T0, T1, T2, T3, T4, T5, T6, T7, T8, T9};
    unsigned char _touchValues[10];//_t4, _t5, _t6, _t7, _t8, _t9;
    unsigned char _touchCounters[10];//_cnt_t4, _cnt_t5, _cnt_t6, _cnt_t7, _cnt_t8, _cnt_t9;
    unsigned char _i;
    
};

extern bool jogUp, jogDown, jogLeft, jogRight;


#endif
