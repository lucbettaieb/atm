/**
 * ATM Controller Simulator
 * Luc Bettaieb, 2021
 */

#ifndef ATM_MACHINE_H
#define ATM_MACHINE_H

// C++ Standard Library
#include <unordered_map>
#include <utility>

static std::unordered_map<uint64_t, uint16_t> kAccountPins = {
  {1234123412341234, 1234},
  {2345234523452345, 2345}
};

enum AccountType {
  CHECKING = 0,
  SAVINGS = 1
};

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

static std::unordered_map<uint64_t, Balances> kAccountBalances = {
  {1234123412341234, {1000, 10000}},
  {2345234523452345, {9999, 99999}}
};

static uint kAvailableCashLogged = 100000;

/**
 * @brief Class to represent machine functions and bank server queries
 */
class Machine {
public:
  Machine();

  uint16_t getPin(uint64_t accountNumber);

  Balances getAccountBalances(uint64_t accountNumber);

  void updateAccountBalance(uint64_t accountNumber, int amount);

  uint getAvailableCash();

  void disburseCash(uint amount);

private:
  inline std::unordered_map<uint64_t, uint16_t> initializeAccountPins() {
    // Make call to server to get account pins
    // TODO(enhancement): Maybe just do one at a time actually
    return kAccountPins;
  }

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
