#include "ArcadeMachine.hpp"
#include "ArcadeBank.hpp" 
#include "ArcadeServices.hpp"

int ArcadeMachine::totalMachinesCreated = 0;

ArcadeMachine::ArcadeMachine(const std::string& n, int cost) 
    : name(n), costPerPlay(cost), occupied(false), revenue(0), condition(100) {
    if (cost < 0) {
        throw InvalidConfigurationException("Costul nu poate fi negativ: ", n);
    }
    totalMachinesCreated++;
    id = totalMachinesCreated; 
}

ArcadeMachine::~ArcadeMachine() {
    totalMachinesCreated--;
}

void ArcadeMachine::degradeCondition(int amount) {
    condition -= amount;
    if (condition < 0) condition = 0;
}

void ArcadeMachine::addRevenue(int amount) {
    revenue += amount;
    ArcadeBank::getInstance().addRevenue(amount);
}

void ArcadeMachine::print(std::ostream& os) const {
    os << "[ID:" << id << "] ";
    printImpl(os);
    os << " | Stare: " << condition << "% | Incasari: " << revenue << " jetoane";
}

std::ostream& operator<<(std::ostream& os, const ArcadeMachine& machine) {
    machine.print(os);
    return os;
}

void ArcadeMachine::performMaintenance() {
    condition = 100;
    std::cout << "-> Mentenanta gata pentru " << name << ".\n";
}

bool ArcadeMachine::isOccupied() const { return occupied; }
int ArcadeMachine::getCost() const { return costPerPlay; }
std::string ArcadeMachine::getName() const { return name; }
int ArcadeMachine::getCondition() const { return condition; }
int ArcadeMachine::getRevenue() const { return revenue; }
void ArcadeMachine::setOccupiedStatus(bool status) { occupied = status; }

int ArcadeMachine::getTotalMachines() { return totalMachinesCreated; }

int ArcadeMachine::getGlobalRevenue() { 
    return ArcadeBank::getInstance().getGlobalRevenue(); 
}

RetroCabinet::RetroCabinet(const std::string& n, int cost, const std::string& type)
    : ArcadeMachine(n, cost), gameType(type), currentHighScore(0), crtScreenFlickering(false) {}

ArcadeMachine* RetroCabinet::clone() const {
    return new RetroCabinet(*this);
}

void RetroCabinet::startGame(int playerTokens) {
    const ArcadePolicy& policy = ArcadePolicy::getInstance();

    if (getCondition() < policy.getRetroMinCondition()) throw NeedsMaintenanceException(getName() + " necesita reparatii.", getCondition());
    if (isOccupied()) throw MachineOccupiedException(getName() + " are deja un jucator.", getName());
    if (playerTokens < getCost()) throw InsufficientTokensException("Prea putine jetoane pentru retrocabinet!!", getCost() - playerTokens);
    
    setOccupiedStatus(true);
    addRevenue(getCost());
    degradeCondition(policy.getRetroDegradeStep());
    
    if (getCondition() < policy.getRetroFlickerThreshold()) crtScreenFlickering = true;
    
    std::cout << "[Retro] Start: " << getName() << " Mod " << gameType << ". Insert coin\n";
    if (crtScreenFlickering) std::cout << "   *Avertisment: Ecranul palpaie usor.*\n";
}

void RetroCabinet::endGame() {
    setOccupiedStatus(false);
    std::cout << "[Retro] GAME OVER.\n";
}

void RetroCabinet::performMaintenance() {
    ArcadeMachine::performMaintenance();
    crtScreenFlickering = false;
    std::cout << "-> Tubul catodic a fost recalibrat.\n";
}

void RetroCabinet::registerNewScore(int score) {
    if (score > currentHighScore) {
        currentHighScore = score;
        std::cout << "[Retro] NOU HIGH SCORE la " << getName() << ": " << currentHighScore << " puncte.\n";
    }
}

void RetroCabinet::printImpl(std::ostream& os) const {
    os << "Retro Cabinet [" << getName() << "] | Genul: " << gameType << " | HighScore: " << currentHighScore;
}

