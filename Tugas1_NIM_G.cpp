#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

string bacaBaris(string prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int bacaAngka(string prompt) {
    while (true) {
        string s = bacaBaris(prompt);
        if (!cin) return 0;
        try {
            size_t pos;
            int v = stoi(s, &pos);
            if (pos == s.size()) return v;
        } catch (...) {}
        cout << "Input harus berupa angka.\n";
    }
}

double bacaIPK(string prompt) {
    while (true) {
        string s = bacaBaris(prompt);
        if (!cin) return 0;
        try {
            size_t pos;
            double v = stod(s, &pos);
            if (pos == s.size() && v >= 0.0 && v <= 4.0) return v;
        } catch (...) {}
        cout << "IPK harus berupa angka 0.00 sampai 4.00.\n";
    }
}

// ===================== SOAL 1: SINGLY LINKED LIST =====================

struct NodeMhs {
    string nim;
    string nama;
    double ipk;
    NodeMhs* next;
};

struct DaftarMahasiswa {
    NodeMhs* head = nullptr;
    NodeMhs* tail = nullptr;
};

DaftarMahasiswa daftar;

void mhsKosongkan() {
    while (daftar.head) {
        NodeMhs* hapus = daftar.head;
        daftar.head = daftar.head->next;
        delete hapus;
    }
    daftar.tail = nullptr;
}

bool mhsAdaNIM(string nim) {
    for (NodeMhs* p = daftar.head; p; p = p->next)
        if (p->nim == nim) return true;
    return false;
}

void mhsTambahAkhir(string nim, string nama, double ipk) {
    NodeMhs* baru = new NodeMhs{nim, nama, ipk, nullptr};
    if (!daftar.head) {
        daftar.head = daftar.tail = baru;
    } else {
        daftar.tail->next = baru;
        daftar.tail = baru;
    }
}

bool mhsHapus(string nim) {
    NodeMhs* prev = nullptr;
    NodeMhs* cur = daftar.head;
    while (cur && cur->nim != nim) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur) {
        cout << "NIM " << nim << " tidak ditemukan.\n";
        return false;
    }
    if (!prev) daftar.head = cur->next;
    else prev->next = cur->next;
    if (cur == daftar.tail) daftar.tail = prev;
    cout << "NIM " << cur->nim << " (" << cur->nama << ") berhasil dihapus.\n";
    delete cur;
    return true;
}

void mhsTampil() {
    if (!daftar.head) {
        cout << "List kosong.\n";
        return;
    }
    cout << "Isi list saat ini:\n";
    int i = 1;
    for (NodeMhs* p = daftar.head; p; p = p->next, i++) {
        cout << "[" << i << "] " << p->nim << " - " << p->nama
             << " - IPK " << fixed << setprecision(2) << p->ipk << "\n";
    }
}

