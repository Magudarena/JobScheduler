#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

// Załączamy nasze nagłówki
#include "JobScheduler.h"
#include "CliDashboard.h"
#include "ComputeTask.h"

int main() {
    std::cout << "=== Start Systemu JobScheduler ===\n\n";

    // 1. Inicjalizacja systemu (pula 4 wątków) i Dashboardu
    auto scheduler = std::make_shared<JobScheduler>(4);
    auto dashboard = std::make_shared<CliDashboard>();

    // 2. Podpięcie interfejsu (Dashboardu) jako obserwatora
    scheduler->addObserver(dashboard);

    // 3. Przesłanie zadań polimorficznych (parametry: ID, Priorytet, "Złożoność")
    std::cout << "Dodawanie zadan do kolejki...\n\n";

    scheduler->submit(std::make_unique<ComputeTask>(101, Priority::LOW, 5.0));    // Długie zadanie, niski priorytet
    scheduler->submit(std::make_unique<ComputeTask>(102, Priority::HIGH, 2.0));   // Krótkie zadanie, wysoki priorytet
    scheduler->submit(std::make_unique<ComputeTask>(103, Priority::NORMAL, 8.0)); // Bardzo długie zadanie, normalny priorytet
    scheduler->submit(std::make_unique<ComputeTask>(104, Priority::HIGH, 1.0));   // Bardzo krótkie, wysoki priorytet

    // Symulujemy czas działania programu głównego, żeby wątki mogły popracować (np. 3 sekundy)
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // 4. Bezpieczne zamknięcie (Graceful Shutdown)
    std::cout << "\nZamykanie systemu...\n";
    scheduler->shutdown();

    std::cout << "Koniec programu.\n";
    return 0;
}
