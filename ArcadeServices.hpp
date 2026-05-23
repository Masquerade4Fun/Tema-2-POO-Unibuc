#ifndef ARCADE_SERVICES_HPP
#define ARCADE_SERVICES_HPP

#include <string>

struct RetroPreset {
    std::string name;
    int cost;
    std::string genre;
};

struct VRPreset {
    std::string name;
    int cost;
    int minAge;
};

class ArcadePolicy {
private:
    int retroMinCondition;
    int retroDegradeStep;
    int retroFlickerThreshold;
    int vrMinCondition;
    int vrDegradeStep;
    int vrCleaningCycle;
    int racingMinCondition;
    int racingDegradeStep;
    int racingWearStep;
    int roomMaintenanceThreshold;

    ArcadePolicy()
        : retroMinCondition(15),
          retroDegradeStep(5),
          retroFlickerThreshold(30),
          vrMinCondition(20),
          vrDegradeStep(10),
          vrCleaningCycle(3),
          racingMinCondition(10),
          racingDegradeStep(8),
          racingWearStep(25),
          roomMaintenanceThreshold(50) {}

public:
    ArcadePolicy(const ArcadePolicy&) = delete;
    ArcadePolicy& operator=(const ArcadePolicy&) = delete;

    static ArcadePolicy& getInstance() {
        static ArcadePolicy instance;
        return instance;
    }

    int getRetroMinCondition() const { return retroMinCondition; }
    int getRetroDegradeStep() const { return retroDegradeStep; }
    int getRetroFlickerThreshold() const { return retroFlickerThreshold; }
    int getVrMinCondition() const { return vrMinCondition; }
    int getVrDegradeStep() const { return vrDegradeStep; }
    int getVrCleaningCycle() const { return vrCleaningCycle; }
    int getRacingMinCondition() const { return racingMinCondition; }
    int getRacingDegradeStep() const { return racingDegradeStep; }
    int getRacingWearStep() const { return racingWearStep; }
    int getRoomMaintenanceThreshold() const { return roomMaintenanceThreshold; }
};

class MachinePresetCatalog {
private:
    RetroPreset pacmanRetro;
    VRPreset premiumVR;

    MachinePresetCatalog()
        : pacmanRetro{"Pac-Man Classic", 2, "Arcade"},
          premiumVR{"Premium Cyberpunk VR", 20, 16} {}

public:
    MachinePresetCatalog(const MachinePresetCatalog&) = delete;
    MachinePresetCatalog& operator=(const MachinePresetCatalog&) = delete;

    static MachinePresetCatalog& getInstance() {
        static MachinePresetCatalog instance;
        return instance;
    }

    const RetroPreset& getPacmanRetro() const { return pacmanRetro; }
    const VRPreset& getPremiumVR() const { return premiumVR; }
};

class MaintenanceLedger {
private:
    int inspections;
    int repairs;
    int sanitizations;

    MaintenanceLedger() : inspections(0), repairs(0), sanitizations(0) {}

public:
    MaintenanceLedger(const MaintenanceLedger&) = delete;
    MaintenanceLedger& operator=(const MaintenanceLedger&) = delete;

    static MaintenanceLedger& getInstance() {
        static MaintenanceLedger instance;
        return instance;
    }

    void noteInspection() { inspections++; }
    void noteRepair() { repairs++; }
    void noteSanitization() { sanitizations++; }

    int getInspections() const { return inspections; }
    int getRepairs() const { return repairs; }
    int getSanitizations() const { return sanitizations; }
};

#endif
