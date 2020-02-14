#include <iostream>
#include <cstring>
#include <cstdlib>
#include <wtypes.h>
#include <vector>
#include <fstream>
#include <windows.h>

using namespace std;



ofstream myfile;
ifstream infile;

/// person - base class . with polymorphic ablity ,virtual methods getdetails most notable

class Person {                   // base class
public:
    string firstName;
    string lastName;


    Person(const string &firstName,
           const string &lastName) : firstName(firstName),
                                     lastName(lastName) {}

    virtual const string &getFirstName() const {
        return firstName;
    }

    virtual const string &getLastName() const {
        return lastName;
    }

    virtual void getDetails() {
        cout << " name is :" << firstName << " " << lastName << endl;
    }


    virtual ~Person() = default;
};


/// customer inherit from person ,(inherited class , parent class)
class Customer : public Person {

public:
    int age;
    string nationality;
    string DateOfBirth;

    Customer(const string &firstName, const string &lastName, int age, const string &nationality,
             const string &DateOfBirth)
            : Person(firstName, lastName), age(age), nationality(nationality), DateOfBirth(DateOfBirth) {}

    int getAge() const {
        return age;
    }

    const string &getNationality() const {
        return nationality;
    }


    void getDetails() {
        cout << "full name :" << firstName  << " "<< lastName << endl;
        cout << "age : " << age << endl;
        cout << "nationality : " << nationality << endl;
    }
};
/// customer account derived from customer, which means all account is attached to a customer

class AccountCustomer : public Customer {

private:
    int accountNumber;
    double balance;
    string accountType;

public:

    AccountCustomer(const string &firstName, const string &lastName, int age, const string &nationality,
                    const string &DateOfBirth, int accountNumber, double balance, string accountType)
            : Customer(
            firstName, lastName, age, nationality, DateOfBirth), accountNumber(accountNumber), balance(balance),
              accountType(accountType) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void getAccountDetails() {
        //cout << endl << "***************************************" << endl;
        cout << "\n\nMr/Mrs :" << firstName << endl;
        cout << "total balance : " << balance << endl;
        cout << "ac no : " << accountNumber << endl;
        cout << "ac type :" << accountType << endl;
    //    cout << "***************************************" << endl;

    }

    int withdrawFromAccout(double amount) {
        cout << "account of MR/MRS " << lastName;
        if (balance > amount) {
            balance = balance - amount;
            cout << "\nwithdrawn successfully ,current balance is " << balance << endl;
            return 1;
        } else {
            cout << "insufficent balance" << endl;

            return 0;
        }

    };


    int depositIntoAccount(double amount) {
        cout << " account of MR/MRS" << lastName;
        balance = balance + amount;
        cout << "\nyour deposit is made ,current balance is " << balance << endl;
    }


    void setAccountNumber(int accountNumber) {
        AccountCustomer::accountNumber = accountNumber;
    }

    const string &getAccountType() const {
        return accountType;
    }

};


int randrange(int low, int high) {
    return rand() % (high - low + 1) + low; // NOLINT
}

/// bank with the operation on accounts , vector used as data structure to store the accounts after reading from text file
class Bank {
public:
    vector<AccountCustomer> accounts;

    void createNewAccount(AccountCustomer newAccount) {
        int random;
        bool check = true;

        do {
            random = randrange(100000, 999999);

            for (int i = 0; i < accounts.size(); ++i) {
                if (random == accounts[i].getAccountNumber()) {
                    check = false;
                    break;
                } else {
                    check = true;
                }
            }

        } while (!check);
        newAccount.setAccountNumber(random);
        accounts.push_back(newAccount);
        saveToFile();
    }

    void depositAccount(int accountNumber, double amount) {
        bool found = false;
        for (int i = 0; i < accounts.size(); ++i) {
            if (accountNumber == accounts[i].getAccountNumber()) {
                accounts[i].depositIntoAccount(amount);
                found = true;
            }
        }
        if (found) {
            saveToFile();
        } else {
            cout << "no account was found for this detail" << endl;
        }

    }

