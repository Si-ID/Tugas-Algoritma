#include <iostream>
#include <string>

using namespace std;

struct pesanan{
     string nama;
     string jenis_roti;
    float total;
};
const int MAKS = 100;
pesanan antrean[MAKS];
pesanan riwayat[MAKS];
int depan = 0;
int belakang = -1;
int jumlah_riwayat = 0;

// Fungsi menambah pesanan
void tambahPesanan(){
    if (belakang == MAKS - 1) {
        cout << "Antrean penuh, tidak bisa menambah pesanan.\n";
        return;
    }

    pesanan p;
    cout << "<========== Ambil Antrean ==========>\n";

    cin.ignore(); // Bersihkan newline sisa input sebelumnya
    cout << "Nama Pemesan: ";
    getline(cin, p.nama);

    cout << "Jenis Roti: ";
    getline(cin, p.jenis_roti);

    cout << "Total Harga: ";
    cin >> p.total;

    belakang++;
    antrean[belakang] = p;
    cout << "Pesanan atas nama \"" << p.nama << "\" telah berhasil ditambahkan ke antrean. \n";
}


void layaniPesanan(){
    if (belakang == -1) {
        cout << "Tidak ada pesanan dalam antrean.\n";
        return;
    }
    pesanan dilayani = antrean[depan];
    depan++;
    if (jumlah_riwayat < MAKS)
    {
        riwayat[jumlah_riwayat] = dilayani;
        jumlah_riwayat++;
    }
    
    cout << "Pesanan atas nama " << dilayani.nama << " telah dilayani.\n";
}

void tampilkanAntrean(){
    if (belakang == -1) {
        cout << "Tidak ada pesanan dalam antrean.\n";
        return;
    }

    cout << "<========== Daftar Antrean ==========>\n";
    for (int i = depan; i <= belakang; i++){
        cout << "Pesanan ke-" << i + 1 << ": " << endl;
        cout << "Nama Pemesan: " << antrean[i].nama << endl;
        cout << "Jenis Roti: " << antrean[i].jenis_roti << endl;
        cout << "Total Harga: " << antrean[i].total << endl;
        cout << "-------------------------------------\n";
    }

}

void batalkanPesanan(){
    string batal;
    if (belakang == -1) {
        cout << "Tidak ada pesanan dalam antrean.\n";
        return;
    }
    cout << "<========== Batalkan Pesanan ==========>\n";
    tampilkanAntrean();
    cin.ignore(); // Bersihkan newline sisa input sebelumnya
    cout << "Pesanan atas nama siapa yang ingin dibatalkan? " << endl;
    cout << "Nama Pemesan: ";
    getline(cin, batal);

    for (int i = depan; i <= belakang; i++){
        if (antrean[i].nama == batal){
            cout << "Pesanan atas nama " << batal << " telah dibatalkan.\n";
            for (int j = i; j < belakang; j++){
                antrean[j] = antrean[j+1];
            }
        }
        belakang--;
        return;
    }
    cout << "Pesanan dengan nama tersebut tidak ditemukan.\n";
} 

void tampilkanRiwayat(){
    if (jumlah_riwayat == 0) {
        cout << "Tidak ada riwayat pesanan.\n";
        return;
    }
    cout << "<========== Riwayat Pesanan ==========>\n";
    for (int i = 0; i < jumlah_riwayat; i++){
        cout << "Pesanan ke-" << i + 1 << ": " << endl;
        cout << "Nama Pemesan: " << riwayat[i].nama << endl;
        cout << "jenis Roti: " << riwayat[i].jenis_roti << endl;
        cout << "Total Harga: " << riwayat[i].total << endl;
        cout << "-------------------------------------\n";
    }
}
int main(){
    int pilihan;
    do {
        cout << "<========== Toko Roti 'Manis Lezat' ==========>\n";
        cout << "<================== Menu =====================>\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Layani Pesanan\n";
        cout << "3. Tampilkan Antrean\n";
        cout << "4. Batalkan Pesanan\n";
        cout << "5. Tampilkan Riwayat Pesanan\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPesanan();
                break;
            case 2:
                layaniPesanan();
                break;
            case 3:
                tampilkanAntrean();
                break;
            case 4:
                batalkanPesanan();
                break;
            case 5:
                tampilkanRiwayat();
                break;
            case 6:
                cout << "Terima kasih telah menggunakan sistem ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}