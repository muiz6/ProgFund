#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
using namespace std;

// prototypes

void dataCheck(); // checks if file exist otherwise creates them
void mainMenu(); // main menu
void adminMenu(); // menu for admin panel
void updClients(); // updates client info in all files
void searchClient(); //can be used for showing data to user itself in user menu
void addNewClient(); // adds new client info in all files
double calPremium(string income, string claimStr); // calculates Premium amount
void userLogin(); // Verifies user credentials
void userMenu(); // user menu
void endProgram();
void colorMenu(); // menu to change themes
void selectionInput(int &num, int min = 0, int max = 0, string str = "\nENTER SELECTION : "); // ensures valid integer input
void validationPhoneNumber(string &CellNo); //validating phone number in addNewClient
void makeID(string &serial); // stores new serial number in a string
void listClient(); // lists clients on console
void cnicValidation(string &CNIC); // ensure valid CNIC number input
double payValidation(string &pay);  //to validate pay
string getUserPasswById(int id); // returns user password when id is given
void overwriteFile(string fileName, string newLine, int id); // can update datafiles
void viewUserInfo(); // lists a specific user's info
void updUserPassw(); // menu to change user password
void loadTheme(); // loads theme at start of program
void validYesNo(string &str, string msg = "ENTER : "); // stores valid Y/N in string
void _getline(string &str, string msg = "ENTER : ", char a = '\n'); // a getline function that doesnt require cin.ignore()

// main()

int main() {
    dataCheck();
    loadTheme();
    mainMenu();

    system("pause");
    return 0;
}

// function bodies

void mainMenu() {
    system("cls");
    cout << "[WELCOME TO CAR INSURANCE MANAGEMENT SYSTEM]\n\n";
    cout << "[1] ADMIN MODE\n";
    cout << "[2] USER MODE\n";
    cout << "[3] EXIT\n";
    void (*menuArr[]) () = {adminMenu, userLogin, endProgram}; // array of function pointers
    int input;
    selectionInput(input, 1, 3);
    (*menuArr[input - 1]) (); // calls a func from array (-1 to sync with array index)
}

void adminMenu() {
    system("cls");
    cout << "[ADMIN PANEL]\n\n";
    cout << "[1] ADD NEW CLIENT\n";
    cout << "[2] UPDATE CLIENTS\n";
    cout << "[3] SEARCH CLIENT\n";
    cout << "[4] CHANGE THEME\n";
    cout << "[5] MAIN MENU\n";
    cout << "[6] EXIT\n";

    void (*menuArr[]) () = {addNewClient, updClients, searchClient, colorMenu, mainMenu, endProgram}; // array of function pointers
    int input;
    selectionInput(input, 1, 6);
    (*menuArr[input - 1]) (); // calls a func from array (-1 to sync with array index)
}

void endProgram () {
    return;
}

void colorMenu() {
    system("cls");
    cout << "[CHANGE THEME]\n\n";
    cout << "[1] LIGHT THEME\n";
    cout << "[2] BLUE THEME\n";
    cout << "[3] PURPLE THEME\n";
    cout << "[4] DARK THEME\n";

    string arr[] = {"f0", "3f", "5f", "0f"};
    int selection;
    selectionInput(selection, 1, 4);
    string str;
    str = "color " + arr[selection - 1]; // -1 to sync with array index

    system(str.c_str()); // .c_str() converts string to system() compatible argument
    ofstream myfile("Data\\settings.txt");
    myfile << "theme=" << str << endl;
    myfile.close();

    system("pause");
    adminMenu();
}

void addNewClient() {
    system("cls");
    cout << "[ADD NEW CLIENT]\n\n";
    int issuedYear;
    string serial, today, name, cellNo, cnic, address, carModel, carRegistryNo, password,pay;
    double salary, installments;
    _getline(name, "ENTER NAME : ");
    cnicValidation(cnic);
    _getline(carModel, "ENTER CAR MODEL : ");
    _getline(carRegistryNo, "ENTER CAR LICENSE PLATE NO : ");
    selectionInput(issuedYear, 2000, 0, "ENTER CAR PURCHASING YEAR : ");
    validationPhoneNumber(cellNo);
    _getline(address, "ENTER ADDRESS : ");
    salary=payValidation(pay);

    makeID(serial);

    ofstream userRecord ("Data\\userRecord.txt", ios::app);
    userRecord <<serial<<"\t"<<"Y"<<"\t"<<name<<"\t"<<cellNo<<"\t"<<cnic<<"\t"<<address<<"\t"<<salary<<"\t"<<carModel<<"\t"<<carRegistryNo<<"\t"<<issuedYear<<"\t"<<"0"<<"\t"<<"0"<<endl;
    userRecord.close();
    ofstream userList("Data\\userList.txt", ios::app);
    userList << serial << "\t" << carRegistryNo << "\t" << cellNo << "\t" << "Y" << "\t" << name << endl;
    userList.close();
    ofstream userAccount("Data\\userAccount.txt", ios::app);
    userAccount << serial << "\t" << "Y" << "\t" << "12345" << endl;

    system("cls");
    cout<<"SERIAL ID : "<< serial <<endl;
    cout<<"PASSWORD : 12345"<<endl;

    system("pause");
    adminMenu();
}

