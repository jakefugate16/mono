#include <iostream>
#include <chrono>
#include <thread>
#include "player.h"
#include "monster.h"

void Monster::turn(Player& player)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
        std::cout << player << std::endl;
        std::cout << *this << "\n\n\n\n";

    player.reduceHealth(getAtk());

    std::cout << getName() << " attacks " << player.getName() << " for " << getAtk() << " damage!\n";
    std::this_thread::sleep_for(2s);
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

std::ostream& operator<<(std::ostream& out, const Monster& self)
{
    out << static_cast<const Creature&>(self);
    return out;
}
