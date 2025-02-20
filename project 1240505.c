#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>  // Windows için _getcwd fonksiyonu 

#define MAX_SATIR 1024  // Maksimum satýr uzunluðu (log satýrlarý için)



// Çift yönlü baðlý liste düðüm yapýsý
typedef struct Dugum {
    char log_satiri[MAX_SATIR]; // Log satýrýný tutan dizi
    struct Dugum* onceki; // Önceki düðüme iþaretçi
    struct Dugum* sonraki; // Sonraki düðüme iþaretçi
} Dugum;

// Yeni düðüm oluþturma fonksiyonu
Dugum* dugumOlustur(char* satir) {
    Dugum* yeniDugum = (Dugum*)malloc(sizeof(Dugum)); // Yeni düðüm için bellek tahsis et
    if (!yeniDugum) { // Bellek tahsis edilemezse hata mesajý ver ve çýk
        perror("Bellek tahsis hatasi");
        exit(1);
    }
    strncpy(yeniDugum->log_satiri, satir, MAX_SATIR); // Log satýrýný düðüme kopyala
    yeniDugum->log_satiri[MAX_SATIR - 1] = '\0'; // Güvenlik için sonlandýrýcý karakter ekle
    yeniDugum->onceki = NULL; // Baþlangýçta önceki düðüm yok
    yeniDugum->sonraki = NULL; // Baþlangýçta sonraki düðüm yok
    return yeniDugum; // Oluþturulan düðümü döndür
}

// Çift yönlü baðlý listeye eleman ekleme (sona ekleme)
void sonaEkle(Dugum** bas, char* satir) {
    Dugum* yeniDugum = dugumOlustur(satir); // Yeni düðüm oluþtur
    if (*bas == NULL) { // Eðer liste boþsa, yeni düðüm baþ düðüm olur
        *bas = yeniDugum;
        return;
    }
    
    Dugum* gecici = *bas;
    while (gecici->sonraki != NULL) { // Listenin sonuna kadar git
        gecici = gecici->sonraki;
    }
    gecici->sonraki = yeniDugum; // Yeni düðümü listenin sonuna ekle
    yeniDugum->onceki = gecici; // Yeni düðümün önceki iþaretçisini güncelle
}

// Baðlý listeyi ekrana yazdýrma (hem ileri hem geri yönlü)
void listeyiYazdir(Dugum* bas) {
    Dugum* gecici = bas;
    printf("\nLog Kayitlari (Ileri Yonlu):\n");
    while (gecici != NULL) { // Listeyi baþtan sona yazdýr
        printf("%s", gecici->log_satiri);
        if (gecici->sonraki == NULL) break; // Son düðüme ulaþýldýðýnda dur
        gecici = gecici->sonraki;
    }

    printf("\nLog Kayitlari (Geri Yonlu):\n");
    while (gecici != NULL) { // Listeyi sondan baþa doðru yazdýr
        printf("%s", gecici->log_satiri);
        gecici = gecici->onceki;
    }
}

// Baðlý listeyi bellekten temizleme (bellek sýzýntýsýný önlemek için)
void listeyiTemizle(Dugum* bas) {
    Dugum* gecici;
    while (bas != NULL) {
        gecici = bas;
        bas = bas->sonraki;
        free(gecici); // Bellekten kaldýr
    }
}

// Log dosyasýna veri ekleme fonksiyonu
void logEkle(const char* mesaj) {
    FILE* dosya = fopen("C:\\Users\\Enes\\Desktop\\Enes\\algoritma\\log.txt", "a"); // Dosyayý ekleme modunda aç
    if (dosya == NULL) { // Dosya açýlamazsa hata ver
        perror("Log dosyasi acilamadi");
        return;
    }
    fprintf(dosya, "%s\n", mesaj); // Dosyaya mesajý yaz
    fclose(dosya); // Dosyayý kapat
}

int main() {
    // Mevcut çalýþma dizinini ekrana yazdýr
    char dizin[1024];
    if (_getcwd(dizin, sizeof(dizin)) != NULL) {
        printf("Mevcut calisma dizini: %s\n", dizin);
    } else {
        perror("Dizin alinamadi");
    }

    // Log dosyasýný aç (okuma modunda)
    FILE* dosya = fopen("C:\\Users\\Enes\\Desktop\\Enes\\algoritma\\log.txt", "r");
    if (dosya == NULL) {
        perror("Log dosyasi acilamadi");
        return 1;
    }

    Dugum* logListesi = NULL; // Baðlý liste baþlangýçta boþ
    char satir[MAX_SATIR]; // Log satýrlarýný geçici olarak tutmak için

    // Dosyayý satýr satýr oku ve baðlý listeye ekle
    while (fgets(satir, MAX_SATIR, dosya)) {
        sonaEkle(&logListesi, satir);
    }

    fclose(dosya); // Dosyayý kapat

    // Baðlý listeyi yazdýr
    listeyiYazdir(logListesi);

    // Belleði temizle
    listeyiTemizle(logListesi);

    // Örnek log mesajlarý ekle
    logEkle("[INFO] Program baslatildi.");
    logEkle("[ERROR] Baglanti hatasi olustu.");
    
    return 0;
}

