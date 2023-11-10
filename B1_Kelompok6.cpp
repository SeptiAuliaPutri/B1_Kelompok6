#include <iostream>
#include <windows.h> 
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

struct paket // struct untuk data paket
{
    string username;
    int id;
    string sender;
    string receiver;
    string destination;
    string origin;
    string type;
    string resi;
    bool confirmed;
    bool bayar;
    float distance;
    float weight;
    float price;
    int estimatedTime;
    paket *next = NULL;
    paket *prev = NULL;
};

struct User // array of struct
{
    string username;
    string password;
};

string user; // Variable Global

bool cek_username(User user, string jenis) // Mengecek apakah username ada di csv lalu mengembalikan nilai boolean (true jika username ada, false jika tidak).
{
    fstream file;
    file.open("regis.csv", ios::in); // membuka file csv untuk regis
    while (!file.eof())
    {
        string username, password;
        getline(file, username, ',');
        getline(file, password, '\n');
        if (jenis == "regis") // Memeriksa apakah username yang ada di file sama dengan username yang ingin diperiksa (dalam objek user).
        {
            if (username == user.username)
            {
                return true;
            }
        }
        else if (jenis == "login") //  Memeriksa apakah username dan password yang ada di file sama dengan username dan password yang ingin diperiksa (dalam objek user)
        {
            if (username == user.username && password == user.password)
            {
                return true;
            }
        }
    }
    return false;
}

bool loginAdmin()
{
    string users = "admin";
    string passwords = "admin";
    string inputuser, inputpass;

    for (int a = 1; a <= 3; a++) // untuk percobaan sebanyak 3 kali
    {
        system("cls");
        cout << "Silahkan masukkan username dan password Anda untuk masuk ke dalam sistem!\n";
        cout << "Username: ";
        cin >> inputuser;
        cout << "Password: ";
        cin >> inputpass;
        cout << "\n";

        for (int i = 0; i < 1; i++)
        {
            if (inputuser == users && inputpass == passwords)
            {
                cout << "Selamat datang, " << inputuser << "!\n\n";
                system("pause");
                system("cls");
                return true;
            }
        }

        cout << "Username atau password salah. Silakan coba lagi.\n\n";
    }

    cout << "Anda telah mencapai batas maksimal 3x login! Silahkan masukkan username dan password anda yang benar!\n\n"; // jika usn dan pass salah sebanyak 3 kali
    return false;
}

void regis_csv() // Membuat regis
{
    User user_baru;
    fstream file; // Menulis di file regis.csv
    file.open("regis.csv", ios ::app);
    cout << "Masukkan username baru : ";
    cin >> ws;
    getline(cin, user_baru.username);
    cout << "Masukkan password baru : ";
    cin >> ws;
    getline(cin, user_baru.password);
    bool ada = cek_username(user_baru, "regis"); // Mengecek apakah regis sudah terdaftar apa belum
    if (ada == true)
    {
        system("cls");
        cout << "\nUsername sudah digunakan. Silahkan regis dengan username lain.\n" << endl;
        system("pause");
        system("cls");
        regis_csv();
    }
    else
    {
        system("cls");
        cout << "Registrasi berhasil. Anda bisa login dengan password dan username anda ^-^" << endl;
        file << user_baru.username << ',';
        file << user_baru.password << '\n';
    }
}

int kes = 3;     // Memberikan kesempatan percobaan 3 kali
void login_csv() // Login regis
{
    User user_new;
    ofstream file; // Untuk melihat data dalam file csv
    file.open("regis.csv", ios ::in);
    cout << "Masukkan username : ";
    cin >> ws;
    getline(cin, user_new.username);
    cout << "Masukkan password : ";
    cin >> ws;
    getline(cin, user_new.password);
    bool login = cek_username(user_new, "login"); // Mengecek apakah data yang dimasukan itu sudah terdaftar di file csv
    if (login == true)
    {
        user = user_new.username;
        cout << "Berhasil login!\n"
             << endl;
    }
    else
    {
        cout << "Login gagal" << endl;
        kes = kes - 1; // Jika login gagal kesempatan berkurang
        if (kes == 0)  // Jika kesempatan sudah habis maka program berhenti
        {
            exit(0);
        }
        login_csv();
    }
}

string generateResi(set<string> &usedResiSet)
{
    const int length = 12;                                                                      // panjang resi adalah 12
    const string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // karakter yang digunakan untuk membuat resi

    while (true)
    {
        string resi = "";

        for (int i = 0; i < length; i++)
        {
            int randomIndex = rand() % characters.length(); // membuat resi secara acak sesuai dengan panjang yang telah ditentukan
            resi += characters[randomIndex];
        }

        // Periksa apakah resi sudah digunakan
        if (usedResiSet.find(resi) == usedResiSet.end())
        {
            // Resi belum digunakan, tambahkan ke set dan kembalikan
            usedResiSet.insert(resi);
            return resi; // mengembalikan nilai resi kepada user
        }
    }
}

