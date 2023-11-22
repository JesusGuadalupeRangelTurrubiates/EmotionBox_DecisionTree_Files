//Esta prueba busca obtener la direcccion fisica de la placa ESP WEMOS s2

// Fuentes de informacion utiles:
// https://randomnerdtutorials.com/telegram-control-esp32-esp8266-nodemcu-outputs/

// Perfiles para cargar codigo a la placa wemos s2 mini
// ESP32S2 NAtive USB - Ver terminal
// ESP32S2 Dev Module - Subir codigo
// LOLIN S2 Mini - ??


// Complete Instructions to Get and Change ESP MAC Address: https://RandomNerdTutorials.com/get-change-esp32-esp8266-mac-address-arduino/

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

void setup(){
  Serial.begin(115200);
}
 
void loop(){

  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
  delay(1000);

}