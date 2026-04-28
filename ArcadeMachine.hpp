#ifndef ARCADE_MACHINE_HPP
#define ARCADE_MACHINE_HPP

#include <string>
#include <iostream>
#include "Exceptions.hpp"

class ArcadeMachine {
private:
    int id;
    std::string name;
    int costPerPlay;
    bool occupied;
    int revenue;
    int condition; 

    static int totalMachinesCreated; 
    static int globalArcadeRevenue;

protected:
    //interfata pentru afisare
    virtual void printImpl(std::ostream& os) const = 0;
    
    void degradeCondition(int amount);
    void addRevenue(int amount);

public:
    ArcadeMachine(const std::string& n, int cost);
    virtual ~ArcadeMachine();

    // Constructorul virtual
    virtual ArcadeMachine* clone() const = 0;

    // afisare
    void print(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const ArcadeMachine& machine);

    virtual void startGame(int playerTokens) = 0;
    virtual void endGame() = 0;
        virtual void performMaintenance();
    bool isOccupied() const;
    int getCost() const;
    std::string getName() const;
    int getCondition() const;
    int getRevenue() const;
    
    void setOccupiedStatus(bool status);
    static int getTotalMachines();
    static int getGlobalRevenue();
};

//retrocabinet
class RetroCabinet : public ArcadeMachine {
private:
    std::string gameType;
    int currentHighScore;
    bool crtScreenFlickering;

public:
    RetroCabinet(const std::string& n, int cost, const std::string& type);
    ArcadeMachine* clone() const override;
    
    void startGame(int playerTokens) override;
    void endGame() override;
    void performMaintenance() override;
    void registerNewScore(int score);

protected:
    void printImpl(std::ostream& os) const override;
};

//VRStation
class VRStation : public ArcadeMachine {
private:
    int minAgeRequired;
    bool needsCleaning;
    int sessionsSinceLastClean;

public:
    VRStation(const std::string& n, int cost, int age);
    ArcadeMachine* clone() const override;
    
    void startGame(int playerTokens) override;
    void endGame() override;
    void performMaintenance() override;
    void sanitizeHeadset();

protected:
    void printImpl(std::ostream& os) const override;
};

//simulator racing
class RacingSimulator : public ArcadeMachine {
private:
    bool hasMotionSeat;
    int tireWearSimulation;

public:
    RacingSimulator(const std::string& n, int cost, bool motion);
    ArcadeMachine* clone() const override;
    
    void startGame(int playerTokens) override;
    void endGame() override;
    void performMaintenance() override;
    void runDiagnostics() const;

protected:
    void printImpl(std::ostream& os) const override;
};

#endif 