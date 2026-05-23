# Sorun Giderme (Troubleshooting)

## 1) NodeMCU WiFi’ye bağlanamıyor

- SSID/Password doğru mu?
- 2.4GHz ağ mı? (ESP8266 genelde 2.4GHz ile çalışır)
- Güç kaynağı yeterli mi?

## 2) MQTT bağlantısı kurulamıyor

- Broker IP/port doğru mu? (varsayılan 1883)
- Broker çalışıyor mu?
- Ağ içinde port erişimi var mı?

## 3) InfluxDB’ye veri yazılmıyor

- Telegraf/consumer çalışıyor mu?
- Topic filtreleri doğru mu?
- Token/Bucket/Org doğru mu?

## 4) Grafana paneli boş

- Data Source bağlantısı doğru mu?
- Sorgu time range uygun mu?
- Measurement/field isimleri gerçekten o isimlerle yazılıyor mu?

## 5) UNO ↔ ESP seri veri bozuk

- Baud rate aynı mı?
- Seviye farkı (5V ↔ 3.3V) sorun çıkarıyor olabilir
- Kablo/ground ortak mı?
