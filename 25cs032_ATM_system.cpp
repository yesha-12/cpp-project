#include<iostream>
#include<fstream>
using namespace std;

class ATM
{
    int cardno, pin, balance;

public:

    bool login()
    {
        int inputCard, inputPin;
        bool found = false;

        cout << "Enter ATM Card Number: ";
        if(!(cin >> inputCard)){
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return false;
        }

        cout << "Enter PIN: ";
        if(!(cin >> inputPin)){
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return false;
        }

        ifstream fin("accounts.txt");

        if(!fin){
            cout << "Error: accounts.txt not found!\n";
            return false;
        }

        int c, p, b;

        while(fin >> c >> p >> b)
        {
            if(c == inputCard && p == inputPin)
            {
                cardno = c;
                pin = p;
                balance = b;
                found = true;
                break;
            }
        }

        fin.close();

        if(found){
            cout << "\nLogin Successful!\n";
            return true;
        }
        else{
            cout << "\nInvalid Card or PIN!\n";
            return false;
        }
    }

    void saveAll()
    {
        ifstream fin("accounts.txt");
        ofstream temp("temp.txt");

        int c, p, b;

        while(fin >> c >> p >> b)
        {
            if(c == cardno)
                temp << cardno << " " << pin << " " << balance << endl;
            else
                temp << c << " " << p << " " << b << endl;
        }

        fin.close();
        temp.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }

    void checkBalance()
    {
        cout << "Balance: " << balance << endl;
    }

    void deposit()
    {
        int amount;
        cout << "Enter amount: ";

        if(!(cin >> amount))
        {
            cout << "❌ Invalid input! Enter numbers only.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;   // return to menu (loop continues)
        }

        balance += amount;
        saveAll();

        cout << "✅ Amount Deposited!\n";
    }

    void withdraw()
    {
        int amount;
        cout << "Enter amount: ";

        if(!(cin >> amount))
        {
            cout << "❌ Invalid input! Enter numbers only.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;   // return to menu (loop continues)
        }

        if(amount <= balance && balance - amount >= 500){
            balance -= amount;
            saveAll();
            cout << "💵 Collect Cash!\n";
        }
        else{
            cout << "❌ Insufficient Balance!\n";
        }
    }

    void changePin()
    {
        int oldpin, newpin;

        cout << "Enter old PIN: ";
        if(!(cin >> oldpin)){
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        if(oldpin == pin){
            cout << "Enter new PIN: ";
            if(!(cin >> newpin)){
                cout << "Invalid input!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                return;
            }

            pin = newpin;
            saveAll();

            cout << "PIN Changed!\n";
        }
        else{
            cout << "Wrong PIN!\n";
        }
    }

    void menu()
    {
        int choice;

        do{
            cout << "\n--- ATM MENU ---\n";
            cout << "1. Check Balance\n";
            cout << "2. Deposit\n";
            cout << "3. Withdraw\n";
            cout << "4. Change PIN\n";
            cout << "5. Exit\n";

            cout << "Enter choice: ";

            if(!(cin >> choice)){
                cout << "❌ Invalid Choice!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            switch(choice)
            {
                case 1: checkBalance(); break;
                case 2: deposit(); break;
                case 3: withdraw(); break;
                case 4: changePin(); break;
                case 5: cout << "Thank You!\n"; break;
                default: cout << "Invalid Choice!\n";
            }

        }while(choice != 5);
    }
};

int main()
{
    ATM user;
    int choice;

    do{
        cout << "\n===== ATM SYSTEM =====\n";
        cout << "1. Login\n";
        cout << "2. Exit\n";

        cout << "Enter choice: ";

        if(!(cin >> choice)){
            cout << "❌ Invalid Choice!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch(choice)
        {
            case 1:
                if(user.login()){
                    user.menu();
                }
                break;

            case 2:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    }while(choice != 2);

    return 0;
}