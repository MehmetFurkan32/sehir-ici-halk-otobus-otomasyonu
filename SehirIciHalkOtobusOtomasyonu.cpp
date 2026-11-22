#include <stdio.h>
#include <stdlib.h>
#include <string.h>




struct Sefer {
    int    seferNo;
    char   hatNo[10];
    char   guzergah[100];
    char   kalkisSaati[10];
    char   varisSaati[10];
    int    kapasite;
    int    doluluk;
    char   soforAdi[50];
    struct Sefer *sonraki;
};

typedef struct Sefer Sefer;




void ekranTemizle() {
    system("cls");
}

void baslik() {
    printf("============================================================\n");
    printf("   ISPARTA SEHIR ICI HALK OTOBUSU PLANLAMA OTOMASYONU\n");
    printf("============================================================\n\n");
}

void bekle() {
    printf("\nDevam etmek icin bir tusa basin...");
    fflush(stdin);
    getchar();
}


//  KAYIT EKLEME

Sefer* kayitEkle(Sefer *bas, Sefer yeniSefer) {
    Sefer *yeni = (Sefer*) malloc(sizeof(Sefer));
    if (yeni == NULL) {
        printf("Bellek hatasi!\n");
        return bas;
    }
    *yeni = yeniSefer;
    yeni->sonraki = NULL;

    if (bas == NULL) {
        return yeni;
    }

    Sefer *tmp = bas;
    while (tmp->sonraki != NULL) {
        tmp = tmp->sonraki;
    }
    tmp->sonraki = yeni;
    return bas;
}

Sefer* kayitEkleMenu(Sefer *bas) {
    ekranTemizle();
    baslik();
    printf("--- KAYIT EKLEME ---\n\n");

    Sefer yeni;
    memset(&yeni, 0, sizeof(Sefer));
    yeni.sonraki = NULL;

    printf("Sefer No       : "); scanf("%d",  &yeni.seferNo);  fflush(stdin);
    printf("Hat No         : "); scanf("%9s",   yeni.hatNo);    fflush(stdin);
    printf("Guzergah       : "); fgets(yeni.guzergah, 100, stdin);
    yeni.guzergah[strcspn(yeni.guzergah, "\n")] = '\0';
    printf("Kalkis Saati   : "); scanf("%9s",  yeni.kalkisSaati); fflush(stdin);
    printf("Varis  Saati   : "); scanf("%9s",  yeni.varisSaati);  fflush(stdin);
    printf("Kapasite       : "); scanf("%d",  &yeni.kapasite);    fflush(stdin);
    printf("Doluluk        : "); scanf("%d",  &yeni.doluluk);     fflush(stdin);
    printf("Sofor Adi      : "); fgets(yeni.soforAdi, 50, stdin);
    yeni.soforAdi[strcspn(yeni.soforAdi, "\n")] = '\0';

    bas = kayitEkle(bas, yeni);
    printf("\nKayit basariyla eklendi!\n");
    bekle();
    return bas;
}


//  KAYIT LÝSTELEME

void kayitListele(Sefer *bas) {
    ekranTemizle();
    baslik();
    printf("--- TUM SEFERLER ---\n\n");

    if (bas == NULL) {
        printf("Listede hic kayit bulunmuyor.\n");
        bekle();
        return;
    }

    printf("%-6s %-8s %-28s %-8s %-8s %-8s %-6s %-20s\n",
           "No", "Hat", "Guzergah", "Kalkis", "Varis", "Kap.", "Dol.", "Sofor");
    printf("-------------------------------------------------------------------------------------------------------\n");

    Sefer *tmp = bas;
    while (tmp != NULL) {
        printf("%-6d %-8s %-28s %-8s %-8s %-8d %-6d %-20s\n",
               tmp->seferNo, tmp->hatNo, tmp->guzergah,
               tmp->kalkisSaati, tmp->varisSaati,
               tmp->kapasite, tmp->doluluk, tmp->soforAdi);
        tmp = tmp->sonraki;
    }
    printf("\n");
    bekle();
}


