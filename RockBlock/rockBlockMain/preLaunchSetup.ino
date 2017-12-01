#include <IridiumSBD.h>
#include <SoftwareSerial.h>


int rxPin = 12;
int txPin = 13;
int sleepPin = 5;


SoftwareSerial nss(rxPin, txPin);
IridiumSBD isbd(nss, sleepPin);

int messagesSent  = 0;
size_t bufferSize = 0;

void setup()
{

  Serial.begin(19200);
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


 


  Serial.print("Signal quality is ");
  Serial.println(signalQuality);
    
    err = isbd.sendSBDText("Hello, world!");
    if (err != 0)
    {
      Serial.print("sendSBDText failed: error ");
      Serial.println(err);
      return;
  }
   Serial.println("Hey, it worked!");
   Serial.print("Messages left: ");
   Serial.println(isbd.getWaitingMessageCount());




}



void sendMessage() //would like to eventually implement the Message class
{
 char outBuffer[200]; //RockBlock works in terms of char buffers

 String messageToSend = "Hello World"; //Sample string to send, will update to 
 //interface with other teams
 messagesSent += 1; 
for(uint8_t i = 0; i < messageToSend.length(); i++){
	
	outBuffer[i] = messageToSend[i]; 
}

uint8_t rxBuffer[200] = {0};
for(int i = 0; i < messageToSend.length(); i++){
      rxBuffer[i] = outBuffer[i];
}

bufferSize = sizeof(rxBuffer);

isbd.sendReceiveSBDBinary(rxBuffer, messageToSend.length(), rxBuffer, bufferSize); 
 
 

}


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
