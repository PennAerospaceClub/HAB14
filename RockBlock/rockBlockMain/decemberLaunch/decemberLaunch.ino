#include <IridiumSBD.h>
#include <SimpleTimer.h>
#include <SoftwareSerial.h>


int rxPin = 10;
int txPin = 11;
int sleepPin = 3;
SimpleTimer timer;
int ledpin = 8;

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
  pinMode (ledpin, OUTPUT);

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
  String messageToSend = "";
  for (int i = 0; i < 3; i++) {
    while (inc.available()) {
      char c = (char) inc.read();  //gets one byte from serial buffer
      Serial.print(c);
      if (c == ';') {
        if (readString.length() > 0) {
          messageToSend += readString;//prints string to serial port out
          //do stuff with the captured readString
          readString = ""; //clears variable for new input
        }
      }
      else {
        inc.listen();

        readString += c; //makes the string readString
      }
    }
  }
  if (!inc.available()) {
    Serial.println("no incoming data");
  }

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

    downMessage += (char) (buffer[i]);

  }
  Serial.println(downMessage);
  if (downMessage.equals("cutBalloon")) {
      digitalWrite(ledpin, HIGH);

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
