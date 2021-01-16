/**
 * ATM Controller Simulator
 * Luc Bettaieb, 2021
 */

// ATM Controller
#include "machine.h"

Machine::Machine() : 
  account_pins_(initializeAccountPins()), 
  available_cash_(initializeAvailableCash())
{}

uint16_t Machine::getPin(uint64_t accountNumber) {
  if (account_pins_.find(accountNumber) == account_pins_.end()) {
    throw std::runtime_error("Account not found");
  }
  return account_pins_.at(accountNumber);
}

Balances Machine::getAccountBalances(uint64_t accountNumber) {
  // simulates request to server for account balance for number and type associated with number
  return kAccountBalances.at(accountNumber);
}

void Machine::updateAccountBalance(uint64_t accountNumber, int amount) {
  // Send to server information about debit or credit to an account
  return;
}

uint Machine::getAvailableCash() {
  return available_cash_;
}

void Machine::disburseCash(uint amount) {
  if (amount > available_cash_) {
    throw std::runtime_error("Cash can't be disbursed");
  }
  // Call to motor controller or something to deposit cash
  available_cash_ -= amount;

  // Update available cash amount in the server, too.
}

