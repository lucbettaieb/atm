/**
 * ATM Controller Simulator
 * Luc Bettaieb, 2021
 */

// C++ Standard Library
#include <memory>

// ATM Controller
#include "account.h"

Account::Account(std::shared_ptr<Machine> machine, uint64_t accountNumber) :
    machine_(machine),
    account_number_(accountNumber),
    locked_(true),
    has_type_(false),
    pin_(machine_->getPin(accountNumber)),
    balances_(machine->getAccountBalances(accountNumber)) {
}

void Account::unlock(uint16_t pin) {
  // TODO(luc): hash
  if (pin == pin_) {
    // Request from server account details

    locked_ = false;
  } else {
    throw std::runtime_error("Wrong pin");
  }
}

void Account::selectType(const AccountType accountType) {
  if (locked_ or has_type_) {
    throw std::runtime_error("Account is locked / type already selected");
  }

  account_type_ = accountType;
  has_type_ = true;
}

int Account::getBalance() {
  if (locked_ or !has_type_) {
    throw std::runtime_error("Account is locked / type not selected");
  }

  return balances_.get(account_type_);
}

void Account::deposit(int deposit_amount) {
  if (locked_ or !has_type_) {
    throw std::runtime_error("Account is locked / type not selected");
  }

  balances_.get(account_type_) += deposit_amount;
}

void Account::withdraw(uint withdraw_amount) {
  if (locked_ or !has_type_) {
    throw std::runtime_error("Account is locked / type not selected");
  } else if (withdraw_amount > machine_->getAvailableCash()) {
    // Should probably give a vague error and tell the user to try another ATM
    throw std::runtime_error("E12345: Something went wrong!");
  } else if (withdraw_amount > balances_.limit(account_type_)) {
    // Should probably lock user out of account for a while and trigger a security alert
    throw std::runtime_error("E12344: Withdraw amount too great, change your settings online");
  } else if (withdraw_amount > balances_.get(account_type_)) {
    // Should probably lock user out of account for a while and trigger a security alert
    throw std::runtime_error("E12343: Insufficient balance!");
  } else {
    // Debit account
    balances_.get(account_type_) -= static_cast<int>(withdraw_amount);
    machine_->updateAccountBalance(account_number_, -withdraw_amount);

    // Disburse cash
    machine_->disburseCash(withdraw_amount);
  }
}




