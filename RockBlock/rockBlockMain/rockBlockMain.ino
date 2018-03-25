#include <IridiumSBD.h>


#include <IridiumSBD.h>


#include <SoftwareSerial.h>


int rxPin = 10;
int txPin = 11;
int sleepPin = 5;


SoftwareSerial nss(rxPin, txPin);
IridiumSBD isbd(nss);
uint8_t buffer[200];

void setup()
{

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

  //take a look at the code below for reference of checking signal quality
  int err = isbd.getSignalQuality(signalQuality);
  if (err != 0)
  {
    Serial.print("SignalQuality failed: error ");
    Serial.println(err);
    return;
  }



  // *************************************** //
  //BELOW IS OLD CODE, USELESS, BUT FEEL FREE TO USE AS REFERNCE


  Serial.print("Signal quality is ");
  Serial.println(signalQuality);
  //  int err;
  //  err = isbd.sendSBDText("Hello, world!");
  //  if (err != 0)
  //  {
  //    Serial.print("sendSBDText failed: error ");
  //    Serial.println(err);
  //    return;
  //  }
  //  Serial.println("Hey, it worked!");
  //  Serial.print("Messages left: ");
  //  Serial.println(isbd.getWaitingMessageCount());

  //*************************************************//



}

//char[] hexToChars(uint8_t[] msg) {
//  for 
//  } 

//requires a Message object. Reger to the message class

void loop()
{
  bool serialReceived = false;
  String incomingSerial;
  int signalQuality = -1;
  //take a look at the code below for reference of checking signal quality
  int err = isbd.getSignalQuality(signalQuality);
  if (err != 0)
  {
    Serial.print("SignalQuality failed: error ");
    Serial.println(err);
    return;
  }


  if (Serial.available() > 0) {
                incomingSerial = Serial.readString();
                Serial.print("I serial received: ");
                serialReceived = true;
    } 


  // *************************************** //
  //BELOW IS OLD CODE, USELESS, BUT FEEL FREE TO USE AS REFERNCE


  Serial.print("Signal quality is ");
  Serial.println(signalQuality);
  if (signalQuality > 0 && serialReceived) {

    char bufferOut[200]; 
    incomingSerial.toCharArray(bufferOut, 200);
    uint8_t bufferIn[200];
    size_t bufferSize = sizeof(bufferIn);
    err = isbd.sendReceiveSBDText(bufferOut, bufferIn, bufferSize);
    if (err != 0)
    {
      Serial.print("sendReceiveSBDText failed: error ");
      Serial.println(err);
      return;
    }

    Serial.print("Inbound buffer size is ");
    Serial.println(bufferSize);
    for (int i = 0; i < bufferSize; ++i)
    {
      Serial.write(buffer[i]);
//      Serial.print("(");
//      Serial.print(buffer[i], HEX);
//      Serial.print(") ");
    }
    Serial.print("Messages left: ");
    Serial.println(isbd.getWaitingMessageCount());
  }
  serialReceived = false;
}


bool ISBDCallback()
{
  return true;
}

