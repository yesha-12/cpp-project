#include<iostream>
#include<fstream>
using namespace std;

class ATM
{
    int accno, pin, balance;

public:

   
    void createAccount()
    {
        ofstream fout("accounts.txt", ios::app);

        int newAcc, newPin, deposit;

        cout << "\n--- Create Account ---\n";

        cout << "Enter new Account Number: ";
        cin >> newAcc;

        cout << "Set PIN: ";
        cin >> newPin;

        cout << "Enter Initial Deposit: ";
        cin >> deposit;

        fout << newAcc << " " << newPin << " " << deposit << endl;

        fout.close();

        cout << "\nAccount Created Successfully!\n";
    }

    
    bool login()
    {
        int inputAcc, inputPin;
        bool found = false;

        cout << "Enter Account Number: ";
        cin >> inputAcc;

        cout << "Enter PIN: ";
        cin >> inputPin;

        ifstream fin("accounts.txt");

        while(fin >> accno >> pin >> balance)
        {
            if(accno == inputAcc && pin == inputPin)
            {
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
            cout << "\nInvalid Account or PIN!\n";
            return false;
        }
    }

    
    void saveAll()
    {
        ifstream fin("accounts.txt");
        ofstream temp("temp.txt");

        int a, p, b;

        while(fin >> a >> p >> b)
        {
            if(a == accno)
                temp << accno << " " << pin << " " << balance << endl;
            else
                temp << a << " " << p << " " << b << endl;
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
        cin >> amount;

        balance += amount;
        saveAll();

        cout << "Amount Deposited!\n";
    }

    void withdraw()
    {
        int amount;
        cout << "Enter amount: ";
        cin >> amount;

        if(amount <= balance && balance - amount >= 500){
            balance -= amount;
            saveAll();
            cout << "Collect Cash!\n";
        }
        else{
            cout << "Insufficient Balance!\n";
        }
    }

    void changePin()
    {
        int oldpin, newpin;

        cout << "Enter old PIN: ";
        cin >> oldpin;

        if(oldpin == pin){
            cout << "Enter new PIN: ";
            cin >> newpin;

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
            cin >> choice;

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
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                user.createAccount();
                break;

            case 2:
                if(user.login()){
                    user.menu();
                }
                break;

            case 3:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    }while(choice != 3);

    return 0;
}