void addPacket(paket *&head, int &currentID, paket *&tail)
{
    paket *newPacket = new paket();                         // membuat paket baru
    ofstream file("paketconfirm.csv", ios::out | ios::app); // menambahkan data ke dalam csv

    newPacket->id = currentID++; // menambahkan id secara otomatis ke dalam csv dan jika datanya lebih dari satu id juga akan bertambah otomatis
    newPacket->confirmed = false;
    newPacket->next = NULL;
    newPacket->prev = NULL;

    newPacket->username = user; // menambahkan user ke dalam data paket sesuai dengan user yang sedang login
    newPacket->username;
    while (true)
    {
        cout << "Masukkan Nama Pengirim: "; // membersihkan buffer setelah pengguna memasukkan data menggunakan cin sehingga karakter yang tidak terbaca tidak mempengaruhi operasi getline atau fungsi input berikutnya.
        fflush(stdin);
        getline(cin, newPacket->sender);
        if (newPacket->sender.empty()) // inputan tidak boleh kosong
        {
            cout << "Nama pengirim tidak boleh kosong." << endl;
            system("pause");
            system("cls");
            continue; // Jika inputan kosong, maka program akan meminta user menginput kembali
        }

        break; // Keluar dari loop jika inputan benar
    }

    while (true)
    {
        cout << "Masukkan Nama Penerima: ";
        getline(cin, newPacket->receiver);
        if (newPacket->receiver.empty())
        {
            cout << "Nama penerima tidak boleh kosong." << endl;
            system("pause");
            system("cls");
            continue; // Jika inputan kosong, maka program akan meminta user menginput kembali
        }
        break; // Keluar dari loop jika inputan benar
    }

    while (true)
    {
        cout << "Masukkan Alamat Tujuan Paket: ";
        getline(cin, newPacket->destination);
        if (newPacket->destination.empty())
        {
            cout << "Alamat tujuan paket tidak boleh kosong." << endl;
            system("pause");
            system("cls");
            continue; // Jika inputan kosong, maka program akan meminta user menginput kembali
        }

        break; // Keluar dari loop jika inputan benar
    }

    while (true)
    {
        cout << "Masukkan Alamat Asal: ";
        getline(cin, newPacket->origin);
        if (newPacket->origin.empty())
        {
            cout << "Alamat asal tidak boleh kosong." << endl;
            system("pause");
            system("cls");
            continue; // Jika inputan kosong, maka program akan meminta user menginput kembali
        }

        if (newPacket->origin == newPacket->destination)
        {
            cout << "Alamat asal dan tujuan tidak boleh sama" << endl;
            system("pause");
            system("cls");

            // kembali ke inputan alamat tujuan
            while (true)
            {
                cout << "Masukkan Alamat Tujuan Paket: ";
                getline(cin, newPacket->destination);
                if (newPacket->destination.empty())
                {
                    cout << "Alamat tujuan Paket tidak boleh kosong." << endl;
                    system("pause");
                    system("cls");
                    continue;
                }

                break;
            }

            // Balik ke inputan Alamat Asal
            continue;
        }

        break;
    }

    while (true)
    {
        cout << "Jenis Paket: ";
        getline(cin, newPacket->type);
        if (newPacket->type.empty())
        {
            cout << "Jenis paket tidak boleh kosong." << endl;
            system("pause");
            system("cls");
            continue; // Jika inputan kosong, maka program akan meminta user menginput kembali
        }
        break; // Keluar dari loop jika inputan benar
    }

    srand(time(0));

    // Set untuk menyimpan resi yang sudah digunakan
    set<string> usedResiSet;

    // Contoh penggunaan
    for (int i = 0; i < 1; i++)
    {
        string resi = generateResi(usedResiSet);
        newPacket->resi = resi;
        cout << "Resi : " << resi << endl;
    }

    // Queue
    if (head == NULL)
    {
        head = newPacket;
        tail = newPacket; // Set tail jika ini adalah node pertama
    }
    else
    {
        paket *lastPacket = tail;
        lastPacket->next = newPacket;
        newPacket->prev = lastPacket;
        tail = newPacket; // Perbarui tail
    }

    file << newPacket->username << ","; // memasukkan data paket yang ditambahkan ke dalam queue
    file << newPacket->id << ",";
    file << newPacket->sender << ",";
    file << newPacket->receiver << ",";
    file << newPacket->destination << ",";
    file << newPacket->origin << ",";
    file << newPacket->type << ",";
    file << newPacket->resi << ",";
    file << "\n";

    file.close();

    cout << "Paket berhasil ditambahkan ke dalam antrean.\n";
}

