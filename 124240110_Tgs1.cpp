#include <iostream>
using namespace std;

void menu(), tampilkan(), searchnim(), searchname(),quick_sort(),sortIPKAsc(),sortIPKDesc();
int pilih;
bool found;

struct mhs
{
    string nama;
    int NIM;
    float IPK;
};

mhs mahasiswa[10] ={
    {"Valdo", 124240110,3.9},
    {"Andi", 124240111,3.1},
    {"Budi", 124240113,3.3},
    {"Tony", 124240112,3.4},
    {"Suki", 124240115,3.7},
    {"Bahlul", 124240114,2.0},
    {"Fufu", 124240117,3.2},
    {"Fafa", 124240120,2.3},
    {"Zul", 124240119,3.0},
    {"Udin", 1242401116,2.2}
};

int n = sizeof(mahasiswa) / sizeof(mahasiswa[0]);


main(){
   while (true)
   {
        sortNama(); //MENGURUTKAN NAMA SEBELUM BINARY SEARCH
        menu();
        switch (pilih)
        {
        case 1:
            tampilkan();
            break;
        case 2:
            searchnim();
            break;
        case 3:
            searchname();
            break;
        case 4:
            sortIPKAsc();
            break;
        case 5:
            sortIPKDesc();
            break;
        case 6:
        default:
            break;
        }
   }
    
    
}

void menu(){
    
    cout << "1. Tampilkan Mahasiswa" << endl;
    cout << "2. Cari Berdasarkan Nim" << endl;
    cout << "3. Cari Berdasarkan Nama" << endl;
    cout << "4. Sort IPK Mahasiswa (Asc)" << endl;
    cout << "5. Sort IPK Mahasiswa (Desc)" << endl;
    cout << "6. Exit" << endl;
    cout << "Pilih Menu: "; cin >> pilih;
}
void tampilkan() {
    system("cls");
    cout << "<========== Menampilkan Data Mahasiswa =========>" << endl;
    mhs *ptr = mahasiswa;
    for (int i = 0; i < 10; i++) {
        cout << i + 1 << ". ";
        cout << "Nama: " << (ptr + i)->nama << " ";
        cout << "NIM: " << (ptr + i)->NIM << " ";
        cout << "IPK: " << (ptr + i)->IPK << " " << endl;
    }
    cout << endl;
    system("pause");
}


//searchnim dengan Sequential Search
void searchnim(){
    int cariNIM;
    char ulang; 
    do
    {
        int i=0;
        found = false;

        system("cls");
        cout << "<========= Cari Berdasarkan NIM ==========>" << endl;
        cout << "Masukan NIM: "; cin >> cariNIM;
    
        while ( i < n && found == false)
        {
            if (mahasiswa[i].NIM == cariNIM)
            {
                system("cls");
                cout << "<========== Cari Berdasarkan NIM ==========>" << endl;
                cout << "Data Ditemukan!" << endl;
                cout << "Nama:" << mahasiswa[i].nama << " " << endl;
                cout << "NIM: " << mahasiswa[i].NIM << " " << endl;
                cout << "IPK: " << mahasiswa[i].IPK << " " << endl;
                found = true;
            }
            i++;
        }
            if (!found)
            {
                system("cls");
                cout << "<========== Cari Berdasarkan NIM ==========>" << endl;
                cout << "Data Tidak Ditemukan!" << endl;
                cout << "ingin mencari lagi?(y/n): "; cin >> ulang;
            }
            else
            {
                ulang = 'n';
            }
    
    } while (ulang == 'y' || ulang == 'Y');
    system("pause");

}
//sorting nama untuk binary
void sortNama() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (mahasiswa[j].nama > mahasiswa[j + 1].nama) {
                swap(mahasiswa[j], mahasiswa[j + 1]);
            }
        }
    }
}
//Mencari nama dengan Search Binary
void searchname() {
    string carinama;
    cout << "<========== Cari Berdasarkan Nama ==========>" << endl;
    cout << "Masukan Nama: "; cin >> carinama;

    int awal = 0, akhir = n - 1, tengah;
    bool found = false;

    while (awal <= akhir && !found) {
        tengah = (awal + akhir) / 2;
        if (mahasiswa[tengah].nama == carinama) {
            found = true;
            cout << "Data Ditemukan!" << endl;
            cout << "Nama: " << mahasiswa[tengah].nama << endl;
            cout << "NIM: " << mahasiswa[tengah].NIM << endl;
            cout << "IPK: " << mahasiswa[tengah].IPK << endl;
        } else if (mahasiswa[tengah].nama < carinama) {
            awal = tengah + 1;
        } else {
            akhir = tengah - 1;
        }
    }

    if (!found) {
        cout << "Data Tidak Ditemukan!" << endl;
    }
    system("pause");
}
    

void sortIPKAsc() {
    int low = 0, high = n - 1;
    mhs pivot = mahasiswa[(low + high) / 2];
    int i = low, j = high;

    while (i <= j) {
        while (mahasiswa[i].IPK < pivot.IPK) i++;
        while (mahasiswa[j].IPK > pivot.IPK) j--;
        if (i <= j) {
            swap(mahasiswa[i], mahasiswa[j]);
            i++;
            j--;
        }
    }

    if (low < j) sortIPKAsc();
    if (i < high) sortIPKAsc();
}

void sortIPKDesc() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (mahasiswa[j].IPK < mahasiswa[j + 1].IPK) {
                swap(mahasiswa[j], mahasiswa[j + 1]);
            }
        }
    }
}
