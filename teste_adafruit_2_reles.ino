#include <ESP8266WiFi.h>
#include "AdafruitIO_WiFi.h"
#include "AdafruitIO.h"

#define LED1 D1
#define LED2 D0

char ssid[] = "brisa-2704049";
char pass[] = "cvetbicz";

// Crie uma instância da biblioteca WiFiClient para se comunicar com o Adafruit IO.
WiFiClient client;

// Substitua com suas informações de autenticação do Adafruit IO.
AdafruitIO_WiFi io("arthurprogpy", "aio_RFUe722UIQ051j0GPaauurnCzdBg", ssid, pass);

// Crie uma instância dos feeds do Adafruit IO para os LEDs.
AdafruitIO_Feed *led1 = io.feed("relay2");
AdafruitIO_Feed *led2 = io.feed("relay1");

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Conecte-se à rede Wi-Fi.
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Conecte-se ao Adafruit IO.
  io.connect();

  // Aguarde a conexão ser estabelecida.
  while (io.status() < AIO_CONNECTED) {
    delay(500);
  }

  // Inscreva-se nos feeds do Adafruit IO para os LEDs.
  led1->onMessage(handleLED1);
  led2->onMessage(handleLED2);
}

void loop() {
  // Mantenha a conexão com o Adafruit IO ativa.
  io.run();
}

// Função de tratamento para o feed do LED 1.
void handleLED1(AdafruitIO_Data *data) {
  int valor = data->toInt();

if(data->isTrue()){
    digitalWrite(LED1,HIGH);
  }
  else{
    digitalWrite(LED1,LOW);
  }
}

// Função de tratamento para o feed do LED 2.
void handleLED2(AdafruitIO_Data *data) {
  int valor = data->toInt();

  // Atualize o estado do LED 2.
  if(data->isTrue()){
    digitalWrite(LED2,HIGH);
  }
  else{
    digitalWrite(LED2,LOW);
  }
}
