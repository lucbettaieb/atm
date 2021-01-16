/**
 * ATM Controller Simulator
 * Luc Bettaieb, 2021
 */

#ifndef ATM_ACCOUNT_H
#define ATM_ACCOUNT_H

#include <exception>
#include <memory>

#include "machine.h"

struct ManagementAction {
  enum ManagementActionType { WITHDRAW = 0, DEPOSIT = 1, BALANCE = 2, DONE = 4};

  ManagementAction(ManagementActionType action, int amount = 0) : 
    action(action), amount(amount) {}

  ManagementActionType action;
  int amount;
};

/**
 * @brief Class representing an individual account in the bank accessed by the ATM
 */
class Account {
 public:
  Account(std::shared_ptr<Machine> machine, uint16_t accountNumber) :
      machine_(machine),
      account_number_(accountNumber),
      locked_(true),
      pin_(machine_->getPin(accountNumber)),
      balances_(machine->getAccountBalances(accountNumber)) {
  }

  void unlock(uint8_t pin) {
    // TODO(luc): hash
    if (pin == pin_) {
      // Request from server account details

      locked_ = false;
    } else {
      throw std::runtime_error("Wrong pin");
    }
  }

  void selectType(const AccountType accountType) {
    if (locked_ and has_type_) {
      throw std::runtime_error("Account is locked!");
    }

    account_type_ = accountType;
  }

  int getBalance() {
    if (locked_ and has_type_) {
      throw std::runtime_error("Account is locked / type not selected");
    }

    return balances_.get(account_type_);
  }

  void deposit(int deposit_amount) {
    if (locked_ and has_type_) {
      throw std::runtime_error("Account is locked / type not selected");
    }

    balances_.get(account_type_) += deposit_amount;
  }

  void withdraw(uint withdraw_amount) {
    if (locked_ and has_type_) {
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

 private:
  /// Pointer to the machine to access control functions
  std::shared_ptr<Machine> machine_;

  /// Whether or not the account is locked
  bool locked_;

  // Whether or not the type of accounthas been set yet
  bool has_type_;

  /// Account number for the account
  uint16_t account_number_;

  /// The pin of the account
  uint8_t pin_;

  /// The type of account we're accessing
  AccountType account_type_;

  /// The balance of the account
  Balances balances_;
};

#endif  // ATM_ACCOUNT_H
