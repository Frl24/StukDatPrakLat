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

struct Node {
    string nim;
    string nama;
    double ipk;
    Node* next;
};

struct DaftarMahasiswa {
    Node* head = nullptr;
    Node* tail = nullptr;
};

void kosongkan(DaftarMahasiswa& daftar) {
    while (daftar.head) {
        Node* hapus = daftar.head;
        daftar.head = daftar.head->next;
        delete hapus;
    }
    daftar.tail = nullptr;
}

bool adaNIM(DaftarMahasiswa& daftar, string nim) {
    for (Node* p = daftar.head; p; p = p->next)
        if (p->nim == nim) return true;
    return false;
}

void tambahAkhir(DaftarMahasiswa& daftar, string nim, string nama, double ipk) {
    Node* baru = new Node{nim, nama, ipk, nullptr};
    if (!daftar.head) {
        daftar.head = daftar.tail = baru;
    } else {
        daftar.tail->next = baru;
        daftar.tail = baru;
    }
}

bool hapus(DaftarMahasiswa& daftar, string nim) {
    Node* prev = nullptr;
    Node* cur = daftar.head;
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

void tampil(DaftarMahasiswa& daftar) {
    if (!daftar.head) {
        cout << "List kosong.\n";
        return;
    }
    cout << "Isi list saat ini:\n";
    int i = 1;
    for (Node* p = daftar.head; p; p = p->next, i++) {
        cout << "[" << i << "] " << p->nim << " - " << p->nama
             << " - IPK " << fixed << setprecision(2) << p->ipk << "\n";
    }
}

int main() {
    DaftarMahasiswa daftar;
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
            if (adaNIM(daftar, nim)) { cout << "NIM sudah terdaftar.\n"; continue; }
            string nama = bacaBaris("Masukkan Nama : ");
            double ipk = bacaIPK("Masukkan IPK : ");
            tambahAkhir(daftar, nim, nama, ipk);
            cout << "Data berhasil ditambahkan.\n";
        } else if (pilihan == 2) {
            string nim = bacaBaris("Masukkan NIM yang akan dihapus: ");
            hapus(daftar, nim);
        } else if (pilihan == 3) {
            tampil(daftar);
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
    kosongkan(daftar);
    return 0;
}