void loadData(paket *&head, paket *&tail, int &currentID)
{
    ifstream file("paketconfirm.csv"); // membuka file csv
    string line;

    while (getline(file, line)) // loop untuk membagi baris csv dengan koma agar data lebih mudah dibaca
    {
        stringstream ss(line);
        string username, id, sender, receiver, destination, origin, type, resi, confirmed, distance, weight, price, estimatedTime, bayar;

        getline(ss, username, ',');
        getline(ss, id, ',');
        getline(ss, sender, ',');
        getline(ss, receiver, ',');
        getline(ss, destination, ',');
        getline(ss, origin, ',');
        getline(ss, type, ',');
        getline(ss, resi, ',');
        getline(ss, confirmed, ',');
        getline(ss, distance, ',');
        getline(ss, weight, ',');
        getline(ss, price, ',');
        getline(ss, estimatedTime, ',');
        getline(ss, bayar, ',');

        paket *newPacket = new paket();
        newPacket->username = username;          // membedakan paket per user
        std::istringstream(id) >> newPacket->id; // Konversi ke int

        // Perbarui currentID jika ID baru yang ditemukan lebih besar
        if (newPacket->id >= currentID)
        {
            currentID = newPacket->id + 1;
        }

        newPacket->sender = sender;
        newPacket->receiver = receiver;
        newPacket->destination = destination;
        newPacket->origin = origin;
        newPacket->type = type;
        newPacket->resi = resi;
        newPacket->confirmed = (confirmed == "Terkonfirmasi");

        if (newPacket->confirmed)
        {
            std::istringstream(distance) >> newPacket->distance;           // Konversi ke float
            std::istringstream(weight) >> newPacket->weight;               // Konversi ke float
            std::istringstream(price) >> newPacket->price;                 // Konversi ke float
            std::istringstream(estimatedTime) >> newPacket->estimatedTime; // Konversi ke int
        }

        if (bayar == "Sudah Dibayar")
        {
            newPacket->bayar = true; // Setel atribut bayar menjadi true jika paket sudah dibayar
        }
        else
        {
            newPacket->bayar = false; // Setel atribut bayar menjadi false jika paket belum dibayar
        }

        newPacket->next = NULL;
        newPacket->prev = NULL;

        if (head == NULL) // menambahkan paket ke dalam queue
        {
            head = newPacket;
            tail = newPacket;
        }
        else
        {
            tail->next = newPacket;
            newPacket->prev = tail;
            tail = newPacket;
        }
    }

    file.close();
}

void savedata(paket *head)
{
    ofstream file("paketconfirm.csv"); // membuka file csv
    if (!file)
    {
        cout << "Gagal membuka file" << endl;
        return;
    }

    paket *paket = head;
    while (paket != NULL) // loop untuk menyimpan data ke dalam csv
    {
        file << paket->username << ",";
        file << paket->id << ",";
        file << paket->sender << ",";
        file << paket->receiver << ",";
        file << paket->destination << ",";
        file << paket->origin << ",";
        file << paket->type << ",";
        file << paket->resi << ",";
        file << (paket->confirmed ? "Terkonfirmasi" : "Belum dikonfirmasi") << ",";
        if (paket->confirmed) // jika paket sudah di konfirmasi, maka data konfirmasi akan tertambah secara otomatis ke dalam csv
        {
            file << paket->distance << ",";
            file << paket->weight << ",";
            file << paket->price << ",";
            file << paket->estimatedTime << ",";
            ;
        }
        file << (paket->bayar ? "Sudah Dibayar" : "Belum Dibayar"); // menambahkan informasi pembayaran ke dalam csv
        file << "\n";

        paket = paket->next;
    }

    file.close();
}

void confirmPackets(paket *head, paket *tail)
{
    if (head != NULL)
    {
        paket *currentPacket = head; // paket yang akan dikonfirmasi akan menjadi head

        while (currentPacket != NULL && currentPacket->confirmed)
        {
            currentPacket = currentPacket->next;
        }

        if (currentPacket != NULL) // loop untuk mengkonfirmasi paket
        {
            cout << "Admin akan mengkonfirmasi Paket " << currentPacket->id << ": " << currentPacket->sender << " -> " << currentPacket->receiver << endl;

            while (true)
            {
                cout << "Masukkan Jarak (km): ";
                if (cin >> currentPacket->distance)
                {
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // error handling untuk inputan harus berupa angka
                    cout << "Harus berupa angka. Coba lagi" << endl;
                }
            }

            while (true)
            {
                cout << "Masukkan Berat (kg): ";
                if (cin >> currentPacket->weight)
                {
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // error handling untuk inputan harus berupa angka
                    cout << "Harus berupa angka. Coba lagi" << endl;
                }
            }

            currentPacket->price = currentPacket->distance * currentPacket->weight; // menampilkan harga secara otomatis dengan cara mengkalikan jarak dan berat paket
            cout << "Harga: " << currentPacket->price << " ribu rupiah" << endl;

            while (true)
            {
                cout << "Masukkan Estimasi Waktu (hari): ";
                if (cin >> currentPacket->estimatedTime)
                {
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // error handling untuk inputan harus berupa angka
                    cout << "Harus berupa angka. Coba lagi" << endl;
                }
            }

            currentPacket->confirmed = true;
            cout << "Admin telah mengkonfirmasi Paket " << currentPacket->id << ": " << currentPacket->sender << " -> " << currentPacket->receiver << endl;
            system("pause");
            system("cls");

            // Menyimpan data yang baru saja diubah
            savedata(head);

            // Menampilkan data yang baru saja diubah
            cout << "=========================================================" << endl;
            cout << "           Data Paket yang baru dikonfirmasi " << endl;
            cout << "=========================================================" << endl;
            cout << "ID: " << currentPacket->id << endl;
            cout << "Nama Pengirim: " << currentPacket->sender << endl;
            cout << "Nama Penerima: " << currentPacket->receiver << endl;
            cout << "Jarak: " << currentPacket->distance << " km" << endl;
            cout << "Berat: " << currentPacket->weight << " kg" << endl;
            cout << "Harga: " << currentPacket->price << " ribu rupiah" << endl;
            cout << "Estimasi Waktu: " << currentPacket->estimatedTime << " hari" << endl;
            cout << "===========================================================" << endl;
        }
        else
        {
            cout << "Semua paket dalam antrian sudah terkonfirmasi atau antrian kosong." << endl;
        }
    }
    else
    {
        cout << "Antrian Paket kosong. Tidak ada paket yang dapat dikonfirmasi." << endl;
    }
}

