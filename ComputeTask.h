#pragma once
#include "ITask.h"
#include <iostream>
#include <thread>
#include <chrono>

class ComputeTask : public ITask {
private:
    double complexity;

public:
    ComputeTask(uint64_t id, Priority prio, double complexity)
        : ITask(id, prio), complexity(complexity) {
    }


    // Nadpisanie czysto wirtualnej metody, znowu tutaj mam polimorfizm
    void execute() override {
        // Symulacja obliczeñ na podstawie z³o¿onoœci
        int sleepTime = static_cast<int>(complexity * 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

        // celowo NIE ma tu "std::cout" bp to ma tylko liczyæ, a nie zajmowaæ siê wyœwietlaniem w konsoli
    }
};