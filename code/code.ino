#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(1000);
}

void loop() {
  Serial.println("Wifi Scannen");

  int aantal = WiFi.scanNetworks();

  if(aantal < 0 ){
    Serial.println("Scannen mislukt");
  } else {
    Serial.print("Aantal gevonden netwerken: ");
    Serial.println(aantal);
  }
  for(int i = 0 )
 WiFi.scanDelete();
delay(5000);
 
}

  