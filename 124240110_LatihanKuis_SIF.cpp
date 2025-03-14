#include <iostream>
#include <cstdio>    // Untuk file handling (fopen, fprintf, fscanf, fclose)
#include <cstring>   // Untuk operasi string (strcmp)
using namespace std;

// Struktur untuk menyimpan data mahasiswa
struct mahasiswa {
    char nama[50];      // Nama mahasiswa
    int NIM;            // Nomor Induk Mahasiswa
    char jurusan[50];   // Jurusan mahasiswa
    int thn_masuk;      // Tahun masuk mahasiswa
    float IPK;          // IPK mahasiswa
};

mahasiswa mhs[100];     // Array untuk menyimpan data mahasiswa
int jumlah = 0;         // Jumlah mahasiswa yang terdaftar
int pilih;              // Pilihan menu

// Deklarasi fungsi
void menu();
void InputData();
void TampilkanData();
void CariNIM();
void CariJurusan();
void UpdateIPK();
void HapusData();
void SimpanKeFile();
void BacaDariFile();
void quickSort(int low, int high);
int partition(int low, int high);

// Fungsi partition untuk Quick Sort
int partition(int low, int high) {
    int pivot = mhs[high].NIM;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (mhs[j].NIM < pivot) {
            i++;
            mahasiswa temp = mhs[i];
            mhs[i] = mhs[j];
            mhs[j] = temp;
        }
    }
    i++;
    mahasiswa temp = mhs[i];
    mhs[i] = mhs[high];
    mhs[high] = temp;
    return i;
}

// Fungsi Quick Sort untuk mengurutkan data berdasarkan NIM
void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

int main() {
    BacaDariFile();  // Membaca data dari file saat program dimulai
    while (true) {   // Loop utama sampai user memilih exit
        menu();
        switch (pilih) {
            case 1:
                InputData();
                break;
            case 2:
                // Mengurutkan data secara ascending menggunakan Quick Sort
                if (jumlah > 0)
                    quickSort(0, jumlah - 1);
                TampilkanData();
                break;
            case 3:
                // Sebelum pencarian, data diurutkan berdasarkan NIM
                if (jumlah > 0)
                    quickSort(0, jumlah - 1);
                CariNIM();
                break;
            case 4:
                CariJurusan();
                break;
            case 5:
                UpdateIPK();
                break;
            case 6:
                HapusData();
                break;
            case 7:
                SimpanKeFile();  // Simpan data sebelum keluar
                cout << "Terima kasih telah menggunakan SmartCampus++! Semoga sukses dalam studi Anda!\n";
                return 0;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }
    return 0;
}

// Fungsi untuk menampilkan menu utama
void menu() {
    cout << "\n<========== SmartCampus++ ==========>\n";
    cout << "1. Menambahkan Mahasiswa Baru\n";
    cout << "2. Menampilkan Seluruh Mahasiswa\n";
    cout << "3. Mencari Mahasiswa Berdasarkan NIM\n";
    cout << "4. Mencari Mahasiswa Berdasarkan Jurusan\n";
    cout << "5. Memperbarui IPK Mahasiswa\n";
    cout << "6. Menghapus Mahasiswa dari Database\n";
    cout << "7. Keluar dari Program\n";
    cout << "Pilih Opsi: "; 
    cin >> pilih;
}

// Fungsi untuk menambahkan data mahasiswa baru
void InputData() {
    int tambah;
    cout << "Berapa data yang ingin ditambahkan?: "; 
    cin >> tambah;
    cin.ignore();  // Bersihkan newline setelah input jumlah
    for (int i = 0; i < tambah; i++) {
        cout << "\nData mahasiswa ke-" << (jumlah + 1) << ":\n";
        cout << "Masukkan Nama: ";
        cin.getline(mhs[jumlah].nama, 50); // Mengizinkan input dengan spasi
        cout << "Masukkan NIM: ";
        cin >> mhs[jumlah].NIM;
        cin.ignore();
        cout << "Masukkan Jurusan: ";
        cin.getline(mhs[jumlah].jurusan, 50); // Mengizinkan input dengan spasi
        cout << "Masukkan Tahun Masuk: ";
        cin >> mhs[jumlah].thn_masuk;
        cin.ignore();
        mhs[jumlah].IPK = 0.0; // IPK awal selalu 0.0
        jumlah++;
    }
    SimpanKeFile();  // Setelah input, simpan data ke file
    cout << "Data berhasil ditambahkan dan disimpan ke file!\n";
}

// Fungsi untuk menampilkan seluruh data mahasiswa
void TampilkanData() {
    if (jumlah == 0) {
        cout << "Data kosong!\n";
        system("pause");
        return;
    }
    cout << "\nData Mahasiswa:\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "-------------------------\n";
        cout << "Nama       : " << mhs[i].nama << "\n";
        cout << "NIM        : " << mhs[i].NIM << "\n";
        cout << "Jurusan    : " << mhs[i].jurusan << "\n";
        cout << "Tahun Masuk: " << mhs[i].thn_masuk << "\n";
        cout << "IPK        : " << mhs[i].IPK << "\n";
    }
    system("pause");
}