bool isEmpty(paket *head, paket *tail)
{
    if (head == NULL && tail == NULL)
    {
        return true;
    }
    return false;
}

paket *SortedMerge(paket *a, paket *b);
void FrontBackSplit(paket *source, paket **frontRef, paket **backRef);
void MergeSort(paket **headRef)
{
    paket *head = *headRef;
    paket *a;
    paket *b;
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }
    FrontBackSplit(head, &a, &b);
    MergeSort(&a);
    MergeSort(&b);
    *headRef = SortedMerge(a, b);
}

paket *SortedMerge(paket *a, paket *b) // sorting paket
{
    paket *result = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (a->estimatedTime <= b->estimatedTime) // sorting berdasarkan estimasi waktu
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

void FrontBackSplit(paket *source, paket **frontRef, paket **backRef)
{
    paket *fast;
    paket *slow;
    slow = source;
    fast = source->next;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void countPacketsPerUser(paket *head, string &loggedInUser)
{
    int packetCount = 0;
    paket *currentPacket = head;

    while (currentPacket != NULL)
    {
        if (currentPacket->username == loggedInUser)
        {
            packetCount++; // menghitung jumlah paket sesuai user yang sedang login
        }
        currentPacket = currentPacket->next;
    }

    cout << "Jumlah data paket untuk pengguna " << loggedInUser << ": " << packetCount << endl;
}

paket *findNode(paket *head, int idx)
{
    paket *temp = head;

    for (int i = 0; i < idx; i++)
    {
        temp = temp->next;
    }

    return temp;
}

const int NO_OF_CHARS = 256;
void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
    {
        badChar[i] = -1;
    }

    for (int i = 0; i < size; i++)
    {
        badChar[tolower((int)str[i])] = i;
    }
}

void boyerMoore(paket *head, string pat, string &loggedInUser)
{
    int m = pat.size(); // mencari sesuai panjang pola
    paket *temp = head;
    int count = 0;
    while (temp != NULL)
    {
        int n = temp->resi.size(); // mencari resi sesuai panjang resi yang ditentukan
        int badChar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badChar);
        int s = 0;

        while (s <= (n - m))
        {
            int j = m - 1;

            while (j >= 0 && tolower(pat[j]) == tolower(temp->resi[s + j]))
            {
                j--;
            }
            if (j < 0 && temp->username == loggedInUser) // menampilkan data sesuai user
            {
                cout << "======================================================================" << endl;
                cout << "ID Paket: " << temp->id << endl;
                cout << "Nama Pengirim: " << temp->sender << endl;
                cout << "Nama Penerima: " << temp->receiver << endl;
                cout << "Alamat Tujuan Paket: " << temp->destination << endl;
                cout << "Alamat Asal: " << temp->origin << endl;
                cout << "Jenis Paket: " << temp->type << endl;
                cout << "Resi Paket: " << temp->resi << endl;
                cout << "Status: " << (temp->confirmed ? "Terkonfirmasi" : "Belum dikonfirmasi") << endl;
                cout << "Jarak: " << temp->distance << " km" << endl;
                cout << "Berat: " << temp->weight << " kg" << endl;
                cout << "Harga: " << temp->price << " ribu rupiah" << endl;
                cout << "Estimasi Waktu: " << temp->estimatedTime << " hari" << endl;
                cout << "======================================================================" << endl;
                count++; // menambah jumlah kemunculan nomor resi
                break;
            }
            else
            {
                s += max(1, j - badChar[temp->resi[s + j]]); // geser pola sejauh langkah maksimum antara karakter yang tidak cocok atau 1
            }
        }
        temp = temp->next; // pindah ke node berikutnya dalam queue
    }
    if (count == 0)
    {
        cout << "Data tidak ditemukan" << endl;
    }
}

