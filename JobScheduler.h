#pragma once
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include "ITask.h"
#include "ITaskObserver.h"
#include "ThreadSafePriorityQueue.h"
#include "Worker.h"

class JobScheduler {
private:
    ThreadSafePriorityQueue taskQueue;
    std::vector<std::jthread> workers;
    std::atomic<bool> stopFlag{ false };

    // Lista obserwatorów
    std::vector<std::shared_ptr<ITaskObserver>> observers;

    // Prywatna metoda do rozsy³ania powiadomieñ
    void notifyObservers(uint64_t id, TaskStatus status) {
        for (auto& obs : observers) {
            if (obs) obs->onTaskStateChanged(id, status);
        }
    }

public:
    JobScheduler(size_t threadCount) {
        // Inicjalizacja puli w¹tków C++20
        for (size_t i = 0; i < threadCount; ++i) {
            workers.emplace_back([this, i]() {
                Worker worker(i);

                // G³ówna pêtla w¹tku zintegrowana ze Schedulerem
                while (!stopFlag) {
                    auto task = taskQueue.pop(stopFlag); // Pobiera zadanie lub usypia

                    if (task) {
                        // 1. Zmiana statusu na RUNNING i powiadomienie
                        notifyObservers(task->getId(), TaskStatus::RUNNING);
                        task->setStatus(TaskStatus::RUNNING);

                        try {
                            // 2. POLIMORFIZM W AKCJI: Wywo³anie metody z klasy pochodnej
                            task->execute();

                            // 3. Sukces - powiadomienie
                            task->setStatus(TaskStatus::COMPLETED);
                            notifyObservers(task->getId(), TaskStatus::COMPLETED);
                        }
                        catch (...) {
                            // 4. B³¹d - przechwytywanie wyj¹tków z w¹tków
                            task->setStatus(TaskStatus::FAILED);
                            notifyObservers(task->getId(), TaskStatus::FAILED);
                        }
                    }
                }
                });
        }
    }

    // Bezpieczne zamkniêcie systemu
    ~JobScheduler() {
        shutdown();
    }

    // Rejestracja obserwatora np konsoli
    void addObserver(std::shared_ptr<ITaskObserver> observer) {
        observers.push_back(observer);
    }

    // Dodanie nowego zadania
    void submit(std::unique_ptr<ITask> task) {
        uint64_t id = task->getId();
        // Powiadamiamy o dodaniu do kolejki
        notifyObservers(id, TaskStatus::PENDING);
        taskQueue.push(std::move(task));
    }

    // Wymuszenie zatrzymania
    void shutdown() {
        if (!stopFlag) {
            stopFlag = true;
            taskQueue.wakeUpAll();
        }
    }
};