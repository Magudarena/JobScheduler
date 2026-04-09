#pragma once
#include <cstdint>
#include "ITask.h" // dla dostêpu do enum TaskStatus

// Interfejs dla wzorca Obserwator
class ITaskObserver {
public:
    // Wirtualny destruktor
    virtual ~ITaskObserver() = default;


    // Metoda wywo³ywana asynchronicznie przez JobScheduler jak jest zmiana statusu
    virtual void onTaskStateChanged(uint64_t id, TaskStatus status) = 0;
};