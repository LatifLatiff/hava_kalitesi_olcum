# Hava Kalitesi Ölçüm (C++)

Bu depo, C++ ile geliştirilmiş **hava kalitesi ölçüm/izleme** projesini içerir. Projenin amacı; sensör verilerini okuyup işleyerek hava kalitesine dair temel metrikleri hesaplamak, ekrana/seri porta yazdırmak ve (varsa) kayıt altına almaktır.

> Not: Bu README, depodaki mevcut kaynak koda göre genel bir şablondur. Sensör modeli, pin bağlantıları ve çıktı formatı gibi detaylar projedeki kod/konfigürasyona göre güncellenmelidir.

## Özellikler

- Sensör/veri kaynağından ölçüm okuma
- Ölçüm değerlerini filtreleme/ortalama alma (varsa)
- Hava kalitesi göstergesi/indeksi hesaplama (varsa)
- Seri port/terminal çıktısı
- (Opsiyonel) Dosyaya kayıt / loglama

## Gereksinimler

- C++ derleyicisi
  - Linux/macOS: `g++` veya `clang++`
  - Windows: MSVC (Visual Studio) veya MinGW
- (Varsa) Projede kullanılan ek kütüphaneler

## Kurulum

Depoyu klonlayın:

```bash
git clone https://github.com/LatifLatiff/hava_kalitesi_olcum.git
cd hava_kalitesi_olcum
```

## Derleme ve Çalıştırma

### Basit derleme (tek dosya ise)

> Kaynak dosya adını projeye göre değiştirin (ör. `main.cpp`).

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o hava_kalitesi main.cpp
./hava_kalitesi
```

### Birden fazla dosya ise

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o hava_kalitesi *.cpp
./hava_kalitesi
```

### CMake (varsa)

Depoda `CMakeLists.txt` bulunuyorsa:

```bash
cmake -S . -B build
cmake --build build
./build/hava_kalitesi
```

## Kullanım

Uygulama çalıştırıldığında sensör/veri kaynağından belirli aralıklarla ölçüm alır ve sonucu terminale yazdırır.

Örnek çıktı (temsili):

```text
PM2.5: 12 µg/m³ | PM10: 20 µg/m³ | AQI: 42 (Good)
```

## Yapılandırma

Aşağıdaki ayarlar projede mevcutsa, ilgili dosyalardan düzenlenebilir:

- Ölçüm periyodu (ms/sn)
- Kalibrasyon katsayıları
- Seri port ayarları (baud rate vb.)
- Log dosyası yolu

## Proje Yapısı (Öneri)

> Depodaki gerçek yapıya göre güncelleyin.

- `src/` : Kaynak kodlar
- `include/` : Başlık dosyaları
- `data/` : Örnek veri/çıktılar
- `docs/` : Dokümantasyon

## Katkıda Bulunma

1. Fork’layın
2. Yeni bir branch oluşturun: `git checkout -b feature/degisiklik`
3. Değişikliklerinizi commit edin: `git commit -m "..."`
4. Push edin: `git push origin feature/degisiklik`
5. Pull Request açın

## Lisans

Bu proje için lisans bilgisi belirtilmemişse, bir lisans dosyası eklemeniz önerilir (örn. MIT, Apache-2.0).

---

İletişim / Sorular: GitHub Issues üzerinden paylaşabilirsiniz.
