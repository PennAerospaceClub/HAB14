#include <SoftwareSerial.h>

SoftwareSerial snd(22, 23); //for sending data (rx is pin 12, tx is pin 13)

void setup() {
  // put your setup code here, to run once:
  
  //begin communication with other arduino
  snd.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  snd.write("19535800,250218,193178,0.1875,-3.7500,-10.8125,39.695999,-75;");
 

  delay(11500);

}