void validationPhoneNumber(string &CellNo) {
    bool condition = false;
    int countA = 0, countN = 0;
    while (countN != 11 || condition == false) {
        countA = 0; //for counting alphabets
        countN = 0; //for counting integers
        cout << "ENTER CELLPHONE NUMBER : ";
        cin >> CellNo;
        if (CellNo.length() == 11 && CellNo.at(0)=='0' && CellNo.at(1) == '3') {
            for (int i = 0; i < 11; i++) {
                if (isalpha(CellNo[i])) {
                    countA++;
                }
                else {
                    countN++;
                }
            }
            if (countA <= 0 && countN >= 0) {
                condition=true;
            }
            else {
                cout << "YOU ENTERED ALPHABET(S), ONLY NUMBERS ALLOWED"<<endl;
            }
        }
        else {
            cout<<"INVALID INPUT, TRY AGAIN."<<endl;
        }
    }
}
double payValidation(string &pay){
    double payI;
    bool flag = false;
    do{
        cout<<"Enter your pay : ";
        cin>>pay;
        stringstream ss(pay);
        if(ss>>payI){
            flag = true;
            return payI;
        }
        else{
            cout<<"TRY AGAIN!"<<endl;
            flag=false;
        }
    }while(flag==false);
}

void selectionInput(int &num, int min, int max, string str) { // set both min and max 0 for no limit
    int input;
    cout << str;
    cin >> input;
    if (cin) {
        if (min == 0 && max == 0) { // returns integer if no parameters provided
            num = input;
        }
        else if (min > 0 && max == 0) { // validation mode for positive integers
            if (input >= min) { // validation check
                num = input;
            }
            else {
                cout << "INVALID INPUT!\n";
                selectionInput(num, min, max, str); // recursion
            }
        }
        else {
            if (input >= min && input <= max) { // validation check
                num = input;
            }
            else {
                cout << "INVALID INPUT!\n";
                selectionInput(num, min, max, str); // recursion
            }
        }
    }
    else {
        cin.clear();
        cin.sync(); // discards data in cin buffer
        cout << "INVALID INPUT!\n";
        selectionInput(num, min, max, str);
    }
}

void makeID(string &serial) {
    string temp;
    ifstream userAccount("Data\\userList.txt");
    int i = 1;
    while (getline(userAccount, temp)) {
        i++;
    }
    ostringstream sStream;
    sStream << i;
    serial = sStream.str();
}

void searchClient() {
    system("cls");
    cout << "[SEARCH CLIENT]\n\n";
    listClient();

    int lookupID;
    selectionInput(lookupID, 1, 0, "ENTER ID OF USER YOU WISH TO SEARCH : ");

    istringstream sStream;
    string line;
    ifstream fin("Data\\userRecord.txt");
    bool flag = false;
    for (int i = 1; getline(fin, line); i++) { // pushes line into string stream if line number matches
        if (i == lookupID) {
            sStream.str(line); // sets line as contents of s
            flag = true;
        }
    }
    if (flag) {
        string word;
        vector <string> row;
        row.clear();
        while(getline(sStream, word, '\t')) {
            row.push_back(word);
        }
        cout << "\nUSER INFO :\n\n";
        cout<<"USER ID : "<<row[0]<<endl;
        cout<<"ACTIVE : "<<row[1]<<endl;
        cout<<"NAME : "<<row[2]<<endl;
        cout<<"PHONE: "<<row[3]<<endl;
        cout<<"CNIC : "<<row[4]<<endl;
        cout<<"ADDRESS: "<<row[5]<<endl;
        cout<<"INCOME : "<<row[6]<<endl;
        cout<<"CAR MODEL : "<<row[7]<<endl;
        cout<<"CAR NUMBER : "<<row[8]<<endl;
        cout<<"PURCHASE YEAR : "<<row[9]<<endl;
        cout << "CLAIM COUNT : "<< row[10] << endl;
        cout << "ACCIDENT COUNT : " << row[11] << endl;
        cout << "PREMIUM PRICE : " << calPremium(row[6], row[10]) << endl;

        system("pause");
        adminMenu();
    }
    else { // could be made more efficient with selectionInput();
        string selection;
        cout<<"RECORD DOESN'T EXIST!"<<endl;
        validYesNo(selection, "TRY ANOTHER ID? (Y/N) : ");
        if (selection == "Y") searchClient();
        else adminMenu();
    }
}

