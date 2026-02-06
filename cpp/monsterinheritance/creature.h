#ifndef _MONSTER_CREATURE_H
#define _MONSTER_CREATURE_H

#include <iostream>
#include <string>
#include <string_view>
#include <iomanip>

class Creature
{
public:

    //Constructor
    Creature(std::string_view name, char symbol = 'a', int health = 10, int atk = 1, int gold = 0)
        : m_name{name}, m_symbol{symbol}, m_health{health}, m_atk{atk}, m_gold{gold}, m_poisoned{false}, m_weaponpoisoned{false}, m_strengthened{false}
    {}

    //member setters
    void addHealth(int hp){ m_health += hp;}
    void poisonWeapon(){ setWeaponPoison(); }
    void Strengthen(){ setStrengthened(); }
    void reduceHealth(int dmg){ m_health -= dmg; }
    void addGold(int amount){ m_gold += amount; }

    void setPoisoned(){ m_poisoned = (m_poisoned ? false : true); }
    void setWeaponPoison(){ m_weaponpoisoned = (m_weaponpoisoned ? false : true); }
    void setStrengthened(){ m_strengthened = (m_strengthened ? false : true); }


    //member getters
    std::string_view getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    int getHealth() const { return m_health; }
    int getAtk() const { return m_atk; }
    int getGold() const { return m_gold; }

    bool isDead() const { return m_health <= 0; }
    bool isPoisoned() const { return m_poisoned; }
    bool isWeaponPoisoned() const { return m_weaponpoisoned; }
    bool isStrengthened() const { return m_strengthened; }

    //member functions
    friend inline std::ostream& operator<<(std::ostream& out, const Creature& self);

protected:
    std::string m_name{};
    char m_symbol{};
    int m_health{};
    int m_atk{};
    int m_gold{};
    bool m_poisoned{};
    bool m_weaponpoisoned{};
    bool m_strengthened{};
};

inline std::ostream& operator<<(std::ostream& out, const Creature& self)
{
    out << self.m_name << std::setw(8) << std::left << "  HP: " << self.m_health
    << std::setw(8) << std::right << "ATK: " << self.m_atk;
    
    return out;  
}
#endif