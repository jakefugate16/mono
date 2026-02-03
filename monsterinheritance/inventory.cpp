#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>
#include <string_view>
#include <unordered_map>
#include "inventory.h"
#include "player.h"
#include "controls.h"

std::string_view Inventory::getName(Item::Type item) const
{
    switch(item)
    {
        case Item::empty:             return "empty";
        case Item::healthpotion:      return "Health Potion";
        case Item::poison:            return "Poison";
        case Item::strengthpotion:    return "Strength Potion";
        default:                      return "empty";
    };
    
    return "empty";
}

void Inventory::addItem(Item::Type item)
{ 
    auto iter = std::ranges::find(m_inv, Item::empty);
    if(iter != m_inv.end())
    {
        *iter = Item{item};
        std::ranges::sort(m_inv);
    }
    else
        std::cout << "Inventory full." << '\n';
}

void Inventory::removeItem(Item::Type item)
{
    *getItem_ptr(item) = Item{};
    std::ranges::sort(m_inv);
}

void Item::useHealthPotion(Creature& self)
{
    const int hp{5};
    std::cout << self.getName() << " used health potion for " << hp << " hp.\n";
    self.addHealth(hp);
}

void Item::useStrengthPotion(Creature& self)
{
    std::cout << self.getName() << " used a strength potion.\n";
    self.setStrengthened();
}

void Item::usePoison(Creature& self)
{
    std::cout << self.getName() << " applied poison to thier weapon.\n";
    self.setWeaponPoison();
}

std::ostream& operator<<(std::ostream& out, const Inventory& items)
{
    for(int i{static_cast<int>(Item::empty)}; i < static_cast<int>(Item::max_items); ++i)
        if( items.getItemCount(static_cast<Item::Type>(i)) )
            out << items.getName(static_cast<Item::Type>(i)) << " x" << items.getItemCount(static_cast<Item::Type>(i)) << '\n';

    return out;
}

void Inventory::open(Player& self)
{
    Controls::g_input = 0;

    while(!(Controls::g_input == 'i' || Controls::g_input =='I'))
    {
        std::cout << *this << '\n';
        std::cout << "U: use item\nQ: drop item\nI: exit\n";

        while(!(Controls::g_input == 'U' || Controls::g_input == 'u' || Controls::g_input == 'Q' || Controls::g_input == 'q')) //wait for valid input
            Controls::g_input = getch();

   
        std::unordered_map<char, int> options = {}; //will store options since number of options can't be known somehow beforehand

        //display options
        if( std::ranges::find_if(m_inv, [](Item i){return i != Item::empty; }) != m_inv.end() )   //will search sorted array for first instance of item
        {
            for(int item{0}, count{1}; count < static_cast<int>(Item::max_items); ++item)   //will print item menu
            {
                if(getItemCount(static_cast<Item::Type>(item)))     //only displays non-zero amount of items
                {
                    options.insert({static_cast<char>(count + '0'), item}); //store count as key ('1', '2', '3') store item as value 
                    std::cout << count << ". " << getName((static_cast<Item::Type>(item))) << " x" << getItemCount(static_cast<Item::Type>(item)) << '\n';
                    ++count;
                }
            }
        }
        else
        {
            std::cout << "Inventory is empty\n";
        }
        //use an item in inventory
        if(Controls::g_input == 'u' || Controls::g_input == 'U')
        {
            std::cout << "Select Item to use.\n";
            while(Controls::g_input < '1' || Controls::g_input > (std::ssize(options) + '0'))
                Controls::g_input = getch();

            std::cout << "Using " << getName(static_cast<Item::Type>((*options.find(Controls::g_input)).second)) << std::endl;
            self.useItem(static_cast<Item::Type>((*options.find(Controls::g_input)).second), self);
        }
        //drop an item from inventory
        else if(Controls::g_input == 'q' || Controls::g_input == 'Q')
        {
            if( std::ranges::find_if(m_inv, [](Item i){return i != Item::empty; }) != m_inv.end() )
                std::cout << "Inventory is empty.\n";
            else
            {
                std::cout << "Select an item to drop.\n";

                while(Controls::g_input < '1' || Controls::g_input > (std::ssize(options) + '0'))
                    Controls::g_input = getch();

                std::cout << "Dropping " << getName(static_cast<Item::Type>((*options.find(Controls::g_input)).second)) << std::endl;
                dropItem(static_cast<Item::Type>((*options.find(Controls::g_input)).second));
            }
        }
    }
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
}