double calPremium(string income, string claimStr) {
    double MonthlyIncome = atof(income.c_str()); // type conversion function in stdlib.h
    int claims = atoi(claimStr.c_str());
    double toPay; //installment
    if (MonthlyIncome < 50000) {
        toPay = MonthlyIncome*0.05;
    }
    else if (MonthlyIncome>=50000 && MonthlyIncome<100000) {
        toPay = MonthlyIncome*0.085;
    }
    else if (MonthlyIncome>=100000 && MonthlyIncome<150000) {
        toPay = MonthlyIncome*0.1;
    }
    else {
        toPay = MonthlyIncome*0.15;
    }
    toPay += toPay*claims*0.5;
    return toPay;
}

void cnicValidation (string &CNIC) {
    bool condition = false;
    int countA = 0, countN = 0;
    while (countN != 13 || condition == false) {
        countA = 0; //for counting alphabets
        countN = 0; //for counting integers
        cout << "Enter your CNIC number : ";
        cin >> CNIC;
        if (CNIC.length() == 13 && CNIC.at(0)!='0' && CNIC.at(1) != '0') {
            for (int i = 0; i < 13; i++) {
                if (CNIC[i]=='0'||CNIC[i]=='1'||CNIC[i]=='2'||CNIC[i]=='3'||CNIC[i]=='4'||CNIC[i]=='5'||CNIC[i]=='6'||CNIC[i]=='7'||CNIC[i]=='8'||CNIC[i]=='9') {
                    countN++;
                }
                else {
                    countA++;
                }
            }
            if (countA <= 0 && countN >= 13) {
                condition=true;
            }
            else {
                cout << "You entered alaphabet(s), only numbers allowed"<<endl;
            }
        }
        else {
            cout<<"Invalid input, try again."<<endl;
        }
    }
}

void updClients() {
    system("cls");

    cout << "[UPDATE CLIENTS]\n\n";
    listClient();

    bool flag = false;
    string line, field;
    vector <string> row;
    int lookupID;
    selectionInput(lookupID, 1, 0, "ENTER ID OF USER YOU WISH TO EDIT : ");

    istringstream sStream;
    ifstream fin("Data\\userRecord.txt");
    for (int i = 1; getline(fin, line); i++) { // pushes line into string stream if line number matches
        if (i == lookupID) {
            sStream.str(line); // sets line as contents of sStream
            flag = true;
        }
    }
    row.clear();
    if (flag) {
        while(getline(sStream, field, '\t')) {
            row.push_back(field);
        }
        cout <<"\nCURRENT INFO :\n\n";
        cout<<"USER ID : "<<row[0]<<endl;
        cout<<"ACTIVE : "<<row[1]<<endl;
        cout<<"NAME : "<<row[2]<<endl;
        cout<<"PHONE: "<<row[3]<<endl;
        cout<<"CNIC : "<<row[4]<<endl;
        cout<<"ADDRESS: "<<row[5]<<endl;
        cout<<"INCOME : "<<row[6]<<endl;
        cout<<"CAR MODEL : "<<row[7]<<endl;
        cout<<"CAR NUMBER : "<<row[8]<<endl;
        cout<<"PURCHASE YEAR : "<<row[9]<<endl;
        cout << "CLAIM COUNT : "<< row[10] << endl;
        cout << "ACCIDENT COUNT : " << row[11] << endl;

        cout <<"\nNEW INFO :\n\n";
        validYesNo(row[1], "IS ACCOUNT ACTIVE (Y/N) : ");
        validationPhoneNumber(row[3]);
        _getline(row[5], "NEW ADDRESS : ");
        _getline(row[6], "NEW INCOME: ");
        _getline(row[10], "CLAIM COUNT : ");
        _getline(row[11], "ACCIDENT COUNT : ");

        int id = atoi(row[0].c_str());

        ostringstream sout1;
        sout1 << row[0] <<"\t"<< row[1]<<"\t"<< row[2] <<"\t"<< row[3] <<"\t"<< row[4] <<"\t"<< row[5] <<"\t"<< row[6] <<"\t"<< row[7] <<"\t"<< row[8] <<"\t"<< row[9] <<"\t"<< row[10] <<"\t"<< row[11];
        string newline1 = sout1.str();
        ostringstream sout2;
        sout2 << row[0] << "\t" << row[8] << "\t" << row[3] << "\t" << row[1] << "\t" << row[2];
        string newline2 = sout2.str();
        ostringstream sout3;
        string userPassw = getUserPasswById(id);
        sout3 << row[0] << "\t" << row[1] << "\t" << userPassw;
        string newline3 = sout3.str();

        overwriteFile("Data\\userRecord.txt", newline1, id);
        overwriteFile("Data\\userList.txt", newline2, id);
        overwriteFile("Data\\userAccount.txt", newline3, id);

        cout << "\nACCOUNT UPDATED SUCCESSFULLY!\n";
        system("pause");
        adminMenu();
    }
    else { // could be made more efficient with selectionInput();
        string selection;
        cout<<"RECORD DOESN'T EXIST!"<<endl;
        validYesNo(selection, "TRY ANOTHER ID? (Y/N) : ");
        if (selection == "Y") updClients();
        else adminMenu();
    }
}

