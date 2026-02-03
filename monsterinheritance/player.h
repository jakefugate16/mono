#ifndef _MONSTER_PLAYER_H
#define _MONSTER_PLAYER_H

#include <iostream>
#include <conio.h>
#include <string>
#include <string_view>
#include <chrono>
#include <thread>
#include "monster.h"
#include "creature.h"
#include "inventory.h"

class Monster;
class Player : public Creature
{
public:
    //constructor
    Player(std::string_view name)
        : Creature{name,'@', 20, 1, 0}, m_level{1}, m_flee{false}, inventory{}
    {}

    //getters
    int getLevel() const { return m_level; }
    bool hasWon() const { return m_level >= 20; }
    bool isFleeing() const { return m_flee; }
    std::string_view getName() const { return Creature::getName(); }

    //setters
    void levelUp(){ ++m_level; ++m_atk; }
    void switchFleeState() { (m_flee) ? (m_flee = false) : (m_flee = true); }
    void addItem(Item::Type item) {inventory.addItem(item);}

    friend std::ostream& operator<<(std::ostream& out, const Player& self);

    //member functions
    void turn(Monster& monster);
    void useItem(Item::Type item, Creature& self);
    void dropItem(Item& item);

    //public members
    Inventory inventory{};

private:
    int m_level{};
    bool m_flee{};
};

#endif