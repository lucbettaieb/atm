/**
 * ATM Controller Simulator
 * Luc Bettaieb, 2021
 */

#ifndef ATM_MACHINE_H
#define ATM_MACHINE_H

// C++ Standard Library
#include <unordered_map>
#include <utility>

/// Enumerated type for which account to access
enum AccountType {
  CHECKING = 0,
  SAVINGS = 1
};

/// Struct to allow for access/modification to account balances and access to limits
struct Balances {
  Balances(int c, int s) :
    savings(s),
    checking(c) {}

  int savings;
  int checking;

  int savings_withdraw_limit{1000};  // Could make this more customized
  int checking_withdraw_limit{5000};

  int& get(AccountType type) {
    if (type == AccountType::CHECKING) {
      return checking;
    } else if (type == AccountType::SAVINGS) {
      return savings;
    }
  }

  int limit(AccountType type) {
    if (type == AccountType::CHECKING) {
      return checking_withdraw_limit;
    } else if (type == AccountType::SAVINGS) {
      return savings_withdraw_limit;
    }
  }
};

/// Simulated accounts and pin
static std::unordered_map<uint64_t, uint16_t> kAccountPins = {
  {1234123412341234, 1234},
  {2345234523452345, 2345}
};

/// Simulated accounts and their balances (checking / savings)
static std::unordered_map<uint64_t, Balances> kAccountBalances = {
  {1234123412341234, {1000, 10000}},
  {2345234523452345, {9999, 99999}}
};

/// Simulated amount of money available in the atm
static uint kAvailableCashLogged = 100000;

/**
 * @brief Class to represent machine functions and bank server queries
 */
class Machine {
public:
  /// Constructor for the machine / server interface
  Machine();

  /// Gets the appropriate pin for an account number
  uint16_t getPin(uint64_t accountNumber);

  /// Creates a balances struct given an account number
  Balances getAccountBalances(uint64_t accountNumber);

  /// Simulates updating the account balance on some server endpoint
  void updateAccountBalance(uint64_t accountNumber, int amount);

  /// Checks to see how much cash is available in the ATM
  uint getAvailableCash();

  /// Dispenses cash to the user
  void disburseCash(uint amount);

private:
  /// Init function for initializing the internal database of account nums and pins
  inline std::unordered_map<uint64_t, uint16_t> initializeAccountPins() {
    // Make call to server to get account pins
    // TODO(enhancement): Maybe just do one at a time actually
    return kAccountPins;
  }

  /// Init function for initializing the amount of available cash
  inline uint initializeAvailableCash() {
    // Query internal ledger to see how much we are supposed to have
    uint amount_logged = []()->uint { return kAvailableCashLogged; }();
    // Query machine to count its own money using internal money counter mechanism (same for now)
    uint amount_available = []()->uint { return kAvailableCashLogged; }();
    if (amount_logged != amount_available) {
      // Trigger a warning and send the notification to home base
    }

    return amount_available;
  }

  /// The amount of cash available in the ATM
  uint available_cash_;

  /// Simulated database of account pins
  std::unordered_map<uint64_t, uint16_t> account_pins_;
};

#endif  // ATM_MACHINE_H