void displayPacketHead(paket *head, paket *tail) // display paket dari head
{
    if (isEmpty(head, tail)) // jika queue paket tidak ada
    {
        cout << "Antrian Paket kosong." << endl;
    }
    else
    {
        paket *temp = head;
        cout << "Data Paket:" << endl;

        while (temp != NULL) // loop yang akan menampilkan data paket jika paket belum di konfirmasi
        {
            cout << "======================================================================" << endl;
            cout << "ID Paket: " << temp->id << endl;
            cout << "Nama Pengirim: " << temp->sender << endl;
            cout << "Nama Penerima: " << temp->receiver << endl;
            cout << "Alamat Tujuan Paket: " << temp->destination << endl;
            cout << "Alamat Asal: " << temp->origin << endl;
            cout << "Jenis Paket: " << temp->type << endl;
            cout << "Resi Paket: " << temp->resi << endl;
            cout << "Status: " << (temp->confirmed ? "Terkonfirmasi" : "Belum dikonfirmasi") << endl;

            if (temp->confirmed) // jika paket sudah di konfirmasi maka informasi ini juga akan muncul
            {
                cout << "Jarak: " << temp->distance << " km" << endl;
                cout << "Berat: " << temp->weight << " kg" << endl;
                cout << "Harga: " << temp->price << " ribu rupiah" << endl;
                cout << "Estimasi Waktu: " << temp->estimatedTime << " hari" << endl;
            }
            else // jika paket belum di konfirmasi maka informasi seperti ini yang akan muncul
            {
                cout << "Jarak: -" << endl;
                cout << "Berat: -" << endl;
                cout << "Harga: -" << endl;
                cout << "Estimasi Waktu: -" << endl;
            }

            cout << "Pembayaran: " << (temp->bayar ? "Sudah Dibayar" : "Belum Dibayar") << endl; // menampilkan informasi pembayaran

            cout << "======================================================================" << endl;
            temp = temp->next;
        }
    }
}

void displayPacketTail(paket *head, paket *tail) // display paket dari tail
{
    if (isEmpty(head, tail))
    {
        cout << "Antrian Paket kosong." << endl;
    }
    else
    {
        paket *temp = tail; // Mulai dari tail
        cout << "Data Paket:" << endl;

        while (temp != NULL) // loop yang akan menampilkan data paket jika paket belum di konfirmasi
        {
            cout << "======================================================================" << endl;
            cout << "ID Paket: " << temp->id << endl;
            cout << "Nama Pengirim: " << temp->sender << endl;
            cout << "Nama Penerima: " << temp->receiver << endl;
            cout << "Alamat Tujuan Paket: " << temp->destination << endl;
            cout << "Alamat Asal: " << temp->origin << endl;
            cout << "Jenis Paket: " << temp->type << endl;
            cout << "Resi Paket: " << temp->resi << endl;
            cout << "Status: " << (temp->confirmed ? "Terkonfirmasi" : "Belum dikonfirmasi") << endl;

            if (temp->confirmed) // jika paket sudah di konfirmasi maka informasi ini juga akan muncul
            {
                cout << "Jarak: " << temp->distance << " km" << endl;
                cout << "Berat: " << temp->weight << " kg" << endl;
                cout << "Harga: " << temp->price << " ribu rupiah" << endl;
                cout << "Estimasi Waktu: " << temp->estimatedTime << " hari" << endl;
            }

            else // jika paket belum di konfirmasi maka informasi seperti ini yang akan muncul
            {
                cout << "Jarak: -" << endl;
                cout << "Berat: -" << endl;
                cout << "Harga: -" << endl;
                cout << "Estimasi Waktu: -" << endl;
            }
            cout << "Pembayaran: " << (temp->bayar ? "Belum Dibayar" : "Sudah Dibayar") << endl;

            cout << "======================================================================" << endl;
            temp = temp->prev; // Bergerak mundur ke node sebelumnya
        }
    }
}

void displayUser(paket *head, paket *tail, const string &loggedInUser)
{
    if (isEmpty(head, tail)) // memeriksa apakah queue paket kosong
    {
        cout << "Antrian Paket kosong." << endl;
    }
    else
    {
        paket *temp = head;
        cout << "Data Paket Milik " << loggedInUser << ":" << endl;

        while (temp != NULL) // loop untuk menampilkan data paket sesuai dengan user yang sedang login
        {
            if (temp->username == loggedInUser)
            {
                cout << "======================================================================" << endl;
                cout << "Nama Pengirim: " << temp->sender << endl;
                cout << "Nama Penerima: " << temp->receiver << endl;
                cout << "Alamat Tujuan Paket: " << temp->destination << endl;
                cout << "Alamat Asal: " << temp->origin << endl;
                cout << "Jenis Paket: " << temp->type << endl;
                cout << "Resi Paket: " << temp->resi << endl;
                cout << "Status: " << (temp->confirmed ? "Terkonfirmasi" : "Belum dikonfirmasi") << endl;
                cout << "======================================================================" << endl;
            }

            temp = temp->next; // pindah ke node berikutnya dalam queue
        }
    }
}

