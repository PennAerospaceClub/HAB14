#include <SoftwareSerial.h>
#include <SimpleTimer.h>

const int rx = 12;
const int tx = 13;
SoftwareSerial Softser(rx, tx);
String readString;
SimpleTimer timer;


void setup() {
  // put your setup code here, to run once:
  
  pinMode(rx, INPUT);
  pinMode(tx, OUTPUT);
  Softser.begin(19200);
  Serial.begin(19200);
    timer.setInterval(0, repeatMe);


}


void loop()
{
    timer.run();
  

}
void repeatMe() //would like to eventually implement the Message class
{
  // put your main code here, to run repeatedly:

  if (Softser.available()){
   // float uv = Softser.read();
    char c = Softser.read();  //gets one byte from serial buffer
    Serial.print(c);
    if (c == ';') {
      if (readString.length() >0) {
        Serial.print(readString); //prints string to serial port out
        Serial.println(','); //prints delimiting ","
        //do stuff with the captured readString 
        readString=""; //clears variable for new input
      }
    }  
    else {     
      readString += c; //makes the string readString
    }
    
    /*Serial.println(uv);     
    readString += c; //makes the string readString
    Serial.print(readString);*/
  }

    

/*  if (!Softser.available()){
    Serial.println("Software Serial unavailable.");
  }*/



}