    void withdraw(int accountNumber, double amount) {
        bool found = false;
        for (int i = 0; i < accounts.size(); ++i) {
            if (accountNumber == accounts[i].getAccountNumber()) {
                accounts[i].withdrawFromAccout(amount);
                found = true;
            }
        }
        if (found) {
            saveToFile();
        } else {
            cout << "no account was found for this detail" << endl;
        }

    }

    bool removeAccount(int accountNumber) {
        bool found = false;
        for (int i = 0; i < accounts.size(); ++i) {
            if (accountNumber == accounts[i].getAccountNumber()) {
                accounts.erase(accounts.begin() + i);
                found = true;
            }
        }
        if (found) {
            saveToFile();
            return true;
        } else {
            cout << "no account was found for this detail" << endl;
            return false;
        }
    }

    void displayDetails(int accountNumber) {
        bool found = false;
        for (int i = 0; i < accounts.size(); ++i) {
            if (accountNumber == accounts[i].getAccountNumber()) {
               // cout << "__________________________________________________" << endl;

                accounts[i].getAccountDetails();
                accounts[i].getDetails();
               // cout << "__________________________________________________" << endl;
                found = true;
            }
        }
        if (found) {

        } else {
            cout << "no account was found for this detail" << endl;
        }
    }

    bool existInRecord(int number) {
        bool check = false;
        for (int i = 0; i < accounts.size(); i++) {
            if (number == accounts[i].getAccountNumber()) {
                check = true;
                break;
            }
        }
        return check;
    }

    int checkBalance(int accountNumber) {

        for (int i = 0; i < accounts.size(); ++i) {
            if (accountNumber == accounts[i].getAccountNumber()) {
                return accounts[i].getBalance();
            }
        }
    }

    void listAll() {
       // cout << "******************************************" << endl;

        for (int i = 0; i < accounts.size(); ++i) {
            accounts[i].getAccountDetails();
        }

    }
    // saving data in record.txt

    void saveToFile() {
        myfile.open("record.txt");
        for (auto &account: accounts) {
            myfile << account.getAccountNumber() << " " << account.getBalance() << " " <<
                   account.getFirstName() << " " <<
                   account.getLastName() << " " << account.getNationality() <<
                   " " << account.getAccountType() << endl;
        }
        myfile.close();
    }

    void readFromFile() {
        infile.open("record.txt");
        int number;
        double balance;
        string firstName;
        string lastName;
        string nationality;
        string accountType;
        while (infile >> number >> balance >> firstName >> lastName >> nationality >> accountType) {

            AccountCustomer account(firstName, lastName, 20, nationality, "20-21", number, balance, accountType);
            accounts.push_back(account);

        }
        infile.close();
    }

};

/// admin account derived from class person , polymorphic ability also
class AdminAccount : public Person {

private:
    string username;
    string password;
    Bank bank;
public:

    AdminAccount(const string &firstName, const string &lastName, const string &username)
            : Person(firstName, lastName), username(username) {
        password = "polsl";

    }

    void getDetails() override {
      //  cout << " name is :" << firstName << " " << lastName << endl;
      //  cout << "username is " << username << endl;
    }

    const string &getPassword() const {
        return password;
    }

    const string &getUsername() const {
        return username;
    }

    void perFormAdminOperatioin() {

        int operation;
        bank.readFromFile();


        do {
            cout << "\n__________________________" << endl;
            cout << "1. Create New Account" << endl;
            cout << "2. List of Accounts" << endl;
            cout << "3. Withdraw money " << endl;
            cout << "4. Deposit money" << endl;
            cout << "5. Show account details" << endl;
            cout << "6. Delete account" << endl;
            cout << "0. RETURN" << endl;
            //cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
           // cout << "perform another operation or press 0 to exit" << endl;
            cin >> operation;
            switch (operation) {
                case 1:
                    createNewCustomerAccount();
                    break;
                case 2:

                    system("cls");
                    cout << "list of all account holders" << endl;
                    bank.listAll();

                    break;
                case 3:
                    system("cls");
                    withdrawFromAccount();
                    break;
                case 4:
                    system("cls");
                    depositIntoCustomerAccount();
                    break;
                case 5:
                    system("cls");
                    details();
                    break;
                case 6:
                    if (removeAccount()) {
                        cout << "successfully removed " << endl;
                    }
                    break;
                default:
                    bank.accounts.clear();
                    break;

            }
        } while (operation != 0);
    }

