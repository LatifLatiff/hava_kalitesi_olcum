# MQTT Mimarisi

Bu doküman, projenin MQTT katmanını (topic stratejisi, payload formatı ve entegrasyon yaklaşımı) açıklar.

## Neden MQTT?

MQTT, düşük bant genişliği ve kesintili bağlantı senaryolarında IoT telemetri için yaygın kullanılan, hafif bir publish/subscribe protokolüdür.

Bu projede NodeMCU:
- Arduino UNO’dan seri veri alır
- JSON’a dönüştürür
- MQTT broker’a publish eder

## Topic Yapısı

Önerilen topic şeması:

- Telemetri:
  - `iot/air-quality/telemetry/<deviceId>`
- Durum / heartbeat:
  - `iot/air-quality/status/<deviceId>`
- Komut (opsiyonel):
  - `iot/air-quality/cmd/<deviceId>`

Örnek:
- `iot/air-quality/telemetry/lab-01`
- `iot/air-quality/status/lab-01`

## QoS / Retain Önerileri

- Telemetri: QoS 0 (yüksek frekanslı ölçümlerde tercih edilebilir)
- Durum/heartbeat: QoS 1, retain=true (son bilinen durumun saklanması için)

> Portföy amaçlı prototiplerde QoS stratejisi ihtiyaca göre değiştirilebilir.

## Örnek MQTT JSON Payload

```json
{
  "deviceId": "lab-01",
  "ts": 1716462000,
  "location": "ofis",
  "dht11": {
    "temperatureC": 24.1,
    "humidity": 48.0
  },
  "mq135": {
    "adc": 512,
    "score": 0.62
  },
  "mq9": {
    "adc": 438,
    "score": 0.41
  },
  "dust": {
    "adc": 376,
    "pm25EstimateUgM3": 18.4
  },
  "rssi": -61,
  "firmware": {
    "uno": "1.0.0",
    "esp8266": "1.0.0"
  }
}
```

## Payload Tasarım Notları

- `adc`: ham analog okuma (0..1023 gibi)
- `score`: kalibrasyonsuz göreli bir skor (0..1). İleride kalibrasyon ile ppm/µg/m³ dönüşebilir.
- `ts`: epoch time (saniye). Alternatif olarak ISO-8601 de kullanılabilir.
