//libreria para bluetooth
#include <SoftwareSerial.h>
SoftwareSerial  ModuloHC05(9, 11); //pin TX, pin RX  modulo bluetooth


int speed = 200; //variar velocidad

char DATO;// para leer lo que manda x blue

//----motor der
int in1 = 2;
int in2 = 4;
int ena = 3;

//----motor izq
int in3 = 5;
int in4 = 7;
int enb = 6;

//// array con los dos motores
//int motores[2][3]  = {{3, 2, 4}, {6, 5, 7}}; //pines de cada uno (ena,en1,en2) (enb,en3,en4)


//----sensores

int sensorIzq = 8; //sensor izquierdo + numero de pin al que esta conectado
int valorsensorIzq; //aca se almacena el valor leido del sensor.

int sensorMed = 10; //sensor medio + numero de pin al que esta conectado
int valorsensorMed; //aca se almacena el valor leido del sensor.

int sensorDer = 12; //sensor derecho + numero de pin al que esta conectado
int valorsensorDer; //aca se almacena el valor leido del sensor.

// para detectar un cambio en el estado del sensor, suponiendo que esta sobre la linea.
#define fuera     0x0
#define enlinea  0x1


void setup() {
  Serial.begin(9600);//inicializar puerto serie por hardw
  ModuloHC05.begin(9600);  //inicializar puerto serie por sotf

  //----motor der
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);
  //----motor izq
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);

  ////for pa los motores
  //  for (int i = 0; i < 2; i++) {
  //    for (int j = 0; j < 3; j++) {
  //      pinMode(motores[i][j], OUTPUT);
  //    }
  //  }


  //--------------------------sensores
  pinMode(sensorIzq, INPUT);
  pinMode(sensorMed, INPUT);
  pinMode(sensorDer, INPUT);

}

void loop() {

  //--------------------------sensores
  //almacena los valores que lee en cada variable (valorsensor..etc)
  valorsensorIzq = digitalRead(sensorIzq);
  valorsensorMed = digitalRead(sensorMed);
  valorsensorDer = digitalRead(sensorDer);


  //-------------------------------------condiciones
  //si el unico en linea es el del medio- - AVANZA BIEN
  if (valorsensorIzq == fuera && valorsensorMed == enlinea && valorsensorDer == fuera ) {
    //----motor DER funcionando
    analogWrite(ena, speed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    //----motor IZQ funcionando
    analogWrite(enb, speed);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

  }
  // si sensor derecho esta en linea- - SE CORRIÓ A LA IZQUIERDA
  if (valorsensorIzq == fuera && valorsensorMed == fuera && valorsensorDer == enlinea || valorsensorIzq == fuera && valorsensorMed == enlinea && valorsensorDer == enlinea ) {

    //----motor izquierdo reversa
    analogWrite(enb, speed);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    //----motor DER funcionando
    analogWrite(ena, speed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  // si sensor izquierdo esta en linea- - SE CORRIÓ A LA DERECHA
  if (valorsensorIzq == enlinea && valorsensorMed == fuera && valorsensorDer == fuera || valorsensorIzq == enlinea && valorsensorMed == enlinea && valorsensorDer == fuera) {

    //----motor IZQ funcionando
    analogWrite(enb, speed);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    //----motor derecho reversa
    analogWrite(ena, speed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }



  // si ninguno detecta linea- retrocede > NO SIRVE
  if (valorsensorIzq == fuera && valorsensorMed == fuera && valorsensorDer == fuera ) {
    //    //----motor izquierdo backwards
    //    analogWrite(enb, speed);
    //    digitalWrite(in3, HIGH);
    //    digitalWrite(in4, LOW);
    //    //----motor derecho backwards
    //    analogWrite(ena, speed);
    //    digitalWrite(in1, LOW);
    //    digitalWrite(in2, HIGH);
    //    delay(50); //100ms

    analogWrite(enb, speed);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    //----motor derecho apagado
    analogWrite(ena, speed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  // si todos detectan linea- - DETECTA POSIBLES CAMINOS
  if (valorsensorIzq == enlinea && valorsensorMed == enlinea && valorsensorDer == enlinea ) {
    //----motor izquierdo apagado
    analogWrite(enb, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    //----motor derecho apagado
    analogWrite(ena, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    //---------indicacion x blue
    if ( ModuloHC05.available() ) { //si llega algo por blue

      DATO = ModuloHC05.read(); //asigna lo que lee al char dato

      //mover robot a la derecha
      if (DATO == 'd') {
        Serial.write(ModuloHC05.read());


        //----motor IZQ funcionando
        analogWrite(enb, speed);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        delay(100);
      }
      //mover robot a la izquierda

      if (DATO == 'a') {
        Serial.write(ModuloHC05.read());


        //----motor DER funcionando
        analogWrite(ena, speed);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        delay(100);
      }

      //mover ambos motores
      if (DATO == 'w') {
        //----motor IZQ funcionando
        analogWrite(enb, speed);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);

        //----motor DER funcionando
        analogWrite(ena, speed);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);


      }
    }
  }
}
