#include <WiFi.h>
void toonMenu(){
  Serial.println("\n Signalshark ");
  Serial.println("w = Wifi scannen");
  Serial.println("m = Menu tonen");
  Serial.println("h = Hulp");
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(1000);
  toonMenu();
}



void scanWifi() {
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
        Serial.println("Zwak Signaal");
      }
    
  }
  
 WiFi.scanDelete();
 
}
void toonHulp(){
  Serial.println("\n Hulp ");
  Serial.println("Typ w = wifi-netwerken");
  Serial.println("Een waarde -> 0 dBm == sterkst");
  Serial.println("Typ m = menu ");
}

void loop(){
  if (Serial.available() > 0) {
    char keuze = Serial.read();

     if (keuze == 'w'){
      scanWifi();
    } else if (keuze == 'm') {
      toonMenu();
    } else if (keuze == 'h'){
      toonHulp();
    }
  }
  delay(10);
}
  