void listClient() {
    string temp;
    cout << "USER ID\tCAR N0#\tPHONE\t\tACTIVE\tNAME\n";
    ifstream iuserList("Data\\userList.txt");
    while (getline(iuserList, temp)) {
        cout << temp << endl;
    }
    iuserList.close();
    cout << endl;
}

string getUserPasswById(int id) {
    string temp;
    istringstream sStream;
    ifstream iuserAccount("Data\\userAccount.txt");
    for (int i = 1; getline(iuserAccount, temp); i++) { // gets the row
        if (i == id) {
            sStream.str(temp);
            break;
        }
    }
    iuserAccount.close();
    string userPassw;
    while (getline(sStream, userPassw, '\t')) {} // gets last entry in a row
    return userPassw;
}

void overwriteFile(string fileName, string newLine, int id) {
    string temp;
    vector <string> vec;
    ifstream fin(fileName.c_str());
    for (int i = 1; getline(fin, temp); i++) {
        if (i == id) vec.push_back(newLine);
        else vec.push_back(temp);
    }
    fin.close();
    ofstream fout(fileName.c_str());
    for (int i = 0; i < vec.size(); i++) {
        fout << vec[i] << endl;
    }
    fout.close();
}

void userMenu() {
    system("cls");
    cout<<"[USER MENU]\n\n";
    cout<<"[1] VIEW INFO\n";
    cout<<"[2] CHANGE PASSWORD\n";
    cout<<"[3] BACK\n";
    int input;
    selectionInput(input, 1, 3);
    void (*menuArr[]) () = {viewUserInfo, updUserPassw, mainMenu};
    (*menuArr[input - 1]) ();
    system("pause");
}

void userLogin() {
    system("cls");
    int id;
    string passw;
    cout << "[LOGIN MENU]\n\n";
    selectionInput(id, 1, 0, "ENTER YOUR ID : ");
    _getline(passw, "ENTER YOUR PASSWORD : ");
    string passCheck = getUserPasswById(id);

    string activeState, temp;
    istringstream sStream;
    ifstream iuserAccount("Data\\userAccount.txt");
    for (int i = 1; getline(iuserAccount, temp); i++) { // gets the row
        if (i == id) {
            sStream.str(temp);
            break;
        }
    }
    iuserAccount.close();
    getline(sStream, activeState, '\t'); // gets 1st entry in row
    getline(sStream, activeState, '\t'); // gets 2nd entry in row

    if (passw == passCheck && (activeState == "Y" || activeState == "y")) {
            ofstream fout("Data\\temp.txt");
            fout << id; // stores session in file
            fout.close();
            userMenu();
    }
    else {
        cout << "\nYOU ENTERED WRONG INFO OR YOUR ACCOUNT IS DEACTIVATED!\n";
        system("pause");
        mainMenu();
    }
}

