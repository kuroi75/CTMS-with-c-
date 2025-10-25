#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <ctime>

using namespace std;

// Train Class
class Train {
private:
    int trainNumber;
    string trainName;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;
    double ticketPrice;
    string departureTime;

public:
    // Constructor
    Train(int num, string name, string src, string dest, int seats, double price, string time) {
        trainNumber = num;
        trainName = name;
        source = src;
        destination = dest;
        totalSeats = seats;
        availableSeats = seats;
        ticketPrice = price;
        departureTime = time;
    }

    // Getter methods
    int getTrainNumber() { return trainNumber; }
    string getTrainName() { return trainName; }
    string getSource() { return source; }
    string getDestination() { return destination; }
    int getTotalSeats() { return totalSeats; }
    int getAvailableSeats() { return availableSeats; }
    double getTicketPrice() { return ticketPrice; }
    string getDepartureTime() { return departureTime; }

    // Setter methods
    void setAvailableSeats(int seats) { availableSeats = seats; }

    // Method to book seats
    bool bookSeats(int numSeats) {
        if (availableSeats >= numSeats) {
            availableSeats -= numSeats;
            return true;
        }
        return false;
    }

    // Method to cancel seats
    void cancelSeats(int numSeats) {
        availableSeats += numSeats;
        if (availableSeats > totalSeats) {
            availableSeats = totalSeats;
        }
    }

    // Method to display train details
    void displayTrainInfo() {
        cout << left << setw(10) << trainNumber
             << setw(20) << trainName
             << setw(15) << source
             << setw(15) << destination
             << setw(15) << availableSeats
             << setw(12) << fixed << setprecision(2) << ticketPrice
             << setw(12) << departureTime << endl;
    }
};

// Ticket Class
class Ticket {
private:
    int ticketId;
    int trainNumber;
    string passengerName;
    int numberOfSeats;
    double totalAmount;
    string bookingDate;
    bool isCancelled;

public:
    // Constructor
    Ticket(int id, int trainNum, string passenger, int seats, double amount, string date) {
        ticketId = id;
        trainNumber = trainNum;
        passengerName = passenger;
        numberOfSeats = seats;
        totalAmount = amount;
        bookingDate = date;
        isCancelled = false;
    }

    // Getter methods
    int getTicketId() { return ticketId; }
    int getTrainNumber() { return trainNumber; }
    string getPassengerName() { return passengerName; }
    int getNumberOfSeats() { return numberOfSeats; }
    double getTotalAmount() { return totalAmount; }
    string getBookingDate() { return bookingDate; }
    bool getIsCancelled() { return isCancelled; }

    // Method to cancel ticket
    void cancelTicket() {
        isCancelled = true;
    }

    // Method to display ticket details
    void displayTicketInfo(Train* train) {
        cout << "\n========================================\n";
        cout << "        TICKET DETAILS\n";
        cout << "========================================\n";
        cout << "Ticket ID: " << ticketId << endl;
        cout << "Passenger: " << passengerName << endl;
        cout << "Train Number: " << trainNumber << endl;
        if (train) {
            cout << "Train Name: " << train->getTrainName() << endl;
            cout << "Route: " << train->getSource() << " -> " << train->getDestination() << endl;
            cout << "Departure: " << train->getDepartureTime() << endl;
        }
        cout << "Seats Booked: " << numberOfSeats << endl;
        cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
        cout << "Booking Date: " << bookingDate << endl;
        cout << "Status: " << (isCancelled ? "CANCELLED" : "CONFIRMED") << endl;
        cout << "========================================\n";
    }
};

// TrainManagementSystem Class
class TrainManagementSystem {
private:
    vector<Train*> trains;
    vector<Ticket*> tickets;
    int ticketCounter;
    const string ADMIN_PASSWORD = "admin123";

    // Helper methods
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void pauseScreen() {
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        return to_string(1900 + ltm->tm_year) + "-" + 
               to_string(1 + ltm->tm_mon) + "-" + 
               to_string(ltm->tm_mday);
    }

    Train* findTrainByNumber(int trainNum) {
        for (auto train : trains) {
            if (train->getTrainNumber() == trainNum) {
                return train;
            }
        }
        return nullptr;
    }

