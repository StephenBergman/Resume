#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "BaseAccount.h"
#include <iostream>

class CheckingAccount : public BaseAccount {
public:
    void Withdraw(float amount) override {
        BaseAccount::Withdraw(amount);
        if (withdrawals > 10) {
            balance -= 5.0f;
            std::cout << "A $5 fee was charged for exceeding 10 withdrawals.\n";
        }
    }
};

#endif 
