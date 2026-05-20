#ifndef MACHINE_FACTORY_HPP
#define MACHINE_FACTORY_HPP

#include "ArcadeMachine.hpp"

class MachineFactory {
public:
    static RetroCabinet createPacmanRetro() {
        return RetroCabinet("Pac-Man Classic", 2, "Arcade");
    }
    
    static VRStation createPremiumVR() {
        return VRStation("Premium Cyberpunk VR", 20, 16);
    }
};

#endif