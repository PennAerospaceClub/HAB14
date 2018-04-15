#include <SoftwareSerial.h>

SoftwareSerial snd(22, 23); //for sending data (rx is pin 12, tx is pin 13)

void setup() {
  // put your setup code here, to run once:
  
  //begin communication with other arduino
  snd.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  snd.write("19535800,250218,193178,0.1875,-3.7500,-10.8125,39.695999,-75");
  snd.write(".768021,177.100010,178.58,0.23,4,0.000,58.7134,61.4324,89.712");
  snd.write("2,-4.4006,1.2170,0.99,54.94,14.94;");
  

  delay(11500);

}
