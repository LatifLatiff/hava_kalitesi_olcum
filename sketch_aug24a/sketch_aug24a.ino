#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// === UNO Haberleşme için Yazılım Serial ===
SoftwareSerial unoSerial(D7, D8); // RX = D7, TX = D8

// === WiFi Bilgileri ===
const char* ssid = "TP-LINK_FFAE";
const char* password = "75850951";

// === MQTT Broker (HiveMQ Public Broker) ===
const char* mqtt_server = "192.168.0.106";
const int mqtt_port = 1883;
const char* mqtt_client_id = "NodeMCU_Client_01";

// === MQTT Konuları (topic) ===
const char* base_topic = "iot/device1/";
const char* temp_topic = "iot/device1/temp";
const char* hum_topic  = "iot/device1/hum";
const char* mq135_topic = "iot/device1/mq135";
const char* mq9_topic   = "iot/device1/mq9";
const char* dust_topic  = "iot/device1/dust";

// === MQTT Nesneleri ===
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("WiFi bağlanılıyor: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi bağlantısı başarılı!");
  Serial.print("IP Adresi: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT bağlantısı kuruluyor...");
    if (client.connect(mqtt_client_id)) {
      Serial.println("Bağlandı!");
    } else {
      Serial.print("Hata, rc=");
      Serial.print(client.state());
      Serial.println(" 5 sn sonra tekrar denenecek");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);        // PC debug için
  unoSerial.begin(9600);     // UNO ile haberleşme
  Serial.println("NodeMCU hazır, UNO verisi bekleniyor...");

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // === UNO’dan veri okuma ===
  if (unoSerial.available()) {
    String payload = unoSerial.readStringUntil('\n');
    payload.trim();

    if (payload.length() > 0) {
      Serial.print("UNO’dan gelen veri: ");
      Serial.println(payload);

      // JSON parse
      StaticJsonDocument<256> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (error) {
        Serial.print("JSON parse hatası: ");
        Serial.println(error.c_str());
        return;
      }

      // Verileri ayır
      float temp = doc["temp"];
      float hum  = doc["hum"];
      int mq135  = doc["mq135"];
      int mq9    = doc["mq9"];
      float dust = doc["dust"];

      // Debug için ekrana yazdır
      Serial.println("=== Ayrıştırılmış Sensör Verileri ===");
      Serial.print("Sıcaklık: "); Serial.println(temp);
      Serial.print("Nem: "); Serial.println(hum);
      Serial.print("MQ135: "); Serial.println(mq135);
      Serial.print("MQ9: "); Serial.println(mq9);
      Serial.print("Toz: "); Serial.println(dust);

      // MQTT'ye publish
      client.publish(temp_topic, String(temp).c_str(), true);
      client.publish(hum_topic,  String(hum).c_str(), true);
      client.publish(mq135_topic, String(mq135).c_str(), true);
      client.publish(mq9_topic,   String(mq9).c_str(), true);
      client.publish(dust_topic,  String(dust).c_str(), true);

      Serial.println("MQTT’ye veriler gönderildi!");
      Serial.println("====================================");
    }
  }
}
