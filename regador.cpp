/*
   Arquivo: regador.c
   Autor: Carolina Imianosky
   Função do arquivo: configurar o regador
   Criado em 20 nov 2020
   Modificado em 05 dez 2020
*/

#include "regador.h"

float leSensorUmidade() {
  float aux = map(analogRead(PIN_SENSOR_UMIDADE), 4095, 1023, 0, 100);
  return  aux;
}

void ativaRegador() {
  ledcWrite(PMW_CHANNEL_R, DUTY_CYCLE_R);
  digitalWrite(PIN_REGADOR1, LOW);
  digitalWrite(PIN_REGADOR2, HIGH);
}

void desativaRegador() {
  digitalWrite(PIN_REGADOR1, LOW);
  digitalWrite(PIN_REGADOR2, LOW);
}

float automRegador(int umidadeMin, int *estadoRegador) {
  float umidadeEstufa = leSensorUmidade();
  if (umidadeEstufa < umidadeMin) {
    ativaRegador();
    *estadoRegador = ON;
  } else {
    desativaRegador();
    *estadoRegador = OFF;
  }
  return umidadeEstufa;
}
