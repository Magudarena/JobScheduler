#pragma once
#include <iostream>
#include <memory>
#include <atomic>
#include "ThreadSafePriorityQueue.h"

class Worker {
private:
    uint32_t id;

public:
    Worker(uint32_t workerId) : id(workerId) {}

    // G³ówna pêtla wykonawcza w¹tku
    void run(ThreadSafePriorityQueue& queue, std::atomic<bool>& stopFlag) {
        while (!stopFlag) {
            // Próba pobrania zadania z kolejki, operacja blokuj¹ca do momentu pojawienia siê zadania
            auto task = queue.pop(stopFlag);

            if (task) {
                // jeœli zadanie to 'execute' bez wiedzy o szczegó³ach zadania - polimorfizm
                task->execute();




                //  dokonczyc aktualizacj¹ statusów i powiadomieniami dla Obserwatorów po po³¹czeniu z klas¹ JobScheduler
            
            
            
            }
        }
    }
};