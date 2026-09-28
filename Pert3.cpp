#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *next;
};

Node *head, *tail;

void listkosong(){
    head = NULL;
    tail = NULL;
}

void sisipnode(int databaru){ //AWAL
    Node *NodeBaru = new Node;
    NodeBaru->data = databaru;
    NodeBaru->next = NULL;
    if(head == NULL && tail == NULL){
        head = NodeBaru;
        tail = NodeBaru;
    } else if (NodeBaru->data < head->data){
        NodeBaru->next = head;
        head = NodeBaru;
    } else if (NodeBaru->data > tail->data){
        tail->next = NodeBaru;
        tail = NodeBaru;
    } else {
        Node *temp = head;
        while(temp->next != NULL && NodeBaru->data > temp->next->data){
            temp = temp->next;
        }
        NodeBaru->next = temp->next;
        temp->next = NodeBaru;
    }
}

void hapusnode(int datahapus){
    if(head == NULL) return;
    if(head->data == datahapus){
    Node *hapus = head;
    head = head->next;
    if(head == NULL) tail = NULL;
    delete hapus;
    return;
    }
    Node *temp = head;
    while(temp != NULL && temp->next->data != datahapus){
        temp = temp->next;
    }
    if(temp->next != NULL){
        Node *hapus = temp->next;
        temp->next = hapus->next;
        if(hapus == tail) tail = temp;
        delete hapus;
    }
}

void printlist(){
    Node *temp = head;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main(){
    listkosong();
    sisipnode(10);
    sisipnode(5);
    sisipnode(69);
    sisipnode(20);
    printlist();
    hapusnode(5);
    printlist();
}