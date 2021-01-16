/**
 * ATM Controller
 * Luc Bettaieb, 2021
 */

// C++ Standard Library
#include <iostream>
#include <thread>

// ATM Controller
#include "atm.h"

static constexpr int kFrequency = 5;

int main() {
  ATM atm{};
  bool ok = true;

  // State service thread
  std::thread t([&ok, &atm](){ 
    while (ok) {
      atm.service();
      // Maintain kFrequency update rate
      const double sleep_s = static_cast<double>(1 / kFrequency);
      const double sleep_ms = sleep_s * 1000;
      std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleep_ms)));
    }
  });

  atm.printState();
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.cardReaderCB(1234123412341234);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.printState();
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.enterPinCB(1234);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.printState();
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.accountSelectCB(AccountType::CHECKING);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.printState();
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  ManagementAction balance_action{ManagementAction::ManagementActionType::BALANCE};
  ManagementAction deposit_action{ManagementAction::ManagementActionType::DEPOSIT, 100};
  ManagementAction withdraw_action{ManagementAction::ManagementActionType::WITHDRAW, 150};
  ManagementAction done_action{ManagementAction::ManagementActionType::DONE};

  atm.accountManagementCB(balance_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.accountManagementCB(deposit_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.accountManagementCB(balance_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.accountManagementCB(withdraw_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.accountManagementCB(balance_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.accountManagementCB(done_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  atm.printState();
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));

  ok = false;
  t.join();
  return 0;
}

