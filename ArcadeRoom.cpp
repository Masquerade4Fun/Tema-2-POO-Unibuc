#include "ArcadeRoom.hpp"

ArcadeRoom::ArcadeRoom(const ArcadeRoom& other) {
    for (const auto& machine : other.machines) {
        machines.push_back(machine->clone());
    }
}

void swap(ArcadeRoom& first, ArcadeRoom& second) noexcept {
    std::swap(first.machines, second.machines);
}

ArcadeRoom& ArcadeRoom::operator=(ArcadeRoom other) {
    swap(*this, other);
    return *this;
}

ArcadeRoom::~ArcadeRoom() {
    closeRoom();
}

void ArcadeRoom::addMachine(const ArcadeMachine& machine) {
    machines.push_back(machine.clone());
}

void ArcadeRoom::attemptPlay(size_t index, int tokens) {
    if (index >= machines.size()) {
        std::cout << "Index aparat invalid.\n";
        return;
    }
    machines[index]->startGame(tokens);
}

void ArcadeRoom::endPlay(size_t index) {
    if (index < machines.size()) {
        machines[index]->endGame();
    }
}

void ArcadeRoom::resolveSpecialMaintenance() {
    std::cout << "\n Procedura Mentenanta si Igienizare \n";
    for (auto& machine : machines) {
        if (machine->getCondition() < 50) {
            std::cout << "Se repara aparatul: " << machine->getName() << "\n";
            machine->performMaintenance();
        }
        VRStation* vr = dynamic_cast<VRStation*>(machine);
        if (vr != nullptr) {
            std::cout << "Verificare VR: ";
            vr->sanitizeHeadset();
        }
    }
}

void ArcadeRoom::viewRacingTelemetry() const {
    std::cout << "\n Simulatoare Auto \n";
    for (const auto& machine : machines) {
        const RacingSimulator* racingSim = dynamic_cast<const RacingSimulator*>(machine);
        if (racingSim != nullptr) {
            racingSim->runDiagnostics();
        }
    }
}

void ArcadeRoom::listMachines() const {
    std::cout << "\n=========== Inventar ===========\n";
    for (size_t i = 0; i < machines.size(); ++i) {
        std::cout << "[" << i << "] " << *(machines[i]) << "\n";
    }
    std::cout << "============================================\n";
}

void ArcadeRoom::printDailyReport() const {
    std::cout << "\n=========== Raport final ===========\n";
    std::cout << "Aparate active in memorie: " << ArcadeMachine::getTotalMachines() << "\n";
    std::cout << "Total Incasari Globale (Jetoane): " << ArcadeMachine::getGlobalRevenue() << "\n";
    std::cout << "=====================================\n";
}

void ArcadeRoom::closeRoom() {
    for (auto& machine : machines) {
        delete machine;
    }
    machines.clear();
}