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
  /// Constructor for the ATM
  ATM();

  /// Main callback service request function
  void service();

  /// Callback function to give the controller an account number, presumably from a card reader
  void cardReaderCB(const uint64_t accountNumber);

  /// Callback function to give the controller an account pin, presumably from a keypad
  void enterPinCB(const uint16_t pin);

  /// Callback function to select which account to use, presumably from a button
  void accountSelectCB(const AccountType accountType);

  /// Callback function for the interface to give an account management action to the controller
  void accountManagementCB(const ManagementAction& action);

  /// Returns the current state of the ATM screen to render to the user
  ATMScreenState getState();

 private:
  /// Internal "callback" to request a state transition
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

  /// The current account being managed.  nullptr if disconnected
  std::shared_ptr<Account> current_account_;

  /// Interface to the machine / server control
  std::shared_ptr<Machine> machine_;

  /// The current state of the ATM Screen
  ATMScreenState state_;

  /// The callback queue of requested state transitions
  std::deque<ATMScreenState> state_transition_cb_queue_;
};

#endif  // ATM_ATM_H
