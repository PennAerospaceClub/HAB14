#include <SoftwareSerial.h>
int rxPin = 5; //wire to pin 6 (tx) on reciever
int txPin = 6; //wire to pin 5 (rx) on reciever

SoftwareSerial snd(5, 6); //for sending data (rx is pin 5, tx is pin 6)

void setup() {
  // put your setup code here, to run once:
  
  //begin communication with other arduino
  snd.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  snd.write("message");
  delay(7000);

}
