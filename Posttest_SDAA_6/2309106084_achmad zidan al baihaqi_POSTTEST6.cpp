#include <iostream>
#include <string>

using namespace std;

struct Node {
    string nama;
    string jenis;
    int umur;
    Node* next;
};

// Function prototypes for Merge Sort and Quick Sort
void mergeSort(Node** headRef);
Node* sortedMerge(Node* a, Node* b);
void frontBackSplit(Node* source, Node** frontRef, Node** backRef);

void quickSort(Node** headRef);
Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd);
Node* quickSortRecur(Node* head, Node* end);
Node* getTail(Node* cur);


void push(Node** top, string nama, string jenis, int umur);
void pop(Node** top);
void enqueue(Node** front, Node** rear, string nama, string jenis, int umur);
void dequeue(Node** front);


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

// Function to display the animals
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

// Merge Sort Functions (Ascending Order)
void mergeSort(Node** headRef) {
    Node* head = *headRef;
    if (!head || !head->next) return;

    Node *a, *b;
    frontBackSplit(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = sortedMerge(a, b);
}

Node* sortedMerge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->umur <= b->umur) {
        a->next = sortedMerge(a->next, b);
        return a;
    } else {
        b->next = sortedMerge(a, b->next);
        return b;
    }
}

void frontBackSplit(Node* source, Node** frontRef, Node** backRef) {
    Node* slow = source;
    Node* fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

// Quick Sort Functions (Descending Order)
void quickSort(Node** headRef) {
    *headRef = quickSortRecur(*headRef, getTail(*headRef));
}

Node* getTail(Node* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node *prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->umur > pivot->umur) { // Descending order
            if (!*newHead) *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            Node* tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if (!*newHead) *newHead = pivot;
    *newEnd = tail;
    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) {
    if (!head || head == end) return head;

    Node *newHead = nullptr, *newEnd = nullptr;
    Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* tmp = newHead;
        while (tmp->next != pivot) tmp = tmp->next;
        tmp->next = nullptr;

        newHead = quickSortRecur(newHead, tmp);
        getTail(newHead)->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

// Stack Operations
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

// Queue Operations
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

int min(int x, int y) {
    return (x <= y) ? x : y;
}

int fibonacciSearch(Node* head, int umur) {
    Node* temp = head;
    int size = 0;
    while (temp != nullptr) {
        size++;
        temp = temp->next;
    }

    int fibMMm2 = 0;  // Bilangan Fibonacci ke-(m-2)
    int fibMMm1 = 1;  // Bilangan Fibonacci ke-(m-1)
    int fibM = fibMMm2 + fibMMm1;  // Bilangan Fibonacci ke-m

    int offset = -1;
    while (fibM < size) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    temp = head;
    Node* current = head;
    while (fibM > 1) {
        int i = min(offset + fibMMm2, size - 1);
        for (int j = 0; j < i; j++) {
            current = current->next;
        }
        
        if (current->umur < umur) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (current->umur > umur) {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && current->umur == umur) {
        return offset + 1;
    }

    return -1;
}

#include <cmath>

int jumpSearch(Node* head, int umur) {
    Node* temp = head;
    int size = 0;
    while (temp != nullptr) {
        size++;
        temp = temp->next;
    }

    int step = sqrt(size);
    int prev = 0;
    Node* current = head;

    while (current != nullptr && current->umur < umur) {
        for (int i = 0; i < step && current->next != nullptr; i++) {
            current = current->next;
            prev++;
        }
    }

    for (int i = 0; i < step && current != nullptr; i++) {
        if (current->umur == umur) {
            return prev;
        }
        current = current->next;
        prev++;
    }

    return -1;
}

#include <cstring>

#define NO_OF_CHARS 256

void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badchar[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        badchar[(int)str[i]] = i;
    }
}

int boyerMooreSearch(Node* head, string pattern) {
    Node* current = head;
    int pos = 0;

    int m = pattern.size();
    int badchar[NO_OF_CHARS];

    badCharHeuristic(pattern, m, badchar);

    while (current != nullptr) {
        string text = current->nama;
        int n = text.size();

        int shift = 0;
        while (shift <= (n - m)) {
            int j = m - 1;

            while (j >= 0 && pattern[j] == text[shift + j]) {
                j--;
            }

            if (j < 0) {
                return pos;  // Pola ditemukan
            } else {
                shift += max(1, j - badchar[(int)text[shift + j]]);
            }
        }

        current = current->next;
        pos++;
    }

    return -1;
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
        cout << "1.  Tambah Hewan" << endl;
        cout << "2.  Tampilkan Daftar Hewan" << endl;
        cout << "3.  Urutkan Hewan (Ascending)" << endl;
        cout << "4.  Urutkan Hewan (Descending)" << endl;
        cout << "5.  Push ke Stack" << endl;
        cout << "6.  Pop dari Stack" << endl;
        cout << "7.  Enqueue ke Queue" << endl;
        cout << "8.  Dequeue dari Queue" << endl;
        cout << "9.  cari umur hewan " << endl;
        cout << "10. cari nama hewan " << endl;
        cout << "11. keluar " << endl;
        cout << "Pilih menu (1-11): ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahHewan(&head);
            break;
        case 2:
            tampilkanHewan(head);
            break;
        case 3:
            mergeSort(&head);
            cout << "Daftar hewan telah diurutkan secara ascending berdasarkan umur." << endl;
            break;
        case 4:
            quickSort(&head);
            cout << "Daftar hewan telah diurutkan secara descending berdasarkan umur." << endl;
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
            cout << "Masukkan umur hewan yang ingin dicari: ";
            cin >> umurHewan;
            if (fibonacciSearch(head, umurHewan) != -1) {
            cout << "Hewan ditemukan di daftar." << endl;
            } else {
             cout << "Hewan tidak ditemukan." << endl;
            }
            break;
        case 10:
            cout << "Masukkan nama hewan yang ingin dicari: ";
            cin >> namaHewan;
            if (boyerMooreSearch(head, namaHewan) != -1) {
            cout << "Hewan ditemukan di daftar." << endl;
        } else {
            cout << "Hewan tidak ditemukan." << endl;
        }
        break;
        case 11:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    } while (pilihan != 11);

    return 0;
}