//  KAYIT GÜNCELLEME

Sefer* kayitGuncelle(Sefer *bas) {
    ekranTemizle();
    baslik();
    printf("--- KAYIT GUNCELLEME ---\n\n");

    if (bas == NULL) {
        printf("Listede hic kayit yok.\n");
        bekle();
        return bas;
    }

    int aranan;
    printf("Guncellenecek Sefer No: "); scanf("%d", &aranan); fflush(stdin);

    Sefer *tmp = bas;
    while (tmp != NULL) {
        if (tmp->seferNo == aranan) {
            printf("\nMevcut bilgiler gosteriliyor, yeni bilgileri girin:\n\n");
            printf("Hat No [%s]         : ", tmp->hatNo);
            fgets(tmp->hatNo, 10, stdin);
            tmp->hatNo[strcspn(tmp->hatNo, "\n")] = '\0';

            printf("Guzergah [%s]       : ", tmp->guzergah);
            fgets(tmp->guzergah, 100, stdin);
            tmp->guzergah[strcspn(tmp->guzergah, "\n")] = '\0';

            printf("Kalkis Saati [%s]   : ", tmp->kalkisSaati);
            fgets(tmp->kalkisSaati, 10, stdin);
            tmp->kalkisSaati[strcspn(tmp->kalkisSaati, "\n")] = '\0';

            printf("Varis Saati  [%s]   : ", tmp->varisSaati);
            fgets(tmp->varisSaati, 10, stdin);
            tmp->varisSaati[strcspn(tmp->varisSaati, "\n")] = '\0';

            printf("Kapasite [%d]        : ", tmp->kapasite);
            char buf[20]; fgets(buf, 20, stdin);
            if (buf[0] != '\n') tmp->kapasite = atoi(buf);

            printf("Doluluk  [%d]        : ", tmp->doluluk);
            fgets(buf, 20, stdin);
            if (buf[0] != '\n') tmp->doluluk = atoi(buf);

            printf("Sofor Adi [%s]      : ", tmp->soforAdi);
            fgets(tmp->soforAdi, 50, stdin);
            tmp->soforAdi[strcspn(tmp->soforAdi, "\n")] = '\0';

            printf("\nKayit guncellendi!\n");
            bekle();
            return bas;
        }
        tmp = tmp->sonraki;
    }
    printf("Sefer No %d bulunamadi.\n", aranan);
    bekle();
    return bas;
}


//  KAYIT SÝLME

Sefer* kayitSil(Sefer *bas) {
    ekranTemizle();
    baslik();
    printf("--- KAYIT SILME ---\n\n");

    if (bas == NULL) {
        printf("Listede hic kayit yok.\n");
        bekle();
        return bas;
    }

    int aranan;
    printf("Silinecek Sefer No: "); scanf("%d", &aranan); fflush(stdin);

    Sefer *onceki = NULL;
    Sefer *tmp    = bas;

    while (tmp != NULL) {
        if (tmp->seferNo == aranan) {
            if (onceki == NULL) {
                bas = tmp->sonraki;
            } else {
                onceki->sonraki = tmp->sonraki;
            }
            free(tmp);
            printf("Sefer No %d silindi.\n", aranan);
            bekle();
            return bas;
        }
        onceki = tmp;
        tmp    = tmp->sonraki;
    }
    printf("Sefer No %d bulunamadi.\n", aranan);
    bekle();
    return bas;
}


//  KAYIT ARAMA

