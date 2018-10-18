#ifndef SerialLog_h
#define SerialLog_h

#define STX 2
#define ETX 3

#define CMD_JOG_UP      10
// param 0-1
#define CMD_JOG_DOWN    11
// param 0-1
#define CMD_JOG_LEFT    12
// param 0-1
#define CMD_JOG_RIGHT   13
// param 0-1
#define CMD_VALVE_ON    14
// param 0-1
#define CMD_STOP        15
//no param
#define CMD_SET_SPEED   24
// param x speed y speed
#define CMD_GOTO        16
//param x target, y target
#define CMD_GET_POS     20
#define CMD_GET_STATUS  21
#define CMD_LED_ON      22
//no param
#define CMD_LED_OFF     23
//no param

#define BUFF_SIZE 256

#include "Arduino.h"

class Protocol
{
  public:
    Protocol();
    //~Protocol();
    bool GetNextCommand();
    void PushChar(uint8_t);
  private:
    uint8_t w_index = 0; // next write index
    uint8_t r_index = 0; // next read index
    uint8_t buffer[BUFF_SIZE];
    
};

extern bool jogUp, jogDown, jogLeft, jogRight;

#endif
