/**
 * ATM Controller Simulator
 * Luc Bettaieb, 2021
 */

// Google Testing
#include <gtest/gtest.h>

// ATM Controller
#include "atm.h"

const uint64_t kTestAccountNum = 1234123412341234;
const uint16_t kTestAccountPin = 1234;
const int kTestAccountCheckingBalance = 1000;
const int kTestAccountSavingsBalance = 10000;

const int kTestAccountSavingsWithdrawLimit = 1000;
const int kTestAccountCheckingWithdrawLimit = 5000;

TEST(MachineTest, machineInit)
{
  Machine m{};
  EXPECT_TRUE(m.getPin(kTestAccountNum) == kTestAccountPin);

  EXPECT_TRUE(m.getAccountBalances(kTestAccountNum).get(AccountType::CHECKING) == kTestAccountCheckingBalance);
  EXPECT_TRUE(m.getAccountBalances(kTestAccountNum).get(AccountType::SAVINGS) == kTestAccountSavingsBalance);
  EXPECT_TRUE(m.getAccountBalances(kTestAccountNum).limit(AccountType::CHECKING) == kTestAccountCheckingWithdrawLimit);
  EXPECT_TRUE(m.getAccountBalances(kTestAccountNum).limit(AccountType::SAVINGS) == kTestAccountSavingsWithdrawLimit);

  EXPECT_TRUE(m.getAvailableCash() == kAvailableCashLogged);
}

TEST(MachineTest, machineUpdate)
{
  Machine m{};

  m.getAccountBalances(kTestAccountNum).get(AccountType::CHECKING) += 100;
  EXPECT_TRUE(m.getAccountBalances(kTestAccountNum).get(AccountType::CHECKING) == kTestAccountCheckingBalance);
  EXPECT_FALSE(m.getAccountBalances(kTestAccountNum).get(AccountType::CHECKING) == kTestAccountCheckingBalance + 100);
}

TEST(MachineTest, machineDisburse)
{
  Machine m{};

  bool except = false;
  try {
    m.disburseCash(kAvailableCashLogged+1);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);

  EXPECT_TRUE(m.getAvailableCash() == kAvailableCashLogged);
  m.disburseCash(100);
  // Would call m.updateAccountBalance(account, -100);
  // But no server interaction exsits
  EXPECT_TRUE(m.getAvailableCash() == kAvailableCashLogged-100);
}

TEST(AccountTest, initLocked)
{
  const auto m = std::make_shared<Machine>();
  Account a(m, kTestAccountNum);

  bool except = false;
  try {
    a.selectType(AccountType::CHECKING);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);

  except = false;
  try {
    a.getBalance();
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);

  except = false;
  try {
    a.deposit(100);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);

  except = false;
  try {
    a.withdraw(100);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);
}

TEST(AccountTest, initUnlockedUnselected)
{
  const auto m = std::make_shared<Machine>();
  Account a(m, kTestAccountNum);

  a.unlock(kTestAccountPin);

  bool except = false;
  try {
    a.getBalance();
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);

  except = false;
  try {
    a.deposit(100);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);

  except = false;
  try {
    a.withdraw(100);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);
}

TEST(AccountTest, initUnlockedSelectedChecking)
{
  const auto m = std::make_shared<Machine>();
  Account a(m, kTestAccountNum);

  a.unlock(kTestAccountPin);

  bool except = false;
  try {
    a.selectType(AccountType::CHECKING);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);

  int balance = 0;

  except = false;
  try {
   balance = a.getBalance();
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);
  EXPECT_TRUE(balance == kTestAccountCheckingBalance);


  except = false;
  try {
    a.deposit(100);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);

  except = false;
  try {
   balance = a.getBalance();
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);
  EXPECT_TRUE(balance == kTestAccountCheckingBalance+100);

  except = false;
  try {
    a.withdraw(100);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);

    except = false;
  try {
   balance = a.getBalance();
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);
  EXPECT_TRUE(balance == kTestAccountCheckingBalance);

  except = false;
  try {
    a.withdraw(100);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);

  except = false;
  try {
   balance = a.getBalance();
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);
  EXPECT_TRUE(balance == kTestAccountCheckingBalance-100);

  except = false;
  try {
    a.withdraw(9999999);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);

  except = false;
  try {
    a.withdraw(kTestAccountCheckingWithdrawLimit+1);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);

  except = false;
  try {
    a.withdraw(2000);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);
}