void kayitAra(Sefer *bas) {
    ekranTemizle();
    baslik();
    printf("--- KAYIT ARAMA ---\n\n");

    if (bas == NULL) {
        printf("Listede hic kayit yok.\n");
        bekle();
        return;
    }

    printf("1. Sefer No ile Ara\n");
    printf("2. Hat No ile Ara\n");
    printf("3. Guzergah ile Ara\n");
    printf("Seciminiz: ");
    int sec; scanf("%d", &sec); fflush(stdin);

    int    bulundu = 0;
    Sefer *tmp     = bas;

    if (sec == 1) {
        int aranan;
        printf("Sefer No: "); scanf("%d", &aranan); fflush(stdin);
        while (tmp != NULL) {
            if (tmp->seferNo == aranan) {
                bulundu = 1;
                printf("\n--- SONUC ---\n");
                printf("Sefer No     : %d\n",  tmp->seferNo);
                printf("Hat No       : %s\n",  tmp->hatNo);
                printf("Guzergah     : %s\n",  tmp->guzergah);
                printf("Kalkis       : %s\n",  tmp->kalkisSaati);
                printf("Varis        : %s\n",  tmp->varisSaati);
                printf("Kapasite     : %d\n",  tmp->kapasite);
                printf("Doluluk      : %d\n",  tmp->doluluk);
                printf("Sofor        : %s\n",  tmp->soforAdi);
                break;
            }
            tmp = tmp->sonraki;
        }
    } else if (sec == 2) {
        char aranan[10];
        printf("Hat No: "); scanf("%9s", aranan); fflush(stdin);
        printf("\n--- SONUCLAR ---\n");
        while (tmp != NULL) {
            if (strcmp(tmp->hatNo, aranan) == 0) {
                bulundu = 1;
                printf("Sefer No: %-4d | Guzergah: %-28s | Kalkis: %-8s | Varis: %-8s | Sofor: %s\n",
                       tmp->seferNo, tmp->guzergah, tmp->kalkisSaati, tmp->varisSaati, tmp->soforAdi);
            }
            tmp = tmp->sonraki;
        }
    } else if (sec == 3) {
        char aranan[100];
        printf("Guzergah (bir kelime): "); scanf("%99s", aranan); fflush(stdin);
        printf("\n--- SONUCLAR ---\n");
        while (tmp != NULL) {
            if (strstr(tmp->guzergah, aranan) != NULL) {
                bulundu = 1;
                printf("Sefer No: %-4d | Hat: %-6s | Guzergah: %-28s | Kalkis: %-8s\n",
                       tmp->seferNo, tmp->hatNo, tmp->guzergah, tmp->kalkisSaati);
            }
            tmp = tmp->sonraki;
        }
    } else {
        printf("Gecersiz secim.\n");
        bekle();
        return;
    }

    if (!bulundu) printf("Kayit bulunamadi.\n");
    bekle();
}


//  DOSYAYA AKTAR (Binary Yazma)

void dosyayaAktar(Sefer *bas) {
    ekranTemizle();
    baslik();
    printf("--- DOSYAYA AKTAR ---\n\n");

    if (bas == NULL) {
        printf("Aktarilacak kayit yok.\n");
        bekle();
        return;
    }

    FILE *fp = fopen("seferler.bin", "wb");
    if (fp == NULL) {
        printf("Dosya acilamadi!\n");
        bekle();
        return;
    }

    
    struct SeferDosya {
        int  seferNo;
        char hatNo[10];
        char guzergah[100];
        char kalkisSaati[10];
        char varisSaati[10];
        int  kapasite;
        int  doluluk;
        char soforAdi[50];
    };
    typedef struct SeferDosya SeferDosya;

    int sayac = 0;
    Sefer *tmp = bas;
    while (tmp != NULL) {
        SeferDosya kayit;
        kayit.seferNo  = tmp->seferNo;
        memcpy(kayit.hatNo,       tmp->hatNo,       10);
        memcpy(kayit.guzergah,    tmp->guzergah,    100);
        memcpy(kayit.kalkisSaati, tmp->kalkisSaati, 10);
        memcpy(kayit.varisSaati,  tmp->varisSaati,  10);
        kayit.kapasite = tmp->kapasite;
        kayit.doluluk  = tmp->doluluk;
        memcpy(kayit.soforAdi,    tmp->soforAdi,    50);

        fwrite(&kayit, sizeof(SeferDosya), 1, fp);
        sayac++;
        tmp = tmp->sonraki;
    }

    fclose(fp);
    printf("%d kayit 'seferler.bin' dosyasina yazildi.\n", sayac);
    bekle();
}


