#include <WiFi.h>
void toonMenu(){
  Serial.println("\n Signalshark ");
  Serial.println("w = Wifi scannen");
  Serial.println("m = Menu tonen");
  Serial.println(beoordeelSignaal(-50));
  Serial.println("h = Hulp");
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(1000);
  toonMenu();
}
const char* beoordeelSignaal(int signaal){
  if(signaal >= -60){
    return "Sterk Signaal";
  }
  if(signaal >= -75){
    return "Gemiddeld Signaal";
  }
  return "Zwak Signaal";
}


void scanWifi() {
  Serial.println("Wifi Scannen");

unsigned long startTijd = millis();
int aantal = WiFi.scanNetworks();
unsigned long scanDuur = millis() - startTijd; 
Serial.print("Scan duurde: ");
Serial.print(scanDuur);
Serial.println("ms");

  if(aantal < 0 ){
    Serial.println("Scannen mislukt");
  } else if (aantal == 0){
    Serial.println("geen netwerk gevonden");
  } else {
    Serial.print("Aantal gevonden netwerken: ");
    Serial.println(aantal);
  }
  for(int i = 0; i < aantal; i++){
    Serial.print(i + 1);
    Serial.print(". ");
    int signaal = WiFi.RSSI(i); 
    Serial.print(WiFi.SSID(i));
    Serial.print(" | kanaal: ");
    Serial.print(WiFi.channel(i));
    Serial.print(" | ");
    Serial.print(signaal);
    Serial.print(" dBm | ");
    Serial.println(beoordeelSignaal(signaal));

    
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

     if (keuze == 'w' || keuze == 'W'){
      scanWifi();
    } else if (keuze == 'm' || keuze == 'M') {
      toonMenu();
    } else if (keuze == 'h' || keuze == 'H'){
      toonHulp();
    } else if (keuze != '\n' && keuze != '\r'){
      Serial.println("Onbekende keuze, klik op m");
    }
  }
  delay(10);
}
  