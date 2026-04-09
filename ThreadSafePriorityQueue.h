#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include "ITask.h"

// Komparator mówi kolejce, jak ma sortowaæ polimorficzne zadania
struct TaskCompare {
    bool operator()(const std::unique_ptr<ITask>& a, const std::unique_ptr<ITask>& b) const {
        // priority_queue to domyœlnie max-heap, najwiêksze na górze, HIGH (2) ma byæ przed LOW (0), to ca³e ma daæ true, jak a jest s³absze ni¿ b
        return static_cast<int>(a->getPriority()) < static_cast<int>(b->getPriority());
    }

};


class ThreadSafePriorityQueue {
private:
    // Wewnêtrzna kolejka przechowuje unikalne wskaŸniki
    std::priority_queue<std::unique_ptr<ITask>, std::vector<std::unique_ptr<ITask>>, TaskCompare> internalQueue;

    // Mechanizmy synchronizacji
    std::mutex queueMutex;
    std::condition_variable cv;


public:
    // Dodawanie zadania do kolejki wywo³ywane przez JobScheduler
    void push(std::unique_ptr<ITask> task) {
        std::lock_guard<std::mutex> lock(queueMutex);
        internalQueue.push(std::move(task));
        cv.notify_one(); // Wybudza tu sobie jeden z uœpionych w¹tków roboczych
    }

    //przekazuje stopFlag, zeby w¹tek wiedzia³, czy ma siê obudziæ z powodu zamkniêcia systemu
    std::unique_ptr<ITask> pop(std::atomic<bool>& stopFlag) {
        std::unique_lock<std::mutex> lock(queueMutex);

        // W¹tek czeka a¿ pojawi siê zadanie lub a¿ system zostanie zamkniêty (stopFlag == true)
        cv.wait(lock, [this, &stopFlag]() { return !internalQueue.empty() || stopFlag; });

        // Jeœli obudziliœmy siê, bo system siê zamyka i nie ma zadañ - zwracamy nullptr
        if (internalQueue.empty() && stopFlag) {
            return nullptr;
        }

        auto task = std::move(const_cast<std::unique_ptr<ITask>&>(internalQueue.top()));
        internalQueue.pop();
        return task;
  
    }


    // Sprawdza czy kolejka jest pusta, to przydatne przy zamykaniu systemu
    bool empty() {
        std::lock_guard<std::mutex> lock(queueMutex);
        return internalQueue.empty();
    }

    // Budzi w¹tki podczas zamykania Schedulera
    void wakeUpAll() {
        cv.notify_all();
    }
};