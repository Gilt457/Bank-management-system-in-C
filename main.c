#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100
#define ACCOUNT_FILE "accounts.dat"
#define USER_FILE "users.dat"

// Structure to store account information
typedef struct {
    int accountNumber;
    char name[100];
    float balance;
    char transactions[MAX_TRANSACTIONS][100];
    int transactionCount;
} Account;

// Structure to store user authentication information
typedef struct {
    char username[50];
    char password[50];
} User;

// Global variables
Account accounts[MAX_ACCOUNTS];
User currentUser;
int accountCount = 0;

// Function prototypes
void createAccount();
void viewAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void deleteAccount();
void viewTransactionHistory();
void menu();
int findAccountIndex(int accNumber);
void clearInputBuffer();
void saveAccounts();
void loadAccounts();
void saveUsers();
void loadUsers();
void login();
bool authenticate(const char *username, const char *password);
void registerUser();
void displayHeader();

// Entry point
int main() {
    loadAccounts();
    loadUsers();
    login();
    menu();
    return 0;
}

// Function to create a new account
void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Account limit reached. Cannot create more accounts.\n");
        return;
    }
    
    Account newAccount;
    newAccount.accountNumber = accountCount + 1;
    newAccount.transactionCount = 0;
    
    printf("Enter the account holder's name: ");
    clearInputBuffer();
    fgets(newAccount.name, 100, stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = '\0';  // Remove newline
    
    newAccount.balance = 0.0;  // Initial balance is 0
    
    accounts[accountCount] = newAccount;
    accountCount++;
    
    printf("Account created successfully! Account Number: %d\n", newAccount.accountNumber);
    saveAccounts();
}

// Function to view account information
void viewAccount() {
    int accNumber;
    printf("Enter account number: ");
    scanf("%d", &accNumber);
    
    int index = findAccountIndex(accNumber);
    if (index != -1) {
        printf("Account Number: %d\n", accounts[index].accountNumber);
        printf("Account Holder: %s\n", accounts[index].name);
        printf("Account Balance: $%.2f\n", accounts[index].balance);
    } else {
        printf("Account not found.\n");
    }
}

// Function to deposit money
void depositMoney() {
    int accNumber;
    float amount;
    
    printf("Enter account number: ");
    scanf("%d", &accNumber);
    
    int index = findAccountIndex(accNumber);
    if (index != -1) {
        printf("Enter amount to deposit: $");
        scanf("%f", &amount);
        
        if (amount > 0) {
            accounts[index].balance += amount;
            printf("Deposit successful! New Balance: $%.2f\n", accounts[index].balance);
            
            // Record transaction
            snprintf(accounts[index].transactions[accounts[index].transactionCount++], 100, "Deposited $%.2f", amount);
            saveAccounts();
        } else {
            printf("Invalid deposit amount.\n");
        }
    } else {
        printf("Account not found.\n");
    }
}

// Function to withdraw money
void withdrawMoney() {
    int accNumber;
    float amount;
    
    printf("Enter account number: ");
    scanf("%d", &accNumber);
    
    int index = findAccountIndex(accNumber);
    if (index != -1) {
        printf("Enter amount to withdraw: $");
        scanf("%f", &amount);
        
        if (amount > 0 && accounts[index].balance >= amount) {
            accounts[index].balance -= amount;
            printf("Withdrawal successful! New Balance: $%.2f\n", accounts[index].balance);
            
            // Record transaction
            snprintf(accounts[index].transactions[accounts[index].transactionCount++], 100, "Withdrew $%.2f", amount);
            saveAccounts();
        } else {
            printf("Invalid withdrawal amount or insufficient balance.\n");
        }
    } else {
        printf("Account not found.\n");
    }
}

// Function to check the balance of an account
void checkBalance() {
    int accNumber;
    
    printf("Enter account number: ");
    scanf("%d", &accNumber);
    
    int index = findAccountIndex(accNumber);
    if (index != -1) {
        printf("Account Balance: $%.2f\n", accounts[index].balance);
    } else {
        printf("Account not found.\n");
    }
}