// Fungsi untuk mencari mahasiswa berdasarkan NIM (menggunakan Binary Search)
void CariNIM() {
    if (jumlah == 0) {
        cout << "Data kosong!\n";
        system("pause");
        return;
    }
    int cari;
    cout << "Masukkan NIM yang dicari: ";
    cin >> cari;
    int low = 0, high = jumlah - 1, mid;
    bool found = false;
    while (low <= high) {
        mid = (low + high) / 2;
        if (mhs[mid].NIM == cari) {
            cout << "Mahasiswa ditemukan:\n";
            cout << "Nama       : " << mhs[mid].nama << "\n";
            cout << "NIM        : " << mhs[mid].NIM << "\n";
            cout << "Jurusan    : " << mhs[mid].jurusan << "\n";
            cout << "Tahun Masuk: " << mhs[mid].thn_masuk << "\n";
            cout << "IPK        : " << mhs[mid].IPK << "\n";
            found = true;
            break;
        } else if (mhs[mid].NIM < cari) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    if (!found)
        cout << "Mahasiswa dengan NIM " << cari << " tidak ditemukan!\n";
    system("pause");
}

// Fungsi untuk mencari mahasiswa berdasarkan jurusan (Sequential Search)
void CariJurusan() {
    if (jumlah == 0) {
        cout << "Data kosong!\n";
        return;
    }
    char cari[50];
    cin.ignore();
    cout << "Masukkan jurusan yang dicari: ";
    cin.getline(cari, 50);
    bool ditemukan = false;
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(mhs[i].jurusan, cari) == 0) {
            cout << "Nama: " << mhs[i].nama << " | NIM: " << mhs[i].NIM << " | IPK: " << mhs[i].IPK << "\n";
            ditemukan = true;
        }
    }
    if (!ditemukan){
        cout << "Mahasiswa dengan jurusan " << cari << " tidak ditemukan!\n";
    }
    system("pause");
}

// Fungsi untuk memperbarui IPK mahasiswa berdasarkan NIM
void UpdateIPK() {
    if (jumlah == 0) {
        cout << "Data kosong!\n";
        return;
    }
    int cari;
    cout << "Masukkan NIM mahasiswa yang akan diperbarui IPK-nya: ";
    cin >> cari;
    for (int i = 0; i < jumlah; i++) {
        if (mhs[i].NIM == cari) {
            cout << "Data mahasiswa ditemukan:\n";
            cout << "Nama    : " << mhs[i].nama << "\n";
            cout << "Jurusan : " << mhs[i].jurusan << "\n";
            cout << "IPK saat ini: " << mhs[i].IPK << "\n";
            cout << "Masukkan IPK baru: ";
            float ipkBaru;
            cin >> ipkBaru;
            if (ipkBaru < 0.0 || ipkBaru > 4.0) {
                cout << "IPK tidak valid! Harus antara 0.0 - 4.0\n";
                return;
            }
            mhs[i].IPK = ipkBaru;
            SimpanKeFile();
            cout << "IPK mahasiswa dengan NIM " << mhs[i].NIM << " berhasil diperbarui!\n";
            return;
        }
    }
    cout << "Mahasiswa tidak ditemukan!\n";
}

// Fungsi untuk menghapus data mahasiswa berdasarkan NIM
void HapusData() {
    if (jumlah == 0) {
        cout << "Data kosong!\n";
        return;
    }
    int cari;
    cout << "Masukkan NIM mahasiswa yang akan dihapus: ";
    cin >> cari;
    bool found = false;
    for (int i = 0; i < jumlah; i++) {
        if (mhs[i].NIM == cari) {
            for (int j = i; j < jumlah - 1; j++) {
                mhs[j] = mhs[j + 1];
            }
            jumlah--;
            found = true;
            SimpanKeFile();
            cout << "Mahasiswa berhasil dihapus!\n";
            return;
        }
    }
    if (!found)
        cout << "Mahasiswa tidak ditemukan!\n";
}

// Fungsi untuk menyimpan data ke dalam file (menggunakan file teks)
// Data disimpan dengan format: nama,NIM,jurusan,thn_masuk,IPK
void SimpanKeFile() {
    FILE *fptr = fopen("MahasiswaData.dat", "w");
    if (!fptr) {
        cout << "Gagal membuka file!\n";
        return;
    }
    for (int i = 0; i < jumlah; i++) {
        fprintf(fptr, "%s,%d,%s,%d,%.2f\n", mhs[i].nama, mhs[i].NIM, mhs[i].jurusan, mhs[i].thn_masuk, mhs[i].IPK);
    }
    fclose(fptr);
}

// Fungsi untuk membaca data dari file
// Data dibaca menggunakan fgets() dan sscanf() dengan delimiter koma
void BacaDariFile() {
    FILE *fptr = fopen("MahasiswaData.dat", "r");
    if (!fptr)
        return;
    jumlah = 0;
    char line[200];
    while (fgets(line, sizeof(line), fptr) != NULL) {
        sscanf(line, " %[^,],%d,%[^,],%d,%f", mhs[jumlah].nama, &mhs[jumlah].NIM, mhs[jumlah].jurusan, &mhs[jumlah].thn_masuk, &mhs[jumlah].IPK);
        jumlah++;
    }
    fclose(fptr);
}
