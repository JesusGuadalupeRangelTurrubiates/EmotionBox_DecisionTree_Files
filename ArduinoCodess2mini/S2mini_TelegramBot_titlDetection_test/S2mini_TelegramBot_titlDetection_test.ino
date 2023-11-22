//Esta prueba busca conectar el modulo ESP S2 MINI con un switch de inclinacion a un bot de telegram 
//Con el objetivo de reconocer el estado de un swtich

// Fuentes de informacion utiles:
// https://randomnerdtutorials.com/telegram-control-esp32-esp8266-nodemcu-outputs/

// Perfiles para cargar codigo a la placa wemos s2 mini
// ESP32S2 NAtive USB - Ver terminal
// ESP32S2 Dev Module - Subir codigo
// LOLIN S2 Mini - ??

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/telegram-esp32-motion-detection-arduino/
  
  Project created using Brian Lough's Universal Telegram Bot Library: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your network credentials
/*// Credenciales red I109
const char* ssid = "AP-I120";
const char* password = "TrGhFdNX";
*/

// Credenciales Casa
const char* ssid = "INFINITUM6059";
const char* password = "1CEF568FA7";

// Initialize Telegram BOT
#define BOTtoken "6338955865:AAExNSySiig3nJDalMdnB7XnC7SWw9QgJJ0"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "6563493359"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

const int tiltSwtich = 1; // PIR Motion Sensor
bool stateDetection = true;

// Indicates when motion is detected
void detectsMovement() {
  // Serial.println("TILT ACTIVATION!!!");
  stateDetection = false;
}

void setup() {
  Serial.begin(115200);

  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(tiltSwtich, INPUT_PULLUP);
  // Set tiltSwtich pin as interrupt, assign interrupt function and set RISING mode
  //attachInterrupt(digitalPinToInterrupt(tiltSwtich), detectsMovement, RISING);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop() {
  if(tiltSwtich == false){ //Por alguna razon LEDS y Tilts estan invertidos, usar false produce True y visceversa idk
    bot.sendMessage(CHAT_ID, "Tilt Active!!", "");
    Serial.println("Tilt Activation");
  }
}