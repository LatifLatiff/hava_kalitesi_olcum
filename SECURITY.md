# Güvenlik Politikası (Security)

Bu proje, eğitim/portföy amaçlı bir IoT prototipidir. Yine de güvenlik bildirimlerini ciddiyetle ele alır.

## Desteklenen Sürümler

- Ana dal (default branch) üzerinden güncel içerik desteklenir.

## Güvenlik Açığı Bildirme

Güvenlik açığı bildirmek için:

1. Public Issue açmak yerine, mümkünse proje sahibi ile özel iletişim kurun.
2. Etkilenen bileşenleri belirtin (MQTT broker, InfluxDB, Grafana, firmware vb.)
3. Yeniden üretme adımlarını ve olası etkileri açıklayın.

## Temel Güvenlik Önerileri

- MQTT broker için kullanıcı/şifre ve TLS kullanın
- InfluxDB token’larını repoya commit etmeyin
- Docker örneklerindeki default şifre/token değerlerini mutlaka değiştirin