void jalankanSoal1() {
    cout << "== DATA MAHASISWA (Singly Linked List) ==\n";
    cout << "Pilih menu:\n"
         << "1. Tambah data\n"
         << "2. Hapus data\n"
         << "3. Tampilkan data\n"
         << "0. Keluar\n";
    while (true) {
        int pilihan = bacaAngka("Pilihan: ");
        if (pilihan == 0) break;
        if (pilihan == 1) {
            string nim = bacaBaris("Masukkan NIM : ");
            if (nim.empty()) { cout << "NIM tidak boleh kosong.\n"; continue; }
            if (mhsAdaNIM(nim)) { cout << "NIM sudah terdaftar.\n"; continue; }
            string nama = bacaBaris("Masukkan Nama : ");
            double ipk = bacaIPK("Masukkan IPK : ");
            mhsTambahAkhir(nim, nama, ipk);
            cout << "Data berhasil ditambahkan.\n";
        } else if (pilihan == 2) {
            string nim = bacaBaris("Masukkan NIM yang akan dihapus: ");
            mhsHapus(nim);
        } else if (pilihan == 3) {
            mhsTampil();
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
    mhsKosongkan();
}

// ===================== SOAL 2: DOUBLY LINKED LIST =====================

struct NodeLagu {
    string judul;
    NodeLagu* prev;
    NodeLagu* next;
};

struct Playlist {
    NodeLagu* head = nullptr;
    NodeLagu* tail = nullptr;
};

Playlist playlist;

void laguKosongkan() {
    while (playlist.head) {
        NodeLagu* hapus = playlist.head;
        playlist.head = playlist.head->next;
        delete hapus;
    }
    playlist.tail = nullptr;
}

void laguTambahAwal(string judul) {
    NodeLagu* baru = new NodeLagu{judul, nullptr, playlist.head};
    if (playlist.head) playlist.head->prev = baru;
    else playlist.tail = baru;
    playlist.head = baru;
}

void laguTambahAkhir(string judul) {
    NodeLagu* baru = new NodeLagu{judul, playlist.tail, nullptr};
    if (playlist.tail) playlist.tail->next = baru;
    else playlist.head = baru;
    playlist.tail = baru;
}

void laguTampilMaju() {
    if (!playlist.head) {
        cout << "Playlist kosong.\n";
        return;
    }
    cout << "Playlist (depan -> belakang):\n";
    int i = 1;
    for (NodeLagu* p = playlist.head; p; p = p->next, i++) {
        cout << i << ". " << p->judul << "\n";
    }
}

void laguTampilMundur() {
    if (!playlist.tail) {
        cout << "Playlist kosong.\n";
        return;
    }
    cout << "Playlist (belakang -> depan):\n";
    int i = 1;
    for (NodeLagu* p = playlist.tail; p; p = p->prev, i++) {
        cout << i << ". " << p->judul << "\n";
    }
}

void jalankanSoal2() {
    cout << "== PLAYLIST (Doubly Linked List) ==\n";
    cout << "1. Tambah Akhir\n"
         << "2. Tambah Awal\n"
         << "3. Tampilkan Playlist (depan -> belakang)\n"
         << "4. Tampilkan Playlist (belakang -> depan)\n"
         << "0. Keluar\n";
    while (true) {
        int pilihan = bacaAngka("Pilihan : ");
        if (pilihan == 0) break;
        if (pilihan == 1) {
            string judul = bacaBaris("Tambah di akhir: ");
            if (judul.empty()) { cout << "Judul tidak boleh kosong.\n"; continue; }
            laguTambahAkhir(judul);
        } else if (pilihan == 2) {
            string judul = bacaBaris("Tambah di awal : ");
            if (judul.empty()) { cout << "Judul tidak boleh kosong.\n"; continue; }
            laguTambahAwal(judul);
        } else if (pilihan == 3) {
            laguTampilMaju();
        } else if (pilihan == 4) {
            laguTampilMundur();
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
    laguKosongkan();
}

// ===================== SOAL 3: CIRCULAR LINKED LIST =====================

struct NodePemain {
    string nama;
    NodePemain* next;
};

struct Lingkaran {
    NodePemain* last = nullptr;
    int jumlah = 0;
};

Lingkaran lingkaran;

void pemainKosongkan() {
    if (!lingkaran.last) return;
    NodePemain* p = lingkaran.last->next;
    lingkaran.last->next = nullptr;
    while (p) {
        NodePemain* berikut = p->next;
        delete p;
        p = berikut;
    }
    lingkaran.last = nullptr;
    lingkaran.jumlah = 0;
}

void pemainTambah(string nama) {
    NodePemain* baru = new NodePemain{nama, nullptr};
    if (!lingkaran.last) {
        baru->next = baru;
    } else {
        baru->next = lingkaran.last->next;
        lingkaran.last->next = baru;
    }
    lingkaran.last = baru;
    lingkaran.jumlah++;
}

void pemainTampil() {
    if (!lingkaran.last) {
        cout << "Belum ada pemain.\n";
        return;
    }
    NodePemain* awal = lingkaran.last->next;
    NodePemain* p = awal;
    cout << "Pemain: " << p->nama;
    p = p->next;
    while (p != awal) {
        cout << " - " << p->nama;
        p = p->next;
    }
    cout << " (Kembali ke " << awal->nama << ")\n";
}

void pemainPutar(int n) {
    if (!lingkaran.last) {
        cout << "Belum ada pemain.\n";
        return;
    }
    cout << "Putaran giliran (" << n << "x keliling):\n";
    NodePemain* p = lingkaran.last->next;
    int total = n * lingkaran.jumlah;
    for (int i = 1; i <= total; i++) {
        if (i < 10) cout << "Giliran " << i << " : " << p->nama << "\n";
        else cout << "Giliran " << i << ": " << p->nama << "\n";
        p = p->next;
    }
}

bool pemainKeluarkan(string nama) {
    if (!lingkaran.last) {
        cout << "Belum ada pemain.\n";
        return false;
    }
    NodePemain* prev = lingkaran.last;
    NodePemain* cur = lingkaran.last->next;
    for (int i = 0; i < lingkaran.jumlah; i++) {
        if (cur->nama == nama) {
            if (lingkaran.jumlah == 1) {
                lingkaran.last = nullptr;
            } else {
                prev->next = cur->next;
                if (cur == lingkaran.last) lingkaran.last = prev;
            }
            cout << cur->nama << " dikeluarkan dari lingkaran.\n";
            delete cur;
            lingkaran.jumlah--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    cout << "Pemain " << nama << " tidak ditemukan.\n";
    return false;
}

void jalankanSoal3() {
    cout << "== ESTAFET GILIRAN (Circular Linked List) ==\n";
    cout << "1. Masukkan Pemain\n"
         << "2. Tampilkan pemain\n"
         << "3. Putar\n"
         << "4. Keluarkan pemain\n"
         << "0. Keluar\n";
    while (true) {
        int pilihan = bacaAngka("Pilihan : ");
        if (pilihan == 0) break;
        if (pilihan == 1) {
            cout << "(Kosongkan nama lalu Enter untuk selesai)\n";
            while (true) {
                string nama = bacaBaris("Masukkan Pemain : ");
                if (nama.empty()) break;
                pemainTambah(nama);
            }
        } else if (pilihan == 2) {
            pemainTampil();
        } else if (pilihan == 3) {
            if (lingkaran.jumlah == 0) { cout << "Belum ada pemain.\n"; continue; }
            int n = bacaAngka("Mau berapa putaran : ");
            if (n <= 0) { cout << "Jumlah putaran harus lebih dari 0.\n"; continue; }
            pemainPutar(n);
        } else if (pilihan == 4) {
            string nama = bacaBaris("Siapa yang ingin dikeluarkan : ");
            pemainKeluarkan(nama);
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
    pemainKosongkan();
}

// ===================== MAIN =====================

int main() {
    while (true) {
        cout << "\n=== TUGAS 1: LINKED LIST ===\n"
             << "1. Soal 1 - Singly Linked List\n"
             << "2. Soal 2 - Doubly Linked List\n"
             << "3. Soal 3 - Circular Linked List\n"
             << "0. Keluar\n";
        int pilihan = bacaAngka("Pilih soal: ");
        if (pilihan == 0) break;
        if (pilihan == 1) jalankanSoal1();
        else if (pilihan == 2) jalankanSoal2();
        else if (pilihan == 3) jalankanSoal3();
        else cout << "Pilihan tidak valid.\n";
    }
    return 0;
}
