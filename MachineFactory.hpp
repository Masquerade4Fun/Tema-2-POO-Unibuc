#ifndef MACHINE_FACTORY_HPP
#define MACHINE_FACTORY_HPP

#include "ArcadeMachine.hpp"
#include "ArcadeServices.hpp"

class MachineFactory {
public:
    static RetroCabinet createPacmanRetro() {
        const RetroPreset& preset = MachinePresetCatalog::getInstance().getPacmanRetro();
        return RetroCabinet(preset.name, preset.cost, preset.genre);
    }
    
    static VRStation createPremiumVR() {
        const VRPreset& preset = MachinePresetCatalog::getInstance().getPremiumVR();
        return VRStation(preset.name, preset.cost, preset.minAge);
    }
};

#endif
