#include <iostream>
#include <string>
using namespace std;

string bacaBaris(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int bacaAngka(const string& prompt) {
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

struct Node {
    string judul;
    int durasi; 
    Node* prev;
    Node* next;
};

string formatDurasi(int detik) {
    string s = to_string(detik / 60) + ":";
    int d = detik % 60;
    if (d < 10) s += "0";
    return s + to_string(d);
}

class Playlist {
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    ~Playlist() {
        while (head) {
            Node* hapus = head;
            head = head->next;
            delete hapus;
        }
    }

    void tambahAwal(const string& judul, int durasi) {
        Node* baru = new Node{judul, durasi, nullptr, head};
        if (head) head->prev = baru;
        else tail = baru;
        head = baru;
    }

    void tambahAkhir(const string& judul, int durasi) {
        Node* baru = new Node{judul, durasi, tail, nullptr};
        if (tail) tail->next = baru;
        else head = baru;
        tail = baru;
    }

    // Traversal maju: head -> tail lewat pointer next
    void tampilMaju() const {
        if (!head) { cout << "Playlist kosong.\n"; return; }
        cout << "Playlist (depan -> belakang):\n";
        int i = 1;
        for (Node* p = head; p; p = p->next, i++)
            cout << i << ". " << p->judul << " (" << formatDurasi(p->durasi) << ")\n";
    }

    // Traversal mundur: tail -> head lewat pointer prev
    void tampilMundur() const {
        if (!tail) { cout << "Playlist kosong.\n"; return; }
        cout << "Playlist (belakang -> depan):\n";
        int i = 1;
        for (Node* p = tail; p; p = p->prev, i++)
            cout << i << ". " << p->judul << " (" << formatDurasi(p->durasi) << ")\n";
    }
};

int bacaDurasi() {
    while (true) {
        int d = bacaAngka("Durasi (detik)  : ");
        if (!cin || d > 0) return d;
        cout << "Durasi harus lebih dari 0.\n";
    }
}

int main() {
    Playlist playlist;
    cout << "== PLAYLIST (Doubly Linked List) ==\n"
         << "1. Tambah Akhir\n"
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
            playlist.tambahAkhir(judul, bacaDurasi());
        } else if (pilihan == 2) {
            string judul = bacaBaris("Tambah di awal : ");
            if (judul.empty()) { cout << "Judul tidak boleh kosong.\n"; continue; }
            playlist.tambahAwal(judul, bacaDurasi());
        } else if (pilihan == 3) {
            playlist.tampilMaju();
        } else if (pilihan == 4) {
            playlist.tampilMundur();
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
    return 0;
}
