#include<bits/stdc++.h>
using namespace std;

// Structure to store train information
struct Train
 {
    int trainNumber;
    string trainName;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;
    double ticketPrice;
    string departureTime;
};

// Structure to store ticket information
struct Ticket
 {
    int ticketId;
    int trainNumber;
    string passengerName;
    int numberOfSeats;
    double totalAmount;
    string bookingDate;
    bool isCancelled;
};

//Global vectors to store data
vector<Train> trains;  //to store stains
vector<Ticket> tickets;// to store tickets
int ticketCounter = 1000;//initial 


//declare cnst Admin password
const string ADMIN_PASSWORD = "admin123";

//  forword Function declarations of our all function that we work on 
void clearScreen();
void pauseScreen();
void mainMenu();
void adminLogin();
void adminMenu();
void userGuestMode();
 void initializeSampleData();
// void addTrain();
// void deleteTrain();
// void manageTrainFunction();
// void viewAllTrains();
// void searchTrainByNumber();
// void buyTicket();
// void cancelTicket();
// void viewTicket();
// void showTrainSchedule();

//--------------------------------------------------------------

// Main function to keep it simple , we use a function called main menu 
int main() 
{
    initializeSampleData(); // Add some sample trains for initial work using vector pushback
    mainMenu();
    return 0;
}
///-------------------------------------------------------------
// Clear screen function
/*we use clear screen to clear our terminal everytimr we run any function , thats gives us more visivility in our terminal*/
void clearScreen() // a  function with no perameter
 {
    #ifdef _WIN32 //check it run on windows
        system("cls"); //clear using system 
    #else
        system("clear"); ///otherwise use other operating system clear
    #endif
}

// Pause screen function
/* pause the screen untill user give any key , also it ignores any previous numeric value */
void pauseScreen()
 {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');//ignore
    cin.get();//get instruction from usser using get
}

// Initialize sample train data for work(number,name,source,destination,totoal s , av s ,price, time)
void initializeSampleData()
 {
    trains.push_back({101, "Dhaka Express", "Dhaka", "Chittagong", 200, 200, 500.0, "08:00 AM"});
    trains.push_back({102, "Sylhet Mail", "Dhaka", "Sylhet", 150, 150, 400.0, "10:30 AM"});
    trains.push_back({103, "Rajshahi Express", "Dhaka", "Rajshahi", 180, 180, 450.0, "02:00 PM"});
    trains.push_back({104, "Khulna Special", "Dhaka", "Khulna", 160, 160, 420.0, "06:00 PM"});
}

// Main Menu
void mainMenu()
 {
    while (true)
     {
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
        
        switch (choice)
         {
            case 1:
                adminLogin(); //call adminlogin
                break;
            case 2:
                userGuestMode();
                break;
            case 3:
                cout << "\n Thank you for using CTMS!\n";
                return;
            default:
                cout << "\n Invalid choice! Please try again.\n";
                pauseScreen();
        }
    }
    
}

//adminlogin

void adminLogin()
 {
    clearScreen();
    cout << "\n========================================\n";
    cout << "        ADMIN LOGIN\n";
    cout << "========================================\n";
    
    string password;
    cout << "Enter Admin Password: ";
    cin >> password;
    
    if (password == ADMIN_PASSWORD) //check condition
     {
        cout << "\nLogin Successful!\n";
        pauseScreen();
       // adminMenu();  add next
    } else {
        cout << "\nIncorrect Password! Access Denied.\n";
        pauseScreen();
    }
}
// userguestmode
void userGuestMode() {
    //need inprovement
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
        
   
}

