# NodeMCU ESP8266 — MQTT Bridge Firmware

Bu modül, **NodeMCU ESP8266** üzerinde çalışan WiFi + MQTT köprü firmware’ini temsil eder.

## Sorumluluklar

- Arduino UNO’dan **SoftwareSerial** ile telemetri satırı almak
- Satırı parse edip JSON payload üretmek
- MQTT broker’a bağlanmak ve publish etmek
- (Opsiyonel) heartbeat/status mesajı yayınlamak

## MQTT

- Telemetri topic:
  - `iot/air-quality/telemetry/<deviceId>`
- Status topic:
  - `iot/air-quality/status/<deviceId>`

## Yapılandırma

- WiFi SSID/Password
- MQTT broker host/port
- `deviceId` ve `location`

## Debug

Seri monitörde bağlantı adımlarını ve publish işlemlerini loglamanız önerilir.
