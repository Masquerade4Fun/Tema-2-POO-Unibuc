#include <iostream>
#include <string>
#include <limits>
#include "ArcadeRoom.hpp"
#include "ArcadeMachine.hpp"
#include "Exceptions.hpp"
#include "MachineFactory.hpp"

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void runStandardSimulation() {
    std::cout << "\n--- Hardcoded ---\n";
    try {
        ArcadeRoom neoTokyoArcade;

        RetroCabinet mortalKombat("Mortal Kombat II", 2, "Fighting");
        auto pacman = MachineFactory::createPacmanRetro();
        auto cyberpunkVR = MachineFactory::createPremiumVR();
        RacingSimulator dirtRally = RacingSimulatorBuilder()
                                        .setName("Dirt Rally 4D")
                                        .setCost(7)
                                        .enableMotionSeat(true)
                                        .build();

        neoTokyoArcade.addMachines(mortalKombat, pacman, cyberpunkVR, dirtRally);
        neoTokyoArcade.listMachines();

        std::cout << "\n Primele sesiuni:\n";
        neoTokyoArcade.attemptPlay(0, 5); 
        neoTokyoArcade.endPlay(0);
        
        neoTokyoArcade.attemptPlay(2, 25); 
        neoTokyoArcade.endPlay(2);
        
        neoTokyoArcade.attemptPlay(2, 20); neoTokyoArcade.endPlay(2);
        neoTokyoArcade.attemptPlay(2, 20); neoTokyoArcade.endPlay(2);

        std::cout << "\n---Exceptii:---\n";
        try {
            neoTokyoArcade.attemptPlay(2, 20);
        } catch (const ArcadeException<int>& e) {
            std::cout << "Prins: " << e << "\n";
        }

        try {
            neoTokyoArcade.attemptPlay(3, 1);
        } catch (const ArcadeException<int>& e) {
            std::cout << "Prins: " << e << "\n";
        }

        try {
            neoTokyoArcade.attemptPlay(0, 10);
            neoTokyoArcade.attemptPlay(0, 10);
        } catch (const ArcadeException<std::string>& e) {
            std::cout << "Prins: " << e << "\n";
            neoTokyoArcade.endPlay(0); 
        }

        neoTokyoArcade.resolveSpecialMaintenance(); 
        neoTokyoArcade.printDailyReport();

        std::cout << "\n--- Configurare invalida ---\n";
        RetroCabinet brokenMachine("Aparat Defect", -5, "Eroare");

    } 
    catch (const std::exception& e) {
        std::cout << "[ Err]: " << e.what() << "\n";
    }
}

void runInteractiveMode() {
    ArcadeRoom myRoom;
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n--- GESTIUNE SALA ---\n";
        std::cout << "1. Adauga aparat: Retro Cabinet\n";
        std::cout << "2. Adauga aparat: VR Station\n";
        std::cout << "3. Adauga aparat: Racing Simulator\n";
        std::cout << "4. Afiseaza inventarul aparatelor\n";
        std::cout << "5. Joaca la un aparat\n";
        std::cout << "6. Opreste jocul la un aparat\n";
        std::cout << "7. Cheama echipa de mentenanta\n";
        std::cout << "8. Raportul financiar al zilei\n";
        std::cout << "0. Iesi din modul interactiv (distruge sala)\n";
        std::cout << "Alege o optiune: ";

        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Introdu un numar valid!\n";
            continue;
        }

        try {
            if (choice == 1) {
                std::string name, type;
                int cost;
                std::cout << "Nume joc: "; std::cin >> std::ws; std::getline(std::cin, name);
                std::cout << "Genul jocului (ex: Arcade, Fighting): "; std::getline(std::cin, type);
                std::cout << "Cost per joc (jetoane): "; std::cin >> cost;
                
                RetroCabinet retro(name, cost, type);
                myRoom.addMachine(retro);
                std::cout << "-> Retro Cabinet adaugat cu succes!\n";

            } else if (choice == 2) {
                std::string name;
                int cost, age;
                std::cout << "Nume statie VR: "; std::cin >> std::ws; std::getline(std::cin, name);
                std::cout << "Varsta minima: "; std::cin >> age;
                std::cout << "Cost per joc: "; std::cin >> cost;

                VRStation vr(name, cost, age);
                myRoom.addMachine(vr);
                std::cout << "-> VR Station adaugat!\n";

            } else if (choice == 3) {
                std::string name;
                int cost, motionInput;
                std::cout << "Nume Simulator Curse: "; std::cin >> std::ws; std::getline(std::cin, name);
                std::cout << "Cost per joc (jetoane): "; std::cin >> cost;
                std::cout << "Are scaun cu miscare (1 pt Da, 0 pt Nu)? "; std::cin >> motionInput;

                RacingSimulator racing = RacingSimulatorBuilder()
                                            .setName(name)
                                            .setCost(cost)
                                            .enableMotionSeat(motionInput == 1)
                                            .build();
                myRoom.addMachine(racing);
                std::cout << "-> Racing Simulator adaugat cu succes!\n";

            } else if (choice == 4) {
                myRoom.listMachines();

            } else if (choice == 5) {
                int index, tokens;
                std::cout << "Introdu ID-ul aparatului(idx-> 0): "; std::cin >> index;
                std::cout << "Cate jetoane bagi? "; std::cin >> tokens;
                myRoom.attemptPlay(index, tokens);

            } else if (choice == 6) {
                int index;
                std::cout << "Introdu ID-ul aparatului pentru a opri jocul: "; std::cin >> index;
                myRoom.endPlay(index);

            } else if (choice == 7) {
                myRoom.resolveSpecialMaintenance();

            } else if (choice == 8) {
                myRoom.printDailyReport();

            } else if (choice != 0) {
                std::cout << "Optiune invalida!\n";
            }
        } 
        catch (const ArcadeException<int>& e) {
            std::cout << "\n[EROARE]: " << e << "\n";
        } catch (const ArcadeException<std::string>& e) {
            std::cout << "\n[EROARE]: " << e << "\n";
        } catch (const std::exception& e) {
            std::cout << "\n[EROARE LA CONFIGURARE]: " << e.what() << "\n";
        }
    }
}
int main() {
    int mainChoice = -1;

    while (mainChoice != 0) {
        std::cout << "\n=======================================\n";
        std::cout << "      SISTEM GESTIUNE SALI ARCADE      \n";
        std::cout << "=======================================\n";
        std::cout << "1. Rulare hardcodata\n";
        std::cout << "2. Creeaza interactiv\n";
        std::cout << "0. Inchide programul\n";
        std::cout << "> Alege o optiune: ";

        if (!(std::cin >> mainChoice)) {
            clearInput();
            continue;
        }

        if (mainChoice == 1) {
            runStandardSimulation();
        } else if (mainChoice == 2) {
            runInteractiveMode();
        } else if (mainChoice != 0) {
            std::cout << "Optiune invalida\n";
        }
    }

    std::cout << "Program incehiat.\n";
    return 0;
}