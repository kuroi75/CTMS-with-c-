#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#include<chrono>
#include<thread>
#ifdef _WIN32
#include<windows.h>
#endif
using namespace std;

// Color definitions for GUI
namespace Color {
    #ifdef _WIN32
    enum {
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHTGRAY = 7,
        DARKGRAY = 8,
        LIGHTBLUE = 9,
        LIGHTGREEN = 10,
        LIGHTCYAN = 11,
        LIGHTRED = 12,
        LIGHTMAGENTA = 13,
        YELLOW = 14,
        WHITE = 15,
        // Add these aliases for compatibility
        BRIGHT_BLUE = LIGHTBLUE,
        BRIGHT_WHITE = WHITE,
        BRIGHT_CYAN = LIGHTCYAN,
        BRIGHT_RED = LIGHTRED,
        BRIGHT_GREEN = LIGHTGREEN,
        BRIGHT_YELLOW = YELLOW,
        BRIGHT_MAGENTA = LIGHTMAGENTA
    };
    
    void set(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }
    #else
    enum {
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        MAGENTA = 35,
        CYAN = 36,
        WHITE = 37,
        BRIGHT_BLACK = 90,
        BRIGHT_RED = 91,
        BRIGHT_GREEN = 92,
        BRIGHT_YELLOW = 93,
        BRIGHT_BLUE = 94,
        BRIGHT_MAGENTA = 95,
        BRIGHT_CYAN = 96,
        BRIGHT_WHITE = 97
    };
    
    void set(int color) {
        cout << "\033[" << color << "m";
    }
    #endif
    
    void reset() {
        #ifdef _WIN32
        set(LIGHTGRAY);
        #else
        cout << "\033[0m";
        #endif
    }
}

// GUI Helper functions
void drawBox(int width, int height) {
    Color::set(Color::CYAN);
    cout << "\xC9"; // Top-left corner
    for(int i = 0; i < width-2; i++) cout << "\xCD"; // Horizontal line
    cout << "\xBB\n"; // Top-right corner
    
    for(int i = 0; i < height-2; i++) {
        cout << "\xBA"; // Vertical line
        for(int j = 0; j < width-2; j++) cout << " "; // Space
        cout << "\xBA\n"; // Vertical line
    }
    
    cout << "\xC8"; // Bottom-left corner
    for(int i = 0; i < width-2; i++) cout << "\xCD"; // Horizontal line
    cout << "\xBC\n"; // Bottom-right corner
    Color::reset();
}

void printCentered(const string& text, int width) {
    int padding = (width - text.length()) / 2;
    for(int i = 0; i < padding; i++) cout << " ";
    cout << text;
}

void printHeader(const string& title) {
    int width = 80;
    Color::set(Color::BRIGHT_BLUE);
    cout << "\xC9";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBB\n";
    
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    printCentered(title, width);
    Color::set(Color::BRIGHT_BLUE);
    cout << "\xBA\n";
    
    cout << "\xC8";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBC\n";
    Color::reset();
}

void printMenuItem(int number, const string& text) {
    Color::set(Color::WHITE);
    cout << " " << number << ". ";
    Color::set(Color::BRIGHT_CYAN);
    cout << text << endl;
    Color::reset();
}

void printError(const string& message) {
    Color::set(Color::BRIGHT_RED);
    cout << "ERROR: " << message << endl;
    Color::reset();
}

void printSuccess(const string& message) {
    Color::set(Color::BRIGHT_GREEN);
    cout << "SUCCESS: " << message << endl;
    Color::reset();
}

void printInfo(const string& message) {
    Color::set(Color::BRIGHT_YELLOW);
    cout << "INFO: " << message << endl;
    Color::reset();
}

// Enhanced table printing functions with proper spacing
void printTableHeader(const vector<string>& headers) {
    // Calculate column widths
    vector<int> widths;
    for (const auto& header : headers) {
        widths.push_back(max((int)header.length() + 2, 12));
    }
    
    // Calculate total width
    int totalWidth = 1; // Start with left border
    for (int w : widths) {
        totalWidth += w + 1; // +1 for right border or separator
    }
    
    // Print top border
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xDA";
    for (int i = 0; i < totalWidth - 2; i++) {
        cout << "\xC4";
    }
    cout << "\xBF\n";
    
    // Print headers
    cout << "\xB3";
    Color::set(Color::BRIGHT_WHITE);
    for (size_t i = 0; i < headers.size(); i++) {
        cout << " " << left << setw(widths[i] - 1) << headers[i] << " ";
        if (i < headers.size() - 1) {
            Color::set(Color::BRIGHT_CYAN);
            cout << "\xB3";
            Color::set(Color::BRIGHT_WHITE);
        }
    }
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xB3\n";
    
    // Print separator line
    cout << "\xC3";
    for (size_t i = 0; i < widths.size(); i++) {
        for (int j = 0; j < widths[i]; j++) {
            cout << "\xC4";
        }
        if (i < widths.size() - 1) {
            cout << "\xC5";
        }
    }
    cout << "\xB4\n";
    Color::reset();
}

void printTableRow(const vector<string>& cells) {
    // Calculate column widths based on content
    vector<int> widths;
    for (const auto& cell : cells) {
        widths.push_back(max((int)cell.length() + 2, 12));
    }
    
    Color::set(Color::CYAN);
    cout << "\xB3";
    Color::set(Color::WHITE);
    for (size_t i = 0; i < cells.size(); i++) {
        cout << " " << left << setw(widths[i] - 1) << cells[i] << " ";
        if (i < cells.size() - 1) {
            Color::set(Color::CYAN);
            cout << "\xB3";
            Color::set(Color::WHITE);
        }
    }
    Color::set(Color::CYAN);
    cout << "\xB3\n";
    Color::reset();
}

