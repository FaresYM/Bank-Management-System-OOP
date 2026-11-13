# 🏦 Bank Management System (Console Application)

A well-structured, modular backend system built from scratch using **C++** and core **Object-Oriented Programming (OOP)** principles. This project simulates real-world banking operations through a secure and interactive console interface, focusing on clean code architecture and data integrity.


## 🔑 Core Features
- **Secured Authentication & Brute-Force Protection:** Multi-user login system with strict input validation and an automated **system lockout mechanism after 3 failed login attempts** to prevent unauthorized access.
- **Role-Based Access Control (Permissions):** Separating system privileges between standard **Users** and system **Admins** to ensure data security.
- **Transactions Management:** Supports seamless financial operations including Instant Deposits, Withdrawals, and Secure Account-to-Account Transfers.
- **Client Management (CRUD):** Fully engineered system to Add, Find, Update, and Delete client accounts efficiently.
- **Real-time Activity Logs:** An automated audit trail tracking and logging every transaction made inside the system.
- **Basic Data Encryption & Persistence:** Implemented a character-shifting cipher (ASCII manipulation) to obfuscate user passwords before storing them in flat-file databases (`Users.txt` & `Clients.txt`).
- **Currency Exchange System:** Integrated a complete currency module supporting real-time exchange rate updates, currency search (by country or code), and a built-in multi-currency converter calculator.



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
1. **Download the project:**
   - **Option A (Direct Download):** Click the green **`<> Code`** button above and select **`Download ZIP`**, then extract the files.
   - **Option B (Using Git):** Run the following command in your terminal:
     ```bash
     git clone https://github.com/FaresYM/Bank-Management-System-OOP.git
     ```
2. **Open the project:** Launch the extracted folder in **Visual Studio** or any standard C++ IDE.
3. **Run:** Build and execute `main.cpp` to start the application.

---
*Developed as part of fundamentals track guided by Eng. Mohammed Abu-Hadhoud.*
