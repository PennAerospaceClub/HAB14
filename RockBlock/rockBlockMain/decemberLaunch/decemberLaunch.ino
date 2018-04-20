#include <IridiumSBD.h>
#include <SimpleTimer.h>
#include <SoftwareSerial.h>


int rxPin = 10;
int txPin = 11;
int sleepPin = 3;
SimpleTimer timer;


SoftwareSerial nss(rxPin, txPin);
IridiumSBD isbd(nss, sleepPin);

uint8_t buffer[270];


SoftwareSerial inc(12, 13); //for incoming data (rx is pin 5, tx is pin 6)
String readString; //to store incoming data


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

  timer.setInterval(10000, repeatMe);

  //begin communication with other arduino
  inc.begin(19200);

}



void repeatMe() //would like to eventually implement the Message class
{
  inc.listen();
  //receive data from other rockblock


  while(inc.available()){
    char a = (char) inc.read(); 
    Serial.print(a);
    inc.flush(); 
  }


    
  String messageToSend = "";


  Serial.println("Message to Send: " + messageToSend);

  char outBuffer[270]; //RockBlock works in terms of char buffers

  //interface with other teams
  messagesSent += 1;
  for (int i = 0; i < messageToSend.length(); i++) {
    outBuffer[i] = messageToSend[i];
  }

  uint8_t rxBuffer[270] = {0};
  for (int i = 0; i < messageToSend.length(); i++) {
    rxBuffer[i] = outBuffer[i];
  }

  bufferSize = sizeof(buffer);
  nss.listen();
  isbd.sendReceiveSBDBinary(rxBuffer, messageToSend.length(), buffer, bufferSize);

  String downMessage = "";
  for (int i = 0; i < sizeof(buffer); ++i)
  {
    downMessage += (buffer[i]);
   
  }

  if(downMessage.equals("cutBallon")){
    Serial.println("cut");
  }
  downMessage = ""; 

}


void loop()
{
  timer.run();


}


bool ISBDCallback()
{
  return true;
}