//  DOSYADAN AL (Binary Okuma)

Sefer* dosyadanAl(Sefer *bas) {
    ekranTemizle();
    baslik();
    printf("--- DOSYADAN AL ---\n\n");

    FILE *fp = fopen("seferler.bin", "rb");
    if (fp == NULL) {
        printf("'seferler.bin' dosyasi bulunamadi. Once 'Dosyaya Aktar' kullananin.\n");
        bekle();
        return bas;
    }

    // Mevcut listeyi temizle
    Sefer *tmp = bas;
    while (tmp != NULL) {
        Sefer *sil = tmp;
        tmp = tmp->sonraki;
        free(sil);
    }
    bas = NULL;

    struct SeferDosya {
        int  seferNo;
        char hatNo[10];
        char guzergah[100];
        char kalkisSaati[10];
        char varisSaati[10];
        int  kapasite;
        int  doluluk;
        char soforAdi[50];
    };
    typedef struct SeferDosya SeferDosya;

    SeferDosya kayit;
    int sayac = 0;

    while (fread(&kayit, sizeof(SeferDosya), 1, fp) == 1) {
        Sefer yeni;
        memset(&yeni, 0, sizeof(Sefer));
        yeni.seferNo  = kayit.seferNo;
        memcpy(yeni.hatNo,       kayit.hatNo,       10);
        memcpy(yeni.guzergah,    kayit.guzergah,    100);
        memcpy(yeni.kalkisSaati, kayit.kalkisSaati, 10);
        memcpy(yeni.varisSaati,  kayit.varisSaati,  10);
        yeni.kapasite = kayit.kapasite;
        yeni.doluluk  = kayit.doluluk;
        memcpy(yeni.soforAdi,    kayit.soforAdi,    50);
        yeni.sonraki  = NULL;

        bas = kayitEkle(bas, yeni);
        sayac++;
    }

    fclose(fp);
    printf("%d kayit dosyadan okunarak listeye aktarildi.\n", sayac);
    bekle();
    return bas;
}


//  BELLEK TEMÝZLEME

void listeTemizle(Sefer *bas) {
    Sefer *tmp;
    while (bas != NULL) {
        tmp = bas;
        bas = bas->sonraki;
        free(tmp);
    }
}


//  ANA MENÜ

int main() {
    Sefer *bas = NULL;
    int secim;

    do {
        ekranTemizle();
        baslik();
        printf("  ANA MENU\n");
        printf("  --------\n");
        printf("  1. Kayit Ekle\n");
        printf("  2. Kayitlari Listele\n");
        printf("  3. Kayit Guncelle\n");
        printf("  4. Kayit Sil\n");
        printf("  5. Kayit Ara\n");
        printf("  6. Dosyaya Aktar \n");
        printf("  7. Dosyadan Al    \n");
        printf("  0. Cikis\n\n");
        printf("  Seciminiz: ");
        scanf("%d", &secim);
        fflush(stdin);

        switch (secim) {
            case 1: bas = kayitEkleMenu(bas);  break;
            case 2: kayitListele(bas);          break;
            case 3: bas = kayitGuncelle(bas);   break;
            case 4: bas = kayitSil(bas);        break;
            case 5: kayitAra(bas);              break;
            case 6: dosyayaAktar(bas);          break;
            case 7: bas = dosyadanAl(bas);      break;
            case 0:
                printf("\nCikis yapiliyor...\n");
                listeTemizle(bas);
                break;
            default:
                printf("Gecersiz secim!\n");
                bekle();
        }

    } while (secim != 0);

    return 0;
}
