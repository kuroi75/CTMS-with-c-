#include <bits/stdc++.h>
using namespace std;

class Train 
{
public:
    int id;
    string name, from, to;
    int seats;
    double price;

    Train(int i, string n, string f, string t, int s, double fa): id(i), name(n), from(f), to(t), seats(s), price(fa) {}

    void show() 
    {
        cout << id << ". " << name << " (" << from << " -> " << to << ")  Seats: " << seats << "  price: " << price << " Tk\n";
    }
};

class TrainSystem 
{
    vector<Train> trains;

public:
    TrainSystem() 
    {
        trains.push_back(Train(1, "Suborno Express", "Dhaka", "Chittagong", 50, 550));
        trains.push_back(Train(2, "Tista Express", "Dhaka", "Dinajpur", 40, 500));
        trains.push_back(Train(3, "Sundarban Express", "Dhaka", "Khulna", 30, 600));
    }

    void viewTrains()
    {
        cout << "\n--- Available Trains ---\n";
        for (auto&t : trains) t.show();
    }

    void buyTicket() 
    {
        int id, seat;
        string name, phone;

        cout << "\nEnter Train ID: ";
        cin >> id;
        if (id < 1 || id > (int)trains.size()) 
        {
            cout << "Invalid Train ID!\n";
            return;
        }

        Train &t = trains[id - 1];
        cout << "Enter Your Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone Number: ";
        getline(cin, phone);
        cout << "How many seats? ";
        cin >> seat;

        if (seat > t.seats || seat <= 0) 
        {
            cout << "Not enough seats!\n";
            return;
        }

        double total = seat * t.price;
        t.seats -= seat;

        cout << "\nTicket Confirmed!\n";
        cout << "Name: " << name << "\nPhone: " << phone
             << "\nTrain: " << t.name << "\nFrom: " << t.from
             << "\nTo: " << t.to << "\nSeats: " << seat
             << "\nTotal price: " << total << " Tk\n";
    }
};

void adminMenu(TrainSystem &sys) 
{
    int ch;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. View Trains\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1) sys.viewTrains();
    } 
    while (ch != 0);
}

void ticketMenu(TrainSystem &sys) 
{
    int ch;
    do {
        cout << "\n--- Ticket Menu ---\n";
        cout << "1. View Trains\n";
        cout << "2. Buy Ticket\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1) sys.viewTrains();
        else if (ch == 2) sys.buyTicket();
    } 
    while (ch != 0);
}

int main() 
{
    TrainSystem system;
    int ch;
    do {
        cout << "\n==== Train Management System ====\n";
        cout << "1. Admin Panel\n";
        cout << "2. Ticket Panel\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1) {
            string pass;
            cout << "Enter Admin Password: ";
            cin >> pass;
            if (pass == "123") adminMenu(system);
            else cout << "Wrong Password!\n";
        }
        else if (ch == 2) ticketMenu(system);
    } 
    while (ch != 0);

    cout << "\nThanks for using CTMS\n";
    return 0;
}
