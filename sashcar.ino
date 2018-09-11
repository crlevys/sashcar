/*
 * Copyright (c) <2018> <Rafael Levy>
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to 
 * whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of 
 * the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
 *NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 *NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 *DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 *
 */
/*  
 *   Sistema alertizador salvaguarda humano-coche
 *   (Semaforo Interactivo)
 *   Este ejemplo muestra un conjunto de semáforos que cambiarán de verde a rojo, ámbar y viceversa, 
 *   luego de un período de tiempo establecido, utilizando el sistema de cuatro estados de Mexico.
 *   Este se extiende para incluir un conjunto de luces peatonales y un botón peatonal para solicitar 
 *   cruzar la calle. El Arduino reaccionará cuando se presione el botón cambiando el estado de las 
 *   luces para que los autos se detengan y permitan que el peatón cruce con seguridad.
 *   
 */
// assign the car lights
const int CAR_RED = 12; 
const int CAR_YELLOW = 11;
const int CAR_GREEN = 10;
// assign the pedestrian lights
const int PED_RED = 6; 
const int PED_GREEN = 5;
// button pin
const int BUTTON = 2;
 
unsigned long crossTime = 10000; // time alloyoud to cross
unsigned long changeTime;        // time since BUTTON pressed
int state = LOW;                 // If is push buttom
void setup() {
  pinMode(CAR_RED, OUTPUT);
  pinMode(CAR_YELLOW, OUTPUT);
  pinMode(CAR_GREEN, OUTPUT);
  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT);
  //Assign the initial lights
  digitalWrite(CAR_GREEN, HIGH);
  digitalWrite(PED_RED, HIGH);
  Serial.begin(9600);
}
void loop() {
  int valor = analogRead(A0);
  crossTime= map(valor, 0, 1023, 10, 60)*1000;
  // starts the car's traffic light cycle
  Serial.println("inicia el ciclo del semáforo del carro");
  digitalWrite(CAR_GREEN, HIGH);
  delay(crossTime); // wait for preset time period
  flash(CAR_GREEN); 
  digitalWrite(CAR_YELLOW, HIGH);
  delay(2000);
  digitalWrite(CAR_YELLOW, LOW);
  digitalWrite(CAR_RED, HIGH);
  delay(1000); // wait 1 second till its safe
  // starts the cycle of the pedestrian traffic light
  Serial.println("inicia el ciclo del semáforo del peatón");
  digitalWrite(PED_RED, LOW);
  digitalWrite(PED_GREEN, HIGH);
  delay(crossTime); // wait for preset time period
  flash(PED_GREEN);
  digitalWrite(PED_RED, HIGH);
  delay(1000); // wait 1 second till its safe
  digitalWrite(CAR_RED, LOW); // red off
  
}
// flash the light in pin n
void flash(int pin){
  
  for (int x=0; x<6; x++) {
    digitalWrite(pin, HIGH);
    delay(250);
    digitalWrite(pin, LOW);
    delay(250);
  }
}
