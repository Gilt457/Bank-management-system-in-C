# Bank Management System

## Overview
This project is a simple Bank Management System implemented in C. It allows users to create accounts, view account details, deposit and withdraw money, check balances, delete accounts, and view transaction history. User authentication is also included to ensure secure access.

## Features
- **Account Management**: Create, view, and delete accounts.
- **Transactions**: Deposit and withdraw money, view transaction history.
- **Balance Inquiry**: Check account balance.
- **User Authentication**: Register and login functionality to secure access.

## Files
- `main.c`: Contains the main logic and functions for the Bank Management System.
- `accounts.dat`: Binary file to store account information.
- `users.dat`: Binary file to store user authentication information.

## Structures
### Account
```c
typedef struct {
    int accountNumber;
    char name[100];
    float balance;
    char transactions[MAX_TRANSACTIONS][100];
    int transactionCount;
} Account;
```

### User
```c
typedef struct {
    char username[50];
    char password[50];
} User;
```

## Functions
### Account Management
- `void createAccount()`: Creates a new account.
- `void viewAccount()`: Views account details.
- `void deleteAccount()`: Deletes an account.

### Transactions
- `void depositMoney()`: Deposits money into an account.
- `void withdrawMoney()`: Withdraws money from an account.
- `void viewTransactionHistory()`: Views the transaction history of an account.

### Balance Inquiry
- `void checkBalance()`: Checks the balance of an account.

### User Authentication
- `void login()`: Handles user login.
- `void registerUser()`: Handles user registration.
- `bool authenticate(const char *username, const char *password)`: Authenticates the user.

### Utility Functions
- `int findAccountIndex(int accNumber)`: Finds the index of an account based on the account number.
- `void clearInputBuffer()`: Clears the input buffer.
- `void saveAccounts()`: Saves account data to a file.
- `void loadAccounts()`: Loads account data from a file.
- `void saveUsers()`: Saves user data to a file.
- `void loadUsers()`: Loads user data from a file.
- `void displayHeader()`: Displays the header.
- `void menu()`: Displays the menu and handles user interaction.

## Usage
1. **Compile the code**:
   ```sh
   gcc main.c -o bank_management
   ```

2. **Run the executable**:
   ```sh
   ./bank_management
   ```

3. **Follow the on-screen instructions** to create accounts, deposit/withdraw money, and manage accounts.

## Notes
- Ensure `accounts.dat` and `users.dat` files are in the same directory as the executable.
- The system supports up to 100 accounts and 100 transactions per account.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.
