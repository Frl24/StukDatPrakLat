#include <bits/stdc++.h>
using namespace std;

struct DNode{
    int data;
    DNode *next;
    DNode *prev;
};

DNode *head = nullptr;
DNode *tail = nullptr;

void sisip(int data){
    DNode *nodeBaru = new DNode;
    nodeBaru->data = data;
    nodeBaru->next = nullptr;
    nodeBaru->prev = nullptr;

    if(head == nullptr && tail == nullptr) head=tail=nodeBaru;
    else if(data < head->data){
        nodeBaru->next = head;
        head->prev = nodeBaru;
        head = nodeBaru;
    } else if(data > tail->data){
        tail->next = nodeBaru;
        nodeBaru->prev = tail;
        tail = nodeBaru;
    } else {
        DNode *temp = head;
        while(temp->next != nullptr && temp->next->data < data){
            temp = temp->next;
        }
        nodeBaru->next = temp->next;
        nodeBaru->prev = temp;
        temp->next->prev = nodeBaru;
        temp->next = nodeBaru;
    }
}

void hapus(int datahapus){
    if(head == nullptr) return;
    if(head->data == datahapus){
        DNode *temp = head;
        head = head->next;
        if(head != nullptr) head->prev = nullptr;
        delete temp;
        return;
    }
    DNode *temp = head->next;
    while(temp != nullptr && temp->data != datahapus){
        temp = temp->next;
}
    if(temp != nullptr){
        if(temp->prev != nullptr) temp->prev->next = temp->next;
        if(temp->next != nullptr) temp->next->prev = temp->prev;
        delete temp;
    } else {
        cout << "Data " << datahapus << " tidak ditemukan." << endl;
    }
}

void printList(){
    DNode *temp = head;
    while(temp != nullptr){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main(){
    sisip(5);
    sisip(3);
    sisip(7);
    sisip(1);
    sisip(9);

    printList(); // Output: 1 3 5 7 9
    hapus(1);
    hapus(3);
    printList(); // Output: 1 5 7 9
    return 0;
}