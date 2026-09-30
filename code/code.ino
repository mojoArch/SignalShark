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
    int signaal = WiFi.RSSI(i); 
    Serial.print(WiFi.SSID(i));
    Serial.print(" | ");
    Serial.print(signaal);
    Serial.print(" dBm | ");

    if(signaal >= -60) {
      Serial.println("Sterk Signaal");
     } else if (signaal >= -75) {
        Serial.println("Gemiddeld Signaal");
      } else {
        Serial.println("Zwak Signa-60)al");
      }
    
  }
  
 WiFi.scanDelete();
delay(5000);
 
}

  