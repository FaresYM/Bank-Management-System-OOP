# 🏦 Bank Management System (Console Application)

A well-structured, modular backend system built from scratch using **C++** and core **Object-Oriented Programming (OOP)** principles. This project simulates real-world banking operations through a secure and interactive console interface, focusing on clean code architecture and data integrity.


## 🔑 Core Features
- **Secured Authentication & Brute-Force Protection:** Multi-user login system with strict input validation and an automated **system lockout mechanism after 3 failed login attempts** to prevent unauthorized access.
- **Role-Based Access Control (Permissions):** Separating system privileges between standard **Users** and system **Admins** to ensure data security.
- **Transactions Management:** Supports seamless financial operations including Instant Deposits, Withdrawals, and Secure Account-to-Account Transfers.
- **Client Management (CRUD):** Fully engineered system to Add, Find, Update, and Delete client accounts efficiently.
- **Real-time Activity Logs:** An automated audit trail tracking and logging every transaction made inside the system.
- **Basic Data Encryption & Persistence:** Implemented a character-shifting cipher (ASCII manipulation) to obfuscate user passwords before storing them in flat-file databases (`Users.txt` & `Clients.txt`).


## 🛠️ Software Engineering & OOP Concepts Applied
Through this project, I deeply focused on applying standard software engineering practices:
- **Data Encapsulation:** Strongly protecting sensitive data such as balances and client credentials.
- **Inheritance & Polymorphism:** Creating clean, reusable, and extensible class structures.
- **Modular Architecture:** The system is meticulously organized into **37 distinct header and source files** along with custom-linked libraries to ensure maximum scalability and maintainability.

## 📁 Project Architecture
The repository is split into a structured layout to separate interface logic from data handling:
- `/Header Files` (`.h` files for class structures and definitions).
- `/Source Files` (`.cpp` files implementing the encapsulated logic).
- `main.cpp` (The central entry point of the system).

## 🚀 How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com
   ```
2. Open the project folder in **Visual Studio** or any standard C++ IDE.
3. Build and Run `main.cpp`.

---
*Developed as part of fundamentals track guided by Eng. Mohammed Abu-Hadhoud.*
