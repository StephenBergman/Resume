#ifndef CREDITACCOUNT_H
#define CREDITACCOUNT_H

#include "BaseAccount.h"
#include <iostream>

class CreditAccount : public BaseAccount {
private:
    int amountSpent;
    static const int SPENDING_LIMIT = 40;

public:
    CreditAccount() : amountSpent(0) {}

    void Withdraw(float amount) override {
        if (amountSpent + amount > SPENDING_LIMIT) {
            balance -= 5000.0f;
            std::cout << "Spending limit exceeded! A $5000 fee was charged.\n";
        }
        else {
            amountSpent += amount;
            BaseAccount::Withdraw(amount);
        }
    }
};

#endif
