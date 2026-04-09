# JobScheduler

Asynchroniczny system kolejkowania i wykonywania zadań w tle, napisany w nowoczesnym standardzie C++20. Projekt demonstruje wykorzystanie mechanizmów wielowątkowości, paradygmatów programowania obiektowego oraz wzorców projektowych.

## Kontekst Akademicki
Projekt został zrealizowany w ramach zajęć na uczelni wyższej.

* **Nazwa przedmiotu:** Zaawansowane C++
* **Realizacja:** rok akademicki 2025/2026, półsemestr: 3
* **Prowadzący zajęcia:** * dr inż. Paweł Wnuk, prof. uczelni, dr hab. inż. Michał Syfert, prof. uczelni

## Opis projektu
Celem projektu jest zarządzanie zadaniami w środowisku wielowątkowym z minimalizacją narzutu na tworzenie nowych procesów. System przyjmuje polimorficzne zadania, kolejkuje je na podstawie priorytetów (HIGH, NORMAL, LOW) i rozdziela między dostępną, stałą pulę wątków roboczych. Warstwa logiki biznesowej jest całkowicie odseparowana od warstwy prezentacji za pomocą wzorca Obserwator, co gwarantuje wysoką skalowalność i czystość architektury.

## Główne funkcjonalności
* **Zarządzanie pulą wątków:** Wykorzystanie `std::jthread` do bezpiecznego i automatycznego zarządzania cyklem życia wątków.
* **Kolejkowanie Priorytetowe:** Wątkowo bezpieczna kolejka oparta na `std::priority_queue`, chroniona przez `std::mutex` i `std::condition_variable`.
* **Polimorfizm i Interfejsy:** Wspólny interfejs `ITask` pozwalający na wykonywanie zadań o różnej charakterystyce bez ścisłego sprzęgania typów.
* **Wzorzec Obserwator:** Asynchroniczne powiadamianie UI o zmianach statusu zadań (PENDING, RUNNING, COMPLETED, FAILED).
* **Wzorzec Fasada:** Główne API ukryte za klasą `JobScheduler`.
* **Graceful Shutdown:** Mechanizm bezpiecznego zamykania systemu, gwarantujący dokończenie trwających zadań i wybudzenie uśpionych wątków przed zamknięciem.

## Wymagania systemowe i technologiczne
* **Język:** Modern C++ (Standard C++20)
* **Kompilator:** MSVC
* **Środowisko:** Visual Studio 2022
* **Zarządzanie pamięcią:** Inteligentne wskaźniki (`std::unique_ptr`, `std::shared_ptr`)

## Instrukcja budowania i uruchamiania
Aby skompilować i uruchomić system JobScheduler lokalnie, wykonaj poniższe kroki:
* **Otwórz projekt** Uruchom Visual Studio 2022 i otwórz plik rozwiązania (`.sln`) lub folder z projektem.
* **Skonfiguruj standard C++20**
* **Zbuduj rozwiązanie** Naciśnij `Ctrl + Shift + B` (lub z górnego menu wybierz *Kompilacja* -> *Kompiluj rozwiązanie*), aby skompilować projekt.
* **Uruchom aplikację** Naciśnij `Ctrl + F5` (Uruchom bez debugowania), aby włączyć aplikację konsolową i zobaczyć działanie systemu na żywo.
