/*
   Arquivo: aplicativo.h
   Autor: Carolina Imianosky
   Função do arquivo: biblioteca para interface com o aplicativo
   Criado em 07 dez 2020
   Modificado em 09 dez 2020
*/

#ifndef ESTUFAINTELIGENTE_H
#define ESTUFAINTELIGENTE_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <DHT_U.h>
#include <BlynkSimpleEsp32.h>
#include <time.h>

#include "regador.h"
#include "lampada.h"
#include "ventilador.h"

#define BLYNK_PRINT Serial
#define DHTTYPE DHT11 // Define o modelo de sensor como DHT 22

#define BLYNK_GRAY   "#7a7a7a"
#define BLYNK_BLACK  "#000000"
#define BLYNK_PURPLE "#5F7EDA"
#define BLYNK_WHITE  "#ffffff"

#define auth "KjRjRY08vK7yx-8ZGu26c7vg6uqHyjZM";     // autenticacao BlynkApp
#define ssid "Carol"                                 // autenticacao wifi
#define pass "di020927"


#endif /*ESTUFAINTELIGENTE_H*/
