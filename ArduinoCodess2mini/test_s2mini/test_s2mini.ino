// Perfiles para cargar codigo a la placa wemos s2 mini
// ESP32S2 Native USB - Ver terminal
// ESP32S2 Dev Module - Subir codigo
// LOLIN S2 Mini - ??

int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(15, HIGH);
  delay(500);
  digitalWrite(15, LOW);
  delay(500);
  Serial.print("Hello, Wemos S2 mini!!!!!! - ");
  i = i + 1;
  Serial.println(i);
}
