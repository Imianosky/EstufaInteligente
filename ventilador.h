/*
   Arquivo: ventilador.h
   Autor: Carolina Imianosky
   Função do arquivo: biblioteca para configurar o ventilador
   Criado em 20 nov 2020
   Modificado em 05 dez 2020
*/

#ifndef VENTILADOR_H
#define VENTILADOR_H

#include <Arduino.h>

// Biblioteca para utilizacao do sensor de umidade
#include <DHT.h>
#include <DHT_U.h>

// Pinos da esp32
#define PIN_VENTILADOR1        5
#define PIN_VENTILADOR2        18
#define PIN_ENABLE_VENTILADOR  19
#define PIN_SENSOR_TEMPERATURA 02

// Configurações da PMW
#define FREQ_V        30000
#define PMW_CHANNEL_V 0
#define RESOLUTION_V  8
#define DUTY_CYCLE_V  220

// Define o modelo de sensor como DHT 22
#define DHTTYPE DHT11

// ON e OFF LED aplicativo
#define ON  255
#define OFF 0

// Prototipo das funcoes
float leSensorTemp(DHT dht);
void  ativaVentilador();
void  desativaVentilador();
int   automVentilador(int temperaturaMax, DHT dht, int *estadoVentilador);


#endif /*VENTILADOR_H*/
