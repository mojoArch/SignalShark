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
  for(int i = 0; i < aantal; i++){
    Serial.print(WiFi.SSID(i));
    Serial.print(" - Signaal : ");
    Serial.print(WiFi.RSSI(i));
    Serial.println("dBm");
  }
  
 WiFi.scanDelete();
delay(5000);
 
}

  