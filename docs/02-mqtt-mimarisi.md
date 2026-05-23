# MQTT Mimarisi

Bu doküman, projenin MQTT katmanını (topic stratejisi, payload formatı ve entegrasyon yaklaşımı) açıklar.

## Neden MQTT?

MQTT, düşük bant genişliği ve kesintili bağlantı senaryolarında IoT telemetri için yaygın kullanılan, hafif bir publish/subscribe protokolüdür.

Bu projede NodeMCU:
- Arduino UNO’dan seri veri alır
- JSON’a dönüştürür
- MQTT broker’a publish eder

## Topic Yapısı (Projede Kullanılan)

Projedeki mevcut kod tanımlarına göre (örnek cihaz kimliği: `device1`) topic şeması şu şekildedir:

- Kök:
  - `iot/device1/`

- Telemetri (her sensör için ayrı topic):
  - Sıcaklık: `iot/device1/temp`
  - Nem: `iot/device1/hum`
  - MQ135: `iot/device1/mq135`
  - MQ9: `iot/device1/mq9`
  - Toz: `iot/device1/dust`

> Not: Bu yapı, tek bir JSON payload yerine sensörleri ayrı topic’lere ayırır. Telegraf tarafında her topic için ayrı parse/field map yapılması gerekebilir.

## QoS / Retain Önerileri

- Telemetri: QoS 0 (yüksek frekanslı ölçümlerde tercih edilebilir)
- Durum/heartbeat (varsa): QoS 1, retain=true

## Örnek MQTT Payload (Öneri)

Proje topic’leri sensör bazlı ayrıldığı için pratikte payload şu şekilde sade olabilir:

- `iot/device1/temp`

```json
{ "temperatureC": 24.1 }
```

- `iot/device1/hum`

```json
{ "humidity": 48.0 }
```

- `iot/device1/mq135`

```json
{ "adc": 512, "score": 0.62 }
```

- `iot/device1/mq9`

```json
{ "adc": 438, "score": 0.41 }
```

- `iot/device1/dust`

```json
{ "adc": 376, "pm25EstimateUgM3": 18.4 }
```

## Payload Tasarım Notları

- `adc`: ham analog okuma (0..1023 gibi)
- `score`: kalibrasyonsuz göreli bir skor (0..1). İleride kalibrasyon ile ppm/µg/m³ dönüşebilir.
- Zaman damgası ihtiyacı varsa iki yaklaşım:
  - Telegraf’ın alım zamanını timestamp olarak kullanmak
  - Payload içine `ts` alanı eklemek (epoch)
