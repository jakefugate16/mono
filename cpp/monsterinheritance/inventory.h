#ifndef _MONSTER_PLAYERINV_H
#define _MONSTER_PLAYERINV_H

#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>
#include <functional>
#include "creature.h"

class Player;
class Item
{
public:
    enum Type : int
    {
        empty,
        healthpotion,
        strengthpotion,
        poison,
        max_items
    };

    //constructor. default to empty slot.
    Item(Type n = empty) : name{n} {}
    Item(int n): name{static_cast<Type>(n)} {}

    void use(Creature& creature)
    {
        switch(name)
        {
            case healthpotion:      useHealthPotion(creature);
            case strengthpotion:    useStrengthPotion(creature);
            case poison:            usePoison(creature);
        };
    }

    friend bool operator==(const Item& item1, const Item& item2){ return item1.name == item2.name; }
    friend bool operator==(const Item& item1, const Type t)     { return item1.name == t; }
    friend bool operator!=(const Item& item1, const Item& item2){ return !(item1 == item2); }
    friend bool operator!=(const Item& item1, const Type t)     { return !(item1 == t); }
    friend bool operator<(const Item& item1, const Item& item2) { return item1.name < item2.name; }
    friend bool operator<(const Item& item1, const Type t)      { return item1.name < t; }
    friend bool operator>(const Item& item1, const Item& item2) { return item1.name > item2.name; }
    friend bool operator>(const Item& item1, const Type t)      { return item1.name > t; }
    friend bool operator<=(const Item& item1, const Item& item2){ return !(item1 > item2); }
    friend bool operator<=(const Item& item1, const Type t)     {return !(item1 > t); } 
    friend bool operator>=(const Item& item1, const Item& item2){ return !(item1 < item2); }
    friend bool operator>=(const Item& item1, const Type t)     { return !(item1 < t); }

    void useHealthPotion(Creature& self);
    void useStrengthPotion(Creature& self);
    void usePoison(Creature& self);

    Type name{};
};

class Inventory
{
public:
    Inventory(std::size_t size = 2): m_inv(size) {} //Constructor

    //member functions
    void open(Player& self);     //open inventory menu

    //getters
    auto getItem_ptr(Item::Type item) { auto it = std::ranges::find(m_inv, Item{item}); return it;}
    int getItemCount(Item::Type item) const { return std::ranges::count(m_inv, Item{item}); }
    //int getItemCount(Item i) const { return std::ranges::count(m_inv, Item{static_cast<Item::Type>(i)}); }
    std::string_view getName(Item::Type item) const;
    std::string_view getName(int item) const;

    //setters
    void addItem(Item::Type item);
    void dropItem(Item::Type item){removeItem(item); }
    void removeItem(Item::Type item);
    //void useItem(Item::Type item, Creature& self);
    void expand(){ m_inv.insert(m_inv.begin(), Item{Item::empty}); }
    
    //output overload
    friend std::ostream& operator<<(std::ostream& out, const Inventory& items);

private:
    std::vector<Item> m_inv{};
};

#endif