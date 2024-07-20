#include <iostream>
#include <vector>
#include <string>

// Forward declarations
class Customer;
class Account;

// Transaction class
class Transaction {
public:
    enum class Type {
        DEPOSIT,
        WITHDRAWAL,
        TRANSFER
    };

    Transaction(Type type, double amount, Account* from = nullptr, Account* to = nullptr)
        : type(type), amount(amount), from(from), to(to) {}

    Type getType() const { return type; }
    double getAmount() const { return amount; }
    const Account* getFromAccount() const { return from; }
    const Account* getToAccount() const { return to; }

private:
    Type type;
    double amount;
    Account* from;
    Account* to;
};

// Customer class
class Customer {
public:
    Customer(int id, std::string name) : id(id), name(name) {}

    int getId() const { return id; }
    std::string getName() const { return name; }

private:
    int id;
    std::string name;
};

// Account class
class Account {
public:
    Account(int accountNumber, Customer* customer, double balance = 0)
        : accountNumber(accountNumber), customer(customer), balance(balance) {}

    int getAccountNumber() const { return accountNumber; }
    const Customer& getCustomer() const { return *customer; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction(Transaction::Type::DEPOSIT, amount, this));
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            transactions.push_back(Transaction(Transaction::Type::WITHDRAWAL, amount, this));
            return true;
        }
        return false;
    }

    bool transfer(double amount, Account& toAccount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            transactions.push_back(Transaction(Transaction::Type::TRANSFER, amount, this, &toAccount));
            return true;
        }
        return false;
    }

    void displayTransactions() const {
        std::cout << "Transactions for Account " << accountNumber << ":" << std::endl;
        for (const auto& transaction : transactions) {
            std::string typeStr;
            switch (transaction.getType()) {
                case Transaction::Type::DEPOSIT:
                    typeStr = "Deposit";
                    break;
                case Transaction::Type::WITHDRAWAL:
                    typeStr = "Withdrawal";
                    break;
                case Transaction::Type::TRANSFER:
                    typeStr = "Transfer";
                    break;
            }
            std::cout << "- " << typeStr << ": $" << transaction.getAmount();
            if (transaction.getType() == Transaction::Type::TRANSFER) {
                std::cout << " from Account " << transaction.getFromAccount()->getAccountNumber();
                std::cout << " to Account " << transaction.getToAccount()->getAccountNumber();
            }
            std::cout << std::endl;
        }
    }

private:
    int accountNumber;
    Customer* customer;
    double balance;
    std::vector<Transaction> transactions;
};

// Banking system class
class BankingSystem {
public:
    void createCustomer(int id, std::string name) {
        customers.push_back(Customer(id, name));
    }

    void createAccount(int accountNumber, int customerId, double initialDeposit = 0) {
        Customer* customer = findCustomerById(customerId);
        if (customer) {
            accounts.push_back(Account(accountNumber, customer, initialDeposit));
        }
    }

    void displayCustomerAccounts(int customerId) const {
        const Customer* customer = findCustomerById(customerId);
        if (customer) {
            std::cout << "Accounts for Customer " << customer->getName() << ":" << std::endl;
            for (const auto& account : accounts) {
                if (&account.getCustomer() == customer) {
                    std::cout << "- Account Number: " << account.getAccountNumber() << ", Balance: $" << account.getBalance() << std::endl;
                }
            }
        } else {
            std::cout << "Customer not found." << std::endl;
        }
    }

