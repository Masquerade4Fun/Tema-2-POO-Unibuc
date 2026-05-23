#ifndef ARCADE_ROOM_HPP
#define ARCADE_ROOM_HPP

#include <vector>
#include <algorithm>
#include <utility>
#include "ArcadeMachine.hpp"

class ArcadeRoom {
private:
    std::vector<ArcadeMachine*> machines; 

public:
    ArcadeRoom() = default; // poate fi o sala goala
    ArcadeRoom(const ArcadeRoom& other);
    friend void swap(ArcadeRoom& first, ArcadeRoom& second) noexcept;
    ArcadeRoom& operator=(ArcadeRoom other);
    ~ArcadeRoom();

    void addMachine(const ArcadeMachine& machine);
    template <typename... Args>//inf arg
    void addMachines(Args&&... machinesArgs) {
        (addMachine(std::forward<Args>(machinesArgs)), ...); //apel addMachine automat
    }
    
    void attemptPlay(size_t index, int tokens);
    void endPlay(size_t index);
    
    void resolveSpecialMaintenance();
    void viewRacingTelemetry() const;

    void listMachines() const;
    void printDailyReport() const;
    void closeRoom();
};

#endif