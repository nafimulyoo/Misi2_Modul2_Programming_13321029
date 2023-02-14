#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Menu {
    int id;
    string name;
    string category;
    double price;
};



vector<Menu> menus;
vector<pair<string, Menu>> salesHistory;

void showMenu() {
    cout << "Menu: " << endl;
    cout << "===========================" << endl;
    cout << "ID\tNama\tKategori\tHarga" << endl;
    cout << "===========================" << endl;
    for (const auto& menu : menus) {
        cout << menu.id << "\t" << menu.name << "\t" << menu.category << "\t" << menu.price << endl;
    }
    cout << "===========================" << endl;
}

void makePurchase(string customerName, int quantity, int id) {
    double total = quantity * menus.price;
    salesHistory.push_back(make_pair(customerName, menus, quantity, total));
    ofstream file("transaction_notes.txt", ios::app);
    file << "Nama: " << customerName << endl;
    file << "Menu: " << menus.name << endl;
    file << "Jumlah: " << quantity << endl;
    file << "Total: " << total << endl;
    file << "===========================" << endl;
    file.close();
}

void showTransaction() {
    string filename = "transaksi.txt";
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void addMenu() {
    menus.push_back({1, "Nasi Goreng", "Makanan", 15000});
    menus.push_back({2, "Mie Ayam", "Makanan", 12000});
    menus.push_back({3, "Es Teh Manis", "Minuman", 5000});
    menus.push_back({4, "Es Jeruk", "Minuman", 6000});
}

int main() {
    string choice1;
    string choice2;
    string customerName;

    addMenu();

    do {
        cout << "Selamat datang di warung kami!" << endl;
        cout << "Silakan pilih salah satu menu di bawah ini:" << endl;
        cout << "1. Tutup" << endl;
        cout << "2. Pelanggan masuk" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> choice1;

        do {
            if (choice1 == "2") {
                cout << "Masukkan nama Anda: ";
                cin >> customerName;
                cout << "Silahkan pilih menu di bawah ini: " << endl;
                cout << "1. Lihat menu" << endl;
                cout << "2. Beli" << endl;
                cout << "3. Keluar" << endl;
                cin >> choice2;


                if (choice2 == "1") {
                    showMenu();
                } else if (choice2 == "2") {
                    int quantity;
                    int id;
                    cout << "Masukkan ID menu: ";
                    cin >> id;
                    cout << "Masukkan jumlah: ";
                    cin >> quantity;
                    makePurchase(customerName, quantity, id);
                } else if (choice2 == "3") {
                    // Looping Ulang
                } else {
                    cout << "Pilihan tidak valid!" << endl;
                }

            } else if (choice1 == "1") {
                if (salesHistory.empty()) {
                    cout << "Penjualan sesi ini:" << endl;
                    cout << "Tidak Ada Penjualan" << endl;
                    cout << "===========================" << endl;
                    cout << "Penjualan sebelumnya:" << endl;
                    showTransaction();
                } else {
                    showTransaction();
                }
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }

        } while (choice2 != "3");
    } while (choice1 != "1");
    return 0;
}