    void deposit(int accountNumber, double amount) {
        Account* account = findAccountByNumber(accountNumber);
        if (account) {
            account->deposit(amount);
            std::cout << "Deposit successful. New balance: $" << account->getBalance() << std::endl;
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

    void withdraw(int accountNumber, double amount) {
        Account* account = findAccountByNumber(accountNumber);
        if (account) {
            if (account->withdraw(amount)) {
                std::cout << "Withdrawal successful. New balance: $" << account->getBalance() << std::endl;
            } else {
                std::cout << "Insufficient funds." << std::endl;
            }
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

    void transfer(int fromAccountNumber, int toAccountNumber, double amount) {
        Account* fromAccount = findAccountByNumber(fromAccountNumber);
        Account* toAccount = findAccountByNumber(toAccountNumber);
        if (fromAccount && toAccount) {
            if (fromAccount->transfer(amount, *toAccount)) {
                std::cout << "Transfer successful." << std::endl;
            } else {
                std::cout << "Transfer failed. Ensure sufficient funds." << std::endl;
            }
        } else {
            std::cout << "One or both accounts not found." << std::endl;
        }
    }

    void displayAccountTransactions(int accountNumber) const {
        const Account* account = findAccountByNumber(accountNumber);
        if (account) {
            account->displayTransactions();
        } else {
            std::cout << "Account not found." << std::endl;
        }
    }

private:
    std::vector<Customer> customers;
    std::vector<Account> accounts;

    // Helper methods
    Customer* findCustomerById(int id) {
        for (auto& customer : customers) {
            if (customer.getId() == id) {
                return &customer;
            }
        }
        return nullptr;
    }

    Account* findAccountByNumber(int accountNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }
};

// Function to display menu and get user input
int displayMenuAndGetSelection() {
    int choice;
    std::cout << "\nBanking System Menu:\n";
    std::cout << "1. Create Customer\n";
    std::cout << "2. Create Account\n";
    std::cout << "3. Deposit\n";
    std::cout << "4. Withdraw\n";
    std::cout << "5. Transfer\n";
    std::cout << "6. Display Customer Accounts\n";
    std::cout << "7. Display Account Transactions\n";
    std::cout << "8. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}

int main() {
    BankingSystem bankingSystem;

    int choice;
    do {
        choice = displayMenuAndGetSelection();

        switch (choice) {
            case 1: {
                int id;
                std::string name;
                std::cout << "Enter customer ID: ";
                std::cin >> id;
                std::cout << "Enter customer name: ";
                std::cin.ignore(); // Ignore newline character left in buffer
                std::getline(std::cin, name);
                bankingSystem.createCustomer(id, name);
                std::cout << "Customer created successfully." << std::endl;
                break;
            }
            case 2: {
                int accountNumber, customerId;
                double initialDeposit;
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                std::cout << "Enter customer ID for the account: ";
                std::cin >> customerId;
                std::cout << "Enter initial deposit amount: ";
                std::cin >> initialDeposit;
                bankingSystem.createAccount(accountNumber, customerId, initialDeposit);
                std::cout << "Account created successfully." << std::endl;
                break;
            }
            case 3: {
                int accountNumber;
                double amount;
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                std::cout << "Enter deposit amount: ";
                std::cin >> amount;
                bankingSystem.deposit(accountNumber, amount);
                break;
            }
            case 4: {
                int accountNumber;
                double amount;
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                std::cout << "Enter withdrawal amount: ";
                std::cin >> amount;
                bankingSystem.withdraw(accountNumber, amount);
                break;
            }
            case 5: {
                int fromAccountNumber, toAccountNumber;
                double amount;
                std::cout << "Enter account number to transfer from: ";
                std::cin >> fromAccountNumber;
                std::cout << "Enter account number to transfer to: ";
                std::cin >> toAccountNumber;
                std::cout << "Enter transfer amount: ";
                std::cin >> amount;
                bankingSystem.transfer(fromAccountNumber, toAccountNumber, amount);
                break;
            }
            case 6: {
                int customerId;
                std::cout << "Enter customer ID: ";
                std::cin >> customerId;
                bankingSystem.displayCustomerAccounts(customerId);
                break;
            }
            case 7: {
                int accountNumber;
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                bankingSystem.displayAccountTransactions(accountNumber);
                break;
            }
            case 8:
                std::cout << "Exiting program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 8." << std::endl;
                break;
        }
    } while (choice != 8);

    return 0;
}
