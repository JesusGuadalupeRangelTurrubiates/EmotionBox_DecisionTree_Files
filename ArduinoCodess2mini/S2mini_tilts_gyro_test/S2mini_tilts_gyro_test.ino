//Esta prueba busca hacer funcionar el modulo giroscopio mpu6059 en conjunto con
//6 swtiches de inclinacion para generar una sola linea separada por comas de los valores
//correspondientes a x, y, Z del acelerometro y giroscopio ademas de los 6 valores de los ilts.

// Fuentes de informacion utiles:
// https://www.reddit.com/r/esp32/comments/10r0vee/trouble_getting_i2c_to_work_on_the_wemos_s2_mini/
// https://www.studiopieters.nl/wp-content/uploads/2022/08/WEMOS-ESP32-S2-MINI.png
// https://www.wemos.cc/en/latest/_static/files/sch_s2_mini_v1.0.0.pdf
// 

// Perfiles para cargar codigo a la placa wemos s2 mini
// ESP32S2 NAtive USB - Ver terminal
// ESP32S2 Dev Module - Subir codigo
// LOLIN S2 Mini - ??

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
const byte tp2 = 2;
const byte tp3 = 3;
const byte tp4 = 4;
const byte tp5 = 5;
const byte tp6 = 6;

int tval1, tval2, tval3, tval4, tval5, tval6; // tval. valor del tilt. puede ser encendido o apagado (0 o 1)
int Shown_Face; // Valor de la cara mostrada. 1 a 6 segun la cara activa hacia arriba.


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


  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(9, HIGH);  
  digitalWrite(11, HIGH);  
  digitalWrite(13, HIGH);  
  digitalWrite(15, HIGH);  

}

void loop() {
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

  // Calcular los ángulos de inclinación en grados
  float pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  float roll = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / PI;
  
  // Asegurarnos de que los ángulos estén entre 0 y 360 grados
  pitch = (pitch < 0) ? (pitch + 360) : pitch;
  roll = (roll < 0) ? (roll + 360) : roll;

  // Identificar la cara correspondiente según el ángulo de inclinación del giroscopio
  int face;
  //-----------Finaliza codigo de funcionamietno del giroscopio

  //Condiciones de decision de la cara activa con base en switches de inclinacion y componentes Pitch y Roll de MPU6050
  //Los valores Pitch y Roll han sido calculados, en pantalla se muestran componentes XYZ de ACelerometro y Giroscopio.
  /*
  if ((pitch >= 0 && pitch < 20) && (roll >= 230 && roll < 360) && tval1 == 0) {
    face = 1;
  } else if ((pitch >= 350 && pitch < 360) && (roll >= 40 && roll <85 ) && tval2 == 0 ) {
    face = 2;
  } else if ((pitch >= 340 || (pitch >= 357 && pitch < 350)) && (roll >= 270 && roll < 280) && tval3 == 0 ){
    face = 3;
  } else if ((pitch >= 50 && pitch < 90) && (roll >= 240 && roll < 360) && tval4 == 0 ){
    face = 4;
  } else if ((pitch >= 270 && pitch < 300) && (roll >= 0 && roll < 360) && tval5 == 0  ) {
    face = 5;
  } else if ((pitch >= 350 && pitch < 360) && (roll >= 350 || (roll >= 350 && roll < 360)) && tval6 == 0 ) {     // cara 1
    face = 6;
  }else {
    face = 0;   // Cara 0 para no identificado
  }
  */

  //Decidir caras
  if ((((pitch > 315 && pitch < 360) || (pitch > 0 && pitch < 45)) && ((roll > 315 && roll < 360) || (roll > 0 && roll < 45))) && tval1 == 0) {
    face = 1;
  } else if ((pitch > 45 && pitch < 135) && tval2 == 0 ) {
    face = 2;
  } else if ((pitch > 225 && pitch < 315) && tval4 == 0 ) {
    face = 4;
  } else if (((pitch > 315 && pitch < 360) || (pitch > 0 && pitch < 45)) && tval6 == 0 ) {
    face = 6;
  } else if ((roll > 45 && pitch < 135) && tval3 == 0 ) {
    face = 3;
  } else if ((roll > 225 && pitch < 315) && tval5 == 0 ) {
    face = 5;
  } else {
    face = 0;   // Cara 0 para no identificado
  }

  //Muestra valores de tilts en el monitor serial. el orden corresponde al tilt switch fisico
  //Y por consecuente a la cara del cubo
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

  /*
  // Mostrar los ángulos en el monitor serial en grados. con esto se confirman los grados que conforman cada lado de la cara
  Serial.print(" ");
  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print("  ");
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print("  ");

  // Mostrar la cara identificada
  Serial.println(face);
  */

  
  // Mostrar la cara identificada
  Serial.print(",");
  Serial.println(face);

  //parpadeo de led integrdo para confirmacion visual fisica.
  delay(200);

}

//Funcion de calibracion del giroscopio
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
