#include <SoftwareSerial.h>

const int rx = 6;
const int tx = 5;
SoftwareSerial Softser(rx, tx);
String readString;


void setup() {
  // put your setup code here, to run once:
  
  pinMode(rx, INPUT);
  pinMode(tx, OUTPUT);
  Softser.begin(9600);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (Softser.available()){
   // float uv = Softser.read();
    char c = Softser.read();  //gets one byte from serial buffer
    if (c == ',') {
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

  delay(1000);


}
