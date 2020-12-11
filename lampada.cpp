/*
   Arquivo: lampada.c
   Autor: Carolina Imianosky
   Função do arquivo: configurar a lampada
   Criado em 07 dez 2020
   Modificado em 07 dez 2020
*/

#include "lampada.h"

int leSensorLuminosidade() {
  return analogRead(PIN_SENSOR_LDR);
}

void ativaLampada() {
  digitalWrite(PIN_LED, 1);
}

void desativaLampada() {
  digitalWrite(PIN_LED, 0);
}

int automLampada(int luminosidadeMin, int *estadoLED) {
  int luminosidadeEstufa = leSensorLuminosidade();
  if (luminosidadeEstufa < luminosidadeMin) {
    ativaLampada();
    *estadoLED = ON;
  } else {
    desativaLampada();
    *estadoLED = OFF;
  }
  return luminosidadeEstufa;
}
