#include <thread>
#include <iostream>
#include <chrono>
#include "random.h"
#include "monster.h"
#include "player.h"
#include "controls.h"

void Player::turn(Monster& monster)
{
    using namespace std::chrono_literals;
    {
        std::cout << Creature::getName() << "'s turn\n\n";
        std::this_thread::sleep_for(2s);
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

        std::cout << *this << std::endl;
        std::cout << monster << "\n\n";

        Controls::g_input = 0;
        std::cout << "Select action\na: attack    r: run\n";
    
        while (!(Controls::g_input=='a' || Controls::g_input=='A' || Controls::g_input=='r' || Controls::g_input=='R' || Controls::g_input=='I' || Controls::g_input=='i'))
            Controls::g_input = getch();

        if(Controls::g_input == 'i' || Controls::g_input == 'I')
            this->inventory.open(*this);

        if(Controls::g_input == 'r' || Controls::g_input == 'R')
        {
            if(Random::coinFlip())  //player flees
            {
                switchFleeState();
                std::cout << "\nfled successfully!\n";
                std::this_thread::sleep_for(1s);
                return;
            }
            else    //player fails flight and costs a turn
            {
                std::cout << "Failed to flee.\n";
                std::this_thread::sleep_for(1s);
                return;
            }
        }
        else
        {
            std::cout << getName() << " hits " << monster.getName() << " for " << getAtk() << " damage!\n";
            monster.reduceHealth(getAtk());
            std::this_thread::sleep_for(1s);
        }

        return;
    }
}

void Player::useItem(Item::Type item, Creature& self)
{
    if(inventory.getItemCount(item))
    {
        switch((*inventory.getItem_ptr(item)).name)
        {
            case Item::healthpotion:      self.addHealth(5); // add 5hp for health potion
            case Item::poison:            self.poisonWeapon();
            case Item::strengthpotion:    self.Strengthen();
        };

        inventory.removeItem(item);
    }

    else
        std::cout << "No " << Item{item}.name << " in inventory";
}

/*
void Player::dropItem(Inventory::Item item)
{

}
*/

std::ostream& operator<<(std::ostream& out, const Player& self)
{
    out << static_cast<const Creature&>(self);
    return out;
}