void bayarPaket(paket *head, string &loggedInUser)
{
    if (head != NULL)
    {
        paket *currentPacket = head;
        bool found = false;
        while (currentPacket != NULL && currentPacket->bayar) // loop untuk menampilkan paket yang belum dibayar oleh user yang sedang login sesuai queue
        {
            currentPacket = currentPacket->next;
        }

        while (currentPacket != NULL)
        {
            if (currentPacket->username == loggedInUser)
            {
                if (currentPacket->confirmed) // jika paket sudah dikonfirmasi maka rincian yang harus dibayar akan muncul
                {
                    found = true;
                    cout << "======================================================" << endl;
                    cout << "                   RINCIAN PAKET                   " << endl;
                    cout << "======================================================" << endl;
                    cout << "Nama Pengirim: " << currentPacket->sender << endl;
                    cout << "Nama Penerima: " << currentPacket->receiver << endl;
                    cout << "Alamat Tujuan Paket: " << currentPacket->destination << endl;
                    cout << "Alamat Asal: " << currentPacket->origin << endl;
                    cout << "Jenis Paket: " << currentPacket->type << endl;
                    cout << "Resi: " << currentPacket->resi << endl;
                    cout << "Harga yang harus dibayar: " << currentPacket->price << " ribu rupiah" << endl;
                    cout << "======================================================" << endl;

                    int choice;
                    cout << "Metode Pembayaran:" << endl;
                    cout << "1. Transfer Bank" << endl;
                    cout << "2. DANA" << endl;
                    cout << "Masukkan Pilihan Metode Pembayaran: ";
                    cin >> choice;
                    system("pause");
                    system("cls");

                    if (choice == 1) // informasi pembayaran transfer bank
                    {
                        cout << "======================================================================" << endl;
                        cout << "Anda Memilih Transfer Bank Sebagai Metode Pembayaran" << endl;
                        cout << "Nomor Rekening Kantor Pos: 26282674998739" << endl;
                        cout << "Silakan transfer jumlah yang sesuai ke nomor rekening di atas." << endl;
                        cout << "======================================================================" << endl;
                    }
                    else if (choice == 2) // informasi pembayaran dana
                    {
                        cout << "======================================================================" << endl;
                        cout << "Anda Memilih DANA Sebagai Metode Pembayaran" << endl;
                        cout << "Nomor Telepon Kantor Pos: 081234456065" << endl;
                        cout << "Silakan transfer jumlah yang sesuai ke nomor telepon di atas." << endl;
                        cout << "======================================================================" << endl;
                    }
                    else
                    {
                        cout << "Pilihan tidak valid. Pembayaran dibatalkan." << endl; // error handling jika pilihan tidak valid
                        return;
                    }

                    while (true)
                    {
                        int input;
                        cout << "Masukkan Nominal Pembayaran: ";
                        cin >> input;

                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                            cout << "Masukkan harus berupa angka." << endl; // error handling agar user hanya menginputkan angka
                        }
                        else if (input < currentPacket->price)
                        {
                            cout << "Nominal pembayaran kurang dari total harga paket." << endl; // error handling jika user menginputkan kurang dari total harga
                        }
                        else if (input > currentPacket->price)
                        {
                            cout << "Nominal pembayaran lebih dari total harga paket." << endl; // error handling jika user menginputkan lebih dari total harga
                        }
                        else
                        {
                            currentPacket->bayar = true;
                            cout << "Pembayaran berhasil. Terima kasih!" << endl;
                            savedata(head); // Simpan perubahan status pembayaran paket ke dalam file csv
                            return;
                        }
                    }
                }
            }
            currentPacket = currentPacket->next;
        }

        if (!found) // jika paket belum dikonfirmasi admin tetapi user ingin membayar paket
        {
            cout << "Tidak ada paket terkonfirmasi untuk dibayar oleh pengguna " << loggedInUser << "." << endl;
        }
    }
    else // jika data paket user yang sedang login kosong
    {
        cout << "Antrian paket kosong. Tidak ada paket yang dapat dibayar." << endl;
    }
}

void editData(paket *head, paket *tail)
{
    if (head == NULL) // jika paket kosong
    {
        cout << "Data masih kosong" << endl;
        return;
    }

    displayPacketHead(head, tail); // menampilkan seluruh data paket yang ada di dalam csv

    int idToEdit; // variabel id yang ingin diubah
    cout << "Masukkan ID Paket yang ingin Anda edit: ";
    cin >> idToEdit;

    paket *currentPacket = head; // paket paling atas akan menjadi head

    while (currentPacket != NULL)
    {
        if (currentPacket->id == idToEdit) // mencari id paket yang sesuai
        {
            if (currentPacket->confirmed) // jika paket sudah dikonfirmasi
            {
                cout << "Paket dengan ID " << idToEdit << " ditemukan." << endl;
                while (true) // loop untuk mengedit estimasi waktu
                {
                    cout << "Masukkan Estimasi Waktu yang baru (hari): ";
                    cin >> currentPacket->estimatedTime;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "Harus berupa angka." << endl; // error handling agar admin hanya menginput angka
                    }
                    else
                    {
                        cout << "Estimasi Waktu berhasil diubah." << endl;
                        savedata(head); // Simpan data setelah perubahan
                        return;         // Keluar dari loop setelah mengedit
                    }
                }
            }
            else
            {
                cout << "Maaf, data belum dikonfirmasi. Tidak dapat mengedit estimasi waktu." << endl;
                return; // Keluar dari loop jika data belum dikonfirmasi
            }
        }
        currentPacket = currentPacket->next; // transversal ke paket next
    }
    cout << "Paket dengan ID " << idToEdit << " tidak ditemukan." << endl; // jika id yang dimasukkan tidak sama dengan id yang terdapat dalam csv
}

