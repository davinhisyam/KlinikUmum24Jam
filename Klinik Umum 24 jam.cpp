#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// Node structure for the linked list
struct Node {
    string name;
    string penyakit; // Informasi penyakit pasien
    string status;   // Status pasien (BPJS/Reguler)
    int harga;       // Harga yang harus dibayar oleh pasien
    Node* next;
};

int top = 0;

string jamjaga1() {
    return "07.00-15.00";
}

string jamjaga2() {
    return "15.00-23.00";
}

string jamjaga3() {
    return "23.00-07.00";
}

void tampilkanDokter(string dokter[3]) {
    cout << "Dokter yang tersedia : " << endl;
    for (int i = 0; i < top; i++) {
        cout << "Dr." << dokter[i] << " berjaga di jam ";
        if (i == 0) {
            cout << jamjaga1();
        }
        else if (i == 1) {
            cout << jamjaga2();
        }
        else if (i == 2) {
            cout << jamjaga3();
        }
        cout << endl;
    }
}

bool isFull() {
    return top >= 3;
}

bool isEmpty() {
    return top == 0; 
}

void tambahDokter(string dokter[3]) {
    if (top < 3) {
        cout << "Tambahkan Dokter: ";
        cin >> dokter[top];
        top++;
    }
    else {
        cout << "Jumlah Dokter Sudah Terpenuhi!" << endl;
    }
}

void tambah(string dokter[3]) {
    if (top < 3) {
        tambahDokter(dokter);
        tambahDokter(dokter);
        tambahDokter(dokter);
    }
    else {
        cout << "Jumlah Dokter Sudah Terpenuhi!" << endl;
    }
}

int getCurrentHour() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return ltm->tm_hour;
}

int getCurrentMinute(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return ltm->tm_min;
}

int getCurrentSecond(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return ltm->tm_sec;
}

int getCurrentDay(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return ltm->tm_mday;
}

int getCurrentMonth(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1 + ltm->tm_mon;
}

int getCurrentYear(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1900 + ltm->tm_year;
}

void dokterJagaSekarang(string dokter[3]) {
    int currentHour = getCurrentHour();
    int currentMinute = getCurrentMinute();
    int currentSecond = getCurrentSecond();
    int currentDay = getCurrentDay();
    int currentMonth = getCurrentMonth();
    int currentYear = getCurrentYear();
    cout << endl;
    cout << "Hari dan Tanggal Sekarang : " << getCurrentDay() << " / " << getCurrentMonth() << " / " << getCurrentYear() << "  / " << currentHour << ":" << currentMinute << ":" << getCurrentSecond() << endl;
    cout << "Dokter yang sedang berjaga : ";
    if (currentHour >= 7 && currentHour < 15) {
        cout << "Dr. " << dokter[0] << " berjaga di jam " << jamjaga1();
    }
    else if (currentHour >= 15 && currentHour < 23) {
        cout << "Dr. " << dokter[1] << " berjaga di jam " << jamjaga2();
    }
    else {
        cout << "Dr. " << dokter[2] << " berjaga di jam " << jamjaga3();
    }
    cout << endl;
}

// Linked list functions
void tambahAntrianDepan(Node*& head, string name, string penyakit, string status, int harga) {
    Node* newNode = new Node;
    newNode->name = name;
    newNode->penyakit = penyakit; // Menyimpan informasi penyakit
    newNode->status = status;     // Menyimpan status pasien
    newNode->harga = harga;       // Menyimpan harga yang harus dibayar
    newNode->next = head;
    head = newNode;
}

