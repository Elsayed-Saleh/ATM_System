# ATM System

A console-based ATM System developed using C++.

## 📌 Description

This project is a console-based ATM application that allows clients to log in using their account number and PIN code and perform basic banking operations.

The system provides quick withdrawal, normal withdrawal, deposit, balance checking, and logout functionality.

Client information and updated account balances are stored in a text file.

## ✨ Features

### 🔐 Login

- Login using Account Number and PIN Code.
- Validates the entered account information.
- Displays an error message when the login credentials are incorrect.

### 💰 Quick Withdraw

Provides predefined withdrawal amounts:

- 20
- 50
- 100
- 200
- 400
- 600
- 800
- 1000

The system checks whether the selected amount is available in the client's balance.

### 💵 Normal Withdraw

- Allows the user to enter a custom withdrawal amount.
- Withdrawal amount must be a multiple of 5.
- Prevents withdrawing more than the available balance.
- Asks for confirmation before completing the transaction.

### 💳 Deposit

- Allows the user to enter a deposit amount.
- Updates the current account balance.
- Asks for confirmation before completing the transaction.

### 📊 Check Balance

Displays the current account balance.

### 🚪 Logout

Logs the current client out and returns to the login screen.

## 🗂️ ATM Main Menu

The application provides the following options:

```text
[1] Quick Withdraw
[2] Normal Withdraw
[3] Deposit
[4] Check Balance
[5] Logout
