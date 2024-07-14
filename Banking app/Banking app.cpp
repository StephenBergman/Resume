#include <iostream>
#include <crtdbg.h>
#include "BaseAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"

// Change this number to the line number the Output window shows you
// to follow a memory leak. Put -1 to disable.
#define MEMORY_LEAK_LINE -1

void Deposit(BaseAccount* account) {
    float amount;
    std::cout << "Enter amount to deposit: \n";
    std::cin >> amount;
    account->Deposit(amount);
}

void Withdraw(BaseAccount* account) {
    float amount;
    std::cout << "Enter amount to withdraw: \n";
    std::cin >> amount;
    account->Withdraw(amount);
}

void DisplayBalances(BaseAccount* checking, BaseAccount* savings, BaseAccount* credit) {
    std::cout << "Checking Account Balance: $" << checking->GetBalance() << "\n";
    std::cout << "Savings Account Balance: $" << savings->GetBalance() << "\n";
    std::cout << "Credit Account Balance: $" << credit->GetBalance() << "\n";
}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetBreakAlloc(MEMORY_LEAK_LINE);

    CheckingAccount* checking = new CheckingAccount();
    SavingsAccount* savings = new SavingsAccount();
    CreditAccount* credit = new CreditAccount();

    bool running = true;
    while (running) {
        int choice;
        std::cout << "Banking App Menu\n";
        std::cout << "1. Deposit to Checking Account\n";
        std::cout << "2. Withdraw from Checking Account\n";
        std::cout << "3. Deposit to Savings Account\n";
        std::cout << "4. Withdraw from Savings Account\n";
        std::cout << "5. Deposit to Credit Account\n";
        std::cout << "6. Withdraw from Credit Account\n";
        std::cout << "7. Display Balances\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            Deposit(checking);
            std::cout << "$ deposited to Checking Account!\n";
            break;
        case 2:
            Withdraw(checking);
            break;
        case 3:
            Deposit(savings);
            std::cout << "$ deposited to Savings Account!\n";
            break;
        case 4:
            Withdraw(savings);
            break;
        case 5:
            Deposit(credit);
            std::cout << "$ deposited to Credit Account!\n";
            break;
        case 6:
            Withdraw(credit);
            break;
        case 7:
            DisplayBalances(checking, savings, credit);
            break;
        case 8:
            running = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    delete checking;
    delete savings;
    delete credit;

    return 0;
}