TEST(AccountTest, initUnlockedSelectedSavings)
{
  const auto m = std::make_shared<Machine>();
  Account a(m, kTestAccountNum);

  a.unlock(kTestAccountPin);

  bool except = false;
  try {
    a.selectType(AccountType::SAVINGS);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);

  int balance = 0;

  except = false;
  try {
   balance = a.getBalance();
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);
  EXPECT_TRUE(balance == kTestAccountSavingsBalance);


  except = false;
  try {
    a.deposit(100);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);

  except = false;
  try {
   balance = a.getBalance();
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);
  EXPECT_TRUE(balance == kTestAccountSavingsBalance+100);

  except = false;
  try {
    a.withdraw(100);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);

    except = false;
  try {
   balance = a.getBalance();
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);
  EXPECT_TRUE(balance == kTestAccountSavingsBalance);

  except = false;
  try {
    a.withdraw(100);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);

  except = false;
  try {
   balance = a.getBalance();
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_FALSE(except);
  EXPECT_TRUE(balance == kTestAccountSavingsBalance-100);

  except = false;
  try {
    a.withdraw(9999999);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);

  except = false;
  try {
    a.withdraw(kTestAccountSavingsBalance+1);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);

  except = false;
  try {
    a.withdraw(20000);
  } catch(std::exception& e) {
    except = true;
  }
  EXPECT_TRUE(except);
}

TEST(ATMTest, correctFunctionality)
{
  ATM atm{};
  ManagementAction balance_action{ManagementAction::ManagementActionType::BALANCE};
  ManagementAction deposit_action{ManagementAction::ManagementActionType::DEPOSIT, 100};
  ManagementAction withdraw_action{ManagementAction::ManagementActionType::WITHDRAW, 150};
  ManagementAction done_action{ManagementAction::ManagementActionType::DONE};

  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);
  
  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);
  
  atm.enterPinCB(kTestAccountPin);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::SELECT_ACCOUNT);

  atm.accountSelectCB(AccountType::CHECKING);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ACCOUNT_MANAGEMENT);

  atm.accountManagementCB(balance_action);
  atm.service();

  atm.accountManagementCB(deposit_action);
  atm.service();

  atm.accountManagementCB(withdraw_action);
  atm.service();

  atm.accountManagementCB(done_action);
  atm.service();

  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);
}

TEST(ATMTest, incorrectFunctionality)
{
  ATM atm{};
  ManagementAction balance_action{ManagementAction::ManagementActionType::BALANCE};
  ManagementAction deposit_action{ManagementAction::ManagementActionType::DEPOSIT, 100};
  ManagementAction withdraw_action{ManagementAction::ManagementActionType::WITHDRAW, 150};
  ManagementAction done_action{ManagementAction::ManagementActionType::DONE};

  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);

  atm.accountSelectCB(AccountType::CHECKING);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);

  atm.accountManagementCB(balance_action);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);

  atm.accountManagementCB(deposit_action);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);

  atm.accountManagementCB(withdraw_action);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);

  atm.accountManagementCB(done_action);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);
}

TEST(ATMTest, incorrectFunctionality2)
{
  ATM atm{};
  ManagementAction balance_action{ManagementAction::ManagementActionType::BALANCE};
  ManagementAction deposit_action{ManagementAction::ManagementActionType::DEPOSIT, 100};
  ManagementAction withdraw_action{ManagementAction::ManagementActionType::WITHDRAW, 150};
  ManagementAction done_action{ManagementAction::ManagementActionType::DONE};

  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  // set up
  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);
  
  atm.enterPinCB(kTestAccountPin);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::SELECT_ACCOUNT);
  // end set up

  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  // set up
  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);
  
  atm.enterPinCB(kTestAccountPin);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::SELECT_ACCOUNT);
  // end set up

  atm.accountManagementCB(balance_action);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  // set up
  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);
  
  atm.enterPinCB(kTestAccountPin);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::SELECT_ACCOUNT);
  // end set up

  atm.accountManagementCB(deposit_action);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  // set up
  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);
  
  atm.enterPinCB(kTestAccountPin);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::SELECT_ACCOUNT);
  // end set up

  atm.accountManagementCB(withdraw_action);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  // set up
  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);
  
  atm.enterPinCB(kTestAccountPin);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::SELECT_ACCOUNT);
  // end set up

  atm.accountManagementCB(done_action);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

}

TEST(ATMTest, incorrectFunctionality3)
{
  ATM atm{};


  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  // set up
  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);
  
  atm.enterPinCB(kTestAccountPin);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::SELECT_ACCOUNT);

  atm.accountSelectCB(AccountType::CHECKING);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ACCOUNT_MANAGEMENT);
  // end set up

  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  // set up
  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);
  
  atm.enterPinCB(kTestAccountPin);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::SELECT_ACCOUNT);

  atm.accountSelectCB(AccountType::CHECKING);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ACCOUNT_MANAGEMENT);
  // end set up

  atm.enterPinCB(kTestAccountPin);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);

  // set up
  atm.cardReaderCB(kTestAccountNum);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ENTER_PIN);
  
  atm.enterPinCB(kTestAccountPin);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::SELECT_ACCOUNT);

  atm.accountSelectCB(AccountType::CHECKING);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::ACCOUNT_MANAGEMENT);
  // end set up

  atm.accountSelectCB(AccountType::CHECKING);
  atm.service();
  ASSERT_TRUE(atm.getState() == ATMScreenState::IDLE);
}
