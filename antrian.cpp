#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

struct Customer
{
    int id;
    string nama;
    string merk;
    time_t kedatangan;
    time_t waktuMulai;
    time_t waktuSelesai;
    int waktuPelayanan;
};

struct Node
{
    Customer data;
    Node *next;
    Node(Customer cust) : data(cust), next(nullptr) {}
};

class Queue
{
private:
    private:
    Node *front;
    Node *rear;
    int count;
    time_t lastArrival = 0; // Waktu kedatangan terakhir

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}
    void enqueue(string nama, string merk);
    void processQueue();
    void printQueue();
    void clearQueue();
    string potongString(const string &s, size_t maxLen);
    ~Queue();
};

string Queue::potongString(const string &s, size_t maxLen)
{
    return s.length() > maxLen ? s.substr(0, maxLen) : s;
}

void Queue::enqueue(string nama, string merk)
{
    count++;
    Customer cust;
    cust.id = count;
    cust.nama = nama;
    cust.merk = merk;

    int offsetMinutes = rand() % 31 + 5; // Tambah 5-35 menit

    // Jika customer pertama, pakai waktu sekarang
    if (lastArrival == 0)
    {
        cust.kedatangan = time(0);
    }
    else
    {
        cust.kedatangan = lastArrival + (offsetMinutes * 60); // setelah customer sebelumnya
    }

    lastArrival = cust.kedatangan;

    cust.waktuPelayanan = rand() % 131 + 20; // 20 - 150 menit
    cust.waktuMulai = 0;
    cust.waktuSelesai = 0;

    Node *temp = new Node(cust);
    if (!front)
    {
        front = rear = temp;
    }
    else
    {
        rear->next = temp;
        rear = temp;
    }

    cout << "\n-" << setfill('-') << setw(70) << right << "-" << endl;
    cout << setfill(' ');
    cout << "Nama customer             : " << cust.nama << endl;
    cout << "Merk motor                : " << cust.merk << endl;
    cout << "Waktu kedatangan          : " << ctime(&cust.kedatangan);
    cout << "Perkiraan waktu pelayanan : " << cust.waktuPelayanan << " menit\n";
    cout << "-" << setfill('-') << setw(70) << right << "-" << endl;
    cout << setfill(' ') << left;

    cout << "Telah ditambahkan ke antrian." << endl;

    system("pause");
    system("cls");
}


void Queue::processQueue()
{
    if (!front)
    {
        cout << "Antrian kosong.\n";
        system("pause");
        system("cls");
        return;
    }

    Node *current = front;
    time_t startTime = current->data.kedatangan;

    while (current)
    {
        if (startTime < current->data.kedatangan)
        {
            startTime = current->data.kedatangan;
        }

        current->data.waktuMulai = startTime;
        current->data.waktuSelesai = current->data.waktuMulai + (current->data.waktuPelayanan * 60);
        startTime = current->data.waktuSelesai;
        current = current->next;
    }
    printQueue();

    system("pause");
    system("cls");
}

void Queue::printQueue()
{
    double totalWait = 0;
    int totalCust = 0;
    if (!front)
    {
        cout << "Antrian kosong.\n";
        system("pause");
        system("cls");
        return;
    }

    Node *curr = front;
    cout << "\n+" << setfill('-') << setw(100) << right << "+" << endl;
    cout << "|" << setfill(' ') << setw(55) << right << "PBO Group" << setw(45) << setfill(' ') << "|" << endl;
    cout << "|" << setfill(' ') << setw(61) << right << "Antrian Service Motor" << setw(39) << setfill(' ') << "|" << endl;
    cout << "+" << setfill('-') << setw(100) << right << "+" << endl;
    cout << setfill(' ') << left;

    cout << "| " << setw(2) << left << "ID"
         << " | " << setw(20) << left << "Nama"
         << " | " << setw(16) << left << "Merk"
         << " | " << setw(10) << left << "Kedatangan "
         << " | " << setw(14) << left << "Pelayanan"
         << " | " << setw(8) << left << "Mulai"
         << " | " << setw(8) << left << "Selesai"
         << " |" << endl;

    cout << "+" << setfill('-') << setw(100) << right << "+" << endl;
    cout << setfill(' ') << left;

    while (curr)
    {
        Customer &c = curr->data;
        cout << "| " << setw(2) << left << c.id
             << " | " << setw(20) << left << potongString(c.nama, 19)
             << " | " << setw(16) << left << potongString(c.merk, 15)
             << " | " << put_time(localtime(&c.kedatangan), " %H:%M:%S  ")
             << " | " << setw(12) << right << (to_string(c.waktuPelayanan) + " menit      ")
             << " | " << put_time(localtime(&c.waktuMulai), " %H:%M  ")
             << " | " << put_time(localtime(&c.waktuSelesai), " %H:%M  ")
             << " |" << endl;

        totalWait += c.waktuPelayanan;
        totalCust++;
        curr = curr->next;
    }

    cout << "+" << setfill('-') << setw(100) << right << "+" << endl;

    double avgWait = (totalCust > 0 ? totalWait / totalCust : 0.0);
    if (avgWait >= 60)
    {
        int jam = static_cast<int>(avgWait) / 60;
        int menit = static_cast<int>(avgWait) % 60;
        cout << "Rata-rata waktu tunggu: " << jam << " jam " << menit << " menit" << endl;
    }
    else
    {
        cout << "Rata-rata waktu tunggu: " << fixed << setprecision(2) << avgWait << " menit" << endl;
    }

    cout << "Total customer: " << totalCust << endl;
    system("pause");
    system("cls");
}

void Queue::clearQueue()
{
    front = rear = nullptr;
    count = 0;

    cout << "Antrian telah dikosongkan.\n";
    system("pause");
    system("cls");
}

Queue::~Queue()
{
    clearQueue();
}

int main()
{
    system("color 0B");
    system("cls");
    Queue antrian;
    string nama, merk;
    int choice;
    srand(time(0));

    while (true)
    {
        cout << "\n===== PBO Group =====\n";
        cout << "\n------ Antrian ------\n";
        cout << "[1] Tambah Customer\n";
        cout << "[2] Simulasikan Pelayanan\n";
        cout << "[3] Tampilkan Antrian\n";
        cout << "[4] Kosongkan Antrian\n";
        cout << "[0] Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Masukkan nama customer: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan merk motor: ";
            getline(cin, merk);
            antrian.enqueue(nama, merk);
            break;

        case 2:
            antrian.processQueue();
        break;
        
        case 3:
            antrian.printQueue();
            break;

        case 4:
            antrian.clearQueue();
            break;

        case 0:
            cout << "Keluar dari program.\n";
            return 0;

        default:
            cout << "Pilihan tidak valid!\n";
            system("pause");
            system("cls");
        }
    }

    return 0;
}
