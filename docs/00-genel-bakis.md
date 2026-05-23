# IoT Hava Kalitesi İzleme Sistemi — Repository Genel Bakış

Bu doküman, `hava_kalitesi_olcum` deposunun **IoT Hava Kalitesi İzleme Sistemi** portföy yapısını ve klasörlerin amacını özetler.

## Amaç

Bu repo; Arduino UNO + NodeMCU ESP8266 tabanlı hava kalitesi izleme projesinin:

- Firmware kaynak kodlarını
- MQTT/InfluxDB/Grafana veri hattı kurulum yönergelerini
- Örnek payload/komut dosyalarını
- Diyagramları ve teknik dokümantasyonu

tek bir yerde, profesyonel bir yapıda sunmayı hedefler.

## Klasörler

- `firmware/`
  - `arduino-uno-sensor-node/`: Sensör okuma ve seri paketleme (UNO)
  - `nodemcu-esp8266-mqtt-bridge/`: WiFi + MQTT köprüsü (ESP8266)

- `infrastructure/`
  - `docker/`: Mosquitto + InfluxDB + Grafana için Docker Compose
  - `influxdb/`: InfluxDB başlangıç notları ve (ops.) init
  - `grafana/`: Dashboard/provisioning iskeleti

- `docs/`: Detaylı teknik dokümantasyon
- `examples/`: Örnek MQTT payload, publish scriptleri, seri çıktı örnekleri
- `diagrams/`: ASCII diyagram ve (ops.) drawio dosyaları

## Not

Bu repo portföy amaçlıdır. MQ serisi sensörler ve toz sensörü doğru sonuçlar için kalibrasyon gerektirebilir.
