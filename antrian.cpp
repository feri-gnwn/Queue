// mensimulasikan antrian

// no antrian
// kapan masuk ke antrian(time)
// kapan keluar dari antrian (service time)

// waktunya acak, tapi karna dia antrian Waktu acakny hrus berurut
// dan rata rata servis time nya

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Customer
{
    int id;
    int arrivalTime;
    int serviceTime;
    int startTime;
    int departureTime;
    int waitingTime;
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
    Node *front;
    Node *rear;
    int count = 0;

public:
    Queue() : front(nullptr), rear(nullptr) {}
    void enqueue(int currentTime);
    void processQueue();
    void printQueue();
    ~Queue();
};

void Queue::enqueue(int currentTime)
{
    count++;
    int arrival = currentTime;
    int service = rand() % 50 + 10; // 10 - 50 menit
    Customer cust = {count, arrival, service, 0, 0, 0};
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

    cout << "Customer " << count << " masuk antrian pada waktu " << arrival << " dengan service time " << service << "\n";
}

void Queue::processQueue()
{
    if (!front)
    {
        cout << "Antrian kosong.\n";
        return;
    }

    cout << "\nMemproses antrian...\n";
    int currentTime = 0;
    Node *curr = front;

    while (curr)
    {
        Customer &c = curr->data;
        c.startTime = max(currentTime, c.arrivalTime);
        c.departureTime = c.startTime + c.serviceTime;
        c.waitingTime = c.startTime - c.arrivalTime;

        currentTime = c.departureTime;
        curr = curr->next;
    }

    printQueue();
}

void Queue::printQueue()
{
    Node *curr = front;
    cout << "\n---------------------------------------------------------\n";
    cout << left << setw(5) << "ID"
         << setw(10) << "Arrival"
         << setw(10) << "Service"
         << setw(10) << "Start"
         << setw(10) << "Finish"
         << setw(10) << "Waiting\n";
    cout << "---------------------------------------------------------\n";
    double totalWait = 0;
    int totalCust = 0;

    while (curr)
    {
        Customer &c = curr->data;
        cout << c.id << "\t" << c.arrivalTime << "\t" << c.serviceTime << "\t"
             << c.startTime << "\t" << c.departureTime << "\t" << c.waitingTime << "\n";
        totalWait += c.waitingTime;
        totalCust++;
        curr = curr->next;
    }

    cout << "---------------------------------------------------------\n";
    cout << "Rata-rata waktu tunggu: "
         << fixed << setprecision(2)
         << (totalCust > 0 ? totalWait / totalCust : 0.0) << "\n";
}

Queue::~Queue()
{
    while (front)
    {
        Node *temp = front;
        front = front->next;
        delete temp;
    }
}

int main()
{
    srand(time(0));
    Queue antrian;
    int time = 0;
    int choice;
    // bool alreadyProcessed = false;


    do
    {
        cout << "\n===== Menu Simulasi Antrian =====\n";
        cout << "[1] Tambah Customer\n";
        cout << "[2] Tampilkan Antrian\n";
        cout << "[3] Simulasikan Pelayanan\n";
        cout << "[0] Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            time += rand() % 5 + 1; // simulasikan waktu berjalan
            antrian.enqueue(time);
            break;
        case 2:
            antrian.printQueue();
            break;
        case 3:
            antrian.processQueue();
            // if (!alreadyProcessed)
            // {
            //     antrian.processQueue();
            //     alreadyProcessed = true;
            // }
            // else
            // {
            //     cout << "Antrian sudah diproses sebelumnya.\n";
            // }
            break;
        case 0:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (choice != 0);

    return 0;
}

// Fitur advanced:
// 1. Masukan data nama yang antri dan waktu seperti jam namun acak ga hars jam sekarang. antrian berikutnya mengikuuti jam yang pertama
// 2. Tammbahkan fitur untuk menghapus customer dari antrian
// 3. Reset antrian
