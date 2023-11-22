//Esta prueba busca determinar que angulos se utilizan en el sensor mpu6050
//Usando los valores de Pitch y Roll
//En el monitor serial se muestran los grados de inclinacion del MPU6050 en X e Y

// Fuentes de informacion utiles:
// https://www.reddit.com/r/esp32/comments/10r0vee/trouble_getting_i2c_to_work_on_the_wemos_s2_mini/
// https://www.studiopieters.nl/wp-content/uploads/2022/08/WEMOS-ESP32-S2-MINI.png
// https://www.wemos.cc/en/latest/_static/files/sch_s2_mini_v1.0.0.pdf
// 

// Perfiles para cargar codigo a la placa wemos s2 mini
// ESP32S2 NAtive USB - Ver terminal
// ESP32S2 Dev Module - Subir codigo
// LOLIN S2 Mini - ??

// Librerias I2C para controlar el mpu6050
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include "MPU6050.h"
#include "I2Cdev.h"
#include "Wire.h"

MPU6050 mpu;

const int pinled = 15; //Led integrado de la placa

float sensitivity = 50.0;
const int calibrationSamples = 200;
float totalAngularVelocity = 0.0;

// tp. tiltpin. numero de pin acorde a construccion fisica.
const byte tp1 = 1;   

int tval1;

void setup() {
  // put your setup code here, to run once:

  pinMode(tp1, INPUT_PULLUP);    //Declaracion de pinesára señals de los tilts

  Serial.begin(9600);

  Wire.begin();     //Conexion con el MPU
  mpu.initialize(); //Inisialzacion del mpu
  calibrateGyro();  //Funcion de calibracion de giroscopio

  pinMode(pinled, OUTPUT);
  digitalWrite(pinled, LOW);


}

void loop() {
  //Obtencion de señal analogica del tilt switch a valores digitales.
  tval1 = digitalRead(tp1);    

  // put your main code here, to run repeatedly:

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

  // Calcular los ángulos de inclinación en grados
  float pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  float roll = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / PI;
  
  // Asegurarnos de que los ángulos estén entre 0 y 360 grados
  pitch = (pitch < 0) ? (pitch + 360) : pitch;
  roll = (roll < 0) ? (roll + 360) : roll;

  int face;


  //Decidir caras
  if ((((pitch > 315 && pitch < 360) || (pitch > 0 && pitch < 45)) && ((roll > 315 && roll < 360) || (roll > 0 && roll < 45))) && tval1 == 0) {
    face = 1;
  }else {
    face = 0;   // Cara 0 para no identificado
  }

  // Mostrar los ángulos en el monitor serial, en grados
  Serial.print(tval1);  //tilt 1
  Serial.print(",");
  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print("  ");
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print("  ");

  // Mostrar la cara identificada
  Serial.print(" ");
  Serial.print("Cara: ");
  Serial.println(face);

  //parpadeo de led integrdo para confirmacion visual fisica.
  digitalWrite(pinled, HIGH);
  delay(50);
  digitalWrite(pinled, LOW);
  delay(50);

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
