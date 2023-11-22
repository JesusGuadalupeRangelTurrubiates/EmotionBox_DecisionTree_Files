//Esta prueba busca hacer funcionar 6 tilt swithces al mismo tiempo
//Para generar una sola lista separada por comas de los valores en el monitor serial

// Perfiles para cargar codigo a la placa wemos s2 mini
// ESP32S2 NAtive USB - Ver terminal
// ESP32S2 Dev Module - Subir codigo
// LOLIN S2 Mini - ??


#include <Wire.h>

const int pinled = 15; //Led integrado de la placa

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
  Serial.begin(9600);
  pinMode(pinled, OUTPUT);
  digitalWrite(pinled, LOW);

  pinMode(tp1, INPUT_PULLUP);    //Obtencion de señales de los tilts
  pinMode(tp2, INPUT_PULLUP);
  pinMode(tp3, INPUT_PULLUP);
  pinMode(tp4, INPUT_PULLUP);
  pinMode(tp5, INPUT_PULLUP);
  pinMode(tp6, INPUT_PULLUP);

}

void loop() {

  //Obtencion de señal analogica del tilt switch a valores digitales.
  tval1 = digitalRead(tp1);    
  tval2 = digitalRead(tp2);
  tval3 = digitalRead(tp3);
  tval4 = digitalRead(tp4);
  tval5 = digitalRead(tp5);
  tval6 = digitalRead(tp6);

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
  Serial.println(tval6);  //tilt 6

  //parpadeo de led integrdo para confirmacion visual fisica.
  digitalWrite(pinled, HIGH);
  delay(100);
  digitalWrite(pinled, LOW);
  delay(100);

}
