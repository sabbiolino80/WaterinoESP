/*
  ex stepperwebserver
  #ESP32 Web Server with graphic buttons downloaded from web cache
  Gareth aka chiprobot 21/3/2016

  ex serialtoserialbt
  //This example creates a bridge between Serial and Classical Bluetooth (SPP)
  //and also demonstrate that SerialBT have the same functionalities of a normal Serial
*/
#include "WConfig.h"
#ifdef WIFI_EN
#include <WiFi.h>
#endif
#ifdef BLUETOOTH_EN
#include "BluetoothSerial.h"
#endif
#include "ManualControls.h"
#include "Definitions.h"
#include "WProtocol.h"
#include "grbl.h"


#ifdef BLUETOOTH_EN
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#endif

int         step_delay   = 5; // stepper delay
#ifdef WIFI_EN
const char* ssid      = "BARALDI_EXT";
const char* password  = "ambarabaciccicocco";
WiFiServer server(80);
#endif

#ifdef BLUETOOTH_EN
BluetoothSerial SerialBT;
Protocol parserBT;
bool newData = false;
#endif

ManualControls manuals;

bool jogUp, jogDown, jogLeft, jogRight;


void setup()
{
  Serial.begin(115200);
  #ifdef BLUETOOTH_EN
  SerialBT.begin("Waterino"); //Bluetooth device name
  #endif

  // PIN MODES
  pinMode(stepper1_sleep, OUTPUT);      // set Stepper direction pin mode
  pinMode(stepper1_step, OUTPUT);      // set Stepper1 pin mode
  pinMode(stepper1_dir, OUTPUT);      // set Stepper2 pin mode
  pinMode(stepper2_step, OUTPUT);      // set Stepper3 pin mode
  pinMode(stepper2_dir, OUTPUT);
  pinMode(ev_out, OUTPUT);
  pinMode(home_top, INPUT_PULLUP);
  pinMode(home_bottom, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  //digitalWrite(led, HIGH);

  Serial.println("The device started, now you can pair it with bluetooth!");
#ifdef WIFI_EN
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Place this IP address into a browser window");
  server.begin();
#endif

  manuals.setup();
}



void loop() {

  /* MANUAL CONTROLS */
  manuals.loop();




  /* BLUETOOTH CONTROLS */

#ifdef BLUETOOTH_EN
  //  SerialBT.write(Serial.read());

  while (SerialBT.available()) {
    newData = true;
    //Serial.println("BT data received");
    parserBT.PushChar(SerialBT.read());
  }

  if (newData)
  {
    newData = false;
    parserBT.GetNextCommand();
  }

#endif





#ifdef WIFI_EN
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {
    //Serial.println("new client");

    String currentLine = "";                   // make a String to hold incoming data from the client
    while (client.connected()) {
      if (client.available()) {                // if there's client data

        char c = client.read();                // read a byte
        if (c == '\n') {                     // check for newline character,
          if (currentLine.length() == 0) {     // if line is blank it means its the end of the client HTTP request
            client.println("<!DOCTYPE html>"); // open wrap the web page
            client.print("<html><head><meta name='viewport' content='initial-scale=1.0'><meta charset='utf-8'><style>#map {height: 100%;}html, body {height: 100%;margin: 0;padding: 0;}</style></head>");
            client.print("<body><h1>ESP32 WebServer Stepper Motor's</h1>");
            // Gui buttons start here
            client.print("<input type=image style=width:33%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonBlueLong.png'onmousedown=location.href='/dec1' >");
            client.print("<input type=image style=width:33%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/nixiesmall1.png'>");
            client.print("<input type=image style=width:33%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonOrangeLong.png'onmousedown=location.href='/inc1' >");

            client.print("<input type=image style=width:33%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonPinkLong.png'onmousedown=location.href='/dec2' >");
            client.print("<input type=image style=width:33%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/nixiesmall2.png'>");
            client.print("<input type=image style=width:33%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonGreenLong.png'onmousedown=location.href='/inc2' >");

            //client.print("<input type=image style=width:33%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonTurqLong.png'onmousedown=location.href='/dec3' >");
            //client.print("<input type=image style=width:33%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/nixiesmall3.png'>");
            //client.print("<input type=image style=width:33%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonPurpleLong.png'onmousedown=location.href='/inc3' >");

            client.print("<input type=image style=width:100%;height:20% src='http://myrobotlab.org/sites/default/files/users/user25images/ButtonRedLong.png'onmousedown=location.href='/stopall' >");
            client.print("</body></html>"); // close wrap the web page

            client.println(); // The HTTP response ends with an extra blank line:

            break;  // break out of the while loop:
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;       // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /dec1")) {
          digitalWrite(stepper1_dir, HIGH);
          for (int i = 0; i <= 200; i++) {
            digitalWrite(stepper1_step, HIGH);
            delay(step_delay);
            digitalWrite(stepper1_step, LOW );
            delay(step_delay);
          }
        }
        if (currentLine.endsWith("GET /inc1")) {
          digitalWrite(stepper1_dir, LOW);
          for (int i = 0; i <= 200; i++) {
            digitalWrite(stepper1_step, HIGH);
            delay(step_delay);
            digitalWrite(stepper1_step, LOW );
            delay(step_delay);
          }
        }
        if (currentLine.endsWith("GET /dec2")) {
          digitalWrite(stepper2_dir, HIGH);
          for (int i = 0; i <= 20; i++) {
            digitalWrite(stepper2_step, HIGH);
            delay(step_delay);
            digitalWrite(stepper2_step, LOW );
            delay(step_delay);
          }
        }
        if (currentLine.endsWith("GET /inc2")) {
          digitalWrite(stepper2_dir, LOW);
          for (int i = 0; i <= 20; i++) {
            digitalWrite(stepper2_step, HIGH);
            delay(step_delay);
            digitalWrite(stepper2_step, LOW );
            delay(step_delay);
          }
        }
        /* if (currentLine.endsWith("GET /dec3")) {digitalWrite(16, HIGH);
              for (int i=0; i <= 43; i++){ digitalWrite(19, HIGH);delay(10);digitalWrite(19,LOW );delay(10); }
          }
          if (currentLine.endsWith("GET /inc3")) {digitalWrite(16, LOW);
              for (int i=0; i <= 43; i++){ digitalWrite(19, HIGH);delay(10);digitalWrite(19,LOW );delay(10); }
          }*/
        if (currentLine.endsWith("GET /stopall")) {
          digitalWrite(16, HIGH);
        }
      }
    }
  }

#endif


}
