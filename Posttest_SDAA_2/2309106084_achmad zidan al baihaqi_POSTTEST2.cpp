#include <iostream>
#include <string>

using namespace std;


struct Hewan {
    string nama;
    string jenis;
    int umur;
};


void tambahHewan(Hewan* daftarHewan, int* jumlahHewan) {
    if (*jumlahHewan < 100) {
        cout << "Masukkan nama hewan: ";
        cin >> daftarHewan[*jumlahHewan].nama;
        cout << "Masukkan jenis hewan: ";
        cin >> daftarHewan[*jumlahHewan].jenis;
        cout << "Masukkan umur hewan: ";
        cin >> daftarHewan[*jumlahHewan].umur;
        (*jumlahHewan)++;
        cout << "Hewan berhasil ditambahkan!" << endl;
    } else {
        cout << "Daftar hewan penuh!" << endl;
    }
}


void tampilkanHewan(Hewan* daftarHewan, int jumlahHewan) {
    if (jumlahHewan == 0) {
        cout << "Belum ada hewan di dalam daftar." << endl;
    } else {
        cout << "Daftar Hewan di Kebun Binatang:" << endl;
        for (int i = 0; i < jumlahHewan; i++) {
            cout << i + 1 << ". Nama: " << daftarHewan[i].nama
                 << ", Jenis: " << daftarHewan[i].jenis
                 << ", Umur: " << daftarHewan[i].umur << " tahun" << endl;
        }
    }
}


Hewan* cariHewan(Hewan* daftarHewan, int jumlahHewan, string nama) {
    for (int i = 0; i < jumlahHewan; i++) {
        if (daftarHewan[i].nama == nama) {
            return &daftarHewan[i];
        }
    }
    return nullptr;
}


void hapusHewan(Hewan* daftarHewan, int* jumlahHewan, string nama) {
    Hewan* hewanDitemukan = cariHewan(daftarHewan, *jumlahHewan, nama);
    if (hewanDitemukan != nullptr) {
        for (int i = hewanDitemukan - daftarHewan; i < *jumlahHewan - 1; i++) {
            daftarHewan[i] = daftarHewan[i + 1];
        }
        (*jumlahHewan)--;
        cout << "Hewan berhasil dihapus!" << endl;
    } else {
        cout << "Hewan tidak ditemukan." << endl;
    }
}

int main() {
    Hewan daftarHewan[100]; 
    int jumlahHewan = 0; 
    int pilihan;
    string namaHewan;

    do {
        cout << "\nMenu Kebun Binatang" << endl;
        cout << "1. Tambah Hewan" << endl;
        cout << "2. Tampilkan Daftar Hewan" << endl;
        cout << "3. Cari Hewan" << endl;
        cout << "4. Hapus Hewan" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahHewan(daftarHewan, &jumlahHewan);
            break;
        case 2:
            tampilkanHewan(daftarHewan, jumlahHewan);
            break;
        case 3:
            cout << "Masukkan nama hewan yang ingin dicari: ";
            cin >> namaHewan;
            if (cariHewan(daftarHewan, jumlahHewan, namaHewan) != nullptr) {
                cout << "Hewan ditemukan!" << endl;
            } else {
                cout << "Hewan tidak ditemukan." << endl;
            }
            break;
        case 4:
            cout << "Masukkan nama hewan yang ingin dihapus: ";
            cin >> namaHewan;
            hapusHewan(daftarHewan, &jumlahHewan, namaHewan);
            break;
        case 5:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    } while (pilihan != 5);

    return 0;
}