void tambahAntrianBelakang(Node*& head, string name, string penyakit, string status, int harga) {
    Node* newNode = new Node;
    newNode->name = name;
    newNode->penyakit = penyakit; // Menyimpan informasi penyakit
    newNode->status = status;     // Menyimpan status pasien
    newNode->harga = harga;       // Menyimpan harga yang harus dibayar
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void tampilkanAntrian(Node* head) {
    Node* temp = head;
    int nomorAntrian = 1;
    cout << "Antrian Pasien: " << endl;
    while (temp != NULL) {
        cout << nomorAntrian << ". Nama: " << temp->name << ", Penyakit: " << temp->penyakit << ", Status: " << temp->status << ", Harga: " << temp->harga << endl;
        temp = temp->next;
        nomorAntrian++;
    }
    if (nomorAntrian == 1) {
        cout << "Antrian Kosong" << endl;
    }
    cout << endl;
}

void updatePenyakitAntrian(Node*& head, string name, string newPenyakit) {
    Node* temp = head;
    bool found = false;
    while (temp != NULL) {
        if (temp->name == name) {
            temp->penyakit = newPenyakit;
            cout << "Informasi penyakit pasien berhasil diubah." << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "Nama pasien tidak ditemukan dalam antrian." << endl;
    }
}

void cariNamaAntrian(Node* head, string name) {
    Node* temp = head;
    int pos = 0;
    while (temp != NULL) {
        if (temp->name == name) {
            cout << "Nama pasien ditemukan pada antrian ke: " << pos + 1 << endl;
            return;
        }
        temp = temp->next;
        pos++;
    }
    cout << "Nama pasien tidak ditemukan." << endl;
}

// Fungsi untuk mencari node minimum dari sebuah linked list berdasarkan nama
Node* cariNodeMinimum(Node* head) {
    Node* minNode = head;
    Node* temp = head->next;
    while (temp != NULL) {
        if (temp->name < minNode->name) {
            minNode = temp;
        }
        temp = temp->next;
    }
    return minNode;
}

// Fungsi untuk melakukan sorting linked list berdasarkan nama secara ascending
void sortingAntrian(Node*& head) {
    Node* sorted = NULL;
    Node* temp = head;
    while (temp != NULL) {
        Node* minNode = cariNodeMinimum(temp);
        // Menghapus node minimum dari list sementara
        if (minNode == temp) {
            temp = temp->next;
        } else {
            Node* prev = temp;
            while (prev->next != minNode) {
                prev = prev->next;
            }
            prev->next = minNode->next;
        }
        // Menambahkan node minimum ke linked list hasil sorting
        minNode->next = sorted;
        sorted = minNode;
    }
    head = sorted;
}

void hapusPasien(Node*& head, string name) {
    Node* temp = head;
    Node* prev = NULL;
    while (temp != NULL && temp->name != name) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        cout << "Nama pasien tidak ditemukan." << endl;
    } else {
        // Menampilkan informasi pasien yang akan dihapus
        cout << "Nama Pasien: " << temp->name << ", Penyakit: " << temp->penyakit << ", Status: " << temp->status << ", Harga: " << temp->harga << endl;
        cout << "Pasien telah selesai di tindak lanjut" << endl;
        
        // Input harga yang harus dibayarkan
        int hargaBaru;
        cout << "Masukkan harga yang harus dibayar oleh pasien ini: ";
        cin >> hargaBaru;
        temp->harga = hargaBaru;
        
        // Konfirmasi untuk menghapus pasien
        char konfirmasi;
        cout << "Apakah Anda yakin ingin menghapus pasien ini? (y/n): ";
        cin >> konfirmasi;
        
        if (konfirmasi == 'y') {
            if (prev == NULL) { // Jika yang dihapus adalah elemen pertama
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Nama pasien berhasil dihapus dari antrian." << endl;
        } else {
            cout << "Penghapusan dibatalkan." << endl;
        }
    }
}

void displayMenu(string dokter[3], Node*& head) {
    int jaw;
    menu:
    cout << "Menu Program Klinik Umum 24 Jam: " << endl;
    if (isEmpty()) {
        cout << "Dokter Belum Tersedia! Silakan tambahkan dokter terlebih dahulu." << endl;
        tambah(dokter);
        system("cls");
        goto menu;
    }
    cout << "1. Dokter yang tersedia" << endl;
    cout << "2. Tampilkan Antrian Pasien" << endl;
    cout << "3. Tambah Antrian Pasien" << endl;
    cout << "4. Mengubah informasi Penyakit Pasien" << endl;
    cout << "5. Mencari Data Pasien" << endl;
    cout << "6. Menghapus Pasien yang sudah di tindak lanjuti dari Antrian" << endl;
    cout << "7. Mengurutkan Antrian Berdasarkan Nama (ascending)" << endl;
    cout << endl;
    cout << "Silahkan Pilih Program : "; cin >> jaw;
    system("cls");
    if (jaw == 1) {
        tampilkanDokter(dokter);
        dokterJagaSekarang(dokter);
        char x;
        cout << "Tekan k untuk kembali ke menu : ";
        cin >> x;
        if (x == 'k') {
            system("cls");
            cout << endl;
            goto menu;
        }
    } else if (jaw == 2) {
        tampilkanAntrian(head);
        char x;
        cout << "Tekan k untuk kembali ke menu : ";
        cin >> x;
        if (x == 'k') {
            system("cls");
            goto menu;
        }
    } else if (jaw == 3) {
        string name, penyakit, status;
        int harga;
        cout << "Masukkan nama pasien: ";
        cin >> name;
        cout << "Masukkan informasi penyakit: ";
        cin >> penyakit;
        cout << "Masukkan status pasien (BPJS/Reguler): ";
        cin >> status;
        cout << "Masukkan harga yang harus dibayar oleh pasien ini: ";
        cin >> harga;
        char darurat;
        cout << "Apakah pasien darurat? (y/n): ";
        cin >> darurat;
        if (darurat == 'y') {
            tambahAntrianDepan(head, name, penyakit, status, harga);
        } else {
            tambahAntrianBelakang(head, name, penyakit, status, harga);
        }
        system ("cls");
        goto menu;
    } else if (jaw == 4) {
        string name, newPenyakit;
        cout << "Masukkan nama pasien yang ingin diubah informasi penyakitnya: ";
        cin >> name;
        cout << "Masukkan informasi penyakit baru: ";
        cin >> newPenyakit;
        updatePenyakitAntrian(head, name, newPenyakit);
        char x;
        cout << "Tekan k untuk kembali ke menu : ";
        cin >> x;
        if (x == 'k') {
            system("cls");
            goto menu;
        }
    } else if (jaw == 5) {
        string name;
        cout << "Masukkan nama pasien yang dicari: ";
        cin >> name;
        cariNamaAntrian(head, name);
        char x;
        cout << "Tekan k untuk kembali ke menu : ";
        cin >> x;
        if (x == 'k') {
            system("cls");
            goto menu;
        }
    } else if (jaw == 6) {
        tampilkanAntrian(head);
        string name;
        cout << "Masukkan nama pasien yang ingin dihapus dari antrian: ";
        cin >> name;
        hapusPasien(head, name);
        char x;
        cout << "Tekan k untuk kembali ke menu : ";
        cin >> x;
        if (x == 'k') {
            system("cls");
            goto menu;
        }
    } else if (jaw == 7) {
        // Sorting antrian berdasarkan nama pasien
        sortingAntrian(head);
        cout << "Antrian berhasil diurutkan berdasarkan nama pasien (ascending)." << endl;
        char x;
        cout << "Tekan k untuk kembali ke menu : ";
        cin >> x;
        if (x == 'k') {
            system("cls");
            goto menu;
        }
    } else {
        cout << "Pilihan tidak valid. Silakan pilih kembali." << endl;
        char x;
        cout << "Tekan k untuk kembali ke menu : ";
        cin >> x;
        if (x == 'k') {
            system("cls");
            goto menu;
        }
    }       
}

int main() {
    string dokter[3];
    Node* head = NULL; // Head of the linked list
    displayMenu(dokter, head);
    return 0;
}
