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

/**
 * @brief A struct to be used as message for actions to be performed on an account
 */
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
  /**
   * @brief Constructor for the account
   * 
   * @param machine A pointer to the machine/server interface
   * @param accountNumber The account number to open and register with
   */
  Account(std::shared_ptr<Machine> machine, uint64_t accountNumber);

  /// Unlocks the account when given the right pin
  void unlock(uint16_t pin);

  /// Selects the account type when given a valid account type
  void selectType(const AccountType accountType);

  /// Returns the balance of the account
  int getBalance();

  /// Deposits money into the account
  void deposit(int deposit_amount);

  /// Withdraws money from the account
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
