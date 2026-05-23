# Arduino UNO — Sensor Node Firmware

Bu modül, **Arduino UNO** üzerinde çalışan sensör okuma firmware’ini temsil eder.

## Sorumluluklar

- DHT11, MQ135, MQ9, GP2Y1014AU sensörlerinden ölçüm almak
- Basit filtreleme/ölçekleme (opsiyonel)
- Ölçümü seri paket formatında NodeMCU’ya göndermek

## Yapılandırma

- Sensör pinleri
- Ölçüm periyodu
- Seri haberleşme hızı (baud rate)

## Seri Paket Formatı (Öneri)

```text
t=24.1;h=48.0;mq135=512;mq9=438;dust_adc=376;pm25=18.4
```

> Kesin format firmware kodu ile birebir aynı olmalıdır.
