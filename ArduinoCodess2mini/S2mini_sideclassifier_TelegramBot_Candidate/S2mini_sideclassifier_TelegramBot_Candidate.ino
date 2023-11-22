//Esta prueba busca hacer funcionar el modulo giroscopio mpu6059 en conjunto con
//6 swtiches de inclinacion para generar una sola linea separada por comas de los valores
//correspondientes a x, y, Z del acelerometro y giroscopio ademas de los 6 valores de los ilts.

//Una vez se de la salida de los 12 valores correspondientes a las caracterizticas del dataseset (caracterizticas sin clase)
//crear una funcion basada en la construccion del clasificador de arbol para prededcir la cara activa
//basandose en datos de entrada constantes
// Tomar la prediccion hecha y manarla a que la muestre un bot de telegram

//Este codigo esta basado en S2mini_tilts_gyro_test para mostrar toda la fila de numeros

// Fuentes de informacion utiles:
// 
// 

// Perfiles para cargar codigo a la placa wemos s2 mini
// ESP32S2 NAtive USB - Ver terminal
// ESP32S2 Dev Module - Subir codigo
// LOLIN S2 Mini - ??

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

//const char* ssid = "AP-I120"; // Credenciales Lab
//const char* password = "TrGhFdNX";

const char* ssid = "INFINITUM6059"; // Credenciales casa
const char* password = "1CEF568FA7";

//Credenciales 687
//const char* ssid = "los odio a todos";
//const char* password = "noseprogramarmevoyapymes";

#define BOTtoken "6338955865:AAExNSySiig3nJDalMdnB7XnC7SWw9QgJJ0"  // your Bot Token (Get from Botfather)
#define CHAT_ID "6563493359"
#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int ledPin = 15;
bool ledState = HIGH;
//-----------------------------------------------

#include "MPU6050.h"
#include "I2Cdev.h"
#include "Wire.h"
MPU6050 mpu;

//-----------------------------------------------

const int calibrationSamples = 200;
float sensitivity = 50.0;
float totalAngularVelocity = 0.0;

// tp. tiltpin. numero de pin acorde a construccion fisica.
const int pinled = 15; //Led integrado de la placa
const byte tp1 = 1;   
const byte tp2 = 2;
const byte tp3 = 3;
const byte tp4 = 4;
const byte tp5 = 5;
const byte tp6 = 6;

int tval1, tval2, tval3, tval4, tval5, tval6; // tval. valor del tilt. puede ser encendido o apagado (0 o 1)
int Shown_Face; // Valor de la cara mostrada. 1 a 6 segun la cara activa hacia arriba.

int last_pred = -1;

int pred_mode = -1; //Valor bandera para prediccion activada o desactivada

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/pred_start to start recieving the face prediction \n";
      welcome += "/pred_stop to stop recieving the face prediction \n";
      welcome += "/box_state to show current box side \n";
      bot.sendMessage(chat_id, welcome, "");
      Serial.println("/start used");
    }


    if (text == "/pred_start"){
      Serial.println("/pred_start used");
      bot.sendMessage(chat_id, "Side Prediction Started - Box will output side when rotated.", "");
      pred_mode = 1;
    }

    if (text == "/pred_stop"){
      Serial.println("/pred_stop used");
      bot.sendMessage(chat_id, "Side Prediction Stopped - Box won't output anything.", "");
      pred_mode = -1;
    }

    if (text == "/curr_state"){
      bot.sendMessage(chat_id, "Show current active face.", "");
    }
  }
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  Wire.begin();     //Conexion con el MPU
  mpu.initialize(); //Inisialzacion del mpu
  calibrateGyro();  //Funcion de calibracion de giroscopio

  pinMode(pinled, OUTPUT);
  digitalWrite(pinled, LOW);

  pinMode(tp1, INPUT_PULLUP);    //Declaracion de pinesára señals de los tilts
  pinMode(tp2, INPUT_PULLUP);
  pinMode(tp3, INPUT_PULLUP);
  pinMode(tp4, INPUT_PULLUP);
  pinMode(tp5, INPUT_PULLUP);
  pinMode(tp6, INPUT_PULLUP);

  //Setup telegramBOT----WIFI----------------------------------------
  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
    client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  #endif

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Setup done - Emotion Box Connected - use /start to begin.", "");
}

void loop() {

  //Serial.println("Loop cicled");  //tilt 1

  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  //-----------Finaliza codigo de funcionamietno del giroscopio

  //Muestra valores de tilts en el monitor serial. el orden corresponde al tilt switch fisico
  //Y por consecuente a la cara del cubo

  //String cube_values = tval1 + "," 
  if (pred_mode == 1){
    prediction_active();
  }
  
  // bot.sendMessage(chat_id, predToshow, "");

  //parpadeo de led integrdo para confirmacion visual fisica.
  delay(1000);

}

