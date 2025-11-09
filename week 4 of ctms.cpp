#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
using namespace std;

// User Class for authentication
class User {
private:
    string username;
    string password;
    string phoneNumber;
    string role; // "admin" or "user"

public:
    User(string uname, string pwd, string phone = "", string r = "user") {
        username = uname;
        password = pwd;
        phoneNumber = phone;
        role = r;
    }

    // Getter methods
    string getUsername() { return username; }
    string getPassword() { return password; }
    string getPhoneNumber() { return phoneNumber; }
    string getRole() { return role; }

    // Setter methods
    void setPassword(string pwd) { password = pwd; }
    void setPhoneNumber(string phone) { phoneNumber = phone; }
    
    // Method to save user data to file
    string toFileString() {
        return username + "," + password + "," + phoneNumber + "," + role;
    }
};

// Train Class
class Train {
private:
    int trainNumber;
    string trainName;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;
    double acPrice;
    double nonAcPrice;
    string departureTime;
    string coachType; // "AC" or "Non-AC"

public:
    // Constructor
    Train(int num, string name, string src, string dest, int seats, double ac, double nonAc, string time, string coach = "Both") {
        trainNumber = num;
        trainName = name;
        source = src;
        destination = dest;
        totalSeats = seats;
        availableSeats = seats;
        acPrice = ac;
        nonAcPrice = nonAc;
        departureTime = time;
        coachType = coach;
    }

    // Getter methods
    int getTrainNumber() { return trainNumber; }
    string getTrainName() { return trainName; }
    string getSource() { return source; }
    string getDestination() { return destination; }
    int getTotalSeats() { return totalSeats; }
    int getAvailableSeats() { return availableSeats; }
    double getAcPrice() { return acPrice; }
    double getNonAcPrice() { return nonAcPrice; }
    string getDepartureTime() { return departureTime; }
    string getCoachType() { return coachType; }

    // Setter methods
    void setAvailableSeats(int seats) { availableSeats = seats; }

    // Method to display train details
    void displayTrainInfo() {
        cout << left << setw(10) << trainNumber
             << setw(20) << trainName
             << setw(15) << source
             << setw(15) << destination
             << setw(10) << availableSeats
             << setw(12) << fixed << setprecision(2) << acPrice
             << setw(12) << fixed << setprecision(2) << nonAcPrice
             << setw(12) << departureTime << endl;
    }

    // Method to save train data to file
    string toFileString() {
        return to_string(trainNumber) + "," + trainName + "," + source + "," + 
               destination + "," + to_string(totalSeats) + "," + 
               to_string(availableSeats) + "," + to_string(acPrice) + "," + 
               to_string(nonAcPrice) + "," + departureTime + "," + coachType;
    }
};

// Ticket Class
class Ticket {
private:
    int ticketId;
    int trainNumber;
    string passengerName;
    string passengerPhone;
    int numberOfSeats;
    double totalAmount;
    string bookingDate;
    string coachType;
    bool isCancelled;
    string refundNumber;

public:
    // Constructor
    Ticket(int id, int trainNum, string passenger, string phone, int seats, double amount, string date, string coach) {
        ticketId = id;
        trainNumber = trainNum;
        passengerName = passenger;
        passengerPhone = phone;
        numberOfSeats = seats;
        totalAmount = amount;
        bookingDate = date;
        coachType = coach;
        isCancelled = false;
        refundNumber = "";
    }

    // Getter methods
    int getTicketId() { return ticketId; }
    int getTrainNumber() { return trainNumber; }
    string getPassengerName() { return passengerName; }
    string getPassengerPhone() { return passengerPhone; }
    int getNumberOfSeats() { return numberOfSeats; }
    double getTotalAmount() { return totalAmount; }
    string getBookingDate() { return bookingDate; }
    string getCoachType() { return coachType; }
    bool getIsCancelled() { return isCancelled; }
    string getRefundNumber() { return refundNumber; }

    void cancelTicket(string refundNum = "") { 
        isCancelled = true;
        refundNumber = refundNum;
    }
    
