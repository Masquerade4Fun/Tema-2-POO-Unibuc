#include <iostream>
#include "ArcadeRoom.hpp"
#include "ArcadeMachine.hpp"
#include "Exceptions.hpp"

int main() {
    try {
        ArcadeRoom neoTokyoArcade;

        // Initializare 
        RetroCabinet mortalKombat("Mortal Kombat II", 2, "Fighting");
        VRStation halfLife("Half-Life Alyx Station", 10, 16);
        RacingSimulator needForSpeed("NFS Heat 4D", 5, true);

        neoTokyoArcade.addMachine(mortalKombat);
        neoTokyoArcade.addMachine(halfLife);
        neoTokyoArcade.addMachine(needForSpeed);

        std::cout << "Sala de jocuri e deschisa:\n";
        neoTokyoArcade.listMachines();

        // Simularea unor sesiuni de joc
        std::cout << "\n Incep sesiunile de dimineata:\n";
        neoTokyoArcade.attemptPlay(0, 5); // Joaca MK (costa 2, da 5 -> ok)
        neoTokyoArcade.endPlay(0);
        
        neoTokyoArcade.attemptPlay(1, 15); // Joaca VR 
        neoTokyoArcade.endPlay(1);
        
        // Simulam mai multe jocuri in VR pentru a forta err
        neoTokyoArcade.attemptPlay(1, 10); neoTokyoArcade.endPlay(1);
        neoTokyoArcade.attemptPlay(1, 10); neoTokyoArcade.endPlay(1);

        // Exceptii 
        std::cout << "\n Verificare Excepții:\n";
        try {
            std::cout << "Client 1 incearca VR: \n";
            neoTokyoArcade.attemptPlay(1, 10); // Ar trebui sa arunce NeedsMaintenanceException
        } catch (const ArcadeException& e) {
            std::cout << "   Prins: " << e.what() << "\n";
        }

        try {
            std::cout << "Client 2 incearca sa fure curent (0 jetoane la cursa): \n";
            neoTokyoArcade.attemptPlay(2, 0); // pune InsufficientTokensException
        } catch (const ArcadeException& e) {
            std::cout << "   Prins: " << e.what() << "\n";
        }

        try {
            std::cout << "Client 3 incearca aparatul ocupat: \n";
            neoTokyoArcade.attemptPlay(0, 10); // punem 2 clienti
            neoTokyoArcade.attemptPlay(0, 10); // -> MachineOccupiedException
        } catch (const ArcadeException& e) {
            std::cout << "   Prins: " << e.what() << "\n";
            neoTokyoArcade.endPlay(0); // eliberarea aparatului
        }

        //Copy & Swap Idiom
        ArcadeRoom backupServer = neoTokyoArcade; // Copy Constructor
        ArcadeRoom offlineStorage;
        offlineStorage = backupServer;            // Operator=

        //Testare Downcast-uri
        neoTokyoArcade.viewRacingTelemetry();     // pe Racing
        neoTokyoArcade.resolveSpecialMaintenance(); // Repar si rulez

        neoTokyoArcade.listMachines();
        neoTokyoArcade.printDailyReport();

        // Conf invalid
        std::cout << "\n Aparat defect din depozit:\n";
        RetroCabinet brokenMachine("Aparat Defect", -5, "Eroare"); // except

    } 
    // alte exceptii
    catch (const InvalidConfigurationException& e) {
        std::cout << "[Err]: " << e.what() << "\n";
    }
    catch (const ArcadeException& e) {
        std::cout << "[Err]: " << e.what() << "\n";
    } 
    catch (const std::exception& e) {
        std::cout << "[Err]: " << e.what() << "\n";
    }

    return 0;
}   