void prediction_active(){
  // put your main code here, to run repeatedly:

  //Obtencion de señal analogica del tilt switch a valores digitales.
  tval1 = digitalRead(tp1);    
  tval2 = digitalRead(tp2);
  tval3 = digitalRead(tp3);
  tval4 = digitalRead(tp4);
  tval5 = digitalRead(tp5);
  tval6 = digitalRead(tp6);

  //-----------Comienza codigo de funcionamietno del giroscopio

  int16_t accX, accY, accZ;   //Componentes XYZ de Acelerometro
  int16_t gyroX, gyroY, gyroZ;    //Componentes XYZ de Giroscopio
  
  mpu.getAcceleration(&accX, &accY, &accZ);   //Obtencion de valores
  mpu.getRotation(&gyroX, &gyroY, &gyroZ);
  
  // Convertir los valores de aceleración y velocidad angular a unidades reales
  float ax = (float)accX / 16384.0; // Dividir por 16384 para obtener g (gravedad, 9.81 m/s^2)
  float ay = (float)accY / 16384.0;
  float az = (float)accZ / 16384.0;
  
  float gx = (float)gyroX / sensitivity; // Convertir a grados por segundo
  float gy = (float)gyroY / sensitivity;
  float gz = (float)gyroZ / sensitivity;

  Serial.print(tval1);  //tilt 1
  Serial.print(",");
  Serial.print(tval2);  //tilt 2
  Serial.print(",");
  Serial.print(tval3);  //tilt 3
  Serial.print(",");
  Serial.print(tval4);  //tilt 4
  Serial.print(",");
  Serial.print(tval5);  //tilt 5
  Serial.print(",");
  Serial.print(tval6);  //tilt 6
  
  //Muestra X , Y, Z tanto del giroscopio como del acelerometro
  Serial.print(",");

  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.print(az);

  Serial.print(",");

   Serial.print(gx);
  Serial.print(",");
  Serial.print(gy);
  Serial.print(",");
  Serial.print(gz);

  int prediction = side_pred(tval1, tval2, tval3, tval4, tval5, tval6, ax, ay, az, gx, gy, gz);
  Serial.print(" | Prediccion: ");
  Serial.println(prediction);

  String predToshow = String(prediction);

  //Mandar mensajes al bot de telegram

  if (last_pred != prediction){
    String chat_id = CHAT_ID;
    bot.sendMessage(chat_id, "(predicted) Current side is: " + predToshow, "");
    last_pred = prediction;
  }

}

int side_pred(int t1, int t2,int t3,int t4,int t5,int t6,float ax,float ay,float az,float gx,float gy,float gz){
  //Serial.print("flag: side_pred reached | ");
  int prediction;

  if(az <= -0.88){
    if(ay <= -0.65){
      prediction = 2;
    }
    if(ay > -0.65){
      if(ax <= 0.745){
        if(ay <= 0.715){
          prediction = 1;
        }
        if(ay > 0.715){
          prediction = 4;
        }
      }
      if(ax > 0.745){
        prediction = 5;
      }
    }
  }
  if(az > -0.88){
    if(az <= 0.535){
      if(ay <= -0.635){
        if(ax <= 0.85){
          if(ax <= -0.625){
            prediction = 3;
          }
          if(ax > -0.625){
            prediction = 2;
          }
        }
        if(az > 0.85){
          if(ay <= -0.055){
            prediction = 5;
          }
          if(ay > -0.055){
            prediction = 2;
          }
        }
      }
      if(ay > -0.635){
        if (ax <= -0.555){
          if(ay <= 0.65){
            prediction = 3;
          }
          if(ay > 0.65){
            prediction = 4;
          }
        }
        if (ax > -0.555){
          if (ax <= 0.685){
            prediction = 4;
          }
          if (ax > 0.685){
            prediction = 5;
          }
        }
      }
    }
    if(az > 0.535){
      if(t4 <= 0.5){
        if(ay <= 0.44){
          prediction = 5;
        }
        if(ay > 0.44){
          if(ax <= -0.5){
            prediction = 6;
          }
          if(ax > -0.5){
            prediction = 4;
          }
        }
      }
      if(ax <= 0.705){
        if(ax <= -0.74){
          prediction = 3;
        }
        if(ax > -0.74){
          prediction = 6;
        }
      }
      if(ax > 0.705){
        if(ay <= 0.255){
          prediction = 5;
        }
        if(ax > 0.255){
          prediction = 6;
        }
      }
    }
  }
                                                                
  return prediction;

}

void calibrateGyro() {
  Serial.println("Calibrando giroscopio...");
  
  for (int i = 0; i < calibrationSamples; i++) {
    int16_t gyroX, gyroY, gyroZ;
    mpu.getRotation(&gyroX, &gyroY, &gyroZ);
    totalAngularVelocity += gyroZ / sensitivity;
    delay(10);
  }
  
  float averageAngularVelocity = totalAngularVelocity / calibrationSamples;
  sensitivity = averageAngularVelocity;
  
  Serial.print("Calibración completa. Sensibilidad: ");
  Serial.println(sensitivity);
}

