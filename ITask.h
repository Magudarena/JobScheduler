#pragma once
#include <cstdint>

// Enumy reprezentuj¹ce stany
enum class Priority { LOW, NORMAL, HIGH };
enum class TaskStatus { PENDING, RUNNING, COMPLETED, FAILED };

// G³ówny interfejs dla wszystkich zadañ - Polimorfizm
class ITask {
protected:
    uint64_t id;
    Priority priority;
    TaskStatus status;



public:
    ITask(uint64_t id, Priority prio)
        : id(id), priority(prio), status(TaskStatus::PENDING) {
    }

    // Wirtualny destruktor niezbêdny dla bezpieczeñstwa pamiêci klas pochodnych
    virtual ~ITask() = default;

    // Czysto wirtualna metoda jako punkt wejœcia dla ka¿dego konkretnego zadania
    virtual void execute() = 0;

    // Gettery i settery
    uint64_t getId() const { return id; }
    Priority getPriority() const { return priority; }
    TaskStatus getStatus() const { return status; }

    void setStatus(TaskStatus newStatus) { status = newStatus; }
};