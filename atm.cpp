/**
 * ATM Controller Simulator
 * Luc Bettaieb, 2021
 */

// C++ Standard Library
#include <deque>
#include <iostream>
#include <memory>

// ATM Controller
#include "atm.h"

ATM::ATM() : 
  current_account_(nullptr), 
  machine_(std::make_shared<Machine>()), 
  state_(ATMScreenState::IDLE) 
{}

void ATM::service() {
  // Check for requested state transitions
  while (!state_transition_cb_queue_.empty()) {
    ATMScreenState desired_state = state_transition_cb_queue_.back();
    state_transition_cb_queue_.pop_back();

    if (validTransition(desired_state)) {
      doStateTransition(desired_state);
    } 
    // else {
    //   throw std::runtime_error("Invalid transiton!");
    //   doStateTransition(ATMScreenState::IDLE);
    // }
  }
}

void ATM::accountManagementCB(const ManagementAction& action) {
  if (state_ != ATMScreenState::ACCOUNT_MANAGEMENT) {
    transitionCB(ATMScreenState::IDLE);
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

void ATM::accountSelectCB(const AccountType accountType) {
  if (state_ != ATMScreenState::SELECT_ACCOUNT) {
    transitionCB(ATMScreenState::IDLE);
    return;
  }

  try {
    if (current_account_){
      current_account_->selectType(accountType);
    }
    transitionCB(ATMScreenState::ACCOUNT_MANAGEMENT);
  } catch (const std::exception& e) {
    // go back to idle
    std::cout << e.what() << std::endl;
    transitionCB(ATMScreenState::IDLE);
  }
}

void ATM::enterPinCB(const uint16_t pin) {
  if (state_ != ATMScreenState::ENTER_PIN) {
    transitionCB(ATMScreenState::IDLE);
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

void ATM::cardReaderCB(const uint64_t accountNumber) {
  if (state_ != ATMScreenState::IDLE) {
    transitionCB(ATMScreenState::IDLE);
    return;
  }

  current_account_ = std::make_shared<Account>(machine_, accountNumber);
  transitionCB(ATMScreenState::ENTER_PIN);
}

void ATM::transitionCB(const ATMScreenState& desiredState) {
  state_transition_cb_queue_.push_front(desiredState);
}

ATMScreenState ATM::getState() {
  return state_;
}

void ATM::doStateTransition(const ATMScreenState& desiredState) {
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

bool ATM::validTransition(const ATMScreenState& desiredState) {
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
