/*
   Arquivo: regador.h
   Autor: Carolina Imianosky
   Função do arquivo: biblioteca para configurar o regador
   Criado em 20 nov 2020
   Modificado em 05 dez 2020
*/

#ifndef REGADOR_H
#define REGADOR_H

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>

// Pinos da esp32
#define PIN_REGADOR1        27
#define PIN_REGADOR2        26
#define PIN_ENABLE_REGADOR  14
#define PIN_SENSOR_UMIDADE  33

// Configurações da PMW
#define FREQ_R        30000
#define PMW_CHANNEL_R 0
#define RESOLUTION_R  8
#define DUTY_CYCLE_R  220

// ON e OFF LED aplicativo
#define ON  255
#define OFF 0

// Prototipo das funcoes
float leSensorUmidade();
void  ativaRegador();
void  desativaRegador();
float automRegador(int umidadeMin, int *estadoRegador);

#endif /*REGADOR_H */
