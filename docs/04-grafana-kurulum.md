# Grafana Kurulum ve Dashboard Yaklaşımı (InfluxDB v2)

Bu doküman, InfluxDB v2 verilerinin Grafana’da görselleştirilmesi için önerilen adımları ve dashboard yaklaşımını özetler.

## Kurulum

Grafana’yı işletim sisteminize göre kurun ve çalıştırın.

> Bu projede Docker kullanılmadan kurulum da desteklenir. `infrastructure/docker/` klasörü sadece opsiyonel demo amaçlıdır.

## Data Source (InfluxDB v2)

Grafana arayüzünde:

1. **Connections / Data sources** → **Add data source**
2. **InfluxDB** seçin
3. Query language olarak genelde **Flux** kullanılır (InfluxDB v2)
4. Aşağıdaki bilgileri girin:

- **URL**: `http://<INFLUXDB_IP>:8086`
- **Organization**: `EnvSensors`
- **Token**: (InfluxDB v2 API Token)
- **Default bucket**: `SensorData`

## Dashboard Önerileri

Önerilen panel seti:

- **Sıcaklık (°C)** — `temperatureC`
- **Nem (%)** — `humidity`
- **PM2.5 tahmini (µg/m³)** — `pm25EstimateUgM3`
- **MQ135 ADC / score** — `adc`, `score`
- **MQ9 ADC / score** — `adc`, `score`

> Not: ADC/score gibi alan adları, MQTT payload’unuzdaki JSON alan isimleriyle birebir aynı olmalıdır.

## Ekran Görüntüleri Notu

Grafana üzerinde görselleştirme **başarıyla** yapılmış olsa da, donanım prototipi demo süreci sonrasında söküldüğü için aynı koşullarda tekrar telemetri üretilip ekran görüntüsü alınamamıştır.

Bu nedenle repo, ekran görüntülerinden ziyade:
- mimari tasarım
- firmware yaklaşımı
- Mosquitto + Telegraf + InfluxDB v2 + Grafana veri hattı dokümantasyonu

odaklı sunulmaktadır.
