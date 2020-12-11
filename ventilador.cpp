/*
   Arquivo: ventilador.c
   Autor: Carolina Imianosky
   Função do arquivo: configurar o ventilador
   Criado em 20 nov 2020
   Modificado em 05 dez 2020
*/

#include "ventilador.h"

float leSensorTemp(DHT dht) {
  return dht.readTemperature();
}

void ativaVentilador() {
  ledcWrite(PMW_CHANNEL_V, DUTY_CYCLE_V);
  digitalWrite(PIN_VENTILADOR1, LOW);
  digitalWrite(PIN_VENTILADOR2, HIGH);
}

void desativaVentilador() {
  digitalWrite(PIN_VENTILADOR1, LOW);
  digitalWrite(PIN_VENTILADOR2, LOW);
}

int automVentilador(int temperaturaMax, DHT dht, int *estadoVentilador) {
  int temperaturaEstufa = leSensorTemp(dht);
  if (temperaturaEstufa > temperaturaMax) {
    ativaVentilador();
    *estadoVentilador = ON;
  } else {
    desativaVentilador();
    *estadoVentilador = OFF;
  }
  return temperaturaEstufa;
}
