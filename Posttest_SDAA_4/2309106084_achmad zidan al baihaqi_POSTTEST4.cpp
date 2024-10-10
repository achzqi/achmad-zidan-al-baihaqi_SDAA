#include <iostream>
#include <string>

using namespace std;

struct Node {
    string nama;
    string jenis;
    int umur;
    Node* next;
};

void tambahHewan(Node** head) {
    Node* newNode = new Node();
    cout << "Masukkan nama hewan: ";
    cin >> newNode->nama;
    cout << "Masukkan jenis hewan: ";
    cin >> newNode->jenis;
    cout << "Masukkan umur hewan: ";
    cin >> newNode->umur;
    newNode->next = nullptr;

    if (*head == nullptr) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "Hewan berhasil ditambahkan!" << endl;
}

void tampilkanHewan(Node* head) {
    if (head == nullptr) {
        cout << "Belum ada hewan di dalam daftar." << endl;
    } else {
        Node* temp = head;
        int i = 1;
        cout << "Daftar Hewan di Kebun Binatang:" << endl;
        while (temp != nullptr) {
            cout << i << ". Nama: " << temp->nama
                 << ", Jenis: " << temp->jenis
                 << ", Umur: " << temp->umur << " tahun" << endl;
            temp = temp->next;
            i++;
        }
    }
}

Node* cariHewan(Node* head, string nama) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->nama == nama) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void hapusHewan(Node** head, string nama) {
    Node* temp = *head;
    Node* prev = nullptr;

    if (temp != nullptr && temp->nama == nama) {
        *head = temp->next;
        delete temp;
        cout << "Hewan berhasil dihapus!" << endl;
        return;
    }

    while (temp != nullptr && temp->nama != nama) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Hewan tidak ditemukan." << endl;
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "Hewan berhasil dihapus!" << endl;
}

// Implementasi Stack: LIFO
void push(Node** top, string nama, string jenis, int umur) {
    Node* newNode = new Node();
    newNode->nama = nama;
    newNode->jenis = jenis;
    newNode->umur = umur;
    newNode->next = *top;
    *top = newNode;
    cout << "Hewan berhasil ditambahkan ke Stack!" << endl;
}

void pop(Node** top) {
    if (*top == nullptr) {
        cout << "Stack kosong!" << endl;
        return;
    }

    Node* temp = *top;
    *top = (*top)->next;
    cout << "Menghapus: " << temp->nama << " dari Stack." << endl;
    delete temp;
}

// Implementasi Queue: FIFO
void enqueue(Node** front, Node** rear, string nama, string jenis, int umur) {
    Node* newNode = new Node();
    newNode->nama = nama;
    newNode->jenis = jenis;
    newNode->umur = umur;
    newNode->next = nullptr;

    if (*rear == nullptr) {
        *front = *rear = newNode;
        cout << "Hewan berhasil ditambahkan ke Queue!" << endl;
        return;
    }

    (*rear)->next = newNode;
    *rear = newNode;
    cout << "Hewan berhasil ditambahkan ke Queue!" << endl;
}

void dequeue(Node** front) {
    if (*front == nullptr) {
        cout << "Queue kosong!" << endl;
        return;
    }

    Node* temp = *front;
    *front = (*front)->next;

    if (*front == nullptr) {
        *front = nullptr;
    }

    cout << "Menghapus: " << temp->nama << " dari Queue." << endl;
    delete temp;
}

int main() {
    Node* head = nullptr;
    Node* stackTop = nullptr;
    Node* queueFront = nullptr;
    Node* queueRear = nullptr;

    int pilihan;
    string namaHewan;
    string jenisHewan;
    int umurHewan;

    do {
        cout << "\nMenu Kebun Binatang" << endl;
        cout << "1. Tambah Hewan" << endl;
        cout << "2. Tampilkan Daftar Hewan" << endl;
        cout << "3. Cari Hewan" << endl;
        cout << "4. Hapus Hewan" << endl;
        cout << "5. Push ke Stack" << endl;
        cout << "6. Pop dari Stack" << endl;
        cout << "7. Enqueue ke Queue" << endl;
        cout << "8. Dequeue dari Queue" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilih menu (1-9): ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahHewan(&head);
            break;
        case 2:
            tampilkanHewan(head);
            break;
        case 3:
            cout << "Masukkan nama hewan yang ingin dicari: ";
            cin >> namaHewan;
            if (cariHewan(head, namaHewan) != nullptr) {
                cout << "Hewan ditemukan!" << endl;
            } else {
                cout << "Hewan tidak ditemukan." << endl;
            }
            break;
        case 4:
            cout << "Masukkan nama hewan yang ingin dihapus: ";
            cin >> namaHewan;
            hapusHewan(&head, namaHewan);
            break;
        case 5:
            cout << "Masukkan nama, jenis, dan umur hewan untuk Stack: ";
            cin >> namaHewan >> jenisHewan >> umurHewan;
            push(&stackTop, namaHewan, jenisHewan, umurHewan);
            break;
        case 6:
            pop(&stackTop);
            break;
        case 7:
            cout << "Masukkan nama, jenis, dan umur hewan untuk Queue: ";
            cin >> namaHewan >> jenisHewan >> umurHewan;
            enqueue(&queueFront, &queueRear, namaHewan, jenisHewan, umurHewan);
            break;
        case 8:
            dequeue(&queueFront);
            break;
        case 9:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    } while (pilihan != 9);

    return 0;
}
