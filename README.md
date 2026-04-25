# Console Banking System

A robust, console-based C++ application designed to manage banking operations, customer accounts, and transaction histories. This project was developed as part of the **CodeAlpha Internship**.

## Features
- **Customer Registration & Identity Verification:** Secure system to register new customers and verify identity for existing accounts.
- **Automated ID Generation:** Intelligent ID assignment for Customers, Accounts, and Transactions to ensure uniqueness.
- **Account Management:** Support for three distinct account types: **Savings**, **Current**, and **Fixed Deposit**.
- **Comprehensive Transaction Suite:** Includes deposits, withdrawals, internal transfers (between user's own accounts), and external transfers (between different customers).
- **Transaction History:** Every financial action is logged with a timestamp and unique Transaction ID for audit trails.
- **Data Persistence:** Automatically saves/loads the system state using local file storage (`bank_data.txt`), ensuring data is not lost after closing the program.

## Programming Concepts Used
This project leverages key Object-Oriented Programming (OOP) and system programming principles:

### 1. Object-Oriented Programming (OOP)
* **Classes and Encapsulation:** The system uses distinct classes (`Customer`, `Account`, `Transaction`, `Manager`) to model real-world entities. Data members are kept `private` to ensure security, accessed only through `public` getter/setter methods.
* **Composition:** A `Customer` "has-a" list of `Account` objects, and an `Account` "has-a" list of `Transaction` objects. This hierarchy allows for efficient data management.
* **Static Members:** Used to implement auto-incrementing IDs (`cID`, `dCount`, `sCount`, etc.). This ensures that every new entity created is assigned a unique, sequential identifier without manual tracking.

### 2. Data Structures
* **Dynamic Arrays (`std::vector`):** The program utilizes `vector` to store customers, accounts, and transactions. This allows the application to handle an arbitrary number of entries dynamically, growing memory as needed during runtime.

### 3. File Handling (`fstream`)
* **Serialization:** Custom logic is implemented to save the state of all objects to `bank_data.txt` and rebuild them upon startup (`loadFromFile`). This simulates a database layer in a text-based environment.

### 4. Robust Input Validation
* **Exception Handling Logic:** Dedicated utility functions (`readInt`, `readFloat`, `readChar`) sanitize user inputs. This prevents the program from crashing if a user enters a string when a number is expected, maintaining system stability.

## How to Run
1. Ensure you have a C++ compiler installed (like MinGW).
2. Clone or download the repository:
   ```bash
   git clone [Your-Repository-URL]
