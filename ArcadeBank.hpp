#ifndef ARCADE_BANK_HPP
#define ARCADE_BANK_HPP

class ArcadeBank {
private:
    int globalRevenue;
        ArcadeBank() : globalRevenue(0) {} 

public:
    ArcadeBank(const ArcadeBank&) = delete;
    ArcadeBank& operator=(const ArcadeBank&) = delete;

    static ArcadeBank& getInstance() {
        static ArcadeBank instance;
        return instance;
    }

    void addRevenue(int amount) { globalRevenue += amount; }
    int getGlobalRevenue() const { return globalRevenue; }
};

#endif