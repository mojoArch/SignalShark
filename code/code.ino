#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(1000);
}

void loop() {
  Serial.println("Wifi Scannen");
  int aantal = WiFi.ScanNetworks();

  if(aantal < 0 ){
    Serial.println("Scannen mislukt");
  } else {
    Serial.println("Aantal gevonden netwerken: ");
  }
}
teller++;
delay(2000);
}
  