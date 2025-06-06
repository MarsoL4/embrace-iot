#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <DHTesp.h>
#include <PubSubClient.h>

// Configurações de WiFi
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

// Configurações de MQTT
const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "esp32_embrace";
const char *TOPIC_PUBLISH = "/embrace/sensores";

// Pinos
#define PINO_DHT 12         // DHT22 (Temperatura e Umidade)
#define PINO_LED 15         // LED de emergência
#define PINO_CHUVA 14       // Botão (pressionado = chovendo)
#define PINO_SOLO 33        // Potenciômetro (Umidade do Solo)

#define INTERVALO_ENVIO 3000

WiFiClient espClient;
PubSubClient mqttClient(espClient);
DHTesp dht;

unsigned long ultimoEnvio = 0;
const int TAMANHO_JSON = 256;

void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado! IP: " + WiFi.localIP().toString());
}

void conectarMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (mqttClient.connect(ID_MQTT)) {
      Serial.println("conectado.");
    } else {
      Serial.print("erro: ");
      Serial.print(mqttClient.state());
      Serial.println(" tentando novamente em 2s...");
      delay(2000);
    }
  }
}

void verificarConexoes() {
  if (WiFi.status() != WL_CONNECTED) conectarWiFi();
  if (!mqttClient.connected()) conectarMQTT();
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, LOW);
  pinMode(PINO_CHUVA, INPUT);
  dht.setup(PINO_DHT, DHTesp::DHT22);
  conectarWiFi();
  mqttClient.setServer(BROKER_MQTT, BROKER_PORT);
}

void loop() {
  verificarConexoes();
  mqttClient.loop();

  if (millis() - ultimoEnvio >= INTERVALO_ENVIO) {
    ultimoEnvio = millis();

    TempAndHumidity leitura = dht.getTempAndHumidity();
    int leitura_solo = analogRead(PINO_SOLO);

    // Converte o valor lido (0–4095) para uma escala de 0–100 (%)
    int umidade_solo = map(leitura_solo, 0, 4095, 0, 100);
    umidade_solo = constrain(umidade_solo, 0, 100);  // Garante que fique entre 0 e 100

    bool estaChovendo = digitalRead(PINO_CHUVA) == HIGH;

    bool risco = (
      !isnan(leitura.humidity) &&
      leitura.humidity > 85 &&
      estaChovendo &&
      umidade_solo > 80
    );

    digitalWrite(PINO_LED, risco ? HIGH : LOW);

    StaticJsonDocument<TAMANHO_JSON> doc;
    doc["temperatura"] = leitura.temperature;
    doc["umidade"] = leitura.humidity;
    doc["chuva"] = estaChovendo ? "SIM" : "NAO";
    doc["umidade_solo"] = umidade_solo;
    doc["alerta"] = risco ? "PERIGO" : "NORMAL";

    char buffer[TAMANHO_JSON];
    serializeJson(doc, buffer);
    mqttClient.publish(TOPIC_PUBLISH, buffer);
    Serial.println(buffer);
  }
}
