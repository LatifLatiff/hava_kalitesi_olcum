# Grafana Kurulum ve Dashboard Yaklaşımı

Bu doküman, InfluxDB verilerinin Grafana’da görselleştirilmesi için önerilen adımları ve dashboard yaklaşımını özetler.

## Kurulum

Grafana’yı Docker ile çalıştırmanız önerilir. `infrastructure/docker/docker-compose.yml` içinde birlikte konumlandırılabilir.

Genel kullanım:

```bash
docker compose up -d
```

## Data Source

- Data Source tipi: InfluxDB
- Bağlantı: InfluxDB URL + Token + Bucket

## Dashboard Önerileri

- Zaman serisi paneller:
  - Sıcaklık (°C)
  - Nem (%)
  - PM2.5 tahmini (µg/m³)
  - MQ135 / MQ9 ham ADC ve göreli skorlar
- Durum panelleri:
  - RSSI
  - Heartbeat / son veri zamanı

## Ekran Görüntüleri Notu

Grafana üzerinde görselleştirme **başarıyla** yapılmış olsa da, donanım prototipi demo süreci sonrasında söküldüğü için aynı koşullarda tekrar telemetri üretilip ekran görüntüsü alınamamıştır.

Bu nedenle repo, ekran görüntülerinden ziyade:
- mimari tasarım
- firmware yaklaşımı
- veri hattı dokümantasyonu

odaklı sunulmaktadır.
