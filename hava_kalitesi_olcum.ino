#include <DHT.h>
#include <SoftwareSerial.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ135_PIN A0
#define MQ9_PIN   A1
#define DUST_LED_PIN 7
#define DUST_PIN A2

SoftwareSerial mySerial(2, 3); // RX, TX (D2=RX, D3=TX → NodeMCU’ya gidiyor)

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  dht.begin();
  pinMode(DUST_LED_PIN, OUTPUT);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  int mq135_adc = analogRead(MQ135_PIN);
  int mq9_adc   = analogRead(MQ9_PIN);

  digitalWrite(DUST_LED_PIN, LOW);
  delayMicroseconds(280);
  int dustVal = analogRead(DUST_PIN);
  digitalWrite(DUST_LED_PIN, HIGH);
  delayMicroseconds(9680);

  float Vout = dustVal * (5.0 / 1023.0);
  float dustDensity = (Vout - 0.6) / 0.005;
  if (dustDensity < 0) dustDensity = 0;

  // JSON formatında string oluştur
  String data = "{";
  data += "\"temp\":" + String(t,1) + ",";
  data += "\"hum\":" + String(h,1) + ",";
  data += "\"mq135\":" + String(mq135_adc) + ",";
  data += "\"mq9\":" + String(mq9_adc) + ",";
  data += "\"dust\":" + String(dustDensity*1000,1);
  data += "}";

  Serial.println(data);    // PC’ye
  mySerial.println(data);  // NodeMCU’ya gönder

  delay(2000);
}
