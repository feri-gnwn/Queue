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

struct Customer {
    int id;
    int arrivalTime;
    int serviceTime;
    int startTime;
    int departureTime;
    int waitingTime;
};

struct Node {
    Customer data;
    Node* next;
    Node(Customer cust) : data(cust), next(nullptr) {}
};

class Queue {
private:
    Node* front;
    Node* rear;
    int count = 0;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(int currentTime) {
        count++;
        int arrival = currentTime;
        int service = rand() % 5 + 2; // 2-6
        Customer cust = {count, arrival, service, 0, 0, 0};
        Node* temp = new Node(cust);
        if (!front) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }

        std::cout << "Customer " << count << " masuk antrian pada waktu " << arrival << " dengan service time " << service << "\n";
    }

    void processQueue() {
        if (!front) {
            std::cout << "Antrian kosong.\n";
            return;
        }

        std::cout << "\nMemproses antrian...\n";
        int currentTime = 0;
        Node* curr = front;

        while (curr) {
            Customer& c = curr->data;
            c.startTime = std::max(currentTime, c.arrivalTime);
            c.departureTime = c.startTime + c.serviceTime;
            c.waitingTime = c.startTime - c.arrivalTime;

            currentTime = c.departureTime;
            curr = curr->next;
        }

        printQueue();
    }

    void printQueue() {
        Node* curr = front;
        std::cout << "\n---------------------------------------------------------\n";
        std::cout << "ID\tArrival\tService\tStart\tFinish\tWaiting\n";
        std::cout << "---------------------------------------------------------\n";
        double totalWait = 0;
        int totalCust = 0;

        while (curr) {
            Customer& c = curr->data;
            std::cout << c.id << "\t" << c.arrivalTime << "\t" << c.serviceTime << "\t"
                      << c.startTime << "\t" << c.departureTime << "\t" << c.waitingTime << "\n";
            totalWait += c.waitingTime;
            totalCust++;
            curr = curr->next;
        }

        std::cout << "---------------------------------------------------------\n";
        std::cout << "Rata-rata waktu tunggu: "
                  << std::fixed << std::setprecision(2)
                  << (totalCust > 0 ? totalWait / totalCust : 0.0) << "\n";
    }

    ~Queue() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main() {
    srand(time(0));
    Queue antrian;
    int time = 0;
    int choice;

    do {
        std::cout << "\n===== Menu Simulasi Antrian =====\n";
        std::cout << "[1] Tambah Customer\n";
        std::cout << "[2] Tampilkan Antrian\n";
        std::cout << "[3] Simulasikan Pelayanan\n";
        std::cout << "[0] Keluar\n";
        std::cout << "Pilihan: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                time += rand() % 5 + 1; // simulasikan waktu berjalan
                antrian.enqueue(time);
                break;
            case 2:
                antrian.printQueue();
                break;
            case 3:
                antrian.processQueue();
                break;
            case 0:
                std::cout << "Keluar dari program.\n";
                break;
            default:
                std::cout << "Pilihan tidak valid!\n";
        }

    } while (choice != 0);

    return 0;
}
