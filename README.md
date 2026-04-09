# JobScheduler

An asynchronous task queuing and background execution system written in **C++20**. This project demonstrates the practical application of multithreading mechanisms, Object-Oriented Programming paradigms, and design patterns.

## Academic Context
This project was developed as part of the university coursework.

* **Course Name:** Advanced C++ (Zaawansowane C++)
* **Term:** Academic year 2025/2026, half-semester: 3
* **Instructors:** dr inż. Paweł Wnuk, prof. uczelni, dr hab. inż. Michał Syfert, prof. uczelni

## Project Description
The main objective of this project is to manage tasks in a multithreaded environment while minimizing the overhead associated with creating new processes. The system accepts polymorphic tasks, queues them based on their priority (HIGH, NORMAL, LOW), and distributes them among an available, fixed pool of worker threads.
The business logic layer is completely decoupled from the presentation layer using the observer design pattern, ensuring high scalability and a clean architecture.

## Key Features
* **Thread Pool Management:** Utilizes `std::jthread` for safe and automatic thread lifecycle management.
* **Priority Queuing (Monitor Pattern):** A thread-safe queue wrapper around `std::priority_queue`, protected by `std::mutex` and `std::condition_variable`.
* **Polimorfizm and Interfaces:** A common `ITask` interface allowing the execution of tasks with different characteristics (e.g., CPU-bound `ComputeTask`, I/O-bound `FileIoTask`) without tight type coupling.
* **Observer Pattern:** Asynchronous UI notifications (`CliDashboard`) regarding task status changes (PENDING, RUNNING, COMPLETED, FAILED).
* **Facade Pattern:** The main API is encapsulated within the `JobScheduler` class.
* **Graceful Shutdown:** A safe termination mechanism that guarantees the completion of ongoing tasks and wakes up idle threads before shutting down.

## 🛠️ System Requirements & Technologies
* **Language:** Modern C++ (Standard C++20)
* **Compiler:** MSVC
* **IDE:** Visual Studio 2022
* **Memory Management:** Smart pointers (`std::unique_ptr`, `std::shared_ptr`)

## Build and Run Instructions
To compile and run the JobScheduler system locally, follow these steps:
**Open the Project:** Launch Visual Studio 2022 and open the provided solution file (`.sln`) or the project folder.
**Build the Solution:** Press `Ctrl + Shift + B` to compile the project.
**Run the Application:** Press `Ctrl + F5` to launch the console application and view the real-time dashboard.
