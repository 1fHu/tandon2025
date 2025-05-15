/*
  rec03.cpp
  Simon Hu
  This file manipulate bank accounts with transactions.
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct AccountInfo {
     string acountName;
     int accountNum;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class AccountInfoClass {
     string accountName;
     int accountNum;

     friend ostream& operator<<(ostream& os, const AccountInfoClass& rhs);


public:
     AccountInfoClass (const string& actName, const int& actNum){
          accountName = actName;
          accountNum = actNum;
     }
     void showing() {
          cout << accountName << ", " << accountNum << endl;
     }
     
     const string& getName() const {
          return accountName;
     }
     int getNum() const {
          return accountNum;
     }

     // AccountInfoClass(const string& name, int num) 
     //      : accountName(name), accountNum(num) {}
     
};

ostream& operator<<(ostream& os, const AccountInfoClass& rhs){
     // os << "Account: " << rhs.getName() << ", Number: " << rhs.getNum() << endl;
     os <<"Account: " << rhs.accountName << ", Number: " << rhs.accountNum <<endl;
     return os;
}
// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".
class Transaction{
     string command;
     int amount;
public:
     // constructor
     Transaction(string cmd, int amt) : command(cmd), amount(amt){}
     
     friend ostream& operator<<(ostream& os, const Transaction& rhs);
};

ostream& operator<<(ostream& os, const Transaction& rhs){
     os << "   " << rhs.command << " " << rhs.amount << endl;
     return os;
}

class AccountNew{
     string accountName;
     int accountNumber;
     int accountBalance = 0;
     vector<Transaction> transHistory;

public:
     // constructor
     AccountNew(const string& aName, const int& aNum) 
     : accountName(aName), accountNumber(aNum){}
     
     void deposit(int amount){
          accountBalance += amount;
          transHistory.emplace_back("deposit", amount);
     }
     void withdraw(int amount){
          //check
          if (amount > accountBalance){
               cout << "Account# " << accountNumber <<
               " has only " << accountBalance << ". Insufficient for withdrawal of "
               << amount << "." << endl;
          }
          else {
               accountBalance -= amount;
               transHistory.emplace_back("withdraw", amount);
          }
     }   

     const string& getName() const {
          return accountName;
     }
     const int& getNum() const {
          return accountNumber;
     }
     friend ostream& operator<<(ostream& os, const AccountNew& rhs);
};

ostream& operator<<(ostream& os, const AccountNew& rhs){
     os << rhs.getName() << ' ' << rhs.getNum() << ':' << endl;
     for (size_t i = 0; i < rhs.transHistory.size(); ++i){
          cout << rhs.transHistory[i];
     }
     return os;
}




// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.

class AccountCombine{
     string accountName;
     int accountNumber;
     int accountBalance = 0;
     vector<Transaction> transHistory;

public:
     // constructor
     AccountCombine(const string& aName, const int& aNum) 
     : accountName(aName), accountNumber(aNum){}

     class Transaction{
          friend ostream& operator<<(ostream& os, const Transaction& rhs);

     public:
          // constructor
          Transaction(const string& cmd, int amt) : command(cmd), amount(amt){}
     private:
          string command;
          int amount;     
          
     };
     friend ostream& operator<<(ostream& os, const Transaction& rhs);

     void deposit(int amount){
          accountBalance += amount;
          transHistory.emplace_back("deposit", amount);
     }
     void withdraw(int amount){
          //check
          if (amount > accountBalance){
               cout << "Account# " << accountNumber <<
               " has only " << accountBalance << ". Insufficient for withdrawal of "
               << amount << "." << endl;
          }
          else {
               accountBalance -= amount;
               transHistory.emplace_back("withdraw", amount);
          }
     }   

     const string& getName() const {
          return accountName;
     }
     const int& getNum() const {
          return accountNumber;
     }
     friend ostream& operator<<(ostream& os, const AccountCombine& rhs);
};

ostream& operator<<(ostream& os, const AccountCombine::Transaction& rhs){
     os << "   " << rhs.command << " " << rhs.amount << endl;
     return os;
}

ostream& operator<<(ostream& os, const AccountCombine& rhs){
     os << rhs.getName() << ' ' << rhs.getNum() << ':' << endl;
     for (size_t i = 0; i < rhs.transHistory.size(); ++i){
          cout << rhs.transHistory[i];
     }
     return os;
}

// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.


int main()
{

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";
     vector<AccountInfo> allAccountInfo;
     ifstream accountFile("accounts.txt");
     if (!accountFile){
          cout << "failed to open accounts.txt" << endl;
          exit(1);
     }

     string oneName;
     int oneActNum;
     while (accountFile >> oneName >> oneActNum ){
          AccountInfo oneNewAccount;
          oneNewAccount.acountName = oneName;
          oneNewAccount.accountNum = oneActNum;
          allAccountInfo.push_back(oneNewAccount);
     }
     accountFile.close();
     for (size_t i = 0; i < allAccountInfo.size(); ++i){
          cout << "Account name: " << allAccountInfo[i].acountName
          <<", Account Number: " << allAccountInfo[i].accountNum << endl;
     }


    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";
     allAccountInfo.clear();
     ifstream accountFileNew("accounts.txt");
     if (!accountFileNew){
          cout << "failed to open accounts.txt" << endl;
          exit(1);
     }
     string oneNameNew;
     int oneActNumNew;
     while (accountFileNew >> oneNameNew >> oneActNumNew ){
          AccountInfo oneNewAccount{oneNameNew, oneActNumNew};
          allAccountInfo.push_back(oneNewAccount);
     }
     accountFileNew.close();
     for (size_t i = 0; i < allAccountInfo.size(); ++i){
          cout << "Account name: " << allAccountInfo[i].acountName
          <<", Account Number: " << allAccountInfo[i].accountNum << endl;
     }

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";
     ifstream accountFile2("accounts.txt");
     if (!accountFile2){
          cout << "failed to open accounts.txt" << endl;
          exit(1);
     }
     string oneName2;
     int oneActNum2;
     vector<AccountInfoClass> allAccountInfo2;
     while (accountFile2 >> oneName2 >> oneActNum2 ){
          AccountInfoClass oneNewAccount{oneName2, oneActNum2};
          allAccountInfo2.push_back(oneNewAccount);
     }
     accountFile2.close();
     for (size_t i = 0; i < allAccountInfo2.size(); ++i){
          allAccountInfo2[i].showing();
     }

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    for (size_t i = 0; i < allAccountInfo2.size(); ++i){
          cout << allAccountInfo2[i];
     }

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
     for (size_t i = 0; i < allAccountInfo2.size(); ++i){
          cout << allAccountInfo2[i];
     }

    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
     vector<AccountInfoClass> allAccount3;
     string oneName3;
     int oneNum3;
     ifstream accountFile3("accounts.txt");
     if (!accountFile3){
          cout << "failed to open accounts.txt" << endl;
          exit(1);
     }
     while (accountFile3 >> oneName3 >> oneNum3){
          
          allAccount3.push_back(AccountInfoClass(oneName3, oneNum3));
     }
     accountFile3.close();
     for (size_t i = 0; i < allAccount3.size(); ++i){
          cout << allAccount3[i];
     }

    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
     vector<AccountInfoClass> allAccount4;
     string oneName4;
     int oneNum4;
     ifstream accountFile4("accounts.txt");
     if (!accountFile4){
          cout << "failed to open accounts.txt" << endl;
          exit(1);
     }
     while (accountFile4 >> oneName4 >> oneNum4){
          
          allAccount4.emplace_back(oneName4, oneNum4);
     }
     accountFile4.close();
     for (size_t i = 0; i < allAccount4.size(); ++i){
          cout << allAccount4[i];
     }
    
    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";
     vector<AccountNew> allAccount5;
     string oneName5;
     string oneCmd;
     int actNum5;
     int transAmount;
     ifstream accountFile5("transactions.txt");
     if (!accountFile5){
          cout << "failed to open transactions.txt" << endl;
          exit(1);
     }
     while (accountFile5 >> oneCmd){
          if (oneCmd == "Account"){
               accountFile5 >> oneName5;
               accountFile5 >> actNum5;
               allAccount5.emplace_back(oneName5, actNum5);
          }
          else if (oneCmd == "Deposit")
          {
               accountFile5 >> actNum5 >> transAmount;
               for (size_t i = 0; i < allAccount5.size(); ++i){
                    if (allAccount5[i].getNum() == actNum5){
                         allAccount5[i].deposit(transAmount);
                    }
               }
          }
          else if (oneCmd == "Withdraw")
          {
               accountFile5 >> actNum5 >> transAmount;
               for (size_t i = 0; i < allAccount5.size(); ++i){
                    if (allAccount5[i].getNum() == actNum5){
                         allAccount5[i].withdraw(transAmount);
                    }
               }
          }

     }

     for (size_t i = 0; i < allAccount5.size(); ++i){
          cout << allAccount5[i] << endl;
     }


    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";
     vector<AccountCombine> allAccount6;
     string oneName6;
     string oneCmd1;
     int actNum6;
     int transAmount1;
     ifstream accountFile6("transactions.txt");
     if (!accountFile6){
          cout << "failed to open transactions.txt" << endl;
          exit(1);
     }
     while (accountFile6 >> oneCmd1){
          if (oneCmd1 == "Account"){
               accountFile6 >> oneName6;
               accountFile6 >> actNum6;
               allAccount6.emplace_back(oneName6, actNum6);
          }
          else if (oneCmd1 == "Deposit")
          {
               accountFile6 >> actNum6 >> transAmount1;
               for (size_t i = 0; i < allAccount6.size(); ++i){
                    if (allAccount6[i].getNum() == actNum6){
                         allAccount6[i].deposit(transAmount1);
                    }
               }
          }
          else if (oneCmd1 == "Withdraw")
          {
               accountFile6 >> actNum6 >> transAmount1;
               for (size_t i = 0; i < allAccount6.size(); ++i){
                    if (allAccount6[i].getNum() == actNum6){
                         allAccount6[i].withdraw(transAmount1);
                    }
               }
          }

     }

     for (size_t i = 0; i < allAccount6.size(); ++i){
          cout << allAccount6[i] << endl;
     }
    
    
    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";

    
} // main
