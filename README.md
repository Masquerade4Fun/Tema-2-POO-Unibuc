```markdown
# Arcade Room - OOP C++ Project Tema 2-> Actualizata pentru Tema 3

## Structura folosita

**Fisiere principale:**
* `ArcadeMachine.hpp` / `ArcadeMachine.cpp`
* `ArcadeRoom.hpp` / `ArcadeRoom.cpp`
* `Exceptions.hpp`
* `ArcadeBank.hpp` 
* `MachineFactory.hpp` 
* `main.cpp`

**Rolul claselor:**
* `ArcadeMachine` - clasa de baza abstracta pentru toate aparatele
* `RetroCabinet` - clasa derivata, aparat de tip consola retro
* `VRStation` - clasa derivata, aparat de tip statie de realitate virtuala
* `RacingSimulator` - clasa derivata, aparat de tip simulator auto
* `RacingSimulatorBuilder` - clasa ajutatoare pentru construirea flexibila a simulatoarelor
* `ArcadeRoom` - gestioneaza colectia de aparate si interactiunea clientilor (este managerul practic)
* `ArcadeBank` - sistem financiar centralizat
* `MachineFactory` - clasa utilitara pentru instantierea rapida a anumitor configuratii de aparate
* `ArcadeException<T>` si clasele derivate - exceptii template proprii pentru erorile specifice din joc

**Elemente folosite:**
In proiect sunt folosite atat concepte de baza, cat si avansate:
* mostenire, functii virtuale pure, suprascriere cu override
* clasa abstracta si pointeri catre clasa de baza
* copiere polimorfica prin clone()
* suprascrierea constructorului de copiere si a operatorului de atribuire (Copy and Swap idiom)
* dynamic_cast pentru downcast cu sens
* **[Nou]** clase sablon (template) si atribute dependente de un tip `T`
* **[Nou]** functii externe friend template
* **[Nou]** variadic templates si fold expressions (C++17)
* **[Nou]** principii SOLID (Single Responsibility Principle)
* **[Nou]** design patterns (Singleton, Factory, Builder, Prototype)
* exceptii proprii (inclusiv throw in constructor)
* try / catch
* membri si metode statice
* utilizare constanta (const correctness)
* interfata non-virtuala (NVI) pentru afisare
* STL: std::vector, std::string

---

## Descrierea Proiectului

Proiectul reprezinta o simulare complexa a unei sali de jocuri. Logica principala se bazeaza pe o clasa fundamentala care defineste caracteristicile comune ale tuturor aparatelor, cum ar fi identificatorul unic, costul de utilizare, starea de uzura si profitul generat individual. Din aceasta baza se desprind trei tipuri specifice de aparate, mai exact cabinele retro, statiile de realitate virtuala si simulatoarele auto, fiecare venind cu un comportament complet diferit in momentul in care un client introduce fise pentru a initia o sesiune de joc.

Sala de jocuri pastreaza o colectie uniforma de pointeri, dar, in momentul apelarii functiei de pornire a jocului, sistemul stie automat sa aplice regulile specifice fiecarui tip de aparat in parte. De asemenea, gestiunea memoriei este tratata cu maxima seriozitate prin aplicarea tehnicilor avansate de copiere si interschimbare a datelor. Acest lucru asigura o stabilitate perfecta, garantand ca duplicarea colectiei de aparate sau mutarea acestora nu va cauza scurgeri de memorie sau opriri neasteptate ale programului.

Pentru ierarhia de aparate, am implementat mostenirea si polimorfismul in fisierele ArcadeMachine. Clasa de baza abstracta reprezinta fundatia ierarhiei, iar in interiorul ei se defineste functia virtuala pura `startGame`. Tot aici se gaseste functia `clone`, care asigura implementarea sablonului de proiectare **Prototype (Design Pattern)**, permitand copierea polimorfica a unui obiect fara sa ii stim tipul exact la executie. Crearea obiectelor complexe a fost imbunatatita prin integrarea sabloanelor **Factory** (in `MachineFactory` pentru instantierea rapida a aparatelor populare) si **Builder** (in `RacingSimulatorBuilder` pentru configurarea parametrizata a simulatoarelor auto).

Clasa de gestiune, `ArcadeRoom`, indeplineste cerinta de a stoca o colectie de pointeri catre baza. Pe langa functiile standard de management si downcast-ul cu sens (folosind `dynamic_cast` catre `VRStation` pentru a igieniza castile), am introdus tehnici moderne din C++17. Mai exact, am definit o functie **Variadic Template** combinata cu **Fold Expressions** (`addMachines(Args&&... machinesArgs)`) care permite salii sa inregistreze oricate aparate simultan, reducand codul repetitiv.

In privinta gestiunii veniturilor, am aplicat **Principiul Single Responsibility (S-ul din SOLID)**. In loc sa lasam clasa de aparate sa se ocupe atat de joc cat si de finantele globale, am extras responsabilitatea incasarilor totale intr-o clasa separata, `ArcadeBank`. Aceasta utilizeaza sablonul de proiectare **Singleton (Design Pattern)**, garantand ca exista mereu o singura seif centralizat pe toata durata rularii programului.

Arhitectura de exceptii regasita in fisierul Exceptions a fost transformata folosind programarea generica. `ArcadeException<T>` este acum o **clasa sablon (template)**, ce contine un atribut generic `errorData` de tip `T` si o metoda dependenta de acesta. Astfel, erorile pot transporta la pachet date esentiale foarte specifice (ex: de tip `int` pentru jetoane lipsa sau `std::string` pentru numele masinariei blocate). Pentru o afisare cat mai eleganta si naturala a acestor erori complexe, clasa dispune de o **functie externa friend template** care supraincarca operatorul `<<`. Toate aceste exceptii sunt interceptate eficient in blocuri `try-catch` in meniul interactiv din main.

---

## Rulare si Output

Pentru a compila proiectul in terminal (sunt incluse toate fisierele sursa adaugate):

```bash
masquerade@masquerade-ThinkPad-E16-Gen-2:~/Desktop/oop_tema2$ g++ *.cpp -o program
masquerade@masquerade-ThinkPad-E16-Gen-2:~/Desktop/oop_tema2$ ./program

```


```

```
