//Esta prueba busca hacer funcionar el modulo giroscopio mpu6059 en conjunto con
//6 swtiches de inclinacion para generar una sola linea separada por comas de los valores
//correspondientes a x, y, Z del acelerometro y giroscopio ademas de los 6 valores de los ilts.

//Una vez se de la salida de los 12 valores correspondientes a las caracterizticas del dataseset (caracterizticas sin clase)
//crear una funcion basada en la construccion del clasificador de arbol para prededcir la cara activa
//basandose en datos de entrada constantes

//Este codigo esta basado en S2mini_tilts_gyro_test para mostrar toda la fila de numeros

// Fuentes de informacion utiles:
// 
// 

// Perfiles para cargar codigo a la placa wemos s2 mini
// ESP32S2 NAtive USB - Ver terminal
// ESP32S2 Dev Module - Subir codigo
// LOLIN S2 Mini - ??

// Este codigo usa el arbol de decisiones de LadosCubo_Tree_Candidate pues utiliza el dataset mas reciente.


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

  //-----------Finaliza codigo de funcionamietno del giroscopio

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

  int prediction = side_pred(tval1, tval2, tval3, tval4, tval5, tval6, ax, ay, az, gx, gy, gz);
  Serial.print(" | Tree Prediction: ");
  Serial.println(prediction);

  //parpadeo de led integrdo para confirmacion visual fisica.
  digitalWrite(pinled, LOW);
  delay(200);
  digitalWrite(pinled, HIGH);

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

//Funcion de prediccion de lado basado en modelo de arbol
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














