/**
 * ATM Controller Simulator
 * Luc Bettaieb, 2021
 */

#ifndef ATM_ATM_H
#define ATM_ATM_H

// C++ Standard Library
#include <deque>
#include <exception>
#include <memory>
#include <thread>
#include <unordered_map>

// ATM Controller
#include "account.h"
#include "machine.h"

enum ATMScreenState { IDLE = 0, ENTER_PIN = 1, SELECT_ACCOUNT = 2, ACCOUNT_MANAGEMENT = 3 };

static std::unordered_map<ATMScreenState, std::string> kATMScreenStateToString{
  {ATMScreenState::IDLE, "IDLE"},
  {ATMScreenState::ENTER_PIN, "ENTER_PIN"},
  {ATMScreenState::SELECT_ACCOUNT, "SELECT_ACCOUNT"},
  {ATMScreenState::ACCOUNT_MANAGEMENT, "ACCOUNT_MANAGEMENT"}
};

class ATM {
 public:
  ATM();

  // Main callback service request function
  void service();

  void accountManagementCB(const ManagementAction& action);

  void accountSelectCB(const AccountType accountType);

  void enterPinCB(const uint16_t pin);

  void cardReaderCB(const uint64_t accountNumber);

  ATMScreenState getState();

 private:

  void transitionCB(const ATMScreenState& desiredState);

  /**
   * @brief Performs the state transition and makes required changes along the way
   * 
   * @param desiredState  The state we are transitioning to
   */
  void doStateTransition(const ATMScreenState& desiredState);
  /**
   * @brief Dictates what is a valid state transition for the ATM Controller
   * @details  IDLE -> ENTER_PIN
   *           ENTER_PIN -> SELECT_ACCOUNT, IDLE
   *           SELECT_ACCOUNT -> ACCOUNT_MANAGEMENT, IDLE
   *           ACCOUNT_MANAGEMENT -> IDLE
   * 
   * @param desiredState  The state we are trying to transition to
   * @return  Whether or not the state transition is valid
   */
  bool validTransition(const ATMScreenState& desiredState);

  std::shared_ptr<Account> current_account_;

  std::shared_ptr<Machine> machine_;

  ATMScreenState state_;

  std::deque<ATMScreenState> state_transition_cb_queue_;
};

#endif  // ATM_ATM_H
