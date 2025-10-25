#include<bits/stdc++.h>
using namespace std;

class TrainManagementSystem  //parent classs for this project
 {
private:
    const string ADMIN_PASSWORD = "tfjr100";


    //use clearscreen to clear terminal
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    //use pause screen to wait for user cinput
    void pauseScreen() {
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore previous 
        cin.get();
    }

public:
    // Main Menu
    void mainMenu()
     {
        while (true)
         {
            clearScreen();
            cout << "\n========================================\n";
            cout << "   TRAIN MANAGEMENT SYSTEM\n";
            cout << "========================================\n";
            cout << "1. Admin Login\n";
            cout << "2. User (Guest Mode)\n";
            cout << "3. Exit\n";
            cout << "========================================\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice)
             {
                case 1:
                    adminLogin(); //call adminlogin method to perform
                    break;
                case 2:
                    userGuestMode(); //call usermode method
                    break;
                case 3:
                    cout << "\nThank you for using CTMS!\n";
                    return;
                default:
                    cout << "\nInvalid choice! Please try again.\n";
                    pauseScreen();
            }
        }
    }

    // Admin Login
    void adminLogin()
     {
        clearScreen();
        cout << "\n========================================\n";
        cout << "        ADMIN LOGIN\n";
        cout << "========================================\n";
        
        string password;
        cout << "Enter Admin Password: ";
        cin >> password;
        
        if (password == ADMIN_PASSWORD)//check password condition
         {
            cout << "\nLogin Successful!\n";
            pauseScreen();
            adminMenu(); //call admin menu for further work
        } 
        else
         {
            cout << "\nIncorrect Password! Access Denied.\n";
            pauseScreen();
        }
    }

    // Admin Menu
    void adminMenu()
     {
        while (true) {
            clearScreen();
            cout << "\n========================================\n";
            cout << "        ADMIN PANEL\n";
            cout << "========================================\n";
            //write method of admin menus
            cout << "1. Manage Train Function\n";
            cout << "2. View All Trains\n";
            cout << "3. Show Train Schedule (Two D1-D2)\n";
            cout << "4. Back to Main Menu\n";
            cout << "========================================\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) //getting input via switch
            {
                case 1:
                    manageTrainFunction(); 
                    break;
                case 2:
                    viewAllTrains();
                    break;
                case 3:
                    showTrainSchedule();
                    break;
                case 4:
                    return;
                default:
                    cout << "\nInvalid choice! Please try again.\n";
                    pauseScreen();
            }
        }
    }

    // Manage Train Function details
    void manageTrainFunction()
    
    {
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
        
        switch (choice)
         {
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
                manageTrainFunction();
        }
    }

    // User Guest Mode
    void userGuestMode()
     {
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
            
            switch (choice)
             {
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

    // ========================================
    // this functions we implimented in future
    // ========================================
    
    void addTrain()
     {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          ADD NEW TRAIN\n";
        cout << "========================================\n";
        cout << "\nFunction to be implemented in future code\n";
        pauseScreen();
    }

    void deleteTrain() 
    {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          DELETE TRAIN\n";
        cout << "========================================\n";
        cout << "\nFunction to be implemented in future code\n";
        pauseScreen();
    }

    void viewAllTrains()
     {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          ALL TRAINS\n";
        cout << "========================================\n";
        cout << "\nFunction to be implemented in future code\n";
        pauseScreen();
    }

    void showTrainSchedule() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "      TRAIN SCHEDULE (D1-D2)\n";
        cout << "========================================\n";
        cout << "\nFunction to be implemented in future code\n";
        pauseScreen();
    }

    void viewTicket()
     {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          VIEW TICKET\n";
        cout << "========================================\n";
        cout << "\nFunction to be implemented in future code\n";
        pauseScreen();
    }

    void buyTicket() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          BUY TICKET\n";
        cout << "========================================\n";
        cout << "\nFunction to be implemented in future code\n";
        pauseScreen();
    }

    void cancelTicket() {
        clearScreen();
        cout << "\n========================================\n";
        cout << "          CANCEL TICKET\n";
        cout << "========================================\n";
        cout << "\nFunction to be implemented in future code\n";
        pauseScreen();
    }
};

// Main function
int main()
 {
    TrainManagementSystem tms; //tms is an object of main class
    tms.mainMenu(); //calling main by tms object reference
    return 0;
}
