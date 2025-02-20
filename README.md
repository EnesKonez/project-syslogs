# Double Linked Log

## 📌 Proje Açıklaması
**Double Linked Log**, log (günlük) verilerini saklamak, listelemek ve yönetmek için **çift yönlü bağlı liste** (double linked list) veri yapısını kullanan bir C programıdır. Program, log dosyasını okur, verileri çift yönlü bağlı listeye ekler ve logları hem ileri hem geri yönde görüntüleyebilir.

## 🚀 Özellikler
- **Çift yönlü bağlı liste kullanımı:** Loglar dinamik olarak bellekte tutulur.
- **Log dosyasını okuma ve işleme:** `log.txt` dosyasını okuyarak log kayıtlarını listeye ekler.
- **Logları ekrana yazdırma:** Logları hem ileri hem geri yönlü sıralı şekilde görüntüleyebilme.
- **Dinamik bellek yönetimi:** Kullanılan bellek, program sonunda serbest bırakılır.
- **Yeni log ekleme:** Log dosyasına yeni kayıt ekleyebilme özelliği.

## 📂 Dosya Yapısı
```
📁 double-linked-log
│── 📄 main.c           # Ana program kodu
│── 📄 log.txt          # Log dosyası
│── 📄 README.md        # Proje açıklamaları
```

## 🔧 Kurulum ve Kullanım

### 1️⃣ Gerekli Bağımlılıklar
Bu program **C dili** ile yazılmıştır. Çalıştırmak için aşağıdaki derleyicilerden birine ihtiyacın olacak:
- GCC (`MinGW` veya `Linux GCC`)
- Clang
- MSVC (Visual Studio için)

### 2️⃣ Derleme
Terminal veya komut satırında aşağıdaki komutu kullanarak kodu derleyebilirsin:
```sh
gcc main.c -o log_app
```

### 3️⃣ Çalıştırma
Derleme başarılı olduysa, aşağıdaki komutla programı çalıştırabilirsin:
```sh
./log_app
```

### 4️⃣ Log Dosyası
`log.txt` dosyası, programın çalıştırıldığı dizinde bulunmalıdır. Örnek bir içerik:
```
[INFO] Program başlatıldı.
[ERROR] Bağlantı hatası oluştu.
[DEBUG] Bellek tahsisi başarılı.
```

## 📜 Kod Açıklamaları

### 🔹 Çift Yönlü Bağlı Liste Yapısı
```c
// Çift yönlü bağlı liste düğüm yapısı
typedef struct Dugum {
    char log_satiri[MAX_SATIR];
    struct Dugum* onceki;
    struct Dugum* sonraki;
} Dugum;
```
Her düğüm bir log satırını saklar ve önceki/sonraki düğümlere işaret eden pointer'lara sahiptir.

### 🔹 Logları Bağlı Listeye Ekleme
```c
void sonaEkle(Dugum** bas, char* satir) {
    Dugum* yeniDugum = dugumOlustur(satir);
    if (*bas == NULL) {
        *bas = yeniDugum;
        return;
    }
    Dugum* gecici = *bas;
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }
    gecici->sonraki = yeniDugum;
    yeniDugum->onceki = gecici;
}
```
Log kayıtları sona eklenerek çift yönlü bir liste oluşturulur.

### 🔹 Logları Dosyaya Yazma
```c
void logEkle(const char* mesaj) {
    FILE* dosya = fopen("log.txt", "a");
    if (dosya == NULL) {
        perror("Log dosyası açılamadı");
        return;
    }
    fprintf(dosya, "%s\n", mesaj);
    fclose(dosya);
}
```
Bu fonksiyon, yeni log kayıtlarını `log.txt` dosyasına ekler.

## 🛠 Geliştirme ve Katkıda Bulunma
Bu proje açık kaynaklıdır. Katkıda bulunmak isterseniz:
1. Bu repoyu fork'layın 🍴
2. Yeni bir branch oluşturun 🌿
3. Geliştirmelerinizi yapın 🛠
4. Pull request gönderin 🚀

## 📜 Lisans
Bu proje **MIT Lisansı** altında lisanslanmıştır. Daha fazla bilgi için `LICENSE` dosyasına göz atabilirsiniz.

---
💡 **İletişim & Destek:** Bir hata bulduysanız veya önerileriniz varsa, GitHub Issues üzerinden bildirebilirsiniz! 😊