void deleteFirst(paket **head, paket **tail)
{
    if ((*head)->next == NULL)
    {
        *head = NULL;
        *tail = NULL;
    }
    else
    {
        delete *head; // memorinya yang dihapus
        *head = (*head)->next;
        (*head)->prev = NULL;
    }
}

void deleteLast(paket **head, paket **tail)
{
    if ((*head)->next == NULL)
    {
        deleteFirst(head, tail);
    }
    else
    {
        delete *tail; // memorinya yang dihapus
        *tail = (*tail)->prev;
        (*tail)->next = NULL;
    }
}

void deleteSpesific(paket **head, paket **tail, int id)
{
    if (*head == NULL) // jika data masih kosong
    {
        cout << "Data masih kosong." << endl;
        return;
    }

    paket *currentPacket = *head;
    bool found = false;

    while (currentPacket != NULL)
    {
        if (currentPacket->id == id)
        {
            found = true;
            break;
        }
        currentPacket = currentPacket->next;
    }

    if (found)
    {
        if (currentPacket->confirmed) // paket dapat dihapus jika sudah terkonfirmasi oleh admin dan dibayar oleh user
            if (currentPacket->bayar)
            {
                if (currentPacket == *head) // jika data yang akan dihapus merupakan head
                {
                    deleteFirst(head, tail);
                }
                else if (currentPacket == *tail) // jika data yang akan dihapus merupakan tail
                {
                    deleteLast(head, tail);
                }
                else
                {
                    currentPacket->prev->next = currentPacket->next; 
                    currentPacket->next->prev = currentPacket->prev;
                    delete currentPacket; // menghapus paket yang sudah sesuai dengan loop
                }
            }
            else // jika paket belum dibayar
            {
                cout << "Paket belum dibayar." << endl;
            }
        else // jika paket belum dikonfirmasi
        {
            cout << "Paket belum dikonfirmasi." << endl;
        }
        // Simpan ulang data ke file CSV setelah penghapusan
        savedata(*head);
    }
    else // jika id paket tidak ada di dalam csv
    { 
        cout << "Paket dengan ID " << id << " tidak ditemukan." << endl;
    }
}

