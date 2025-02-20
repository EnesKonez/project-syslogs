#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>  // Windows i�in _getcwd fonksiyonu 

#define MAX_SATIR 1024  // Maksimum sat�r uzunlu�u (log sat�rlar� i�in)



// �ift y�nl� ba�l� liste d���m yap�s�
typedef struct Dugum {
    char log_satiri[MAX_SATIR]; // Log sat�r�n� tutan dizi
    struct Dugum* onceki; // �nceki d���me i�aret�i
    struct Dugum* sonraki; // Sonraki d���me i�aret�i
} Dugum;

// Yeni d���m olu�turma fonksiyonu
Dugum* dugumOlustur(char* satir) {
    Dugum* yeniDugum = (Dugum*)malloc(sizeof(Dugum)); // Yeni d���m i�in bellek tahsis et
    if (!yeniDugum) { // Bellek tahsis edilemezse hata mesaj� ver ve ��k
        perror("Bellek tahsis hatasi");
        exit(1);
    }
    strncpy(yeniDugum->log_satiri, satir, MAX_SATIR); // Log sat�r�n� d���me kopyala
    yeniDugum->log_satiri[MAX_SATIR - 1] = '\0'; // G�venlik i�in sonland�r�c� karakter ekle
    yeniDugum->onceki = NULL; // Ba�lang��ta �nceki d���m yok
    yeniDugum->sonraki = NULL; // Ba�lang��ta sonraki d���m yok
    return yeniDugum; // Olu�turulan d���m� d�nd�r
}

// �ift y�nl� ba�l� listeye eleman ekleme (sona ekleme)
void sonaEkle(Dugum** bas, char* satir) {
    Dugum* yeniDugum = dugumOlustur(satir); // Yeni d���m olu�tur
    if (*bas == NULL) { // E�er liste bo�sa, yeni d���m ba� d���m olur
        *bas = yeniDugum;
        return;
    }
    
    Dugum* gecici = *bas;
    while (gecici->sonraki != NULL) { // Listenin sonuna kadar git
        gecici = gecici->sonraki;
    }
    gecici->sonraki = yeniDugum; // Yeni d���m� listenin sonuna ekle
    yeniDugum->onceki = gecici; // Yeni d���m�n �nceki i�aret�isini g�ncelle
}

// Ba�l� listeyi ekrana yazd�rma (hem ileri hem geri y�nl�)
void listeyiYazdir(Dugum* bas) {
    Dugum* gecici = bas;
    printf("\nLog Kayitlari (Ileri Yonlu):\n");
    while (gecici != NULL) { // Listeyi ba�tan sona yazd�r
        printf("%s", gecici->log_satiri);
        if (gecici->sonraki == NULL) break; // Son d���me ula��ld���nda dur
        gecici = gecici->sonraki;
    }

    printf("\nLog Kayitlari (Geri Yonlu):\n");
    while (gecici != NULL) { // Listeyi sondan ba�a do�ru yazd�r
        printf("%s", gecici->log_satiri);
        gecici = gecici->onceki;
    }
}

// Ba�l� listeyi bellekten temizleme (bellek s�z�nt�s�n� �nlemek i�in)
void listeyiTemizle(Dugum* bas) {
    Dugum* gecici;
    while (bas != NULL) {
        gecici = bas;
        bas = bas->sonraki;
        free(gecici); // Bellekten kald�r
    }
}

// Log dosyas�na veri ekleme fonksiyonu
void logEkle(const char* mesaj) {
    FILE* dosya = fopen("C:\\Users\\Enes\\Desktop\\Enes\\algoritma\\log.txt", "a"); // Dosyay� ekleme modunda a�
    if (dosya == NULL) { // Dosya a��lamazsa hata ver
        perror("Log dosyasi acilamadi");
        return;
    }
    fprintf(dosya, "%s\n", mesaj); // Dosyaya mesaj� yaz
    fclose(dosya); // Dosyay� kapat
}

int main() {
    // Mevcut �al��ma dizinini ekrana yazd�r
    char dizin[1024];
    if (_getcwd(dizin, sizeof(dizin)) != NULL) {
        printf("Mevcut calisma dizini: %s\n", dizin);
    } else {
        perror("Dizin alinamadi");
    }

    // Log dosyas�n� a� (okuma modunda)
    FILE* dosya = fopen("C:\\Users\\Enes\\Desktop\\Enes\\algoritma\\log.txt", "r");
    if (dosya == NULL) {
        perror("Log dosyasi acilamadi");
        return 1;
    }

    Dugum* logListesi = NULL; // Ba�l� liste ba�lang��ta bo�
    char satir[MAX_SATIR]; // Log sat�rlar�n� ge�ici olarak tutmak i�in

    // Dosyay� sat�r sat�r oku ve ba�l� listeye ekle
    while (fgets(satir, MAX_SATIR, dosya)) {
        sonaEkle(&logListesi, satir);
    }

    fclose(dosya); // Dosyay� kapat

    // Ba�l� listeyi yazd�r
    listeyiYazdir(logListesi);

    // Belle�i temizle
    listeyiTemizle(logListesi);

    // �rnek log mesajlar� ekle
    logEkle("[INFO] Program baslatildi.");
    logEkle("[ERROR] Baglanti hatasi olustu.");
    
    return 0;
}

