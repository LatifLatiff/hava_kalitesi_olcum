# Donanım ve Bağlantılar

Bu doküman, IoT Hava Kalitesi İzleme Sistemi’nin donanım bileşenlerini ve önerilen bağlantı yaklaşımını açıklar.

## Donanım Bileşenleri

- Arduino UNO (ana sensör kontrol kartı)
- NodeMCU ESP8266 (WiFi + MQTT köprüsü)
- Sensörler
  - DHT11 (sıcaklık/nem)
  - MQ135 (hava kalitesi / göreli analog ölçüm)
  - MQ9 (CO / gaz / göreli analog ölçüm)
  - GP2Y1014AU (toz sensörü, PM2.5 tahmini)
- Breadboard, jumper kablolar, uygun dirençler
- Stabil güç kaynağı

## İletişim Topolojisi

Arduino UNO ile NodeMCU ESP8266 arasında **SoftwareSerial** üzerinden iki yönlü haberleşme yapılır.

- Arduino UNO: Sensörleri okur, veriyi paketler
- NodeMCU: Bu paketi alır, JSON’a çevirir ve MQTT’ye yayınlar

## Elektriksel Uyarılar (Önemli)

- NodeMCU ESP8266 **3.3V** lojik seviyesinde çalışır. Arduino UNO tarafı **5V** seviyesindedir.
  - RX/TX hatlarında tasarımınıza göre seviye dönüştürücü/voltaj bölücü gerekebilir.
- MQ serisi sensörler ısıtıcı içerir ve görece yüksek akım çekebilir.
  - Güç kaynağının stabil olması, ölçüm kararlılığı için kritiktir.

## Pin Haritalama

> Bu repo, farklı prototiplerde değişebilir pin seçimlerine izin verecek şekilde yapılandırılmıştır. Kesin pin haritasını firmware altındaki README dosyalarında sabitlemeniz önerilir:
>
> - `firmware/arduino-uno-sensor-node/README.md`
> - `firmware/nodemcu-esp8266-mqtt-bridge/README.md`

Öneri (temsili):

- Arduino UNO
  - DHT11: D2
  - MQ135: A0
  - MQ9: A1
  - GP2Y1014AU: A2 (+ LED sürme pini gerekiyorsa D3)
  - SoftwareSerial: D10 (RX), D11 (TX)

- NodeMCU ESP8266
  - SoftwareSerial / UART: D5 (RX), D6 (TX) *(veya kartınıza uygun pinler)*

## Seri Paket Formatı

Önerilen yaklaşım:
- UNO → ESP: tek satır, ayrıştırması kolay, alan adları sabit

Örnek:

```text
t=24.1;h=48.0;mq135=512;mq9=438;dust_adc=376;pm25=18.4
```

NodeMCU bu satırı JSON’a çevirip MQTT publish eder.
