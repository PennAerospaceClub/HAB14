#include <IridiumSBD.h>
#include <SimpleTimer.h>
#include <SoftwareSerial.h>


int rxPin = 10;
int txPin = 11;
int sleepPin = 5;
SimpleTimer timer;


SoftwareSerial nss(rxPin, txPin);
IridiumSBD isbd(nss, sleepPin);

uint8_t buffer[200];


SoftwareSerial inc(5, 6); //for incoming data (rx is pin 5, tx is pin 6)
String Data = ""; //to store incoming data


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

  //begin communication with other arduino
  inc.begin(9600);

  //take a look at the code below for reference of checking signal quality
  int err = isbd.getSignalQuality(signalQuality);
  if (err != 0)
  {
    Serial.print("SignalQuality failed: error ");
    Serial.println(err);
    return;
  }
  timer.setInterval(10000, repeatMe);



}



void repeatMe() //would like to eventually implement the Message class
{
  while (inc.available())
  {
    char character = mySerial.read(); // Receive a single character from the software serial port
    Data.concat(character); // Add the received character to the receive buffer

  }
  String messageToSend = Data; //Sample string to send, will update to
  Data = "";

  Serial.print("hello!");
  char outBuffer[200]; //RockBlock works in terms of char buffers


  //interface with other teams
  messagesSent += 1;
  for (uint8_t i = 0; i < messageToSend.length(); i++) {

    outBuffer[i] = messageToSend[i];
  }

  uint8_t rxBuffer[200] = {0};
  for (int i = 0; i < messageToSend.length(); i++) {
    rxBuffer[i] = outBuffer[i];
  }

  bufferSize = sizeof(buffer);

  isbd.sendReceiveSBDBinary(rxBuffer, messageToSend.length(), buffer, bufferSize);

  for (int i = 0; i < sizeof(buffer); ++i)
  {
    Serial.write(buffer[i]);
    // Serial.print("(");
    // Serial.print(bufferIn[i], HEX);
    // Serial.print(") in");
  }

}


void loop()
{
  timer.run();


}


bool ISBDCallback()
{
  return true;
}
