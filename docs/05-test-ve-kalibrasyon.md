# Test, Kalibrasyon ve Ölçüm Kalitesi

Bu doküman, sensör ölçümlerinin doğruluğu ve sistemin kararlılığı açısından temel önerileri içerir.

## DHT11

- DHT11 düşük maliyetli bir sensördür; hassasiyet sınırlıdır.
- Daha iyi hassasiyet için DHT22/AM2302 gibi alternatifler değerlendirilebilir.

## MQ135 / MQ9

- MQ serisi sensörler ısıtıcı içerir ve ısınma süresi gerektirir.
- Ortam sıcaklığı/nem değişimleri ölçümü etkileyebilir.
- Portföy amaçlı prototiplerde “göreli skor” yaklaşımı tercih edilebilir.

## GP2Y1014AU

- Toz sensörü okuması; hava akışı, optik hazne temizliği ve ışık kirliliğinden etkilenebilir.
- LED sürme zamanlaması ve analog okuma anı doğru ayarlanmalıdır.

## Önerilen Test Senaryoları

- Boşta ortam ölçümü (baseline)
- Kapalı ortamda kısa süreli aerosol/partikül artışı simülasyonu
- MQ sensörlerinde farklı gaz kaynaklarına kontrollü yaklaşım

> Güvenlik notu: Gaz/aerosol testleri iyi havalandırılan ortamda yapılmalıdır.