    // Method to save ticket data to file
    string toFileString() {
        return to_string(ticketId) + "," + to_string(trainNumber) + "," + passengerName + "," + 
               passengerPhone + "," + to_string(numberOfSeats) + "," + to_string(totalAmount) + "," + 
               bookingDate + "," + coachType + "," + (isCancelled ? "1" : "0") + "," + refundNumber;
    }
};

// TrainManagementSystem Class
class TrainManagementSystem {
private:
    vector<Train*> trains;
    vector<Ticket*> tickets;
    vector<User*> users;
    vector<User*> admins;
    int ticketCounter;
    User* currentUser;

    const string TRAIN_FILE = "trains.txt";
    const string USER_FILE = "users.txt";
    const string ADMIN_FILE = "admins.txt";
    const string TICKET_FILE = "tickets.txt";
    const string DISTRICTS_FILE = "districts.txt";
    const string REFUND_LOG_FILE = "refund_log.txt";

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

    User* findUserByUsername(string username) {
        for (auto user : users) {
            if (user->getUsername() == username) {
                return user;
            }
        }
        return nullptr;
    }

    User* findAdminByUsername(string username) {
        for (auto admin : admins) {
            if (admin->getUsername() == username) {
                return admin;
            }
        }
        return nullptr;
    }

    // File operations
    void saveTrainsToFile() {
        ofstream file(TRAIN_FILE);
        if (file.is_open()) {
            for (auto train : trains) {
                file << train->toFileString() << endl;
            }
            file.close();
        }
    }

    void loadTrainsFromFile() {
        ifstream file(TRAIN_FILE);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string token;
                vector<string> tokens;
                
                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }
                
                if (tokens.size() == 10) {
                    Train* train = new Train(
                        stoi(tokens[0]), tokens[1], tokens[2], tokens[3],
                        stoi(tokens[4]), stod(tokens[6]), stod(tokens[7]), tokens[8], tokens[9]
                    );
                    train->setAvailableSeats(stoi(tokens[5]));
                    trains.push_back(train);
                }
            }
            file.close();
        }
    }

    void saveUsersToFile() {
        ofstream file(USER_FILE);
        if (file.is_open()) {
            for (auto user : users) {
                file << user->toFileString() << endl;
            }
            file.close();
        }
    }

    void loadUsersFromFile() {
        ifstream file(USER_FILE);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string token;
                vector<string> tokens;
                
                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }
                
                if (tokens.size() == 4) {
                    User* user = new User(tokens[0], tokens[1], tokens[2], tokens[3]);
                    users.push_back(user);
                }
            }
            file.close();
        }
    }

    void saveAdminsToFile() {
        ofstream file(ADMIN_FILE);
        if (file.is_open()) {
            for (auto admin : admins) {
                file << admin->toFileString() << endl;
            }
            file.close();
        }
    }

    void loadAdminsFromFile() {
        ifstream file(ADMIN_FILE);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string token;
                vector<string> tokens;
                
                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }
                
                if (tokens.size() == 4) {
                    User* admin = new User(tokens[0], tokens[1], tokens[2], tokens[3]);
                    admins.push_back(admin);
                }
            }
            file.close();
        }
    }

    void saveTicketsToFile() {
        ofstream file(TICKET_FILE);
        if (file.is_open()) {
            for (auto ticket : tickets) {
                file << ticket->toFileString() << endl;
            }
            file.close();
        }
    }

    void loadTicketsFromFile() {
        ifstream file(TICKET_FILE);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string token;
                vector<string> tokens;
                
                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }
                
                if (tokens.size() == 10) {
                    Ticket* ticket = new Ticket(
                        stoi(tokens[0]), stoi(tokens[1]), tokens[2], tokens[3],
                        stoi(tokens[4]), stod(tokens[5]), tokens[6], tokens[7]
                    );
                    if (tokens[8] == "1") {
                        ticket->cancelTicket(tokens[9]);
                    }
                    tickets.push_back(ticket);
                    ticketCounter = max(ticketCounter, stoi(tokens[0]) + 1);
                }
            }
            file.close();
        }
    }

    void createDistrictsFile() {
        ofstream file(DISTRICTS_FILE);
        if (file.is_open()) {
            string districts[] = {
                "Dhaka", "Chittagong", "Sylhet", "Rajshahi", "Khulna", "Barisal", "Rangpur", "Mymensingh",
                "Comilla", "Narayanganj", "Gazipur", "Bogra", "Dinajpur", "Jessore", "Pabna", "Kushtia",
                "Noakhali", "Faridpur", "Tangail", "Jamalpur", "Satkhira", "Feni", "Lakshmipur", "Cox's Bazar",
                "Jhenaidah", "Magura", "Meherpur", "Narail", "Chuadanga", "Manikganj", "Munshiganj", "Shariatpur",
                "Madaripur", "Gopalganj", "Sherpur", "Kishoreganj", "Netrokona", "Sunamganj", "Habiganj", "Brahmanbaria",
                "Chandpur", "Lakshmipur", "Narsingdi", "Moulvibazar", "Gaibandha", "Kurigram", "Lalmonirhat", "Nilphamari",
                "Panchagarh", "Thakurgaon", "Joypurhat", "Naogaon", "Natore", "Chapainawabganj", "Pirojpur", "Bagerhat",
                "Jhalokati", "Barguna", "Bandarban", "Rangamati", "Khagrachhari", "Sirajganj", "Nawabganj", "Mongla"
            };
            
            for (int i = 0; i < 64; i++) {
                file << districts[i] << endl;
            }
            file.close();
        }
    }

    void logRefund(string username, int ticketId, double amount, string refundNumber, string method) {
        ofstream file(REFUND_LOG_FILE, ios::app);
        if (file.is_open()) {
            file << "Date: " << getCurrentDate() 
                 << " | User: " << username 
                 << " | Ticket ID: " << ticketId 
                 << " | Amount: " << amount 
                 << " | Refund Number: " << refundNumber 
                 << " | Method: " << method << endl;
            file.close();
        }
    }

    bool isValidPhoneNumber(string phone) {
        // Simple validation for Bangladeshi phone numbers
        return (phone.length() == 11 && phone.substr(0, 2) == "01");
    }

    bool isValidBkashNumber(string phone) {
        return (phone.length() == 11 && phone.substr(0, 3) == "013");
    }

