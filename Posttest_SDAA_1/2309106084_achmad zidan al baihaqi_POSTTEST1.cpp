#include <iostream>
using namespace std;


void printRow(int row, int count) {
    if (count == 0) {
        return;
    }
    cout << row; 
    printRow(row, count - 1);  
}


void printTriangle(int row, int levels) {
    if (row > levels) {
        return;
    }
    printRow(row, row);  // Cetak baris dengan angka berulang
    cout << endl;
    printTriangle(row + 1, levels);  // Panggil rekursif untuk baris berikutnya
}

int main() {
    int levels = 3;
    cout << "Segitiga dengan pola 1 22 333:\n";
    printTriangle(1, levels);  // Mulai mencetak dari baris 1
    return 0;
}
