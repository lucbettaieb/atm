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

      // Maybe have a timer in here to see if no state transitons have been requested in some timeout time, then
      // automatically call for one to occur to back to idle as a safety feature to log the user out

      // Maintain kFrequency update rate
      const double sleep_s = static_cast<double>(1 / kFrequency);
      const double sleep_ms = sleep_s * 1000;
      std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleep_ms)));
    }
  });

  std::cout << "Initial State" << std::endl;

  std::cout << "State: " << kATMScreenStateToString.at(atm.getState()) << std::endl;;
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << std::endl;

  std::cout << "Card reader: 1234123412341234" << std::endl;
  atm.cardReaderCB(1234123412341234);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << "State: " << kATMScreenStateToString.at(atm.getState()) << std::endl;;
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << std::endl;

  std::cout << "Enter pin: 1234" << std::endl;
  atm.enterPinCB(1234);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << "State: " << kATMScreenStateToString.at(atm.getState()) << std::endl;;
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << std::endl;

  std::cout << "Select CHECKING account" << std::endl;
  atm.accountSelectCB(AccountType::CHECKING);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << "State: " << kATMScreenStateToString.at(atm.getState()) << std::endl;;
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << std::endl;

  ManagementAction balance_action{ManagementAction::ManagementActionType::BALANCE};
  ManagementAction deposit_action{ManagementAction::ManagementActionType::DEPOSIT, 100};
  ManagementAction withdraw_action{ManagementAction::ManagementActionType::WITHDRAW, 150};
  ManagementAction done_action{ManagementAction::ManagementActionType::DONE};

  std::cout << "Check balance" << std::endl;
  atm.accountManagementCB(balance_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << std::endl;

  std::cout << "Deposit 100 bucks" << std::endl;
  atm.accountManagementCB(deposit_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << "Check balance" << std::endl;
  atm.accountManagementCB(balance_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << std::endl;

  std::cout << "Withdraw 150 bucks" << std::endl;
  atm.accountManagementCB(withdraw_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << "Check balance" << std::endl;
  atm.accountManagementCB(balance_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << std::endl;

  std::cout << "Signal done with the ATM" << std::endl;
  atm.accountManagementCB(done_action);
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << "State: " << kATMScreenStateToString.at(atm.getState()) << std::endl;;
  std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000)));
  std::cout << std::endl;

  ok = false;
  t.join();
  return 0;
}
