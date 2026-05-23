# InfluxDB v2 Kurulum ve Entegrasyon (Telegraf ile)

Bu doküman, MQTT telemetrisinin **Telegraf** aracılığıyla **InfluxDB v2**’ye yazılması için pratik ve portföy odaklı bir yaklaşım sunar.

## Önerilen Veri Akışı

```text
NodeMCU (MQTT) -> Mosquitto (MQTT Broker) -> Telegraf (MQTT Consumer) -> InfluxDB v2 -> Grafana
```

## InfluxDB v2 Hazırlık

1. InfluxDB v2 kurulumunu tamamlayın.
2. UI üzerinden aşağıdakileri oluşturun:
   - **Organization (Org)**
   - **Bucket**
   - **API Token** (read/write)

Projede kullanılan örnek değerler:

- Org: `EnvSensors`
- Bucket: `SensorData`

> Token’ı repoya commit etmeyin. `.env` veya işletim sistemi secret mekanizmalarıyla saklayın.

## Telegraf Kurulumu

Telegraf’ı işletim sisteminize göre kurun (Linux/Windows/macOS).

## Telegraf Konfigürasyonu (Örnek)

Aşağıdaki örnek, projedeki topic yapısına göre (`iot/device1/...`) MQTT’den veri alıp InfluxDB v2’ye yazmayı hedefler.

> Önemli: JSON payload formatı ve topic eşleşmeleri, sizin publish formatınızla birebir aynı olmalıdır.

```toml
# =========================================
# INPUT: MQTT Consumer
# =========================================
[[inputs.mqtt_consumer]]
  servers = ["tcp://<BROKER_IP>:1883"]
  topics  = [
    "iot/device1/temp",
    "iot/device1/hum",
    "iot/device1/mq135",
    "iot/device1/mq9",
    "iot/device1/dust"
  ]
  qos = 0
  connection_timeout = "30s"

  # JSON parse
  data_format = "json"

  # Her topic için ayrı measurement yazmak isterseniz topic_parsing kullanabilirsiniz.
  # Basit portföy yaklaşımı: tek measurement + topic tag.
  topic_tag = "topic"

  # Öneri: sabit deviceId tag
  [inputs.mqtt_consumer.tags]
    deviceId = "device1"


# =========================================
# OUTPUT: InfluxDB v2
# =========================================
[[outputs.influxdb_v2]]
  urls = ["http://<INFLUXDB_IP>:8086"]
  token = "$INFLUX_TOKEN"
  organization = "EnvSensors"
  bucket = "SensorData"
```

### Notlar

- Payload’lar sensör bazlı ayrıldığı için InfluxDB’de alanlar (fields) topic’e göre oluşur.
  - Örn. `temp` topic’i: `temperatureC`
  - `mq135` topic’i: `adc`, `score`
- İsterseniz `topic_parsing` ile topic parçalarını tag’lere ayırıp daha temiz bir şema kurabilirsiniz.

## Doğrulama

1. Mosquitto üzerinden topic’leri dinleyin:

```bash
mosquitto_sub -h <BROKER_IP> -t 'iot/device1/#' -v
```

2. Telegraf loglarını kontrol edin.
3. InfluxDB UI üzerinden bucket’ta veri görünüyor mu kontrol edin.

Sorunlarda: `docs/99-sorun-giderme.md`
