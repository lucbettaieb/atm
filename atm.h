/**
 * ATM Controller Simulator
 * Luc Bettaieb, 2021
 */

#ifndef ATM_ATM_H
#define ATM_ATM_H

// ATM Controller
#include "account.h"
#include "machine.h"

// C++ Standard Library
#include <deque>
#include <exception>
#include <memory>
#include <thread>
#include <unordered_map>

enum ATMScreenState { IDLE = 0, ENTER_PIN = 1, SELECT_ACCOUNT = 2, ACCOUNT_MANAGEMENT = 3 };

static std::unordered_map<ATMScreenState, std::string> kATMScreenStateToString{
  {ATMScreenState::IDLE, "IDLE"},
  {ATMScreenState::ENTER_PIN, "ENTER_PIN"},
  {ATMScreenState::SELECT_ACCOUNT, "SELECT_ACCOUNT"},
  {ATMScreenState::ACCOUNT_MANAGEMENT, "ACCOUNT_MANAGEMENT"}
};

class ATM {
 public:
  ATM() : current_account_(nullptr), machine_(std::make_shared<Machine>()), state_(ATMScreenState::IDLE) {
  }

  void service() {
    // Check for requested state transitions
    while (!state_transition_cb_queue_.empty()) {
      ATMScreenState desired_state = state_transition_cb_queue_.back();
      state_transition_cb_queue_.pop_back();

      if (validTransition(desired_state)) {
        doStateTransition(desired_state);
      } else {
        throw std::runtime_error("Invalid transiton!");
        doStateTransition(ATMScreenState::IDLE);
      }
    }
  }

  void accountManagementCB(const ManagementAction& action) {
    if (state_ != ATMScreenState::ACCOUNT_MANAGEMENT) {
      return;
    }

    try {
      switch (action.action) {
        case ManagementAction::ManagementActionType::WITHDRAW:
          current_account_->withdraw(action.amount);
          break;
        case ManagementAction::ManagementActionType::DEPOSIT:
          current_account_->deposit(action.amount);
          break;
        case ManagementAction::ManagementActionType::BALANCE:
          // Here would be some kind of hook to put it on the display
          std::cout << "BALANCE: [$" << current_account_->getBalance() << "]" << std::endl;
          break;
        case ManagementAction::ManagementActionType::DONE:
          transitionCB(ATMScreenState::IDLE);
          break;
      }
    } catch (const std::exception& e) {
      // go back to idle
      std::cout << e.what() << std::endl;
      transitionCB(ATMScreenState::IDLE);
    }
  }

  void accountSelectCB(const AccountType accountType) {
    if (state_ != ATMScreenState::SELECT_ACCOUNT) {
      return;
    }
    try {
      current_account_->selectType(accountType);
      transitionCB(ATMScreenState::ACCOUNT_MANAGEMENT);
    } catch (const std::exception& e) {
      // go back to idle
      std::cout << e.what() << std::endl;
      transitionCB(ATMScreenState::IDLE);
    }
  }

  void enterPinCB(const uint8_t pin) {
    if (state_ != ATMScreenState::ENTER_PIN) {
      return;
    }
    try {
      current_account_->unlock(pin);
      transitionCB(ATMScreenState::SELECT_ACCOUNT);
    } catch (const std::exception& e) {
      // go back to idle
      std::cout << e.what() << std::endl;
      transitionCB(ATMScreenState::IDLE);
    }
  }

  void cardReaderCB(const uint16_t accountNumber) {
    if (state_ != ATMScreenState::IDLE) {
      return;
    }
    current_account_ = std::make_shared<Account>(machine_, accountNumber);
    transitionCB(ATMScreenState::ENTER_PIN);
  }

  void transitionCB(const ATMScreenState& desiredState) {
    state_transition_cb_queue_.push_front(desiredState);
  }

  void printState() {
    std::cout << "Current State: " << kATMScreenStateToString.at(state_) << std::endl;
  }

 private:
  /**
   * @brief Performs the state transition and makes required changes along the way
   * 
   * @param desiredState  The state we are transitioning to
   */
  void doStateTransition(const ATMScreenState& desiredState) {
    if (desiredState == ATMScreenState::IDLE) {
      // Disconnect current account
      current_account_ = nullptr;
    } else if (state_ == ATMScreenState::IDLE and desiredState == ATMScreenState::ENTER_PIN) {
      // check if account number has been selected
    } else if (state_ == ATMScreenState::ENTER_PIN and desiredState == ATMScreenState::SELECT_ACCOUNT) {
      // Make sure the current account is unlocked
    } else if (state_ == ATMScreenState::SELECT_ACCOUNT and desiredState == ATMScreenState::ACCOUNT_MANAGEMENT) {
      // Make sure the current account has an account selected
    }
    state_ = desiredState;
  }
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
  bool validTransition(const ATMScreenState& desiredState) {
    std::cout << kATMScreenStateToString.at(state_) << " -> " << kATMScreenStateToString.at(desiredState) << std::endl;

    if (state_ == ATMScreenState::IDLE and desiredState != ATMScreenState::ENTER_PIN) {
      return false;
    } else if (state_ == ATMScreenState::ENTER_PIN and !(desiredState == ATMScreenState::SELECT_ACCOUNT or
               desiredState == ATMScreenState::IDLE)) {
      return false;
    } else if (state_ == ATMScreenState::SELECT_ACCOUNT and !(desiredState == ATMScreenState::ACCOUNT_MANAGEMENT or
               desiredState == ATMScreenState::IDLE)) {
      return false;
    } else if (state_ == ATMScreenState::ACCOUNT_MANAGEMENT and desiredState != ATMScreenState::IDLE) {
      return false;
    } else {
      return true;
    }
  }

  std::shared_ptr<Account> current_account_;

  std::shared_ptr<Machine> machine_;

  ATMScreenState state_;

  std::deque<ATMScreenState> state_transition_cb_queue_;
};

#endif  // ATM_ATM_H
