#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN

void setup() {1
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:

}
