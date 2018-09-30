#include <cstdint>
#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
#include "Protocol.h"
#include "Definitions.h"

Protocol::Protocol()
{

}

bool Protocol::GetNextCommand()
{
  uint8_t start_idx, end_idx, msg_len;
  bool ok = false;
  if (w_index == r_index)
    return false;

  // search message start
  if (w_index < r_index)
  {
    // wrap around buffer end
    for (uint8_t i = r_index; i < BUFF_SIZE; i++)
    {
      if (buffer[i] == STX)
      { start_idx = i;
        ok = true;
        break;
      }
    }
    if (!ok)
      for (uint8_t i = 0; i < w_index; i++)
      {
        if (buffer[i] == STX)
        { start_idx = i;
          ok = true;
          break;
        }
      }
  }
  else
  {
    for (uint8_t i = r_index; i < w_index; i++)
    {
      if (buffer[i] == STX)
      { start_idx = i;
        ok = true;
        break;
      }
    }
  }
  //TODO start_idx should be = r_index
  if (!ok) return false;

  // get message length
  msg_len = buffer[(start_idx + 1) % BUFF_SIZE];
  end_idx = (start_idx + msg_len + 2) % BUFF_SIZE;


  //  uint8_t* msg = (uint8_t*)malloc(msg_len);
  //  if ((start_idx + msg_len + 2) >= BUFF_SIZE)
  //  {
  //    uint8_t first = BUFF_SIZE - start_idx - 2;
  //    memcpy(msg, buffer + start_idx + 2, first);
  //    memcpy(msg + first, buffer, msg_len - first);
  //  }
  //  else
  //  {
  //    memcpy(msg, buffer + start_idx + 2, msg_len);
  //  }
  //  Serial.println(msg);
  //  free(msg);

  uint8_t len = msg_len;
  while (len)
  {
    Serial.print(buffer[(start_idx + 2 + msg_len - len) % BUFF_SIZE]);
    len--;
  }
  Serial.println();

  if (buffer[end_idx] != ETX)
  {
    return false;
  }

  // MESSAGE PARSING
  switch (buffer[(start_idx + 2) % BUFF_SIZE])
  {
    case CMD_JOG_UP:
      if (buffer[(start_idx + 3) % BUFF_SIZE])
        {
          jogUp = true;
          Serial.println("JOG UP ON");
        }
      else
        {
          jogUp = false;
          Serial.println("JOG UP OFF");
        }
      break;

    case CMD_JOG_DOWN:
      if (buffer[(start_idx + 3) % BUFF_SIZE])
        {
          jogDown = true;
          Serial.println("JOG UP ON");
        }
      else
        {
          jogDown = false;
          Serial.println("JOG UP OFF");
        }
      break;

    case CMD_JOG_LEFT:
      if (buffer[(start_idx + 3) % BUFF_SIZE])
        {
          jogLeft = true;
          Serial.println("JOG UP ON");
        }
      else
        {
          jogLeft = false;
          Serial.println("JOG UP OFF");
        }
      break;

    case CMD_JOG_RIGHT:
      if (buffer[(start_idx + 3) % BUFF_SIZE])
        {
          jogRight = true;
          Serial.println("JOG UP ON");
        }
      else
        {
          jogRight = false;
          Serial.println("JOG UP OFF");
        }
      break;

    case CMD_STOP:
        jogRight = false;
        jogLeft = false;
        jogDown = false;
        jogUp = false;
      break;

    case CMD_SET_SPEED:

      break;

    case CMD_GOTO:

      break;

    case CMD_LED_ON:
      Serial.println("LED ON");
      digitalWrite(led, HIGH);
      break;

    case CMD_LED_OFF:
      Serial.println("LED OFF");
      digitalWrite(led, LOW);
      break;

    case CMD_VALVE_ON:
      if (buffer[(start_idx + 3) % BUFF_SIZE])
        {
          digitalWrite(ev_out, HIGH);
          Serial.println("VALVE ON");
        }
      else
        {
          digitalWrite(ev_out, LOW);
          Serial.println("VALVE OFF");
        }
      break;

    case CMD_GET_POS:

      break;

    case CMD_GET_STATUS:

      break;
  }



  r_index = (end_idx + 1) % BUFF_SIZE;

  return true;
}

void Protocol::PushChar(uint8_t charin)
{
  if ((w_index + 1 ) % BUFF_SIZE == r_index)
    return;//buffer full!!!
  buffer[w_index] = charin;
  w_index = (w_index + 1 ) % BUFF_SIZE;
}
