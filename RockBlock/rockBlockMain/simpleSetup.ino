#include <Time.h>
#include <TimeLib.h>

#include <QueueArray.h>
#include <IridiumSBD.h>
#include <SoftwareSerial.h>
#include "Message/Message.cpp"


SoftwareSerial ssIridium(10, 11); // RockBLOCK serial port on 18/19
 
IridiumSBD isbd(ssIridium, 5);   // RockBLOCK SLEEP pin on 10
 
void setup()
{
   isbd.setPowerProfile(1); // This is a low power application
   isbd.begin(); 

   Serial.begin(38400);
  Serial.print("started");
  //RockBlock signal quality can range from 0-5..
  //should NOT try to send a message if the signal quality is not
  //at least 1.
  int signalQuality = -1;

  nss.begin(19200);

  isbd.attachConsole(Serial);
  isbd.attachDiags(Serial);
  isbd.setPowerProfile(0);
  isbd.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
