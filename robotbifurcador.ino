/*
  Dweet.io GET client for ArduinoHttpClient library
  Connects to dweet.io once every ten seconds,
  sends a GET request and a request body. Uses SSL

  Shows how to use Strings to assemble path and parse content
  from response. dweet.io expects:
  https://dweet.io/get/latest/dweet/for/thingName

  For more on dweet.io, see https://dweet.io/play/

  created 15 Feb 2016
  updated 22 Jan 2019
  by Tom Igoe

  this example is in the public domain
*/
#define ETHERNET

#define EN_MARCHA 0
#define EN_BIFURCACION 1
#define ESPERANDO_DECISION 2

#include <ArduinoHttpClient.h>
#include "red.h"
#include "server_requests.h"

long proximaBifuracion = 5000;
long proximoChequeoEleccion = 0;

int estado = EN_MARCHA;

void setup() {
  Ethernet.init(10);  // Most Arduino shields
  Serial.begin(9600);
  while (!Serial);
  #ifdef ETHERNET
    setupEthernet();
  #else
    setupWIFI();
  #endif

  proximaBifuracion = 0; //millis()+random(1000,8000);
}

void loop() {
  if (estado == EN_MARCHA) {    
    if (millis() > proximaBifuracion) {
      configurarTimer(10);
      proximoChequeoEleccion = millis() + 15*1000; // dentro de 15 segundos voy a chequear...
      estado = ESPERANDO_DECISION;
    } 
  } else if (estado == ESPERANDO_DECISION) {
    if (millis() > proximoChequeoEleccion) {
      // es tiempo de ver qué pasó: si devuelve 0 es izquierda, 1 es derecha
      int decision = obtenerDecision();
      ponerEnCero();
      if (decision == 0) Serial.println("Eligieron a la izquierda");
      else Serial.println("Eligieron a la derecha");

      proximaBifuracion = millis() + 15000;
      estado = EN_MARCHA;
    }
  }
 
}
