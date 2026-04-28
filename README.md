# Arcade Room - OOP C++ Project

## Structura folosita

**Fisiere principale:**
* `ArcadeMachine.hpp` / `ArcadeMachine.cpp`
* `ArcadeRoom.hpp` / `ArcadeRoom.cpp`
* `Exceptions.hpp`
* `main.cpp`

**Rolul claselor:**
* `ArcadeMachine` - clasa de baza abstracta pentru toate aparatele
* `RetroCabinet` - clasa derivata, aparat de tip consola retro
* `VRStation` - clasa derivata, aparat de tip statie de realitate virtuala
* `RacingSimulator` - clasa derivata, aparat de tip simulator auto
* `ArcadeRoom` - gestioneaza colectia de aparate si interactiunea clientilor (este manageru practic)
* `ArcadeException` si clasele derivate - exceptii proprii pentru erorile specifice din joc

**Elemente folosite:**
In proiect sunt folosite:
* mostenire
* functii virtuale pure
* suprascriere cu override
* clasa abstracta
* pointeri catre clasa de baza
* copiere polimorfica prin clone()
* suprascrierea constructorului de copiere si a operatorului de atribuire (Copy and Swap idiom)
* dynamic_cast pentru downcast cu sens
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

Un alt aspect esential al arhitecturii este sistemul personalizat de tratare a erorilor. In loc ca programul sa se blocheze atunci cand un client nu are destule jetoane, cand incearca sa acceseze un aparat deja ocupat sau cand un echipament necesita reparatii urgente, sistemul genereaza si arunca exceptii specifice. Aceste alerte sunt apoi interceptate elegant in scenariul principal de executie, permitand salii de jocuri sa isi continue activitatea fara intreruperi fatale, informand totodata utilizatorul cu privire la natura exacta a problemei.

Pentru ierarhia de aparate, am implementat mostenirea si polimorfismul in fisierele ArcadeMachine. Clasa de baza abstracta cu acelasi nume reprezinta fundatia ierarhiei proprii si contine datele esentiale, cum ar fi numele, costul, starea, impreuna cu atribute statice pentru contorizare. Din aceasta am derivat trei clase, mai exact RetroCabinet, VRStation si RacingSimulator. Fiecare mosteneste public ArcadeMachine, iar in constructorii lor se apeleaza explicit constructorul clasei de baza. Legat de polimorfism, am definit functia virtuala pura startGame care este specifica temei. Desi este apelata printr un pointer de baza, ea executa cod diferit in functie de aparat, de exemplu unitatea VR verifica curatenia, iar unitatea Retro verifica ecranul. Tot aici se gaseste constructorul virtual definit sub forma functiei clone, care permite copierea polimorfica a unui obiect fara sa ii stim tipul exact la executie. Pentru afisare am folosit o interfata non virtuala. Functia publica print apeleaza intern functia virtuala protejata printImpl, facand astfel operatorul de afisare sa functioneze perfect pentru clasele derivate prin pointeri de baza.

Clasa de gestiune indeplineste cerinta de a avea o clasa cu un atribut de tip pointer la o clasa de baza cu derivate. Aceasta foloseste o colectie standard de tip vector pentru a stoca pointeri catre aparate. Pentru gestiunea memoriei am implementat idiomul Copy and Swap. Deoarece clasa contine pointeri raw, am definit un constructor de copiere care face o dublare in profunzime folosind functia clone, o functie friend denumita swap si am suprascris operatorul de atribuire. Acest design asigura copierea corecta si previne scurgerile de memorie. Mai mult, in aceasta clasa am folosit operatiunea de downcast cu sens prin dynamic cast. In functia de mentenanta se parcurge vectorul de baze, iar pentru a accesa metoda de igienizare a castii existenta exclusiv la aparatele VR, codul face un dynamic cast catre pointerul clasei VRStation. Daca rezultatul este valid, se executa functia respectiva de nivel inalt.

Arhitectura de exceptii se regaseste in fisierul Exceptions, unde am creat o ierarhie independenta. Clasa de baza ArcadeException mosteneste clasa standard exception din C++. Din ea am derivat patru clase de erori complet distincte pentru a trata lipsa de jetoane, aparatele ocupate, configuratiile gresite si necesitatea de mentenanta. Pentru cerinta de utilizare cu sens, am folosit instructiunea throw direct in constructor. Daca se incearca crearea unui aparat cu un cost negativ, constructorul arunca direct o eroare de configuratie. Toate aceste exceptii sunt interceptate elegant in fisierul main, unde apelurile catre obiecte sunt incluse in blocuri try si catch pentru a testa comportamentul sistemului la rulare fara a il bloca.

In tot acest cod am aplicat riguros regulile cerute la final. Am definit atribute statice independente de obiectele individuale pentru a tine evidenta centralizata a incasarilor si a inventarului total. Am utilizat functii de nivel inalt in loc de setteri sau getteri clasici, astfel incat clasele isi manipuleaza datele intern prin actiuni cu sens, precum inceperea jocului sau degradarea conditiei fizice a aparatului. Nu in ultimul rand, am respectat regula utilizarii constante, marcand cu const la final absolut orice functie care doar citeste date, cum ar fi extragerea numelui sau afisarea inventarului, asigurand astfel compilatorul ca starea obiectului nu va fi modificata din greseala.

---

## Rulare si Output

Pentru a compila si rula programul in terminal:

```bash
masquerade@masquerade-ThinkPad-E16-Gen-2:~/Desktop/oop_tema2$ g++ *.cpp -o program
masquerade@masquerade-ThinkPad-E16-Gen-2:~/Desktop/oop_tema2$ ./program
