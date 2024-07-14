#ifndef BASEACCOUNT_H
#define BASEACCOUNT_H

class BaseAccount {
protected:
    float balance;
    int withdrawals;

public:
    BaseAccount() : balance(0.0f), withdrawals(0) {}

    virtual void Withdraw(float amount) {
        balance -= amount;
        withdrawals++;
    }

    virtual void Deposit(float amount) {
        balance += amount;
    }

    float GetBalance() const {
        return balance;
    }
};

#endif 

