#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Function declarations
int login(int accountNumbers[], int pins[], int totalUsers);
int findAccount(int accountNumbers[], int totalUsers, int accountNumber);
void displayMenu();
void deposit(double &balance, int accountNumber);
void withdraw(double &balance, int accountNumber);
void sendCash(double balances[], int accountNumbers[], int totalUsers, int senderIndex);
void checkBalance(double balance, int accountNumber);
void displayUserDetails(string names[], int accountNumbers[], double balances[], int totalUsers);

int main()
{
    // Details for the three sample GCC Bank users
    const int totalUsers = 3;

    string names[totalUsers] = {"Thabo Mokoena", "Lerato Dlamini", "Amina Khan"};
    int accountNumbers[totalUsers] = {1001, 1002, 1003};
    int pins[totalUsers] = {1234, 2345, 3456};
    double balances[totalUsers] = {2500.00, 1800.00, 3200.00};

    cout << "====================================" << endl;
    cout << "             GCC BANK" << endl;
    cout << "====================================" << endl;

    int userIndex = login(accountNumbers, pins, totalUsers);

    if (userIndex == -1)
    {
        cout << "Login unsuccessful. Please try again later." << endl;
        return 0;
    }

    cout << endl;
    cout << "Welcome, " << names[userIndex] << "!" << endl;

    int choice = 0;

    // Keep displaying the menu until the user chooses Exit
    while (choice != 5)
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                deposit(balances[userIndex], accountNumbers[userIndex]);
                break;

            case 2:
                withdraw(balances[userIndex], accountNumbers[userIndex]);
                break;

            case 3:
                sendCash(balances, accountNumbers, totalUsers, userIndex);
                break;

            case 4:
                checkBalance(balances[userIndex], accountNumbers[userIndex]);
                break;

            case 5:
                cout << "Thank you for banking with GCC Bank." << endl;
                cout << "Goodbye, " << names[userIndex] << "!" << endl;
                break;

            default:
                cout << "Invalid menu choice. Please select a number from 1 to 5." << endl;
        }
    }

    return 0;
}

// Checks the account number and PIN and returns the user's array position
int login(int accountNumbers[], int pins[], int totalUsers)
{
    int enteredAccount;
    int enteredPin;

    cout << "Enter your account number: ";
    cin >> enteredAccount;

    cout << "Enter your PIN: ";
    cin >> enteredPin;

    for (int i = 0; i < totalUsers; i++)
    {
        if (accountNumbers[i] == enteredAccount && pins[i] == enteredPin)
        {
            return i;
        }
    }

    cout << "Incorrect account number or PIN." << endl;
    return -1;
}

// Searches the account number array and returns its position
int findAccount(int accountNumbers[], int totalUsers, int accountNumber)
{
    for (int i = 0; i < totalUsers; i++)
    {
        if (accountNumbers[i] == accountNumber)
        {
            return i;
        }
    }

    return -1;
}

// Displays the available banking options
void displayMenu()
{
    cout << endl;
    cout << "========== GCC BANK MENU ==========" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Send Cash" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
    cout << "===================================" << endl;
}

// Adds a positive amount to the selected user's balance
void deposit(double &balance, int accountNumber)
{
    double amount;

    cout << "Enter the amount to deposit: R";
    cin >> amount;

    if (amount > 0)
    {
        balance = balance + amount;
        cout << fixed << setprecision(2);
        cout << "Deposit successful." << endl;
        cout << "Account number: " << accountNumber << endl;
        cout << "New balance: R" << balance << endl;
    }
    else
    {
        cout << "Invalid amount. The deposit must be more than R0.00." << endl;
    }
}

// Subtracts money only when the amount is positive and the balance is sufficient
void withdraw(double &balance, int accountNumber)
{
    double amount;

    cout << "Enter the amount to withdraw: R";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid amount. Enter an amount greater than R0.00." << endl;
    }
    else if (amount > balance)
    {
        cout << "Transaction declined. Insufficient funds." << endl;
    }
    else
    {
        balance = balance - amount;
        cout << fixed << setprecision(2);
        cout << "Withdrawal successful." << endl;
        cout << "Account number: " << accountNumber << endl;
        cout << "Remaining balance: R" << balance << endl;
    }
}

// Transfers money between two existing accounts
void sendCash(double balances[], int accountNumbers[], int totalUsers, int senderIndex)
{
    int recipientAccount;
    double amount;

    cout << "Enter the recipient account number: ";
    cin >> recipientAccount;

    int recipientIndex = findAccount(accountNumbers, totalUsers, recipientAccount);

    if (recipientIndex == -1)
    {
        cout << "Recipient account does not exist." << endl;
    }
    else if (recipientIndex == senderIndex)
    {
        cout << "You cannot send cash to your own account." << endl;
    }
    else
    {
        cout << "Enter the amount to send: R";
        cin >> amount;

        if (amount <= 0)
        {
            cout << "Invalid amount. Enter an amount greater than R0.00." << endl;
        }
        else if (amount > balances[senderIndex])
        {
            cout << "Transfer declined. Insufficient funds." << endl;
        }
        else
        {
            balances[senderIndex] = balances[senderIndex] - amount;
            balances[recipientIndex] = balances[recipientIndex] + amount;

            cout << fixed << setprecision(2);
            cout << "Cash sent successfully." << endl;
            cout << "Recipient account: " << recipientAccount << endl;
            cout << "Amount sent: R" << amount << endl;
            cout << "Your new balance: R" << balances[senderIndex] << endl;
        }
    }
}

// Displays the current balance of the logged-in user
void checkBalance(double balance, int accountNumber)
{
    cout << fixed << setprecision(2);
    cout << endl;
    cout << "---------- ACCOUNT BALANCE ----------" << endl;
    cout << "Account number: " << accountNumber << endl;
    cout << "Available balance: R" << balance << endl;
    cout << "-------------------------------------" << endl;
}

// Displays the sample account information (not used to reveal PINs)
void displayUserDetails(string names[], int accountNumbers[], double balances[], int totalUsers)
{
    cout << fixed << setprecision(2);

    for (int i = 0; i < totalUsers; i++)
    {
        cout << names[i] << " | Account: " << accountNumbers[i]
             << " | Balance: R" << balances[i] << endl;
    }
}
