# InfluxDB Kurulum ve Entegrasyon

Bu doküman, MQTT telemetrisinin InfluxDB’ye yazılması için önerilen yaklaşımı özetler.

## Önerilen Veri Akışı

```text
NodeMCU (MQTT JSON) -> MQTT Broker -> Telegraf (MQTT Consumer) -> InfluxDB
```

Telegraf; MQTT topic’lerini dinleyip JSON payload’u parse ederek InfluxDB’ye yazar.

## Docker ile Hızlı Kurulum (Önerilen)

> Bu repo altında `infrastructure/docker/docker-compose.yml` örnek bir iskelet sunar.

Genel kullanım:

```bash
docker compose up -d
```

## InfluxDB Temel Kavramlar

- **Org / Bucket / Token**: erişim ve veri organizasyonu
- **Measurement / Field / Tag**: zaman serisi veri modeli

## Şema Önerisi

- measurement: `air_quality`
- tags:
  - `deviceId`
  - `location` (opsiyonel)
- fields:
  - `temperatureC`, `humidity`
  - `mq135_adc`, `mq135_score`
  - `mq9_adc`, `mq9_score`
  - `pm25EstimateUgM3`, `dust_adc`
  - `rssi`

## Doğrulama

- InfluxDB UI üzerinden bucket’a veri gelip gelmediğini kontrol edin.
- Hatalarda `docs/99-sorun-giderme.md` dokümanına bakın.
