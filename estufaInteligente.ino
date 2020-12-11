/*
   Arquivo: estufaInteligente.ino
   Autor: Carolina Imianosky
   Função do arquivo: main
   Criado em 20 nov 2020
   Modificado em 09 dez 2020
*/

#include "estufaInteligente.h"

//DHT irá interpretar os valores de leitura do pino de acordo com o tipo de sensor
DHT dht(PIN_SENSOR_TEMPERATURA, DHTTYPE);

BlynkTimer timer;

int   buttonVentilador, buttonRegador, buttonLED, buttonFunc;
int   temperaturaMax, umidadeMin, luminosidadeMin;
int   estadoRegador, estadoVentilador, estadoLED;
float temperaturaEstufa;
int   umidadeEstufa, luminosidadeEstufa;

void atualizaApp(){
  Blynk.virtualWrite(V20, temperaturaEstufa);
  Blynk.virtualWrite(V21, umidadeEstufa);
  Blynk.virtualWrite(V22, luminosidadeEstufa);
  Blynk.virtualWrite(V12, estadoLED);
  Blynk.virtualWrite(V13, estadoVentilador);
  Blynk.virtualWrite(V14, estadoRegador);
}

void estufaInteligente(){
  if (buttonFunc == 1){
    umidadeEstufa      = automRegador    (umidadeMin,      &estadoRegador);
    luminosidadeEstufa = automLampada    (luminosidadeMin, &estadoLED);
    temperaturaEstufa  = automVentilador (temperaturaMax,  dht, &estadoVentilador);

  }else{
    umidadeEstufa       = leSensorUmidade();
    luminosidadeEstufa  = leSensorLuminosidade();
    //temperaturaEstufa = leSensorTemp(dht);
  }

  atualizaApp();
}

void setup() {
  
  // sets the pins as outputs:
  pinMode(PIN_REGADOR1,       OUTPUT);
  pinMode(PIN_REGADOR2,       OUTPUT);
  pinMode(PIN_ENABLE_REGADOR, OUTPUT);
  pinMode(PIN_LED,            OUTPUT);

  // configura funcionalidades do LED do PWM
  ledcSetup(PMW_CHANNEL_R, FREQ_R, RESOLUTION_R);
  ledcSetup(PMW_CHANNEL_V, FREQ_V, RESOLUTION_V);

  // atribui o canal para os GPIOS  a serem controlados
  ledcAttachPin(PIN_ENABLE_REGADOR,    PMW_CHANNEL_R);
  ledcAttachPin(PIN_ENABLE_VENTILADOR, PMW_CHANNEL_V);
  
  dht.begin();

  Serial.begin(115200);
  delay(10);

  // conexao com wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Blynk.begin("KjRjRY08vK7yx-8ZGu26c7vg6uqHyjZM", ssid, pass);

  timer.setInterval(1000L, estufaInteligente);
}

void loop() {
  Blynk.run();
  timer.run();
  delay(5);
}


// @brief: controle do input luminosidade minima
BLYNK_WRITE(V1) { luminosidadeMin  = param.asInt(); }

// @brief: controle do input temperatura maxima
BLYNK_WRITE(V3) { temperaturaMax   = param.asInt(); }

// @brief: controle do input umidade minima
BLYNK_WRITE(V5) { umidadeMin       = param.asInt(); }

// @brief: controle do botao virtual on/off LED
BLYNK_WRITE(V0) { buttonLED        = param.asInt(); }

// @brief: controle do botao virtual on/off Ventilador
BLYNK_WRITE(V2) { buttonVentilador = param.asInt(); }

// @brief: controle do botao virtual on/off regador
BLYNK_WRITE(V4) { buttonRegador    = param.asInt(); }

//@brief: controle do botao de funcionamento
BLYNK_WRITE(V6) {
  buttonFunc = param.asInt();              // virtualButton recebe o valor do botao no app
  if(buttonFunc){

    desativaLampada();
    desativaRegador();
    desativaVentilador();

    Blynk.virtualWrite(V1,  0);
    Blynk.virtualWrite(V3,  0);
    Blynk.virtualWrite(V4,  0);

    Blynk.setProperty(V0, "onLabel"     , "OFF");
    Blynk.setProperty(V0, "offLabel"    , "OFF");
    Blynk.setProperty(V0, "onColor"     , BLYNK_GRAY);
    Blynk.setProperty(V0, "offColor"    , BLYNK_GRAY);
    Blynk.setProperty(V0, "onBackColor" , BLYNK_BLACK);
    Blynk.setProperty(V0, "offBackColor", BLYNK_BLACK);

    Blynk.setProperty(V2, "onLabel"     , "OFF");
    Blynk.setProperty(V2, "offLabel"    , "OFF");
    Blynk.setProperty(V2, "onColor"     , BLYNK_GRAY);
    Blynk.setProperty(V2, "offColor"    , BLYNK_GRAY);
    Blynk.setProperty(V2, "onBackColor" , BLYNK_BLACK);
    Blynk.setProperty(V2, "offBackColor", BLYNK_BLACK);

    Blynk.setProperty(V4, "onLabel"     , "OFF");
    Blynk.setProperty(V4, "offLabel"    , "OFF");
    Blynk.setProperty(V4, "onColor"     , BLYNK_GRAY);
    Blynk.setProperty(V4, "offColor"    , BLYNK_GRAY);
    Blynk.setProperty(V4, "onBackColor" , BLYNK_BLACK);
    Blynk.setProperty(V4, "offBackColor", BLYNK_BLACK);

  }else{ //manual

    desativaLampada();
    desativaRegador();
    desativaVentilador();

    Blynk.virtualWrite(V1,  0);
    Blynk.virtualWrite(V3,  0);
    Blynk.virtualWrite(V4,  0);

    Blynk.setProperty(V0, "onLabel"     , "ON" );
    Blynk.setProperty(V0, "offLabel"    , "OFF");
    Blynk.setProperty(V0, "onColor"     , BLYNK_WHITE);
    Blynk.setProperty(V0, "offColor"    , BLYNK_BLACK);
    Blynk.setProperty(V0, "onBackColor" , BLYNK_PURPLE);
    Blynk.setProperty(V0, "offBackColor", BLYNK_PURPLE);

    Blynk.setProperty(V2, "onLabel"     , "ON" );
    Blynk.setProperty(V2, "offLabel"    , "OFF");
    Blynk.setProperty(V2, "onColor"     , BLYNK_WHITE);
    Blynk.setProperty(V2, "offColor"    , BLYNK_BLACK);
    Blynk.setProperty(V2, "onBackColor" , BLYNK_PURPLE);
    Blynk.setProperty(V2, "offBackColor", BLYNK_PURPLE);

    Blynk.setProperty(V4, "onLabel"     , "ON" );
    Blynk.setProperty(V4, "offLabel"    , "OFF");
    Blynk.setProperty(V4, "onColor"     , BLYNK_WHITE);
    Blynk.setProperty(V4, "offColor"    , BLYNK_BLACK);
    Blynk.setProperty(V4, "onBackColor" , BLYNK_PURPLE);
    Blynk.setProperty(V4, "offBackColor", BLYNK_PURPLE);
  }
}