int main()
{
    paket *head = NULL;              // variabel pointer head untuk menunjuk ke node pertama dan diatur ke NULL karena linked list masih kosong.
    paket *tail = NULL;              // variabel pointer tail untuk menunjuk ke node terakhir dan diatur ke NULL karena linked list masih kosong.
    bool isLoggedIn = false;         // variabel boolean untuk menandai apakah pengguna sudah masuk atau belum.
    string loggedInUser;             // menyimpan nama pengguna yang sedang masuk
    int currentID = 1;               // inisialisasi id paket
    loadData(head, tail, currentID); // memuat data paket dari file CSV ke dalam linked list dab mengupdate currentID sesuai dengan ID paket yang sudah ada.
    while (true)
    {
        cout << "=======================================" << endl;
        cout << "    Selamat Datang Di Kantor Pos       " << endl;
        cout << "=======================================" << endl;
        cout << "\t1. Admin" << endl;
        cout << "\t2. User" << endl;
        cout << "\t0. Exit" << endl;
        cout << "=======================================" << endl;
        cout << "Masukkan Pilihan Menu: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            isLoggedIn = loginAdmin(); // login sebagai admin

            while (isLoggedIn)
            {
                cout << "=========================" << endl;
                cout << "        MENU ADMIN       " << endl;
                cout << "=========================" << endl;
                cout << "1. Konfirmasi Paket" << endl;
                cout << "2. Sorting Paket" << endl;
                cout << "3. Display Paket" << endl;
                cout << "4. Update Paket" << endl;
                cout << "5. Hapus Paket" << endl;
                cout << "0. Logout" << endl;
                cout << "=========================" << endl;
                cout << "Masukkan Pilihan: ";
                cin >> choice;
                system("cls");

                if (choice == 1)
                {
                    confirmPackets(head, tail); // memanggil void confirm untuk menu konfirmasi paket
                    system("pause");
                    system("cls"); // membersihkan layar
                }
                else if (choice == 2)
                {
                    MergeSort(&head);              // memanggil void merge sort
                    displayPacketHead(head, tail); // menampilkan data setelah disorting
                    system("pause");
                    system("cls");
                }
                else if (choice == 3)
                {
                    system("cls");
                    int pilih;
                    cout << "=========================" << endl;
                    cout << "       DISPLAY DATA      " << endl;
                    cout << "=========================" << endl;
                    cout << "1. Display Head" << endl;
                    cout << "2. Display Tail" << endl;
                    cout << "=========================" << endl;
                    cout << "Masukkan Pilihan : ";
                    cin >> pilih;
                    system("cls");

                    if (pilih == 1)
                    {
                        displayPacketHead(head, tail); // memanggil void displayPacketHead
                        system("pause");
                        system("cls");
                    }
                    else if (pilih == 2)
                    {
                        displayPacketTail(head, tail); // memanggil void displayPacketTail
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        cout << "INPUT YANG BENAR" << endl; // error handling jika inputan tidak sesuai
                    }
                }
                else if (choice == 4)
                {
                    editData(head, tail); // memanggil void edit data
                    system("pause");
                    system("cls");
                }
                else if (choice == 5)
                {
                    while (true) // loop untuk menghapus data
                    {
                        if (head == NULL) // jika data masih kosong
                        {
                            cout << "Data masih kosong." << endl;
                            system("pause");
                            system("cls");
                            break;
                        }
                        int idToDelete; // memasukkan id paket yang akan dihapus
                        cout << "Masukkan ID paket yang ingin dihapus: ";
                        cin >> idToDelete;
                        deleteSpesific(&head, &tail, idToDelete); // memanggil void deletespesific
                        system("pause");
                        system("cls");
                        break;
                    }
                }
                else if (choice == 0)
                {
                    isLoggedIn = false; // jika login tidak berhasil
                    system("cls");
                }
                else
                {
                    cout << "Menu tidak ditemukan." << endl; // jika menu yang diinputkan tidak sesuai dengan menu yang tersedia
                    system("pause");
                    system("cls");
                }
            }
        }
        else if (choice == 2) // login user
        {
            system("cls");
            cout << "=========================" << endl;
            cout << "           USER          " << endl;
            cout << "=========================" << endl;
            cout << "1. Login" << endl;
            cout << "2. Registrasi" << endl;
            cout << "0. Logout" << endl;
            cout << "=========================" << endl;
            cout << "Masukkan Pilihan: ";
            cin >> choice;

            if (choice == 1)
            {
                login_csv();                     // login dengan data yang terdapat pada csv
                countPacketsPerUser(head, user); // menghitung jumlah paket per user
                system("pause");
                system("cls");

                while (true)
                {
                    cout << "\t" << endl;
                    cout << "=========================" << endl;
                    cout << "         MENU USER       " << endl;
                    cout << "=========================" << endl;
                    cout << "1. Tambah Paket" << endl;
                    cout << "2. Display Paket" << endl;
                    cout << "3. Bayar Paket" << endl;
                    cout << "4. Searching Paket" << endl;
                    cout << "0. Logout" << endl;
                    cout << "=========================" << endl;
                    cout << "Masukkan Pilihan: ";
                    cin >> choice;
                    system("cls");

                    if (choice == 1)
                    {
                        addPacket(head, currentID, tail); // memanggil void addPacket
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 2)
                    {
                        displayUser(head, tail, user); // memanggil void displayUser
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 3)
                    {
                        bayarPaket(head, user); // memanggil void bayarpaket
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 4)
                    {
                        string cari; // variabel untuk memasukkan nomor resi yang akan dicari
                        cout << "Masukkan nomor resi : ";
                        cin >> cari;
                        while (true)
                        {
                            if (cari.length() != 12) // memastikan panjang inputan
                            {
                                cout << "Nomor resi harus terdiri dari 12 karakter." << endl;
                                system("pause");
                                system("cls");
                                break;
                            }
                            boyerMoore(head, cari, user); // memanggil void boyermoore
                            system("pause");
                            system("cls");
                            break;
                        }
                    }
                    else if (choice == 0) // jika ingin logout dari menu user
                    {
                        break;
                        system("cls");
                    }
                    else // jika user menginputkan menu yang tidak ada pada pilihan
                    {
                        cout << "Menu tidak ditemukan." << endl;
                        system("pause");
                        system("cls");
                    }
                }
            }
            else if (choice == 2) // memanggil void regis jika user ingin registrasi
            {
                regis_csv();
                system("pause");
                system("cls");
            }
            else if (choice == 0) // jika ingin logout dari menu user
            {
                cout << "Logout berhasil." << endl;
                system("pause");
                system("cls"); // Keluar dari loop setelah logout berhasil
            }
        }
        else if (choice == 0) // logout dari menu utama
        {
            break;
            system("cls");
        }
        else // jika menu yang diinputkan tidak sesuai
        {
            cout << "Menu tidak ditemukan." << endl;
            system("pause");
            system("cls");
        }
    }

    return 0;
}