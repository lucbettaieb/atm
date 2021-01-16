/**
 * ATM Controller Simulator
 * Luc Bettaieb, 2021
 */

#ifndef ATM_ACCOUNT_H
#define ATM_ACCOUNT_H

// C++ Standard Library
#include <exception>
#include <memory>

// ATM Controller
#include "machine.h"

struct ManagementAction {
  enum ManagementActionType { WITHDRAW = 0, DEPOSIT = 1, BALANCE = 2, DONE = 4 };

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
  Account(std::shared_ptr<Machine> machine, uint64_t accountNumber);

  void unlock(uint16_t pin);

  void selectType(const AccountType accountType);

  int getBalance();

  void deposit(int deposit_amount);

  void withdraw(uint withdraw_amount);

 private:
  /// Pointer to the machine to access control functions
  std::shared_ptr<Machine> machine_;

  /// Whether or not the account is locked
  bool locked_;

  // Whether or not the type of accounthas been set yet
  bool has_type_;

  /// Account number for the account
  uint64_t account_number_;

  /// The pin of the account
  uint16_t pin_;

  /// The type of account we're accessing
  AccountType account_type_;

  /// The balance of the account
  Balances balances_;
};

#endif  // ATM_ACCOUNT_H
