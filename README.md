# iot-air-quality-monitor — IoT Hava Kalitesi İzleme Sistemi

[![Language](https://img.shields.io/badge/language-C%2B%2B-00599C?logo=c%2B%2B)](#)
[![Platform](https://img.shields.io/badge/platform-Arduino%20UNO-00979D?logo=arduino)](#)
[![Platform](https://img.shields.io/badge/platform-ESP8266-000000)](#)
[![Messaging](https://img.shields.io/badge/MQTT-supported-660066?logo=eclipse-mosquitto)](#)
[![Time%20Series](https://img.shields.io/badge/InfluxDB-integrated-22ADF6?logo=influxdb)](#)
[![Observability](https://img.shields.io/badge/Grafana-visualized-F46800?logo=grafana)](#)
[![License](https://img.shields.io/badge/license-MIT-green)](#lisans)

Bu proje, **Arduino UNO + NodeMCU ESP8266** tabanlı bir **IoT Hava Kalitesi İzleme Sistemi**’dir. Arduino UNO sensör okumalarını yapar, NodeMCU ESP8266 bu verileri **MQTT** üzerinden yayınlar. Veriler **InfluxDB**’ye yazılır ve **Grafana** ile görselleştirilir.

> Not: Grafana tarafındaki görselleştirme başarıyla yapılmıştır; ancak donanım prototipi demo sonrasında söküldüğü için aynı koşullarda tekrar telemetri üretilip ekran görüntüsü alınamamıştır. Bu repo, mimari + firmware + veri hattı dokümantasyonu odaklı sunulmaktadır.

## İçindekiler

- [Sistem Özeti](#sistem-özeti)
- [Özellikler](#özellikler)
- [Kullanılan Teknolojiler](#kullanılan-teknolojiler)
- [Donanım Bileşenleri](#donanım-bileşenleri)
- [İletişim ve Veri Akışı](#iletişim-ve-veri-akışı)
- [Sistem Mimarisi (ASCII)](#sistem-mimarisi-ascii)
- [MQTT Mimarisi](#mqtt-mimarisi)
  - [Topic Yapısı](#topic-yapısı)
  - [Örnek MQTT JSON Verisi](#örnek-mqtt-json-verisi)
- [Bağlantı Açıklamaları](#bağlantı-açıklamaları)
- [Örnek Seri Monitör Çıktısı](#örnek-seri-monitör-çıktısı)
- [Kurulum Rehberi](#kurulum-rehberi)
  - [MQTT Broker Kurulumu](#mqtt-broker-kurulumu)
  - [InfluxDB Entegrasyonu](#influxdb-entegrasyonu)
  - [Grafana](#grafana)
- [Gelecek Geliştirmeler](#gelecek-geliştirmeler)
- [Katkıda Bulunma](#katkıda-bulunma)
- [Lisans](#lisans)

---

## Sistem Özeti

- **Arduino UNO**: Sensör okumaları, temel filtreleme/ölçekleme ve seri paketleme
- **NodeMCU ESP8266**: WiFi bağlantısı + MQTT istemcisi (seri porttan gelen veriyi JSON’a çevirip publish eder)
- **InfluxDB**: Zaman serisi veri tabanı (telemetri depolama)
- **Grafana**: Dashboard ve görselleştirme

---

## Özellikler

- DHT11 ile **sıcaklık/nem** ölçümü
- MQ135 ile **hava kalitesi** (analog okuma / göreli değer)
- MQ9 ile **CO / gaz** algılama (analog okuma / göreli değer)
- GP2Y1014AU ile **toz yoğunluğu** (PM2.5 tahmini için analog ölçüm)
- Arduino UNO ↔ NodeMCU arasında **SoftwareSerial** haberleşme
- MQTT üzerinden **JSON payload** yayınlama
- InfluxDB + Grafana hattında uçtan uca veri görselleştirme

---

## Kullanılan Teknolojiler

- Gömülü: Arduino UNO, NodeMCU ESP8266
- Dil: C/C++ (Arduino framework)
- Haberleşme: SoftwareSerial, UART
- IoT: MQTT
- Veri formatı: JSON
- Veri tabanı: InfluxDB
- Görselleştirme: Grafana
- (Opsiyonel) Docker Compose ile hızlı altyapı ayağa kaldırma

---

## Donanım Bileşenleri

- Arduino UNO (ana sensör kontrol kartı)
- NodeMCU ESP8266 (WiFi + MQTT köprüsü)
- Sensörler
  - DHT11 (Temperature/Humidity)
  - MQ135 (Air Quality / VOC benzeri gazlara duyarlı)
  - MQ9 (CO / Gas)
  - GP2Y1014AU (Dust sensor, PM2.5 tahmini)

Detaylar için: `docs/01-donanim.md`

---

## İletişim ve Veri Akışı

**Arduino UNO ↔ NodeMCU**: SoftwareSerial ile paketlenmiş ölçüm verisi

**NodeMCU → MQTT**: JSON publish

**MQTT → InfluxDB → Grafana**: veri toplama ve görselleştirme hattı

---

## Sistem Mimarisi (ASCII)

```text
+-------------------+        SoftwareSerial        +---------------------------+
|   Arduino UNO     |  <-------------------------> |     NodeMCU ESP8266       |
|  (Sensor Node)    |                              | (WiFi + MQTT Bridge)      |
|                   |                              |                           |
| DHT11             |                              | MQTT Client (Publish)     |
| MQ135             |                              +-------------+-------------+
| MQ9               |                                            |
| GP2Y1014AU        |                                            | MQTT (JSON)
+---------+---------+                                            v
          |                                            +------------------+
          |                                            |   MQTT Broker    |
          |                                            | (Mosquitto vb.)  |
          |                                            +--------+---------+
          |                                                     |
          |                                                     | Telegraf/Consumer
          |                                                     v
          |                                            +------------------+
          |                                            |     InfluxDB     |
          |                                            +--------+---------+
          |                                                     |
          |                                                     v
          |                                            +------------------+
          +--------------------------------------------|     Grafana      |
                                                       +------------------+
```

Ayrıca: `diagrams/architecture-ascii.txt`

---

## MQTT Mimarisi

NodeMCU, Arduino’dan gelen seri veriyi doğrular, alanları ayrıştırır ve **tek bir JSON payload** olarak MQTT’ye yayınlar.

Detaylar için: `docs/02-mqtt-mimarisi.md`

### Topic Yapısı

- Telemetri:
  - `iot/air-quality/telemetry/<deviceId>`
- Durum/heartbeat:
  - `iot/air-quality/status/<deviceId>`
- Komut (opsiyonel):
  - `iot/air-quality/cmd/<deviceId>`

### Örnek MQTT JSON Verisi

Örnek payload: `examples/mqtt-payload.json`

---

## Bağlantı Açıklamaları

Elektriksel ve pin bağlantı notları için: `docs/01-donanim.md`

---

## Örnek Seri Monitör Çıktısı

Örnek çıktı: `examples/serial-monitor-output.txt`

---

## Kurulum Rehberi

### MQTT Broker Kurulumu

Geliştirme için en pratik yol: **Eclipse Mosquitto**.

Docker ile hızlı kurulum:

```bash
cd infrastructure/docker
docker compose up -d
```

### InfluxDB Entegrasyonu

Yaklaşım ve şema önerisi:
- `docs/03-influxdb-kurulum.md`

### Grafana

Kurulum ve dashboard yaklaşımı:
- `docs/04-grafana-kurulum.md`

---

## Gelecek Geliştirmeler

- Sensör kalibrasyonu ve gerçek birimlere dönüşüm (ppm / µg/m³)
- OTA (ESP8266) güncelleme desteği
- MQTT QoS/retain stratejisinin netleştirilmesi
- Offline buffer (WiFi/MQTT kesintilerinde veri kaybını azaltma)
- Dashboard JSON export/import ile otomatik Grafana provision

---

## Katkıda Bulunma

1. Fork’layın
2. Yeni bir branch oluşturun: `feature/<kisa-aciklama>`
3. Değişikliklerinizi commit edin
4. Pull Request açın

---

## Lisans

Bu proje açık kaynak olarak paylaşılmaktadır.

- Önerilen lisans: **MIT**
- `LICENSE` dosyasını ekleyerek netleştirmeniz tavsiye edilir.