    void createNewCustomerAccount() {

        double startAmount;
        string accountType;
        Customer customer("dummmy", "dumm", 20, "ibadan", "22-02");

        Person *person = &customer;   /// polymorphosim  using the reference of person to get a customer
        cout << "first name " << endl;
        cin >> person->firstName;
        cout << "last Name" << endl;
        cin >> person->lastName;
        cout << "age  " << endl;
        cin >> customer.age;
        cout << "nationality" << endl;
        cin >> customer.nationality;
        cout << "opening amount" << endl;
        cin >> startAmount;

        do {
            cout << "account type (current/savings/fixed) :" ;
            cin >> accountType;
        } while ((accountType != "current") && (accountType != "savings") && (accountType != "fixed"));


        AccountCustomer accountCustomer(person->firstName, person->lastName, customer.age, customer.nationality, "20",
                                        0, startAmount, accountType);
        bank.createNewAccount(accountCustomer);

    }

    void depositIntoCustomerAccount() {
        int number;
        double amount;
        cout << "Account number of client" << endl;
        cin >> number;
        cout << "amount to deposit" << endl;
        cin >> amount;
        bank.depositAccount(number, amount);
    }

    void withdrawFromAccount() {
        int number;
        double amount;
        cout << "Account number of client" << endl;
        cin >> number;
        cout << "amount to withdraw" << endl;
        cin >> amount;
        bank.withdraw(number, amount);
    }

    void details() {
        int number;
        cout << "Account number of client" << endl;
        cin >> number;
        bank.displayDetails(number);
    }

    bool removeAccount() {
        int number;
        cout << "Account number of client" << endl;
        cin >> number;
        return bank.removeAccount(number);
    };

};


int main() {
    Bank bank;
    AdminAccount adminAccount("BANK BUDAPEST", "polsl", "polsl");
    Person *person = &adminAccount;                     /// you are using reference to create an admin  this is polymorphic
    person->getDetails();                     /// polymorphorsim using person as an admin
    int commandIn;


    do {
        cout << "\nBANK BUDAPEST" << endl;
        cout << "\n\n1.ADMIN" << endl;
        cout << "2.ACCOUNT HOLDER" << endl;
        cout << "0.QUIT" << endl;
       // cout << "_________________________________________" << endl;
       // cout << " enter desire operation _" << endl;
        cin >> commandIn;
        string password;
        string username;
        switch (commandIn) {
            case 1 :
                do {
                    cout << "Enter username" << endl;
                    cin >> username;
                    cout << "Enter password" << endl;
                    cin >> password;
                } while ((username != adminAccount.getUsername()) || (password != adminAccount.getPassword()));
                adminAccount.perFormAdminOperatioin();
                break;
            case 2:

                int number;
                int operation;

                do {
                    // the customer does't have right to deposit or withdraw without permission of admin
                    bank.readFromFile();

                    cout << "make sure you use correct account number" << endl;
                    cout << "enter your account number" << endl;
                    cin >> number;
                    if (bank.existInRecord(number)) {
                        do {

                         //   cout << "__________________________________________________" << endl;
                            cout << "\n1. Account details " << endl;
                            cout << "2. balance inquiry " << endl;
                            cout << "0. LOG-OUT " << endl;
                          //  cout << "__________________________________________________" << endl;
                            cin >> operation;

                            switch (operation) {
                                case 1:
                                    system("cls");
                                    bank.displayDetails(number);
                                    break;
                                case 2:
                                    system("cls");
                                    cout << "current balance is " << bank.checkBalance(number) << endl;
                                    break;
                                default:

                                    break;
                            }
                        } while (operation != 0);
                    } else {
                        cout << "not found" << endl;
                    }

                } while (!bank.existInRecord(number));

                break;
            default:
                cout << "POWERD BY BANK BUDAPEST" << endl;
                break;
        }

    } while (commandIn != 0);

}


