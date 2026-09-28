#include <bits/stdc++.h>
using namespace std;

struct CNode{
    int data;
    CNode *next;
};

CNode *head = nullptr;
CNode *tail = nullptr;

bool listkosong(){
    return head == nullptr && tail == nullptr;
}

void sisip(int data){
    CNode *nodeBaru = new CNode;
    nodeBaru->data = data;
    nodeBaru->next = nullptr;

    if (listkosong()){
        head = tail = nodeBaru;
        nodeBaru->next = head;
    } else if(data < head->data){
        nodeBaru->next = head;
        head = nodeBaru;
        tail->next = head;
    } else if(data > tail->data){
        tail->next = nodeBaru;
        tail = nodeBaru;
        tail->next = head;
    } else {
        CNode *temp = head;
        while(temp->next != head && temp->next->data < data){
            temp = temp->next;
        }
        nodeBaru->next = temp->next;
        temp->next = nodeBaru;
    }
}

void hapusNode(int datahapus){
    if (listkosong()) return;
    CNode *temp = tail;
    CNode *hapus = head;
    do{
        if(hapus->data == datahapus){
            if(head == tail) head = tail = nullptr;
            else {
                temp->next = hapus->next;
                if(hapus == head) head = hapus->next;
                if(hapus == tail) tail = temp;
            }
            delete hapus;
            return;
        }
        temp = hapus;
        hapus = hapus->next;
    } while(hapus != head);
    cout << "Data tidak ditemukan" << endl;
}

void tampil(){
    if (listkosong()) {
        cout << "List kosong" << endl;
        return;
    }
    CNode *temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while(temp != head);
    cout << endl;
}

int main(){
    sisip(10);
    sisip(20);
    sisip(5);
    sisip(15);
    tampil(); // Output: 5 10 15 20

    hapusNode(10);
    tampil(); // Output: 5 15 20

    hapusNode(5);
    tampil(); // Output: 15 20

    hapusNode(20);
    tampil(); // Output: 15

    hapusNode(15);
    tampil(); // Output: List kosong

    return 0;
}