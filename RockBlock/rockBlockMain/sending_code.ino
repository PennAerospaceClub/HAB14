#include <SoftwareSerial.h>

SoftwareSerial snd(12, 13); //for sending data (rx is pin 12, tx is pin 13)

void setup() {
  // put your setup code here, to run once:
  
  //begin communication with other arduino
  snd.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  snd.write("message,");
  delay(10000);

}