VRStation::VRStation(const std::string& n, int cost, int age)
    : ArcadeMachine(n, cost), minAgeRequired(age), needsCleaning(false), sessionsSinceLastClean(0) {
    if (age <= 0 || age > 100) {
        throw InvalidConfigurationException("Varsta aparat VR invalida.", std::to_string(age));
    }
}

ArcadeMachine* VRStation::clone() const {
    return new VRStation(*this);
}

void VRStation::startGame(int playerTokens) {
    const ArcadePolicy& policy = ArcadePolicy::getInstance();

    if (needsCleaning) throw NeedsMaintenanceException(getName() + " necesita igienizare inainte de utilizare.", sessionsSinceLastClean);
    if (getCondition() < policy.getVrMinCondition()) throw NeedsMaintenanceException(getName() + " are erori de tracking.", getCondition());
    if (isOccupied()) throw MachineOccupiedException(getName() + " este utilizat in VR.", getName());
    if (playerTokens < getCost()) throw InsufficientTokensException("Fonduri insuficiente pentru VR Station.", getCost() - playerTokens);
    
    setOccupiedStatus(true);
    addRevenue(getCost());
    degradeCondition(policy.getVrDegradeStep()); 
    sessionsSinceLastClean++;
    
    if (sessionsSinceLastClean >= policy.getVrCleaningCycle()) needsCleaning = true; 
    
    std::cout << "[VR] START: Calibrare headset " << getName() << "...\n";
}

void VRStation::endGame() {
    setOccupiedStatus(false);
    std::cout << "[VR] Sesiunea s-a incheiat.\n";
}

void VRStation::sanitizeHeadset() {
    needsCleaning = false;
    sessionsSinceLastClean = 0;
    std::cout << "-> Casca pentru " << getName() << " a fost stearsa.\n";
}

void VRStation::performMaintenance() {
    ArcadeMachine::performMaintenance();
    sanitizeHeadset();
    std::cout << "-> Lentilele si senzorii de miscare au fost recalibrati.\n";
}

void VRStation::printImpl(std::ostream& os) const {
    os << "VR Station [" << getName() << "] | Varsta min: " << minAgeRequired << " | Necesita curatare: " << (needsCleaning ? "Da" : "Nu");
}

RacingSimulator::RacingSimulator(const std::string& n, int cost, bool motion)
    : ArcadeMachine(n, cost), hasMotionSeat(motion), tireWearSimulation(0) {}

ArcadeMachine* RacingSimulator::clone() const {
    return new RacingSimulator(*this);
}

void RacingSimulator::startGame(int playerTokens) {
    const ArcadePolicy& policy = ArcadePolicy::getInstance();

    if (getCondition() < policy.getRacingMinCondition()) throw NeedsMaintenanceException(getName() + " sistem hidraulic blocat.", getCondition());
    if (isOccupied()) throw MachineOccupiedException(getName() + " cursa in desfasurare.", getName());
    if (playerTokens < getCost()) throw InsufficientTokensException("Lipsa jetoane Cursa.", getCost() - playerTokens);
    
    setOccupiedStatus(true);
    addRevenue(getCost());
    degradeCondition(policy.getRacingDegradeStep());
    tireWearSimulation += policy.getRacingWearStep(); 
    
    std::cout << "[Racing] START: Motor dat drumul la " << getName() << ".\n";
    if (hasMotionSeat) std::cout << "   Scaunul este activ\n";
    if (tireWearSimulation >= 100) std::cout << "   *Avertisment: Manevrabilitate redusa (Anvelope uzate)*\n";
}

void RacingSimulator::endGame() {
    setOccupiedStatus(false);
    std::cout << "[Racing] Cursa terminata.\n";
}

void RacingSimulator::runDiagnostics() const {
    std::cout << ">>> Diagnoza (" << getName() << "): Uzura anvelope " << tireWearSimulation << "%. Scaun miscare: " << (hasMotionSeat ? "Online" : "Indisponibil") << ".\n";
}

void RacingSimulator::performMaintenance() {
    ArcadeMachine::performMaintenance();
    tireWearSimulation = 0;
    std::cout << "-> Uleiul schimbat.\n";
}

void RacingSimulator::printImpl(std::ostream& os) const {
    os << "Racing Simulator [" << getName() << "] | Scaun Mobil: " << (hasMotionSeat ? "Da" : "Nu");
}
