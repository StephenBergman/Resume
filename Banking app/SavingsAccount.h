#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "BaseAccount.h"
#include <iostream>

class SavingsAccount : public BaseAccount {
public:
    void Withdraw(float amount) override {
        if (withdrawals < 3) {
            BaseAccount::Withdraw(amount);
        }
        else {
            std::cout << "Withdrawal limit exceeded. No more withdrawals allowed.\n";
        }
    }
};

#endif 