    Ticket* findTicketById(int ticketId) {
        for (auto ticket : tickets) {
            if (ticket->getTicketId() == ticketId) {
                return ticket;
            }
        }
        return nullptr;
    }

public:
    // Constructor
    TrainManagementSystem() {
        ticketCounter = 1000;
        initializeSampleData();
    }

    // Destructor to free memory
    ~TrainManagementSystem() {
        for (auto train : trains) {
            delete train;
        }
        for (auto ticket : tickets) {
            delete ticket;
        }
    }

    // Initialize sample data
    void initializeSampleData() {
        trains.push_back(new Train(101, "Dhaka Express", "Dhaka", "Chittagong", 200, 500.0, "08:00 AM"));
        trains.push_back(new Train(102, "Sylhet Mail", "Dhaka", "Sylhet", 150, 400.0, "10:30 AM"));
        trains.push_back(new Train(103, "Rajshahi Express", "Dhaka", "Rajshahi", 180, 450.0, "02:00 PM"));
        trains.push_back(new Train(104, "Khulna Special", "Dhaka", "Khulna", 160, 420.0, "06:00 PM"));
    }

    // Main Menu
    void mainMenu() {
        while (true) {
            clearScreen();
            cout << "\n========================================\n";
            cout << "   TRAIN MANAGEMENT SYSTEM\n";
            cout << "========================================\n";
            cout << "1. Admin Login (By Pass)\n";
            cout << "2. User (Guest Mode)\n";
            cout << "3. Exit\n";
            cout << "========================================\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1:
                    adminLogin();
                    break;
                case 2:
                    userGuestMode();
                    break;
                case 3:
                    cout << "\nThank you for using Train Management System!\n";
                    return;
                default:
                    cout << "\nInvalid choice! Please try again.\n";
                    pauseScreen();
            }
        }
    }

    // Admin Login
    void adminLogin() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "        ADMIN LOGIN\n";
        cout << "========================================\n";
        
        string password;
        cout << "Enter Admin Password: ";
        cin >> password;
        
        if (password == ADMIN_PASSWORD) {
            cout << "\nLogin Successful!\n";
            pauseScreen();
            adminMenu();
        } else {
            cout << "\nIncorrect Password! Access Denied.\n";
            pauseScreen();
        }
    }

    // Admin Menu
    void adminMenu() {
        while (true) {
            clearScreen();
            cout << "\n========================================\n";
            cout << "        ADMIN PANEL\n";
            cout << "========================================\n";
            cout << "1. Manage Train Function\n";
            cout << "2. View All Trains\n";
            cout << "3. Show Train Schedule (Two D1-D2)\n";
            cout << "4. Back to Main Menu\n";
            cout << "========================================\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1:
                    manageTrainFunction();
                    break;
                case 2:
                    viewAllTrains();
                    pauseScreen();
                    break;
                case 3:
                    showTrainSchedule();
                    pauseScreen();
                    break;
                case 4:
                    return;
                default:
                    cout << "\nInvalid choice! Please try again.\n";
                    pauseScreen();
            }
        }
    }

    // Manage Train Function
    void manageTrainFunction() {
        while (true) {
            clearScreen();
            cout << "\n========================================\n";
            cout << "    MANAGE TRAIN FUNCTION\n";
            cout << "========================================\n";
            cout << "1. Add Train\n";
            cout << "2. Delete Train\n";
            cout << "3. Back to Admin Menu\n";
            cout << "========================================\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1:
                    addTrain();
                    break;
                case 2:
                    deleteTrain();
                    break;
                case 3:
                    return;
                default:
                    cout << "\nInvalid choice! Please try again.\n";
                    pauseScreen();
            }
        }
    }

    // Add Train
    void addTrain() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          ADD NEW TRAIN\n";
        cout << "========================================\n";
        
        int trainNumber, totalSeats;
        string trainName, source, destination, departureTime;
        double ticketPrice;
        
        cout << "Enter Train Number: ";
        cin >> trainNumber;
        
        cin.ignore();
        cout << "Enter Train Name: ";
        getline(cin, trainName);
        
        cout << "Enter Source Station: ";
        getline(cin, source);
        
        cout << "Enter Destination Station: ";
        getline(cin, destination);
        
        cout << "Enter Total Seats: ";
        cin >> totalSeats;
        
        cout << "Enter Ticket Price: ";
        cin >> ticketPrice;
        
        cin.ignore();
        cout << "Enter Departure Time (e.g., 08:00 AM): ";
        getline(cin, departureTime);
        
        Train* newTrain = new Train(trainNumber, trainName, source, destination, totalSeats, ticketPrice, departureTime);
        trains.push_back(newTrain);
        
        cout << "\nTrain added successfully!\n";
        pauseScreen();
    }

    // Delete Train
    void deleteTrain() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          DELETE TRAIN\n";
        cout << "========================================\n";
        
        if (trains.empty()) {
            cout << "\nNo trains available to delete!\n";
            pauseScreen();
            return;
        }
        
        viewAllTrains();
        
        int trainNum;
        cout << "\nEnter Train Number to Delete: ";
        cin >> trainNum;
        
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i]->getTrainNumber() == trainNum) {
                delete trains[i];
                trains.erase(trains.begin() + i);
                cout << "\nTrain deleted successfully!\n";
                pauseScreen();
                return;
            }
        }
        
        cout << "\nTrain not found!\n";
        pauseScreen();
    }

    // View All Trains
    void viewAllTrains() {
        clearScreen();
        cout << "\n========================================================================================================\n";
        cout << "                                    ALL TRAINS\n";
        cout << "========================================================================================================\n";
        
        if (trains.empty()) {
            cout << "\nNo trains available!\n";
            return;
        }
        
        cout << left << setw(10) << "Train No" 
             << setw(20) << "Train Name" 
             << setw(15) << "Source" 
             << setw(15) << "Destination" 
             << setw(15) << "Available" 
             << setw(12) << "Price" 
             << setw(12) << "Time" << endl;
        cout << "--------------------------------------------------------------------------------------------------------\n";
        
        for (auto train : trains) {
            train->displayTrainInfo();
        }
    }

    // Show Train Schedule
    void showTrainSchedule() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "      TRAIN SCHEDULE (D1-D2)\n";
        cout << "========================================\n";
        
        string source, destination;
        cin.ignore();
        
        cout << "Enter Source Station (D1): ";
        getline(cin, source);
        
        cout << "Enter Destination Station (D2): ";
        getline(cin, destination);
        
        bool found = false;
        
        cout << "\n========================================================================================================\n";
        cout << left << setw(10) << "Train No" 
             << setw(20) << "Train Name" 
             << setw(15) << "Available" 
             << setw(12) << "Price" 
             << setw(12) << "Time" << endl;
        cout << "--------------------------------------------------------------------------------------------------------\n";
        
        for (auto train : trains) {
            if (train->getSource() == source && train->getDestination() == destination) {
                cout << left << setw(10) << train->getTrainNumber()
                     << setw(20) << train->getTrainName()
                     << setw(15) << train->getAvailableSeats()
                     << setw(12) << fixed << setprecision(2) << train->getTicketPrice()
                     << setw(12) << train->getDepartureTime() << endl;
                found = true;
            }
        }
        
        if (!found) {
            cout << "\nNo trains available for this route!\n";
        }
    }

    // User Guest Mode
    void userGuestMode() {
        while (true) {
            clearScreen();
            cout << "\n========================================\n";
            cout << "        USER (GUEST MODE)\n";
            cout << "========================================\n";
            cout << "1. View Ticket\n";
            cout << "2. Buy Ticket\n";
            cout << "3. Cancel Ticket\n";
            cout << "4. Back to Main Menu\n";
            cout << "========================================\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1:
                    viewTicket();
                    break;
                case 2:
                    buyTicket();
                    break;
                case 3:
                    cancelTicket();
                    break;
                case 4:
                    return;
                default:
                    cout << "\nInvalid choice! Please try again.\n";
                    pauseScreen();
            }
        }
    }

    // Buy Ticket
    void buyTicket() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          BUY TICKET\n";
        cout << "========================================\n";
        
        // Show delay if any
        cout << "Checking train status...\n";
        cout << "All trains are running on time!\n\n";
        
        viewAllTrains();
        
        int trainNum;
        cout << "\nEnter Train Number: ";
        cin >> trainNum;
        
        Train* selectedTrain = findTrainByNumber(trainNum);
        
        if (selectedTrain == nullptr) {
            cout << "\nTrain not found!\n";
            pauseScreen();
            return;
        }
        
        int numSeats;
        cout << "Enter Number of Seats: ";
        cin >> numSeats;
        
        if (numSeats <= 0) {
            cout << "\nInvalid number of seats!\n";
            pauseScreen();
            return;
        }
        
        if (!selectedTrain->bookSeats(numSeats)) {
            cout << "\nInsufficient seats available!\n";
            cout << "Available seats: " << selectedTrain->getAvailableSeats() << endl;
            pauseScreen();
            return;
        }
        
        string passengerName;
        cin.ignore();
        cout << "Enter Passenger Name: ";
        getline(cin, passengerName);
        
        double totalAmount = numSeats * selectedTrain->getTicketPrice();
        
        // Payment
        cout << "\n========================================\n";
        cout << "Total Payment: $" << fixed << setprecision(2) << totalAmount << endl;
        cout << "========================================\n";
        cout << "Processing payment...\n";
        
        Ticket* newTicket = new Ticket(ticketCounter++, trainNum, passengerName, numSeats, totalAmount, getCurrentDate());
        tickets.push_back(newTicket);
        
        // Print Ticket
        cout << "\n========================================\n";
        cout << "        TICKET CONFIRMED\n";
        cout << "========================================\n";
        cout << "Ticket ID: " << newTicket->getTicketId() << endl;
        cout << "Passenger: " << newTicket->getPassengerName() << endl;
        cout << "Train: " << selectedTrain->getTrainName() << " (" << trainNum << ")" << endl;
        cout << "From: " << selectedTrain->getSource() << " To: " << selectedTrain->getDestination() << endl;
        cout << "Seats: " << numSeats << endl;
        cout << "Departure: " << selectedTrain->getDepartureTime() << endl;
        cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
        cout << "Booking Date: " << newTicket->getBookingDate() << endl;
        cout << "========================================\n";
        cout << "\nTicket booked successfully!\n";
        
        pauseScreen();
    }

    // View Ticket
    void viewTicket() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          VIEW TICKET\n";
        cout << "========================================\n";
        
        int ticketId;
        cout << "Enter Ticket ID: ";
        cin >> ticketId;
        
        Ticket* ticket = findTicketById(ticketId);
        
        if (ticket) {
            Train* train = findTrainByNumber(ticket->getTrainNumber());
            ticket->displayTicketInfo(train);
        } else {
            cout << "\nTicket not found!\n";
        }
        
        pauseScreen();
    }

    // Cancel Ticket
    void cancelTicket() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          CANCEL TICKET\n";
        cout << "========================================\n";
        
        int ticketId;
        cout << "Enter Ticket ID to Cancel: ";
        cin >> ticketId;
        
        string reason;
        cin.ignore();
        cout << "Enter Reason for Cancellation: ";
        getline(cin, reason);
        
        Ticket* ticket = findTicketById(ticketId);
        
        if (ticket && !ticket->getIsCancelled()) {
            ticket->cancelTicket();
            
            // Return seats to train
            Train* train = findTrainByNumber(ticket->getTrainNumber());
            if (train) {
                train->cancelSeats(ticket->getNumberOfSeats());
            }
            
            double refundAmount = ticket->getTotalAmount() * 0.8; // 80% refund
            
            cout << "\n========================================\n";
            cout << "Ticket cancelled successfully!\n";
            cout << "Refund Amount: $" << fixed << setprecision(2) << refundAmount << endl;
            cout << "Reason: " << reason << endl;
            cout << "Confirmation sent to your account.\n";
            cout << "========================================\n";
        } else {
            cout << "\nTicket not found or already cancelled!\n";
        }
        
        pauseScreen();
    }
};

// Main function
int main() {
    TrainManagementSystem tms;
    tms.mainMenu();
    return 0;
}
