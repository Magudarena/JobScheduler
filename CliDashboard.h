#pragma once
#include "ITaskObserver.h"
#include <iostream>
#include <string>
#include <mutex>

class CliDashboard : public ITaskObserver {
private:
    // Mutex zabezpieczaj¹cy konsolê ¿eby kilka w¹tków nie pisa³o naraz
    std::mutex consoleMutex;

    // zamienia enum na tekst
    std::string statusToString(TaskStatus status) {
        switch (status) {
        case TaskStatus::PENDING: return "PENDING";
        case TaskStatus::RUNNING: return "RUNNING";
        case TaskStatus::COMPLETED: return "COMPLETED";
        case TaskStatus::FAILED: return "FAILED";
        default: return "UNKNOWN";
        }
    }

public:
    // Metoda wymuszona przez interfejs ITaskObserver
    void onTaskStateChanged(uint64_t id, TaskStatus status) override {
        std::lock_guard<std::mutex> lock(consoleMutex);

        std::cout << "[Dashboard Event] Zadanie #" << id
            << " zmienilo status na: " << statusToString(status) << "\n";
    }
};