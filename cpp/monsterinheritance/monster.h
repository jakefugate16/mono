#ifndef _MONSTER_MONSTER_H
#define _MONSTER_MONSTER_H

#include "creature.h"
#include "inventory.h"
#include "monster.h"
#include "player.h"
#include "random.h"

class Player;
class Monster : public Creature
{
public:
    enum Type{orc, dragon, slime, max_types};

    Monster(Type type)
        : Creature{monsterData[type]}
    {}

    static Type getRandomMonster(){ return static_cast<Type>(Random::get(orc, max_types - 1)); }

    Item::Type dropItem(){ return static_cast<Item::Type>(Random::get(1, 3)); }
    void turn(Player& player);

    friend std::ostream& operator<<(std::ostream& out, const Monster& self);

private:
    static inline Creature monsterData[]
    {
        {"orc", 'o', 4, 2, 25},
        {"dragon", 'D', 20, 4, 100},
        {"slime", 's', 1, 1, 10}
    };
};

#endif