void printTableFooter() {
    // We'll use a fixed width for simplicity
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xC0";
    for (int i = 0; i < 78; i++) {
        if (i % 14 == 13) cout << "\xC1";
        else cout << "\xC4";
    }
    cout << "\xD9\n";
    Color::reset();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    Color::set(Color::BRIGHT_MAGENTA);
    cout << "\nPress Enter to continue...";
    Color::reset();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Enhanced loading bar with percentage and status
void showLoadingBar(const string& message, int duration_ms = 1000) {
    int width = 60;
    int barWidth = 40;
    
    // Top border
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xC9";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBB\n";
    
    // Message line
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    printCentered(message, width);
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Empty line
    cout << "\xBA";
    for(int i = 0; i < width-2; i++) cout << " ";
    cout << "\xBA\n";
    
    // Loading bar line
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    cout << "Loading: [";
    Color::set(Color::BRIGHT_GREEN);
    
    int steps = 20;
    int stepDuration = duration_ms / steps;
    for(int i = 0; i < steps; i++) {
        cout << "\xDB";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(stepDuration));
        
        // Update percentage
        cout << "\r\xBA";
        Color::set(Color::BRIGHT_WHITE);
        cout << "Loading: [";
        Color::set(Color::BRIGHT_GREEN);
        for(int j = 0; j <= i; j++) cout << "\xDB";
        Color::set(Color::BRIGHT_WHITE);
        cout << "] " << (i+1)*5 << "%";
        Color::set(Color::BRIGHT_CYAN);
        cout << "\xBA";
    }
    
    Color::set(Color::BRIGHT_WHITE);
    cout << "\r\xBA";
    cout << "Loading: [";
    Color::set(Color::BRIGHT_GREEN);
    for(int i = 0; i < steps; i++) cout << "\xDB";
    Color::set(Color::BRIGHT_WHITE);
    cout << "] 100% Complete!";
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Empty line
    cout << "\xBA";
    for(int i = 0; i < width-2; i++) cout << " ";
    cout << "\xBA\n";
    
    // Bottom border
    cout << "\xC8";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBC\n";
    Color::reset();
}

// Enhanced searching animation with train icon
void showSearchingAnimation() {
    int width = 50;
    int height = 10;
    
    // Top border
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xC9";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBB\n";
    
    // Empty line
    cout << "\xBA";
    for(int i = 0; i < width-2; i++) cout << " ";
    cout << "\xBA\n";
    
    // Searching message
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    printCentered("Searching for trains...", width);
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Train animation
    for(int frame = 0; frame < 3; frame++) {
        cout << "\xBA";
        for(int i = 0; i < width-2; i++) {
            if(i == 5 + frame*5) {
                Color::set(Color::BRIGHT_YELLOW);
                cout << "<o=o>";
                i += 4;
            } else if(i == 10 + frame*5) {
                Color::set(Color::WHITE);
                cout << "=";
                i += 0;
            } else {
                Color::set(Color::BRIGHT_CYAN);
                cout << " ";
            }
        }
        Color::set(Color::BRIGHT_CYAN);
        cout << "\xBA\n";
        
        this_thread::sleep_for(chrono::milliseconds(300));
        
        // Clear previous train position
        for(int i = 0; i < 3; i++) {
            cout << "\x1b[A"; // Move cursor up
            cout << "\r"; // Move to beginning of line
        }
    }
    
    // Animated dots
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    printCentered("Please wait", width);
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Empty line
    cout << "\xBA";
    for(int i = 0; i < width-2; i++) cout << " ";
    cout << "\xBA\n";
    
    // Bottom border
    cout << "\xC8";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBC\n";
    Color::reset();
    
    // Animated dots
    for(int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
        cout.flush();
    }
    
    cout << "\n";
}

// New animation for ticket booking
void showTicketBookingAnimation() {
    int width = 60;
    int height = 12;
    
    // Top border
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xC9";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBB\n";
    
    // Empty line
    cout << "\xBA";
    for(int i = 0; i < width-2; i++) cout << " ";
    cout << "\xBA\n";
    
    // Booking message
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    printCentered("Processing your ticket booking...", width);
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Empty line
    cout << "\xBA";
    for(int i = 0; i < width-2; i++) cout << " ";
    cout << "\xBA\n";
    
    // Ticket animation
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    printCentered("Generating Ticket", width);
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Empty line
    cout << "\xBA";
    for(int i = 0; i < width-2; i++) cout << " ";
    cout << "\xBA\n";
    
    // Animated ticket
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    cout << "  _________________________  \n";
    cout << "\xBA |                         | \n";
    cout << "\xBA |   TRAIN TICKET          | \n";
    cout << "\xBA |   Processing...         | \n";
    cout << "\xBA |_________________________| \n";
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Bottom border
    cout << "\xC8";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBC\n";
    Color::reset();
    
    // Animated dots
    for(int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
        cout.flush();
    }
    
    cout << "\n";
}