public:
    // Constructor
    TrainManagementSystem() {
        ticketCounter = 1000;
        currentUser = nullptr;
        createDistrictsFile();
        loadAdminsFromFile();
        loadUsersFromFile();
        loadTrainsFromFile();
        loadTicketsFromFile();
        
        // If no admins exist, create default admin
        if (admins.empty()) {
            admins.push_back(new User("admin", "admin123", "01700000000", "admin"));
            saveAdminsToFile();
        }
        
        // If no trains exist, initialize sample data
        if (trains.empty()) {
            initializeSampleData();
        }
    }

    // Destructor to free memory
    ~TrainManagementSystem() {
        for (auto train : trains) {
            delete train;
        }
        for (auto ticket : tickets) {
            delete ticket;
        }
        for (auto user : users) {
            delete user;
        }
        for (auto admin : admins) {
            delete admin;
        }
    }

    // Initialize sample data    
    void initializeSampleData() {
        trains.push_back(new Train(101, "Dhaka Express", "Dhaka", "Chittagong", 200, 800.0, 500.0, "08:00 AM"));
        trains.push_back(new Train(102, "Sylhet Mail", "Dhaka", "Sylhet", 150, 700.0, 400.0, "10:30 AM"));
        trains.push_back(new Train(103, "Rajshahi Express", "Dhaka", "Rajshahi", 180, 750.0, 450.0, "02:00 PM"));
        trains.push_back(new Train(104, "Khulna Special", "Dhaka", "Khulna", 160, 720.0, 420.0, "06:00 PM"));
        saveTrainsToFile();
    }

    // User Authentication
    bool userLogin() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "           USER LOGIN\n";
        cout << "========================================\n";
        
        string username, password;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        
        User* user = findUserByUsername(username);
        if (user != nullptr && user->getPassword() == password) {
            currentUser = user;
            cout << "\nLogin Successful!\n";
            pauseScreen();
            return true;
        } else {
            cout << "\nInvalid username or password!\n";
            pauseScreen();
            return false;
        }
    }

    void userRegistration() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "         USER REGISTRATION\n";
        cout << "========================================\n";
        
        string username, password, phone;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Phone Number (11 digits): ";
        cin >> phone;
        
        if (!isValidPhoneNumber(phone)) {
            cout << "\nInvalid phone number! Please use 11-digit Bangladeshi format (01XXXXXXXXX).\n";
            pauseScreen();
            return;
        }
        
        if (findUserByUsername(username) != nullptr) {
            cout << "\nUsername already exists!\n";
            pauseScreen();
            return;
        }
        
        users.push_back(new User(username, password, phone, "user"));
        saveUsersToFile();
        cout << "\nRegistration Successful! You can now login.\n";
        pauseScreen();
    }

    void adminResetPassword() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "       ADMIN PASSWORD RESET\n";
        cout << "========================================\n";
        
        string username, newPassword;
        cout << "Enter Username to reset password: ";
        cin >> username;
        cout << "Enter New Password: ";
        cin >> newPassword;
        
        User* user = findUserByUsername(username);
        if (user != nullptr) {
            user->setPassword(newPassword);
            saveUsersToFile();
            cout << "\nPassword reset successfully!\n";
        } else {
            cout << "\nUser not found!\n";
        }
        pauseScreen();
    }

    // Main Menu
    void mainMenu() {
        while (true) {
            clearScreen();
            cout << "\n========================================\n";
            cout << "   TRAIN MANAGEMENT SYSTEM\n";
            cout << "========================================\n";
            cout << "1. Admin Login\n";
            cout << "2. User Login\n";
            cout << "3. User Registration\n";
            cout << "4. Guest Mode\n";
            cout << "5. Exit\n";
            cout << "========================================\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1:
                    if (adminLogin()) {
                        adminMenu();
                    }
                    break;
                case 2:
                    if (userLogin()) {
                        userMenu();
                    }
                    break;
                case 3:
                    userRegistration();
                    break;
                case 4:
                    userGuestMode();
                    break;
                case 5:
                    cout << "\nThank you for using Train Management System!\n";
                    return;
                default:
                    cout << "\nInvalid choice! Please try again.\n";
                    pauseScreen();
            }
        }
    }

    // Admin Login
    bool adminLogin() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "        ADMIN LOGIN\n";
        cout << "========================================\n";
        
        string username, password;
        cout << "Enter Admin Username: ";
        cin >> username;
        cout << "Enter Admin Password: ";
        cin >> password;
        
        User* admin = findAdminByUsername(username);
        if (admin != nullptr && admin->getPassword() == password && admin->getRole() == "admin") {
            currentUser = admin;
            cout << "\nLogin Successful!\n";
            pauseScreen();
            return true;
        } else {
            cout << "\nInvalid admin credentials! Access Denied.\n";
            pauseScreen();
            return false;
        }
    }

    // Admin Menu
    void adminMenu() {
        while (true) {
            clearScreen();
            cout << "\n========================================\n";
            cout << "        ADMIN PANEL\n";
            cout << "========================================\n";
            cout << "Welcome, " << currentUser->getUsername() << "!\n";
            cout << "Phone: " << currentUser->getPhoneNumber() << "\n";
            cout << "1. Manage Train Function\n";
            cout << "2. View All Trains\n";
            cout << "3. Show Train Schedule\n";
            cout << "4. Reset User Password\n";
            cout << "5. View All Tickets\n";
            cout << "6. View Refund Logs\n";
            cout << "7. Back to Main Menu\n";
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
                    adminResetPassword();
                    break;
                case 5:
                    viewAllTickets();
                    pauseScreen();
                    break;
                case 6:
                    viewRefundLogs();
                    pauseScreen();
                    break;
                case 7:
                    currentUser = nullptr;
                    return;
                default:
                    cout << "\nInvalid choice! Please try again.\n";
                    pauseScreen();
            }
        }
    }

    // User Menu
    void userMenu() {
        while (true) {
            clearScreen();
            cout << "\n========================================\n";
            cout << "        USER PANEL\n";
            cout << "========================================\n";
            cout << "Welcome, " << currentUser->getUsername() << "!\n";
            cout << "Phone: " << currentUser->getPhoneNumber() << "\n";
            cout << "1. View All Trains\n";
            cout << "2. Show Train Schedule\n";
            cout << "3. Buy Ticket\n";
            cout << "4. View My Tickets\n";
            cout << "5. Cancel Ticket\n";
            cout << "6. Logout\n";
            cout << "========================================\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1:
                    viewAllTrains();
                    pauseScreen();
                    break;
                case 2:
                    showTrainSchedule();
                    pauseScreen();
                    break;
                case 3:
                    buyTicket();
                    break;
                case 4:
                    viewUserTickets();
                    pauseScreen();
                    break;
                case 5:
                    cancelUserTicket();
                    break;
                case 6:
                    currentUser = nullptr;
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
        double acPrice, nonAcPrice;
        
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
        
        cout << "Enter AC Price: ";
        cin >> acPrice;
        
        cout << "Enter Non-AC Price: ";
        cin >> nonAcPrice;
        
        cin.ignore();
        cout << "Enter Departure Time (e.g., 08:00 AM): ";
        getline(cin, departureTime);
        
        Train* newTrain = new Train(trainNumber, trainName, source, destination, totalSeats, acPrice, nonAcPrice, departureTime);
        trains.push_back(newTrain);
        saveTrainsToFile();
        
        cout << "\nTrain added successfully!\n";
        pauseScreen();
    }

    // Delete Train
    void deleteTrain() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          DELETE TRAIN\n";
        cout << "========================================\n";
        
        viewAllTrains();
        int trainNum;
        cout << "\nEnter Train Number to Delete: ";
        cin >> trainNum;
        
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i]->getTrainNumber() == trainNum) {
                delete trains[i];
                trains.erase(trains.begin() + i);
                saveTrainsToFile();
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
        cout << "\n================================================================================================================\n";
        cout << "                                              ALL TRAINS\n";
        cout << "================================================================================================================\n";
        
        if (trains.empty()) {
            cout << "\nNo trains available!\n";
            return;
        }
        
        cout << left << setw(10) << "Train No" 
             << setw(20) << "Train Name" 
             << setw(15) << "Source" 
             << setw(15) << "Destination" 
             << setw(10) << "Seats" 
             << setw(12) << "AC Price" 
             << setw(12) << "Non-AC Price" 
             << setw(12) << "Time" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------\n";
        
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
        
        string d1, d2;
        cin.ignore();
        cout << "Enter Departure Station (D1): ";
        getline(cin, d1);
        cout << "Enter Arrival Station (D2): ";
        getline(cin, d2);
        
        bool found = false;
        for (auto train : trains) {
            if (train->getSource() == d1 && train->getDestination() == d2) {
                if (!found) {
                    cout << left << setw(10) << "Train No" 
                         << setw(20) << "Train Name" 
                         << setw(15) << "Source" 
                         << setw(15) << "Destination" 
                         << setw(10) << "Seats" 
                         << setw(12) << "AC Price" 
                         << setw(12) << "Non-AC Price" 
                         << setw(12) << "Time" << endl;
                    cout << "----------------------------------------------------------------------------------------------------------------\n";
                    found = true;
                }
                train->displayTrainInfo();
            }
        }
        
        if (!found) {
            cout << "\nNo trains found for the given route!\n";
        }
    }

    // User Guest Mode
    void userGuestMode() {
        while (true) {
            clearScreen();
            cout << "\n========================================\n";
            cout << "        USER (GUEST MODE)\n";
            cout << "========================================\n";
            cout << "1. View All Trains\n";
            cout << "2. Show Train Schedule\n";
            cout << "3. Back to Main Menu\n";
            cout << "========================================\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1:
                    viewAllTrains();
                    pauseScreen();
                    break;
                case 2:
                    showTrainSchedule();
                    pauseScreen();
                    break;
                case 3:
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
        
        viewAllTrains();
        
        int trainNum, seats;
        string passengerName, coachType;
        
        cout << "\nEnter Train Number: ";
        cin >> trainNum;
        
        Train* train = findTrainByNumber(trainNum);
        if (train == nullptr) {
            cout << "\nTrain not found!\n";
            pauseScreen();
            return;
        }
        
        cout << "Enter Passenger Name: ";
        cin.ignore();
        getline(cin, passengerName);
        
        cout << "Enter Number of Seats: ";
        cin >> seats;
        
        if (seats <= 0) {
            cout << "\nInvalid number of seats!\n";
            pauseScreen();
            return;
        }
        
        cout << "Enter Coach Type (AC/Non-AC): ";
        cin >> coachType;
        
        // Convert to lowercase for comparison
        transform(coachType.begin(), coachType.end(), coachType.begin(), ::tolower);
        
        double pricePerSeat;
        if (coachType == "ac") {
            pricePerSeat = train->getAcPrice();
            coachType = "AC";
        } else if (coachType == "non-ac" || coachType == "nonac") {
            pricePerSeat = train->getNonAcPrice();
            coachType = "Non-AC";
        } else {
            cout << "\nInvalid coach type! Please enter 'AC' or 'Non-AC'.\n";
            pauseScreen();
            return;
        }
        
        if (train->getAvailableSeats() < seats) {
            cout << "\nNot enough seats available! Available seats: " << train->getAvailableSeats() << endl;
            pauseScreen();
            return;
        }
        
        double totalAmount = seats * pricePerSeat;
        
        // Create ticket
        Ticket* ticket = new Ticket(ticketCounter++, trainNum, passengerName, 
                                   currentUser->getPhoneNumber(), seats, totalAmount, 
                                   getCurrentDate(), coachType);
        tickets.push_back(ticket);
        
        // Update train seats
        train->setAvailableSeats(train->getAvailableSeats() - seats);
        saveTrainsToFile();
        saveTicketsToFile();
        
        cout << "\nTicket booked successfully!\n";
        cout << "Ticket ID: " << ticket->getTicketId() << endl;
        cout << "Passenger: " << passengerName << endl;
        cout << "Train: " << train->getTrainName() << " (" << trainNum << ")\n";
        cout << "Coach Type: " << coachType << endl;
        cout << "Seats: " << seats << endl;
        cout << "Total Amount: " << totalAmount << " Taka\n";
        pauseScreen();
    }

    // View User Tickets
    void viewUserTickets() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          MY TICKETS\n";
        cout << "========================================\n";
        
        if (tickets.empty()) {
            cout << "\nNo tickets found!\n";
            return;
        }
        
        bool found = false;
        for (auto ticket : tickets) {
            if (ticket->getPassengerPhone() == currentUser->getPhoneNumber() && !ticket->getIsCancelled()) {
                if (!found) {
                    cout << left << setw(12) << "Ticket ID" 
                         << setw(15) << "Train No" 
                         << setw(20) << "Passenger Name" 
                         << setw(15) << "Coach Type"
                         << setw(10) << "Seats" 
                         << setw(12) << "Amount" 
                         << setw(12) << "Date" << endl;
                    cout << "--------------------------------------------------------------------\n";
                    found = true;
                }
                
                Train* train = findTrainByNumber(ticket->getTrainNumber());
                string trainName = (train != nullptr) ? train->getTrainName() : "Unknown";
                
                cout << left << setw(12) << ticket->getTicketId()
                     << setw(15) << ticket->getTrainNumber()
                     << setw(20) << ticket->getPassengerName()
                     << setw(15) << ticket->getCoachType()
                     << setw(10) << ticket->getNumberOfSeats()
                     << setw(12) << fixed << setprecision(2) << ticket->getTotalAmount()
                     << setw(12) << ticket->getBookingDate() << endl;
            }
        }
        
        if (!found) {
            cout << "\nNo active tickets found!\n";
        }
    }

    // Cancel User Ticket with Refund
    void cancelUserTicket() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          CANCEL TICKET\n";
        cout << "========================================\n";
        
        viewUserTickets();
        
        int ticketId;
        cout << "\nEnter Ticket ID to cancel: ";
        cin >> ticketId;
        
        Ticket* ticket = findTicketById(ticketId);
        if (ticket == nullptr) {
            cout << "\nTicket not found!\n";
            pauseScreen();
            return;
        }
        
        if (ticket->getPassengerPhone() != currentUser->getPhoneNumber()) {
            cout << "\nYou can only cancel your own tickets!\n";
            pauseScreen();
            return;
        }
        
        if (ticket->getIsCancelled()) {
            cout << "\nTicket is already cancelled!\n";
            pauseScreen();
            return;
        }
        
        // Refund process
        cout << "\nRefund Amount: " << ticket->getTotalAmount() << " Taka\n";
        cout << "Select Refund Method:\n";
        cout << "1. bKash\n";
        cout << "2. Nagad\n";
        cout << "3. Rocket\n";
        cout << "Enter choice (1-3): ";
        
        int refundChoice;
        cin >> refundChoice;
        
        string refundMethod, refundNumber;
        switch (refundChoice) {
            case 1:
                refundMethod = "bKash";
                break;
            case 2:
                refundMethod = "Nagad";
                break;
            case 3:
                refundMethod = "Rocket";
                break;
            default:
                cout << "\nInvalid choice!\n";
                pauseScreen();
                return;
        }
        
        cout << "Enter " << refundMethod << " Number (11 digits): ";
        cin >> refundNumber;
        
        if (!isValidPhoneNumber(refundNumber)) {
            cout << "\nInvalid phone number!\n";
            pauseScreen();
            return;
        }
        
        // Process cancellation and refund
        Train* train = findTrainByNumber(ticket->getTrainNumber());
        if (train != nullptr) {
            // Restore seats
            train->setAvailableSeats(train->getAvailableSeats() + ticket->getNumberOfSeats());
            saveTrainsToFile();
        }
        
        ticket->cancelTicket(refundNumber);
        saveTicketsToFile();
        
        // Log refund
        logRefund(currentUser->getUsername(), ticketId, ticket->getTotalAmount(), refundNumber, refundMethod);
        
        cout << "\nTicket cancelled successfully!\n";
        cout << "Refund of " << ticket->getTotalAmount() << " Taka will be sent to " << refundMethod << " number: " << refundNumber << endl;
        pauseScreen();
    }

    // View All Tickets (Admin)
    void viewAllTickets() {
        clearScreen();
        cout << "\n========================================================================================================\n";
        cout << "                                          ALL TICKETS\n";
        cout << "========================================================================================================\n";
        
        if (tickets.empty()) {
            cout << "\nNo tickets found!\n";
            return;
        }
        
        cout << left << setw(12) << "Ticket ID" 
             << setw(15) << "Train No" 
             << setw(20) << "Passenger Name" 
             << setw(15) << "Phone"
             << setw(12) << "Coach Type"
             << setw(8) << "Seats" 
             << setw(12) << "Amount" 
             << setw(12) << "Date"
             << setw(10) << "Status" << endl;
        cout << "--------------------------------------------------------------------------------------------------------\n";
        
        for (auto ticket : tickets) {
            string status = ticket->getIsCancelled() ? "Cancelled" : "Active";
            cout << left << setw(12) << ticket->getTicketId()
                 << setw(15) << ticket->getTrainNumber()
                 << setw(20) << ticket->getPassengerName()
                 << setw(15) << ticket->getPassengerPhone()
                 << setw(12) << ticket->getCoachType()
                 << setw(8) << ticket->getNumberOfSeats()
                 << setw(12) << fixed << setprecision(2) << ticket->getTotalAmount()
                 << setw(12) << ticket->getBookingDate()
                 << setw(10) << status << endl;
        }
    }

    // View Refund Logs (Admin)
    void viewRefundLogs() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "           REFUND LOGS\n";
        cout << "========================================\n";
        
        ifstream file(REFUND_LOG_FILE);
        if (!file.is_open()) {
            cout << "\nNo refund logs found!\n";
            return;
        }
        
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
};

// Main function
int main() {
    TrainManagementSystem tms;
    tms.mainMenu();
    return 0;
}