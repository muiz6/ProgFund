#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

// prototypes

void mainMenu();
void adminLogin(); // Incomplete
void adminMenu();
void updClients();
void updPkg();
void userMenu(); // Incomplete
void settingsMenu(); // Incomplete
void endProgram();
void colorMenu();
void loadSettings();
int selectionInput(int arrLength);

// main()

int main() {
    loadSettings();
    mainMenu();

    system("pause");
    return 0;
}

// function bodies

void mainMenu() {
    cout << "WELCOME TO CAR INSURANCE MANAGEMENT SYSTEM\n\n";
    cout << "[1] ADMIN MODE\n";
    cout << "[2] USER MODE\n";
    void (*menuArr[]) () = {adminLogin, userMenu}; // array of function pointers
    int input = selectionInput(2);
    (*menuArr[input - 1]) (); // calls a func from array (-1 to sync with array index)
}

void adminMenu() {
    system("cls");
    cout << "[ADMIN PANEL]\n\n";
    cout << "[1] UPDATE CLIENTS\n";
    cout << "[2] UPDATE PACKAGES\n";
    cout << "[3] SETTINGS\n";
    cout << "[4] EXIT\n";

    void (*menuArr[]) () = {updClients, updPkg, settingsMenu, endProgram}; // array of function pointers
    int input = selectionInput(4);
    (*menuArr[input - 1]) (); // calls a func from array (-1 to sync with array index)
}

int selectionInput(int arrLength) { // returns valid input for selection menus
    int input;
    cout << "\nENTER SELECTION : ";
    cin >> input;
    if (input <= 0 || input > arrLength) { // validation check
        cout << "INVALID INPUT!\n";
        selectionInput(arrLength); // recursion
    }
    else {
        return input;
    }
}

void endProgram () {
    return;
}

void adminLogin() { // asks for password at program launch (Incomplete)
    system("cls");
    cout << "ENTER PASWORD TO PROCEED : ";
    system("pause");
    adminMenu();
}

void settingsMenu() {
    system("cls");
    cout << "SETTINGS\n\n";
    cout << "[1] CHANGE THEME\n";
    cout << "[2] BACK\n";
    cout << "[#] (MORE OPTIONS)\n";
    int selection = selectionInput(2);
    void (*menuArr[]) () = {colorMenu, adminMenu}; // array of func pointers
    (*menuArr[selection - 1]) (); // calls func from array (-1 to sync with array index)
}

void colorMenu() {
    system("cls");
    cout << "CHANGE THEME\n\n";
    cout << "[1] LIGHT THEME\n";
    cout << "[2] BLUE THEME\n";
    cout << "[3] PURPLE THEME\n";
    cout << "[4] DARK THEME\n";

    string arr[] = {"f0", "3f", "5f", "0f"};
    int arrLength = sizeof(arr) / sizeof(arr[0]);
    int selection = selectionInput(arrLength);
    string str = "color ";
    str += arr[selection - 1]; // -1 to sync with array index

    system(str.c_str()); // .c_str() converts string to system() compatible argument
    system("mkdir Data"); // creates subfolder 'Data'
    ofstream myfile("Data\\settings.txt");
    myfile << "theme=" << str << endl;
    myfile.close();

    system("pause");
    settingsMenu();
}

void loadSettings()  {
    string str, temp;
    ifstream myfile("Data\\settings.txt");
    if (!myfile.is_open()) {
        system("mkdir Data"); // creat subfolder 'Data'
        ofstream myfile("Data\\settings.txt");
        myfile << "theme=color 0f" << endl;
        myfile.close();
        loadSettings(); //recursion
    }
    getline(myfile, temp, '='); // gets everything before =
    getline(myfile, str); // gets everything in line after previous getline
    myfile.close();
    system(str.c_str()); // .c_str() converts string to system() compatible argument
}

void userMenu() {}
void updClients() {}
void updPkg() {}