// New animation for ticket cancellation
void showTicketCancellationAnimation() {
    int width = 60;
    int height = 12;
    
    // Top border
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xC9";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBB\n";
    
    // Empty line
    cout << "\xBA";
    for(int i = 0; i < width-2; i++) cout << " ";
    cout << "\xBA\n";
    
    // Cancellation message
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    printCentered("Processing ticket cancellation...", width);
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Empty line
    cout << "\xBA";
    for(int i = 0; i < width-2; i++) cout << " ";
    cout << "\xBA\n";
    
    // Refund animation
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    printCentered("Initiating Refund", width);
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Empty line
    cout << "\xBA";
    for(int i = 0; i < width-2; i++) cout << " ";
    cout << "\xBA\n";
    
    // Animated money
    cout << "\xBA";
    Color::set(Color::BRIGHT_GREEN);
    cout << "    $$$$$$$$$$$$$$$$$$$    \n";
    cout << "\xBA   $                    $   \n";
    cout << "\xBA  $   REFUND PROCESS    $  \n";
    cout << "\xBA   $                    $   \n";
    cout << "\xBA    $$$$$$$$$$$$$$$$$$$    \n";
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Bottom border
    cout << "\xC8";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBC\n";
    Color::reset();
    
    // Animated dots
    for(int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
        cout.flush();
    }
    
    cout << "\n";
}

