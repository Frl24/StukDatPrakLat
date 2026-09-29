// Tugas 1 Praktikum Struktur Data
// Soal 3: Circular Linked List (estafet giliran)

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

// ---------- Fungsi bantu input ----------

string bacaBaris(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int bacaAngka(const string& prompt) {
    while (true) {
        string s = bacaBaris(prompt);
        if (!cin) return 0;  // input habis, keluar dari menu
        try {
            size_t pos;
            int v = stoi(s, &pos);
            if (pos == s.size()) return v;
        } catch (...) {}
        cout << "Input harus berupa angka.\n";
    }
}

string huruf_kecil(string s) {
    for (char& c : s) c = tolower((unsigned char)c);
    return s;
}

// ---------- Soal 3 ----------


struct Node {
    string nama;
    Node* next;
};

class Lingkaran {
    Node* last = nullptr;  // node terakhir; last->next adalah node pertama
    int jumlah = 0;

public:
    ~Lingkaran() {
        if (!last) return;
        Node* p = last->next;
        last->next = nullptr;  // putus lingkaran agar bisa dihapus berurutan
        while (p) {
            Node* berikut = p->next;
            delete p;
            p = berikut;
        }
    }

    int banyak() const { return jumlah; }

    void tambah(const string& nama) {
        Node* baru = new Node{nama, nullptr};
        if (!last) {
            baru->next = baru;
        } else {
            baru->next = last->next;
            last->next = baru;
        }
        last = baru;
        jumlah++;
    }

    void tampil() const {
        if (!last) { cout << "Belum ada pemain.\n"; return; }
        Node* awal = last->next;
        cout << "Pemain: ";
        Node* p = awal;
        do {
            cout << p->nama;
            p = p->next;
            if (p != awal) cout << " - ";
        } while (p != awal);
        cout << " (Kembali ke " << awal->nama << ")\n";
    }

    void putar(int n) const {
        if (!last) { cout << "Belum ada pemain.\n"; return; }
        cout << "Putaran giliran (" << n << "x keliling):\n";
        Node* p = last->next;
        int total = n * jumlah;
        for (int i = 1; i <= total; i++, p = p->next)
            cout << "Giliran " << left << setw(2) << i << ": " << p->nama << "\n";
    }

    bool keluarkan(const string& nama) {
        if (!last) { cout << "Belum ada pemain.\n"; return false; }
        Node* prev = last;
        Node* cur = last->next;
        for (int i = 0; i < jumlah; i++) {
            if (huruf_kecil(cur->nama) == huruf_kecil(nama)) {
                if (jumlah == 1) {
                    last = nullptr;
                } else {
                    prev->next = cur->next;
                    if (cur == last) last = prev;
                }
                cout << cur->nama << " dikeluarkan dari lingkaran.\n";
                delete cur;
                jumlah--;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        cout << "Pemain " << nama << " tidak ditemukan.\n";
        return false;
    }
};

int main() {
    Lingkaran lingkaran;
    cout << "== ESTAFET GILIRAN (Circular Linked List) ==\n"
         << "1. Masukkan Pemain\n"
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
                lingkaran.tambah(nama);
            }
        } else if (pilihan == 2) {
            lingkaran.tampil();
        } else if (pilihan == 3) {
            if (lingkaran.banyak() == 0) { cout << "Belum ada pemain.\n"; continue; }
            int n = bacaAngka("Mau berapa putaran : ");
            if (n <= 0) { cout << "Jumlah putaran harus lebih dari 0.\n"; continue; }
            lingkaran.putar(n);
        } else if (pilihan == 4) {
            string nama = bacaBaris("Siapa yang ingin dikeluarkan : ");
            lingkaran.keluarkan(nama);
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
    return 0;
}
