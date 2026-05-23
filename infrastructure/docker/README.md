# Docker Altyapısı

Bu klasör, geliştirme/portföy demosu için aşağıdaki bileşenleri Docker ile hızlıca ayağa kaldırmayı amaçlar:

- MQTT Broker (Mosquitto)
- InfluxDB (v2)
- Grafana

## Çalıştırma

```bash
docker compose up -d
```

## Erişim Bilgileri

- Mosquitto: `localhost:1883`
- InfluxDB UI: `http://localhost:8086`
- Grafana: `http://localhost:3000`

## Güvenlik Notu

`docker-compose.yml` içinde örnek kullanıcı/şifre/token değerleri bulunur. Gerçek kullanımda mutlaka değiştirin.