// New animation for file operations
void showFileOperationAnimation(const string& operation, const string& filename) {
    int width = 60;
    
    // Top border
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xC9";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBB\n";
    
    // Message line
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    printCentered(operation + " " + filename, width);
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Progress bar
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    cout << "Progress: [";
    Color::set(Color::BRIGHT_BLUE);
    
    int steps = 10;
    for(int i = 0; i < steps; i++) {
        cout << "\xDB";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    Color::set(Color::BRIGHT_WHITE);
    cout << "] Done!";
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Bottom border
    cout << "\xC8";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBC\n";
    Color::reset();
}

// Enhanced welcome screen with more effects
void welcomeScreen() {
    clearScreen();
    
    // Draw a box around the welcome screen
    int width = 60;
    int height = 15;
    
    // Top border
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xC9";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBB\n";
    
    // Empty lines
    for(int i = 0; i < 3; i++) {
        cout << "\xBA";
        for(int j = 0; j < width-2; j++) cout << " ";
        cout << "\xBA\n";
    }
    
    // Title with animation
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    string title = "TRAIN MANAGEMENT SYSTEM";
    int padding = (width - 2 - title.length()) / 2;
    for(int i = 0; i < padding; i++) cout << " ";
    
    // Animated title
    for(int i = 0; i < title.length(); i++) {
        if(i % 2 == 0) Color::set(Color::BRIGHT_YELLOW);
        else Color::set(Color::BRIGHT_WHITE);
        cout << title[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    
    for(int i = 0; i < (width-2) - padding - title.length(); i++) cout << " ";
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Empty lines
    for(int i = 0; i < 2; i++) {
        cout << "\xBA";
        for(int j = 0; j < width-2; j++) cout << " ";
        cout << "\xBA\n";
    }
    
    // Loading bar
    cout << "\xBA";
    Color::set(Color::BRIGHT_WHITE);
    cout << "Loading: [";
    Color::set(Color::BRIGHT_GREEN);
    for(int i = 0; i < 20; i++) {
        cout << "\xDB";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    Color::set(Color::BRIGHT_WHITE);
    cout << "]";
    Color::set(Color::BRIGHT_CYAN);
    cout << "\xBA\n";
    
    // Empty lines
    for(int i = 0; i < 3; i++) {
        cout << "\xBA";
        for(int j = 0; j < width-2; j++) cout << " ";
        cout << "\xBA\n";
    }
    
    // Bottom border
    cout << "\xC8";
    for(int i = 0; i < width-2; i++) cout << "\xCD";
    cout << "\xBC\n";
    Color::reset();
    
    pauseScreen();
}

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
        vector<string> row = {
            to_string(trainNumber),
            trainName,
            source,
            destination,
            to_string(availableSeats),
            to_string(acPrice),
            to_string(nonAcPrice),
            departureTime
        };
        printTableRow(row);
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
    vector<string> districts;

    const string TRAIN_FILE = "trains.txt";
    const string USER_FILE = "users.txt";
    const string ADMIN_FILE = "admins.txt";
    const string TICKET_FILE = "tickets.txt";
    const string DISTRICTS_FILE = "districts.txt";
    const string REFUND_LOG_FILE = "refund_log.txt";

    string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        return to_string(1900 + ltm->tm_year) + "-" + 
               to_string(1 + ltm->tm_mon) + "-" + 
               to_string(ltm->tm_mday);
    }

    Train* findTrainByNumber(int trainNum) {
        for (size_t i = 0; i < trains.size(); i++) {
            if (trains[i]->getTrainNumber() == trainNum) {
                return trains[i];
            }
        }
        return nullptr;
    }

    Ticket* findTicketById(int ticketId) {
        for (size_t i = 0; i < tickets.size(); i++) {
            if (tickets[i]->getTicketId() == ticketId) {
                return tickets[i];
            }
        }
        return nullptr;
    }

    User* findUserByUsername(string username) {
        for (size_t i = 0; i < users.size(); i++) {
            if (users[i]->getUsername() == username) {
                return users[i];
            }
        }
        return nullptr;
    }

    User* findAdminByUsername(string username) {
        for (size_t i = 0; i < admins.size(); i++) {
            if (admins[i]->getUsername() == username) {
                return admins[i];
            }
        }
        return nullptr;
    }

    // File operations
    void saveTrainsToFile() {
        showFileOperationAnimation("Saving", "train data");
        ofstream file(TRAIN_FILE);
        if (file.is_open()) {
            for (size_t i = 0; i < trains.size(); i++) {
                file << trains[i]->toFileString() << endl;
            }
            file.close();
        } else {
            printError("Failed to save trains to file!");
        }
    }

    void loadTrainsFromFile() {
        showFileOperationAnimation("Loading", "train data");
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
                
                try {
                    if (tokens.size() == 10) {
                        Train* train = new Train(
                            stoi(tokens[0]), tokens[1], tokens[2], tokens[3],
                            stoi(tokens[4]), stod(tokens[6]), stod(tokens[7]), tokens[8], tokens[9]
                        );
                        train->setAvailableSeats(stoi(tokens[5]));
                        trains.push_back(train);
                    }
                } catch (const exception& e) {
                    printError("Error loading train data: " + string(e.what()));
                }
            }
            file.close();
        } else {
            printError("Failed to load trains from file!");
        }
    }

    void saveUsersToFile() {
        showFileOperationAnimation("Saving", "user data");
        ofstream file(USER_FILE);
        if (file.is_open()) {
            for (size_t i = 0; i < users.size(); i++) {
                file << users[i]->toFileString() << endl;
            }
            file.close();
        } else {
            printError("Failed to save users to file!");
        }
    }

    void loadUsersFromFile() {
        showFileOperationAnimation("Loading", "user data");
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
                
                try {
                    if (tokens.size() == 4) {
                        User* user = new User(tokens[0], tokens[1], tokens[2], tokens[3]);
                        users.push_back(user);
                    }
                } catch (const exception& e) {
                    printError("Error loading user data: " + string(e.what()));
                }
            }
            file.close();
        } else {
            printError("Failed to load users from file!");
        }
    }

    void saveAdminsToFile() {
        showFileOperationAnimation("Saving", "admin data");
        ofstream file(ADMIN_FILE);
        if (file.is_open()) {
            for (size_t i = 0; i < admins.size(); i++) {
                file << admins[i]->toFileString() << endl;
            }
            file.close();
        } else {
            printError("Failed to save admins to file!");
        }
    }

    void loadAdminsFromFile() {
        showFileOperationAnimation("Loading", "admin data");
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
                
                try {
                    if (tokens.size() == 4) {
                        User* admin = new User(tokens[0], tokens[1], tokens[2], tokens[3]);
                        admins.push_back(admin);
                    }
                } catch (const exception& e) {
                    printError("Error loading admin data: " + string(e.what()));
                }
            }
            file.close();
        } else {
            printError("Failed to load admins from file!");
        }
    }

    void saveTicketsToFile() {
        showFileOperationAnimation("Saving", "ticket data");
        ofstream file(TICKET_FILE);
        if (file.is_open()) {
            for (size_t i = 0; i < tickets.size(); i++) {
                file << tickets[i]->toFileString() << endl;
            }
            file.close();
        } else {
            printError("Failed to save tickets to file!");
        }
    }

    void loadTicketsFromFile() {
        showFileOperationAnimation("Loading", "ticket data");
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
                
                try {
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
                } catch (const exception& e) {
                    printError("Error loading ticket data: " + string(e.what()));
                }
            }
            file.close();
        } else {
            printError("Failed to load tickets from file!");
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

    void loadDistrictsFromFile() {
        showFileOperationAnimation("Loading", "district data");
        ifstream file(DISTRICTS_FILE);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                districts.push_back(line);
            }
            file.close();
        } else {
            printError("Failed to load districts from file!");
        }
    }

    void logRefund(string username, int ticketId, double amount, string refundNumber, string method) {
        showFileOperationAnimation("Logging", "refund information");
        ofstream file(REFUND_LOG_FILE, ios::app);
        if (file.is_open()) {
            file << "Date: " << getCurrentDate() 
                 << " | User: " << username 
                 << " | Ticket ID: " << ticketId 
                 << " | Amount: " << amount 
                 << " | Refund Number: " << refundNumber 
                 << " | Method: " << method << endl;
            file.close();
        } else {
            printError("Failed to log refund!");
        }
    }

    bool isValidPhoneNumber(string phone) {
        // Check for Bangladeshi phone numbers
        if (phone.length() != 11) return false;
        if (phone.substr(0, 2) != "01") return false;
        
        // Check if all characters are digits
        for (char c : phone) {
            if (!isdigit(c)) return false;
        }
        
        return true;
    }

    bool isValidBkashNumber(string phone) {
        // Check for bKash numbers (starting with 013)
        if (phone.length() != 11) return false;
        if (phone.substr(0, 3) != "013") return false;
        
        // Check if all characters are digits
        for (char c : phone) {
            if (!isdigit(c)) return false;
        }
        
        return true;
    }

    // Display stations in a grid format with page navigation
    int displayStationOptions(const string& title, int startIdx = 0) {
        clearScreen();
        printHeader(title);
        
        int itemsPerPage = 16; // 4x4 grid
        int totalPages = (districts.size() + itemsPerPage - 1) / itemsPerPage;
        int currentPage = startIdx / itemsPerPage;
        
        while (true) {
            clearScreen();
            printHeader(title);
            
            Color::set(Color::BRIGHT_WHITE);
            cout << "Page " << (currentPage + 1) << " of " << totalPages << endl;
            Color::reset();
            
            // Display stations in a 4x4 grid
            int endIdx = min(startIdx + itemsPerPage, (int)districts.size());
            for (int i = startIdx; i < endIdx; i++) {
                int gridPos = i - startIdx;
                if (gridPos % 4 == 0) cout << endl;
                
                Color::set(Color::WHITE);
                cout << setw(3) << (i + 1) << ". ";
                Color::set(Color::BRIGHT_CYAN);
                cout << setw(15) << left << districts[i];
                Color::reset();
            }
            
            cout << endl << endl;
            
            // Navigation options
            if (currentPage > 0) {
                printMenuItem(99, "Previous Page");
            }
            if (currentPage < totalPages - 1) {
                printMenuItem(100, "Next Page");
            }
            printMenuItem(0, "Back to Main Menu");
            
            Color::set(Color::BRIGHT_BLUE);
            cout << "\n========================================\n";
            Color::set(Color::WHITE);
            cout << "Enter your choice: ";
            Color::reset();
            
            int choice;
            cin >> choice;
            
            if (choice == 0) {
                return -1; // Back to main menu
            } else if (choice == 99 && currentPage > 0) {
                // Previous page
                currentPage--;
                startIdx = currentPage * itemsPerPage;
            } else if (choice == 100 && currentPage < totalPages - 1) {
                // Next page
                currentPage++;
                startIdx = currentPage * itemsPerPage;
            } else if (choice >= 1 && choice <= (int)districts.size()) {
                return choice - 1; // Return the index of selected station
            } else {
                printError("Invalid choice! Please try again.");
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
        }
    }

public:
    // Constructor
    TrainManagementSystem() {
        ticketCounter = 1000;
        currentUser = nullptr;
        createDistrictsFile();
        loadDistrictsFromFile();
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
        for (size_t i = 0; i < trains.size(); i++) {
            delete trains[i];
        }
        for (size_t i = 0; i < tickets.size(); i++) {
            delete tickets[i];
        }
        for (size_t i = 0; i < users.size(); i++) {
            delete users[i];
        }
        for (size_t i = 0; i < admins.size(); i++) {
            delete admins[i];
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
        printHeader("USER LOGIN");
        
        string username, password;
        Color::set(Color::WHITE);
        cout << "Enter Username: ";
        Color::reset();
        cin >> username;
        
        Color::set(Color::WHITE);
        cout << "Enter Password: ";
        Color::reset();
        cin >> password;
        
        // Show loading animation
        showLoadingBar("Authenticating user credentials...", 800);
        
        User* user = findUserByUsername(username);
        if (user != nullptr && user->getPassword() == password) {
            currentUser = user;
            printSuccess("Login Successful!");
            pauseScreen();
            return true;
        } else {
            printError("Invalid username or password!");
            pauseScreen();
            return false;
        }
    }

    void userRegistration() {
        clearScreen();
        printHeader("USER REGISTRATION");
        
        string username, password, phone;
        Color::set(Color::WHITE);
        cout << "Enter Username: ";
        Color::reset();
        cin >> username;
        
        Color::set(Color::WHITE);
        cout << "Enter Password: ";
        Color::reset();
        cin >> password;
        
        Color::set(Color::WHITE);
        cout << "Enter Phone Number (11 digits): ";
        Color::reset();
        cin >> phone;
        
        if (!isValidPhoneNumber(phone)) {
            printError("Invalid phone number! Please use 11-digit Bangladeshi format (01XXXXXXXXX).");
            pauseScreen();
            return;
        }
        
        if (findUserByUsername(username) != nullptr) {
            printError("Username already exists!");
            pauseScreen();
            return;
        }
        
        // Show loading animation
        showLoadingBar("Creating new user account...", 800);
        
        users.push_back(new User(username, password, phone, "user"));
        saveUsersToFile();
        printSuccess("Registration Successful! You can now login.");
        pauseScreen();
    }

    void adminResetPassword() {
        clearScreen();
        printHeader("ADMIN PASSWORD RESET");
        
        string username, newPassword;
        Color::set(Color::WHITE);
        cout << "Enter Username to reset password: ";
        Color::reset();
        cin >> username;
        
        Color::set(Color::WHITE);
        cout << "Enter New Password: ";
        Color::reset();
        cin >> newPassword;
        
        User* user = findUserByUsername(username);
        if (user != nullptr) {
            // Show loading animation
            showLoadingBar("Resetting user password...", 800);
            
            user->setPassword(newPassword);
            saveUsersToFile();
            printSuccess("Password reset successfully!");
        } else {
            printError("User not found!");
        }
        pauseScreen();
    }

    // Main Menu
    void mainMenu() {
        while (true) {
            clearScreen();
            printHeader("TRAIN MANAGEMENT SYSTEM");
            
            cout << "\n";
            printMenuItem(1, "Admin Login");
            printMenuItem(2, "User Login");
            printMenuItem(3, "User Registration");
            printMenuItem(4, "Guest Mode");
            printMenuItem(5, "Exit");
            
            Color::set(Color::BRIGHT_BLUE);
            cout << "\n========================================\n";
            Color::set(Color::WHITE);
            cout << "Enter your choice: ";
            Color::reset();
            
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
                    printSuccess("Thank you for using Train Management System!");
                    return;
                default:
                    printError("Invalid choice! Please try again.");
                    pauseScreen();
            }
        }
    }

    // Admin Login
    bool adminLogin() {
        clearScreen();
        printHeader("ADMIN LOGIN");
        
        string username, password;
        Color::set(Color::WHITE);
        cout << "Enter Admin Username: ";
        Color::reset();
        cin >> username;
        
        Color::set(Color::WHITE);
        cout << "Enter Admin Password: ";
        Color::reset();
        cin >> password;
        
        // Show loading animation
        showLoadingBar("Authenticating admin credentials...", 800);
        
        User* admin = findAdminByUsername(username);
        if (admin != nullptr && admin->getPassword() == password && admin->getRole() == "admin") {
            currentUser = admin;
            printSuccess("Login Successful!");
            pauseScreen();
            return true;
        } else {
            printError("Invalid admin credentials! Access Denied.");
            pauseScreen();
            return false;
        }
    }

    // Admin Menu
    void adminMenu() {
        while (true) {
            clearScreen();
            printHeader("ADMIN PANEL");
            
            Color::set(Color::BRIGHT_YELLOW);
            cout << "Welcome, " << currentUser->getUsername() << "!\n";
            cout << "Phone: " << currentUser->getPhoneNumber() << "\n\n";
            Color::reset();
            
            printMenuItem(1, "Manage Train Function");
            printMenuItem(2, "View All Trains");
            printMenuItem(3, "Show Train Schedule");
            printMenuItem(4, "Reset User Password");
            printMenuItem(5, "View All Tickets");
            printMenuItem(6, "View Refund Logs");
            printMenuItem(7, "Back to Main Menu");
            
            Color::set(Color::BRIGHT_BLUE);
            cout << "\n========================================\n";
            Color::set(Color::WHITE);
            cout << "Enter your choice: ";
            Color::reset();
            
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
                    printError("Invalid choice! Please try again.");
                    pauseScreen();
            }
        }
    }

    // User Menu
    void userMenu() {
        while (true) {
            clearScreen();
            printHeader("USER PANEL");
            
            Color::set(Color::BRIGHT_YELLOW);
            cout << "Welcome, " << currentUser->getUsername() << "!\n";
            cout << "Phone: " << currentUser->getPhoneNumber() << "\n\n";
            Color::reset();
            
            printMenuItem(1, "View All Trains");
            printMenuItem(2, "Show Train Schedule");
            printMenuItem(3, "Buy Ticket");
            printMenuItem(4, "View My Tickets");
            printMenuItem(5, "Cancel Ticket");
            printMenuItem(6, "Logout");
            
            Color::set(Color::BRIGHT_BLUE);
            cout << "\n========================================\n";
            Color::set(Color::WHITE);
            cout << "Enter your choice: ";
            Color::reset();
            
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
                    printError("Invalid choice! Please try again.");
                    pauseScreen();
            }
        }
    }

    // Manage Train Function
    void manageTrainFunction() {
        while (true) {
            clearScreen();
            printHeader("MANAGE TRAIN FUNCTION");
            
            printMenuItem(1, "Add Train");
            printMenuItem(2, "Delete Train");
            printMenuItem(3, "Back to Admin Menu");
            
            Color::set(Color::BRIGHT_BLUE);
            cout << "\n========================================\n";
            Color::set(Color::WHITE);
            cout << "Enter your choice: ";
            Color::reset();
            
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
                    printError("Invalid choice! Please try again.");
                    pauseScreen();
            }
        }
    }

    // Add Train
    void addTrain() {
        clearScreen();
        printHeader("ADD NEW TRAIN");
        
        int trainNumber, totalSeats;
        string trainName, source, destination, departureTime;
        double acPrice, nonAcPrice;
        
        Color::set(Color::WHITE);
        cout << "Enter Train Number: ";
        Color::reset();
        cin >> trainNumber;
        
        // Check if train number already exists
        if (findTrainByNumber(trainNumber) != nullptr) {
            printError("Train number already exists!");
            pauseScreen();
            return;
        }
        
        cin.ignore();
        Color::set(Color::WHITE);
        cout << "Enter Train Name: ";
        Color::reset();
        getline(cin, trainName);
        
        // Select source station
        int sourceIdx = displayStationOptions("SELECT SOURCE STATION");
        if (sourceIdx == -1) return;
        source = districts[sourceIdx];
        
        // Select destination station
        int destIdx = displayStationOptions("SELECT DESTINATION STATION");
        if (destIdx == -1) return;
        destination = districts[destIdx];
        
        Color::set(Color::WHITE);
        cout << "Enter Total Seats: ";
        Color::reset();
        cin >> totalSeats;
        
        Color::set(Color::WHITE);
        cout << "Enter AC Price: ";
        Color::reset();
        cin >> acPrice;
        
        Color::set(Color::WHITE);
        cout << "Enter Non-AC Price: ";
        Color::reset();
        cin >> nonAcPrice;
        
        cin.ignore();
        Color::set(Color::WHITE);
        cout << "Enter Departure Time (e.g., 08:00 AM): ";
        Color::reset();
        getline(cin, departureTime);
        
        Train* newTrain = new Train(trainNumber, trainName, source, destination, totalSeats, acPrice, nonAcPrice, departureTime);
        trains.push_back(newTrain);
        saveTrainsToFile();
        
        printSuccess("Train added successfully!");
        pauseScreen();
    }

    // Delete Train
    void deleteTrain() {
        clearScreen();
        printHeader("DELETE TRAIN");
        
        viewAllTrains();
        
        int trainNum;
        Color::set(Color::WHITE);
        cout << "\nEnter Train Number to Delete: ";
        Color::reset();
        cin >> trainNum;
        
        // Check if the train has any active tickets
        for (size_t i = 0; i < tickets.size(); i++) {
            if (tickets[i]->getTrainNumber() == trainNum && !tickets[i]->getIsCancelled()) {
                printError("Cannot delete train with active tickets!");
                pauseScreen();
                return;
            }
        }
        
        for (size_t i = 0; i < trains.size(); i++) {
            if (trains[i]->getTrainNumber() == trainNum) {
                delete trains[i];
                trains.erase(trains.begin() + i);
                saveTrainsToFile();
                printSuccess("Train deleted successfully!");
                pauseScreen();
                return;
            }
        }
        
        printError("Train not found!");
        pauseScreen();
    }

    // View All Trains
    void viewAllTrains() {
        clearScreen();
        printHeader("ALL TRAINS");
        
        if (trains.empty()) {
            printInfo("No trains available!");
            return;
        }
        
        vector<string> headers = {"Train No", "Train Name", "Source", "Destination", "Seats", "AC Price", "Non-AC", "Time"};
        printTableHeader(headers);
        
        for (size_t i = 0; i < trains.size(); i++) {
            trains[i]->displayTrainInfo();
        }
        
        printTableFooter();
    }

    // Show Train Schedule - Enhanced with station selection
    void showTrainSchedule() {
        clearScreen();
        printHeader("TRAIN SCHEDULE");
        
        // Select source station
        int sourceIdx = displayStationOptions("SELECT DEPARTURE STATION");
        if (sourceIdx == -1) return;
        string d1 = districts[sourceIdx];
        
        // Select destination station
        int destIdx = displayStationOptions("SELECT ARRIVAL STATION");
        if (destIdx == -1) return;
        string d2 = districts[destIdx];
        
        // Show loading animation
        showSearchingAnimation();
        
        // Search for trains
        bool found = false;
        vector<Train*> foundTrains;
        
        for (size_t i = 0; i < trains.size(); i++) {
            if (trains[i]->getSource() == d1 && trains[i]->getDestination() == d2) {
                foundTrains.push_back(trains[i]);
                found = true;
            }
        }
        
        // Show results
        clearScreen();
        printHeader("SEARCH RESULTS: " + d1 + " TO " + d2);
        
        if (found) {
            Color::set(Color::BRIGHT_GREEN);
            cout << "Found " << foundTrains.size() << " trains for your route!" << endl;
            Color::reset();
            cout << endl;
            
            vector<string> headers = {"Train No", "Train Name", "Source", "Destination", "Seats", "AC Price", "Non-AC", "Time"};
            printTableHeader(headers);
            
            for (size_t i = 0; i < foundTrains.size(); i++) {
                foundTrains[i]->displayTrainInfo();
            }
            
            printTableFooter();
        } else {
            printInfo("No trains found for the given route!");
            
            // Show alternative routes
            vector<Train*> alternativeTrains;
            for (size_t i = 0; i < trains.size(); i++) {
                if (trains[i]->getSource() == d1 || trains[i]->getDestination() == d2) {
                    alternativeTrains.push_back(trains[i]);
                }
            }
            
            if (!alternativeTrains.empty()) {
                cout << endl;
                Color::set(Color::BRIGHT_YELLOW);
                cout << "Alternative trains with partial route match:" << endl;
                Color::reset();
                cout << endl;
                
                vector<string> headers = {"Train No", "Train Name", "Source", "Destination", "Seats", "AC Price", "Non-AC", "Time"};
                printTableHeader(headers);
                
                for (size_t i = 0; i < alternativeTrains.size(); i++) {
                    alternativeTrains[i]->displayTrainInfo();
                }
                
                printTableFooter();
            }
        }
    }

    // User Guest Mode
    void userGuestMode() {
        while (true) {
            clearScreen();
            printHeader("USER (GUEST MODE)");
            
            printMenuItem(1, "View All Trains");
            printMenuItem(2, "Show Train Schedule");
            printMenuItem(3, "Back to Main Menu");
            
            Color::set(Color::BRIGHT_BLUE);
            cout << "\n========================================\n";
            Color::set(Color::WHITE);
            cout << "Enter your choice: ";
            Color::reset();
            
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
                    printError("Invalid choice! Please try again.");
                    pauseScreen();
            }
        }
    }

    // Buy Ticket
    void buyTicket() {
        clearScreen();
        printHeader("BUY TICKET");
        
        // Check if user is logged in
        if (currentUser == nullptr) {
            printError("Please login to buy tickets!");
            pauseScreen();
            return;
        }
        
        viewAllTrains();
        
        int trainNum, seats;
        string passengerName, coachType;
        
        Color::set(Color::WHITE);
        cout << "\nEnter Train Number: ";
        Color::reset();
        cin >> trainNum;
        
        Train* train = findTrainByNumber(trainNum);
        if (train == nullptr) {
            printError("Train not found!");
            pauseScreen();
            return;
        }
        
        Color::set(Color::WHITE);
        cout << "Enter Passenger Name: ";
        Color::reset();
        cin.ignore();
        getline(cin, passengerName);
        
        Color::set(Color::WHITE);
        cout << "Enter Number of Seats: ";
        Color::reset();
        cin >> seats;
        
        if (seats <= 0) {
            printError("Invalid number of seats!");
            pauseScreen();
            return;
        }
        
        if (train->getAvailableSeats() < seats) {
            printError("Not enough seats available! Available seats: " + to_string(train->getAvailableSeats()));
            pauseScreen();
            return;
        }
        
        Color::set(Color::WHITE);
        cout << "Enter Coach Type (AC/Non-AC): ";
        Color::reset();
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
            printError("Invalid coach type! Please enter 'AC' or 'Non-AC'.");
            pauseScreen();
            return;
        }
        
        double totalAmount = seats * pricePerSeat;
        
        // Show loading animation
        showTicketBookingAnimation();
        
        // Create ticket
        Ticket* ticket = new Ticket(ticketCounter++, trainNum, passengerName, 
                                   currentUser->getPhoneNumber(), seats, totalAmount, 
                                   getCurrentDate(), coachType);
        tickets.push_back(ticket);
        
        // Update train seats
        train->setAvailableSeats(train->getAvailableSeats() - seats);
        saveTrainsToFile();
        saveTicketsToFile();
        
        printSuccess("Ticket booked successfully!");
        printInfo("Ticket ID: " + to_string(ticket->getTicketId()));
        printInfo("Passenger: " + passengerName);
        printInfo("Train: " + train->getTrainName() + " (" + to_string(trainNum) + ")");
        printInfo("Coach Type: " + coachType);
        printInfo("Seats: " + to_string(seats));
        printInfo("Total Amount: " + to_string(totalAmount) + " Taka");
        pauseScreen();
    }

    // View User Tickets
    void viewUserTickets() {
        clearScreen();
        printHeader("MY TICKETS");
        
        // Check if user is logged in
        if (currentUser == nullptr) {
            printError("Please login to view your tickets!");
            pauseScreen();
            return;
        }
        
        if (tickets.empty()) {
            printInfo("No tickets found!");
            return;
        }
        
        bool found = false;
        for (size_t i = 0; i < tickets.size(); i++) {
            if (tickets[i]->getPassengerPhone() == currentUser->getPhoneNumber() && !tickets[i]->getIsCancelled()) {
                if (!found) {
                    vector<string> headers = {"Ticket ID", "Train No", "Passenger", "Coach", "Seats", "Amount", "Date"};
                    printTableHeader(headers);
                    found = true;
                }
                
                Train* train = findTrainByNumber(tickets[i]->getTrainNumber());
                string trainName = (train != nullptr) ? train->getTrainName() : "Unknown";
                
                vector<string> row = {
                    to_string(tickets[i]->getTicketId()),
                    to_string(tickets[i]->getTrainNumber()),
                    tickets[i]->getPassengerName(),
                    tickets[i]->getCoachType(),
                    to_string(tickets[i]->getNumberOfSeats()),
                    to_string(tickets[i]->getTotalAmount()),
                    tickets[i]->getBookingDate()
                };
                printTableRow(row);
            }
        }
        
        if (found) {
            printTableFooter();
        } else {
            printInfo("No active tickets found!");
        }
    }

    // Cancel User Ticket with Refund
    void cancelUserTicket() {
        clearScreen();
        printHeader("CANCEL TICKET");
        
        // Check if user is logged in
        if (currentUser == nullptr) {
            printError("Please login to cancel tickets!");
            pauseScreen();
            return;
        }
        
        viewUserTickets();
        
        int ticketId;
        Color::set(Color::WHITE);
        cout << "\nEnter Ticket ID to cancel: ";
        Color::reset();
        cin >> ticketId;
        
        Ticket* ticket = findTicketById(ticketId);
        if (ticket == nullptr) {
            printError("Ticket not found!");
            pauseScreen();
            return;
        }
        
        if (ticket->getPassengerPhone() != currentUser->getPhoneNumber()) {
            printError("You can only cancel your own tickets!");
            pauseScreen();
            return;
        }
        
        if (ticket->getIsCancelled()) {
            printError("Ticket is already cancelled!");
            pauseScreen();
            return;
        }
        
        // Refund process
        printInfo("Refund Amount: " + to_string(ticket->getTotalAmount()) + " Taka");
        cout << "\n";
        printMenuItem(1, "bKash");
        printMenuItem(2, "Nagad");
        printMenuItem(3, "Rocket");
        
        Color::set(Color::WHITE);
        cout << "Enter choice (1-3): ";
        Color::reset();
        
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
                printError("Invalid choice!");
                pauseScreen();
                return;
        }
        
        Color::set(Color::WHITE);
        cout << "Enter " << refundMethod << " Number (11 digits): ";
        Color::reset();
        cin >> refundNumber;
        
        if (!isValidPhoneNumber(refundNumber)) {
            printError("Invalid phone number!");
            pauseScreen();
            return;
        }
        
        // Show loading animation
        showTicketCancellationAnimation();
        
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
        
        printSuccess("Ticket cancelled successfully!");
        printInfo("Refund of " + to_string(ticket->getTotalAmount()) + " Taka will be sent to " + refundMethod + " number: " + refundNumber);
        pauseScreen();
    }

    // View All Tickets (Admin)
    void viewAllTickets() {
        clearScreen();
        printHeader("ALL TICKETS");
        
        // Check if user is an admin
        if (currentUser == nullptr || currentUser->getRole() != "admin") {
            printError("Access denied! Admin privileges required.");
            pauseScreen();
            return;
        }
        
        if (tickets.empty()) {
            printInfo("No tickets found!");
            return;
        }
        
        vector<string> headers = {"Ticket ID", "Train No", "Passenger", "Phone", "Coach", "Seats", "Amount", "Date", "Status"};
        printTableHeader(headers);
        
        for (size_t i = 0; i < tickets.size(); i++) {
            string status = tickets[i]->getIsCancelled() ? "Cancelled" : "Active";
            
            vector<string> row = {
                to_string(tickets[i]->getTicketId()),
                to_string(tickets[i]->getTrainNumber()),
                tickets[i]->getPassengerName(),
                tickets[i]->getPassengerPhone(),
                tickets[i]->getCoachType(),
                to_string(tickets[i]->getNumberOfSeats()),
                to_string(tickets[i]->getTotalAmount()),
                tickets[i]->getBookingDate(),
                status
            };
            printTableRow(row);
        }
        
        printTableFooter();
    }

    // View Refund Logs (Admin)
    void viewRefundLogs() {
        clearScreen();
        printHeader("REFUND LOGS");
        
        // Check if user is an admin
        if (currentUser == nullptr || currentUser->getRole() != "admin") {
            printError("Access denied! Admin privileges required.");
            pauseScreen();
            return;
        }
        
        ifstream file(REFUND_LOG_FILE);
        if (!file.is_open()) {
            printInfo("No refund logs found!");
            return;
        }
        
        string line;
        while (getline(file, line)) {
            Color::set(Color::BRIGHT_YELLOW);
            cout << line << endl;
            Color::reset();
        }
        file.close();
    }
};

// Main function
int main() {
    // Set console to support extended characters
    #ifdef _WIN32
    SetConsoleOutputCP(437);
    #endif
    
    // Show welcome screen
    welcomeScreen();
    
    TrainManagementSystem tms;
    tms.mainMenu();
    return 0;
}