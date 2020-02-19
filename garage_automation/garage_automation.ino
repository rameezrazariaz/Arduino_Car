/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;     //Make a simple timer

void checkSwitch();

int relayState = LOW;
int switchState = HIGH;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "BxVoOl0SiO3BHhHXvJt9SWd1bxNhO3YD";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "D-Link_DIR-600M";
char pass[] = "Aventador";

#define RELAY_PIN 5  //D1
#define SWITCH 2     //D4
#define VPIN V2

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(VPIN);  //Syncing state from server
}

BLYNK_WRITE(VPIN)
{
  relayState = param.asInt();
  digitalWrite(RELAY_PIN, relayState);   //When app button is used reflect the state
}

void checkSwitch()
{
  if (digitalRead(SWITCH) == LOW)
  {
    if (switchState != LOW)
    {
      relayState = HIGH;
      digitalWrite(RELAY_PIN, relayState);   //Changing relay state
      Blynk.virtualWrite(VPIN, relayState);  //update widget in blynk
    }
    switchState = LOW;
  }
  else if (digitalRead(SWITCH) == HIGH)
  {
    if (switchState != HIGH)
    {
      relayState = LOW;
      digitalWrite(RELAY_PIN, relayState);
      Blynk.virtualWrite(VPIN, relayState);
    }
    switchState = HIGH;
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  digitalWrite(RELAY_PIN, relayState);

  timer.setInterval(500L, checkSwitch);
}

void loop()
{
  Blynk.run();
  timer.run();
}
