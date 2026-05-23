# iot-air-quality-monitor — IoT Hava Kalitesi İzleme Sistemi

[![Language](https://img.shields.io/badge/language-C%2B%2B-00599C?logo=c%2B%2B)](#)
[![Platform](https://img.shields.io/badge/platform-Arduino%20UNO-00979D?logo=arduino)](#)
[![Platform](https://img.shields.io/badge/platform-ESP8266-000000)](#)
[![Messaging](https://img.shields.io/badge/MQTT-Mosquitto-660066?logo=eclipse-mosquitto)](#)
[![Pipeline](https://img.shields.io/badge/pipeline-MQTT%20%E2%86%92%20Telegraf%20%E2%86%92%20InfluxDB%20v2%20%E2%86%92%20Grafana-2ea44f)](#)
[![License](https://img.shields.io/badge/license-MIT-green)](#lisans)

Bu proje, **Arduino UNO + NodeMCU ESP8266** tabanlı bir **IoT Hava Kalitesi İzleme Sistemi**’dir.

- Arduino UNO sensör okumalarını yapar ve **SoftwareSerial** ile NodeMCU’ya aktarır.
- NodeMCU ESP8266 veriyi **JSON** formatına çevirip **MQTT (Mosquitto)** üzerinden yayınlar.
- **Telegraf**, MQTT mesajlarını tüketerek veriyi **InfluxDB v2**’ye yazar.
- **Grafana** ile veriler görselleştirilir.

> Not: Grafana tarafındaki görselleştirme başarıyla yapılmıştır; ancak donanım prototipi demo sonrasında söküldüğü için aynı koşullarda tekrar telemetri üretilip ekran görüntüsü alınamamıştır. Bu repo, mimari + firmware + veri hattı dokümantasyonu odaklı sunulmaktadır.

## İçindekiler

- [Sistem Özeti](#sistem-özeti)
- [Özellikler](#özellikler)
- [Kullanılan Teknolojiler](#kullanılan-teknolojiler)
- [Donanım Bileşenleri](#donanım-bileşenleri)
- [İletişim ve Veri Akışı](#iletişim-ve-veri-akışı)
- [Sistem Mimarisi (ASCII)](#sistem-mimarisi-ascii)
- [MQTT Mimarisi](#mqtt-mimarisi)
  - [MQTT Topic Yapısı](#mqtt-topic-yapısı)
  - [Örnek MQTT JSON Verisi](#örnek-mqtt-json-verisi)
- [Bağlantı Açıklamaları](#bağlantı-açıklamaları)
- [Örnek Seri Monitör Çıktısı](#örnek-seri-monitör-çıktısı)
- [Kurulum Rehberi](#kurulum-rehberi)
  - [MQTT Broker (Mosquitto)](#mqtt-broker-mosquitto)
  - [InfluxDB v2 Entegrasyonu](#influxdb-v2-entegrasyonu)
  - [Telegraf (MQTT → InfluxDB)](#telegraf-mqtt--influxdb)
  - [Grafana](#grafana)
- [Grafana Ekran Görüntüleri Neden Yok?](#grafana-ekran-görüntüleri-neden-yok)
- [Gelecek Geliştirmeler](#gelecek-geliştirmeler)
- [Katkıda Bulunma](#katkıda-bulunma)
- [Lisans](#lisans)

---

## Sistem Özeti

- **Arduino UNO**: Sensör okumaları + seri paketleme
- **NodeMCU ESP8266**: WiFi + MQTT publish (JSON)
- **Mosquitto**: MQTT broker
- **Telegraf**: MQTT consumer + parse + InfluxDB yazımı
- **InfluxDB v2**: Zaman serisi veri tabanı
- **Grafana**: Dashboard ve görselleştirme

---

## Özellikler

- DHT11 ile **sıcaklık/nem** ölçümü
- MQ135 ile **hava kalitesi** (analog okuma / göreli değer)
- MQ9 ile **CO / gaz** algılama (analog okuma / göreli değer)
- GP2Y1014AU ile **toz yoğunluğu** (PM2.5 tahmini için analog ölçüm)
- Arduino UNO ↔ NodeMCU arasında **SoftwareSerial** haberleşme
- MQTT üzerinden **JSON payload** yayınlama
- Telegraf ile MQTT’den InfluxDB v2’ye yazım
- Grafana ile görselleştirme

---

## Kullanılan Teknolojiler

- Gömülü: Arduino UNO, NodeMCU ESP8266
- Dil: C/C++ (Arduino framework)
- Haberleşme: SoftwareSerial, UART
- IoT: MQTT (Mosquitto)
- Veri formatı: JSON
- Veri hattı: Telegraf
- Veri tabanı: InfluxDB v2
- Görselleştirme: Grafana

> `infrastructure/docker/` klasörü **opsiyonel** bir kolay demo altyapısıdır. Bu proje pratikte Docker kullanılmadan da kurulabilir.

---

## Donanım Bileşenleri

- Arduino UNO (ana sensör kontrol kartı)
- NodeMCU ESP8266 (WiFi + MQTT köprüsü)
- Sensörler
  - DHT11 (Temperature/Humidity)
  - MQ135 (Air Quality)
  - MQ9 (CO / Gas)
  - GP2Y1014AU (Dust sensor, PM2.5 tahmini)

Detaylar için: `docs/01-donanim.md`

---

## İletişim ve Veri Akışı

Arduino UNO → NodeMCU → MQTT → Telegraf → InfluxDB v2 → Grafana

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
          |                                            |  Mosquitto       |
          |                                            |  MQTT Broker     |
          |                                            +--------+---------+
          |                                                     |
          |                                                     | Telegraf (MQTT Consumer)
          |                                                     v
          |                                            +------------------+
          |                                            |   InfluxDB v2    |
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

### MQTT Topic Yapısı

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

Aşağıdaki adımlar, **Docker kullanmadan** (yani native kurulumla) kurulumu hedefler. İsterseniz `infrastructure/docker/` altında opsiyonel Docker Compose iskeleti de mevcuttur.

### MQTT Broker (Mosquitto)

- Mosquitto’yu kurun ve çalıştırın.
- Varsayılan port: `1883`

Hızlı test (subscribe):

```bash
mosquitto_sub -h <broker-ip> -t 'iot/air-quality/#' -v
```

### InfluxDB v2 Entegrasyonu

- InfluxDB v2 kurulumunu tamamlayın.
- UI üzerinden **Org**, **Bucket** ve **Token** oluşturun.

Detaylar: `docs/03-influxdb-kurulum.md`

### Telegraf (MQTT → InfluxDB)

- Telegraf’ı kurun.
- `inputs.mqtt_consumer` ile ilgili topic’i dinleyin.
- `outputs.influxdb_v2` ile InfluxDB v2’ye yazın.

Detaylar: `docs/03-influxdb-kurulum.md`

### Grafana

- Grafana’yı kurun.
- Data Source olarak InfluxDB v2 ekleyin.
- Dashboard panellerini oluşturun.

Detaylar: `docs/04-grafana-kurulum.md`

---

## Grafana Ekran Görüntüleri Neden Yok?

Grafana üzerinde görselleştirme **başarıyla** yapılmış olsa da, donanım prototipi demo süreci sonrasında söküldüğü için aynı koşullarda tekrar telemetri üretilip ekran görüntüsü alınamamıştır.

Bu nedenle repo, ekran görüntülerinden ziyade:
- mimari tasarım
- firmware yaklaşımı
- MQTT/InfluxDB/Grafana veri hattı dokümantasyonu

odaklı sunulmaktadır.

---

## Gelecek Geliştirmeler

- Sensör kalibrasyonu ve gerçek birimlere dönüşüm (ppm / µg/m³)
- MQTT QoS/retain stratejisinin netleştirilmesi
- Offline buffer (WiFi/MQTT kesintilerinde veri kaybını azaltma)
- Grafana dashboard export/provisioning dosyalarının eklenmesi
- OTA (ESP8266) güncelleme desteği

---

## Katkıda Bulunma

1. Fork’layın
2. Yeni bir branch oluşturun: `feature/<kisa-aciklama>`
3. Değişikliklerinizi commit edin
4. Pull Request açın

---

## Lisans

MIT