// Function to delete an account
void deleteAccount() {
    int accNumber;
    printf("Enter account number to delete: ");
    scanf("%d", &accNumber);
    
    int index = findAccountIndex(accNumber);
    if (index != -1) {
        for (int i = index; i < accountCount - 1; i++) {
            accounts[i] = accounts[i + 1];
        }
        accountCount--;
        saveAccounts();
        printf("Account deleted successfully.\n");
    } else {
        printf("Account not found.\n");
    }
}

// Function to view transaction history
void viewTransactionHistory() {
    int accNumber;
    printf("Enter account number: ");
    scanf("%d", &accNumber);
    
    int index = findAccountIndex(accNumber);
    if (index != -1) {
        printf("Transaction History for Account %d:\n", accNumber);
        for (int i = 0; i < accounts[index].transactionCount; i++) {
            printf("%d. %s\n", i + 1, accounts[index].transactions[i]);
        }
        if (accounts[index].transactionCount == 0) {
            printf("No transactions available.\n");
        }
    } else {
        printf("Account not found.\n");
    }
}

// Menu function to interact with the user
void menu() {
    int choice;
    
    while (1) {
        displayHeader();
        printf("1. Create Account\n");
        printf("2. View Account\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Check Balance\n");
        printf("6. Delete Account\n");
        printf("7. View Transaction History\n");
        printf("8. Exit\n");
        printf("=====================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                depositMoney();
                break;
            case 4:
                withdrawMoney();
                break;
            case 5:
                checkBalance();
                break;
            case 6:
                deleteAccount();
                break;
            case 7:
                viewTransactionHistory();
                break;
            case 8:
                printf("Thank you for using the Bank Management System. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to find the index of an account based on the account number
int findAccountIndex(int accNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNumber) {
            return i;
        }
    }
    return -1;  // Account not found
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Function to save account data to a file
void saveAccounts() {
    FILE *file = fopen(ACCOUNT_FILE, "wb");
    if (file != NULL) {
        fwrite(&accountCount, sizeof(int), 1, file);
        fwrite(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    } else {
        printf("Error saving account data.\n");
    }
}

// Function to load account data from a file
void loadAccounts() {
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file != NULL) {
        fread(&accountCount, sizeof(int), 1, file);
        fread(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    } else {
        printf("No previous account data found.\n");
    }
}

// Function to save user data to a file
void saveUsers() {
    FILE *file = fopen(USER_FILE, "wb");
    if (file != NULL) {
        fwrite(&currentUser, sizeof(User), 1, file);
        fclose(file);
    } else {
        printf("Error saving user data.\n");
    }
}

// Function to load user data from a file
void loadUsers() {
    FILE *file = fopen(USER_FILE, "rb");
    if (file != NULL) {
        fread(&currentUser, sizeof(User), 1, file);
        fclose(file);
       } else {
        printf("No previous user data found. Please register.\n");
        registerUser();
    }
}

// Function to handle user login
void login() {
    char username[50];
    char password[50];

    printf("===== Login =====\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
        printf("Do you want to register? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            registerUser();
        } else {
            printf("Exiting the system.\n");
            exit(0);
        }
    }
}

// Function to authenticate the user
bool authenticate(const char *username, const char *password) {
    return (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0);
}

// Function to handle user registration
void registerUser() {
    printf("===== Register =====\n");
    printf("Enter new username: ");
    scanf("%s", currentUser.username);
    printf("Enter new password: ");
    scanf("%s", currentUser.password);
    
    saveUsers();
    printf("Registration successful! You can now log in.\n");
    login();
}

// Function to display the header
void displayHeader() {
    printf("=====================\n");
    printf(" Bank Management System\n");
    printf("=====================\n");
}


    