void viewUserInfo() {
    system("cls");
    int lookupID;
    ifstream fin("Data\\temp.txt");
    fin >> lookupID; // gets lookup id from temp file that stores session
    fin.close();

    string line;
    istringstream sStream;
    bool flag;
    ifstream iuserRecord("Data\\userRecord.txt");
    for (int i = 1; getline(iuserRecord, line); i++) { // pushes line into string stream if line number matches
        if (i == lookupID) {
            sStream.str(line); // sets line as contents of s
            flag = true;
        }
    }
    iuserRecord.close();
    if (flag) {
        string entry;
        vector <string> row;
        // row.clear();
        while(getline(sStream, entry, '\t')) {
            row.push_back(entry);
        }
        cout << "[USER INFO]\n\n";
        cout<<"USER ID : "<<row[0]<<endl;
        cout<<"ACTIVE : "<<row[1]<<endl;
        cout<<"NAME : "<<row[2]<<endl;
        cout<<"PHONE: "<<row[3]<<endl;
        cout<<"CNIC : "<<row[4]<<endl;
        cout<<"ADDRESS: "<<row[5]<<endl;
        cout<<"INCOME : "<<row[6]<<endl;
        cout<<"CAR MODEL : "<<row[7]<<endl;
        cout<<"CAR NUMBER : "<<row[8]<<endl;
        cout<<"PURCHASE YEAR : "<<row[9]<<endl;
        cout << "CLAIM COUNT : "<< row[10] << endl;
        cout << "ACCIDENT COUNT : " << row[11] << endl;
        cout << "PREMIUM PRICE : " << calPremium(row[6], row[10]) << endl;
        system("pause");
        userMenu();
    }
}

void updUserPassw() {
    system("cls");
    cout << "[CHANGE PASSWORD]\n\n";

    int lookupID;
    ifstream fin("Data\\temp.txt");
    fin >> lookupID; // gets lookup id from temp file that stores session
    fin.close();
    string passCheck = getUserPasswById(lookupID);

    string passw, newpass1, newpass2;
    _getline(passw, "ENTER OLD PASSWORD : ");
    if (passw == passCheck) {
        _getline(newpass1, "ENTER NEW PASSWORD : ");
        _getline(newpass2, "RE-ENTER NEW PASSWORD : ");

        if (newpass1 == newpass2 && newpass1 != "") {
            ostringstream sout;
            sout << lookupID << "\t" << "Y" << "\t" << newpass1;
            string line = sout.str();
            overwriteFile("Data\\userAccount.txt", line, lookupID);
            cout << "\nPASSWORD CHANGED SUCCESSFULLY!\n";
            system("pause");
            userMenu();
        }
        else {
            cout << "\nPASSWORDS NOT CORRECT!\n";
            system("pause");
            userMenu();
        }
    }
    else {
        cout << "\nYOU ENTERED WRONG PASSWORD!\n";
        system("pause");
        userMenu();
    }
}

void dataCheck()  {
    ifstream iuserList("Data\\userList.txt");
    ifstream iuserRecord("Data\\userRecord.txt");
    ifstream iuserAccount("Data\\userAccount.txt");
    ifstream isettings("Data\\settings.txt");
    if (!(iuserList.is_open() && iuserRecord.is_open() && iuserAccount.is_open() && isettings.is_open())) {
        cout << "COULD NOT ACCESS FILES ;-;\n";
        iuserList.close();
        iuserRecord.close();
        iuserAccount.close();
        isettings.close();
        system("rmdir /q /s Data");
        cout << "DATA DELETED!\n";

        system("mkdir Data");
        ofstream ouserList("Data\\userList.txt");
        ofstream ouserRecord("Data\\userRecord.txt");
        ofstream ouserAccount("Data\\userAccount.txt");
        ofstream osettings("Data\\settings.txt");
        osettings << "theme=color 0f"<<endl;
        ouserList.close();
        ouserRecord.close();
        ouserAccount.close();
        osettings.close();

        dataCheck(); // recursion
    }
    else {
        iuserList.close();
        iuserRecord.close();
        iuserAccount.close();
        isettings.close();
    }

    system("cls");
}

void loadTheme() {
    string temp, theme;
    ifstream fin("Data\\settings.txt");
    getline(fin, temp, '=');
    getline(fin, theme);
    fin.close();

   system(theme.c_str());
}

void validYesNo(string &str, string msg) {
    string input;
    _getline(input, msg);
    if (input == "Y" || input == "y") {
        str = "Y";
    }
    else if (input == "N" || input == "n") {
        str = "N";
    }
    else {
        cout << "INVALID INPUT!\n";
        validYesNo(str, msg);
    }
}

void _getline(string &str, string msg, char a) {
    cout << msg;
    do {
        getline(cin, str, a);
    } while (str == "");
}










