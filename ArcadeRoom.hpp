#ifndef ARCADE_ROOM_HPP
#define ARCADE_ROOM_HPP

#include <vector>
#include <algorithm>
#include "ArcadeMachine.hpp"

class ArcadeRoom {
private:
    std::vector<ArcadeMachine*> machines; 

public:
    ArcadeRoom() = default;

    // Copy Constructor
    ArcadeRoom(const ArcadeRoom& other);

    // Funcție friend pentru Swap idiom
    friend void swap(ArcadeRoom& first, ArcadeRoom& second) noexcept;

    // Operator= folosind Copy and Swap
    ArcadeRoom& operator=(ArcadeRoom other);

    ~ArcadeRoom();

    // Gestiune a colectiei
    void addMachine(const ArcadeMachine& machine);
    
    // Func logica de sala
    void attemptPlay(size_t index, int tokens);
    void endPlay(size_t index);
    
    // Downcast
    void resolveSpecialMaintenance();
    void viewRacingTelemetry() const;

    void listMachines() const;
    void printDailyReport() const;
    void closeRoom();
};

#endif 