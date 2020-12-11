/*
   Arquivo: lampada.h
   Autor: Carolina Imianosky
   Função do arquivo: biblioteca para configurar a lampada
   Criado em 07 dez 2020
   Modificado em 07 dez 2020
*/

#ifndef LAMPADA_H
#define LAMPADA_H

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>

// Pinos da esp32
#define PIN_LED          22
#define PIN_SENSOR_LDR   35

// ON e OFF LED aplicativo
#define ON  255
#define OFF 0

// Prototipo das funcoes
int  leSensorLuminosidade();
void ativaLampada();
void desativaLampada();
int  automLampada(int luminosidadeMin,  int *estadoLampada);


#endif /*VENTILADOR_H */
