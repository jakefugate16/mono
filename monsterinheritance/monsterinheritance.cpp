#include <iostream>
#include <string>
#include <string_view>
#include <iomanip>
#include <chrono>
#include <thread>
#include "controls.h"
#include "random.h"
#include "player.h"
#include "monster.h"

void Battle(Player& player, Monster& monster)
{
    using namespace std::chrono_literals;
    //player attacks first
    if(Random::coinFlip())
    {
        while(true)
        {
            player.turn(monster);

            if(monster.isPoisoned())
                monster.reduceHealth(1);

            if(monster.isDead())
                break;
            if( player.isFleeing() ) 
                {
                    player.switchFleeState();
                    return;
                }

            monster.turn(player);

            if(player.isPoisoned())
                player.reduceHealth(1);

            if(player.isDead())
                return;
        }
    }
    //monster attacks first
    else
    {
        while(true)
        {
            monster.turn(player);
            if(monster.isPoisoned())
                monster.reduceHealth(1);

            if (player.isDead())
                return;

            player.turn(monster);
            if(player.isPoisoned())
            {
                std::cout << "Player takes " << 1 <<  "damage.\n";
                player.reduceHealth(1);
            }

            if(monster.isDead())
                break;

            if( player.isFleeing() )
            {
                player.switchFleeState();
                return;
            }
        }
    }

    if(monster.isDead())
    {
        std::cout << "\n" << monster.getName() << " has died.\n";
        std::this_thread::sleep_for(1s);
        std::cout << monster.getName() << " had " << monster.getGold() << " gold.\n";
        player.addGold(monster.getGold());

        if(Random::get(0, 2) == 0) //33% chance to drop item
            player.inventory.addItem(monster.dropItem());
        player.levelUp();
        //std::this_thread::sleep_for(1s);
        std::cout << "You now have " << player.getGold() << " gold.\n";
        std::this_thread::sleep_for(2s);
        std::cout << "You are now level " << player.getLevel() << "!\n";
        std::this_thread::sleep_for(2s);
    }
}

void encounter(Player& player)
{
    using namespace std::chrono_literals;
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //clear screen

    //player encounters
    Monster monster{ Monster::getRandomMonster() };
    std::cout << "You have encountered a(n) " << monster.getName() << ".\n";

    //player decides to fight or flee
    std::cout << "(R)un or (F)ight!?:\n";
    
    Controls::g_input = 0;
    while(!(Controls::g_input=='R' || Controls::g_input=='r' || Controls::g_input=='f' || Controls::g_input=='F' || Controls::g_input=='I'|| Controls::g_input=='i'))  //wait for valid input
        Controls::g_input = getch();

    //open inventory
    if(Controls::g_input=='I' || Controls::g_input=='i')
    {
        player.inventory.open(player);
    }

    //fight option
    else if(Controls::g_input=='f' || Controls::g_input=='F')
    {
        std::cout << "\nPlayer fights!\n";
        std::this_thread::sleep_for(1s);
        Battle(player, monster);
        //temporary buffs expire after encounter
        player.setWeaponPoison();
        player.setStrengthened();
        return;
    }

    //run option
    else if(Controls::g_input == 'R' || Controls::g_input =='r'){
        //player succeeds in fleeing 50/50 odds
        if( Random::coinFlip() )
        {
            std::cout << "You escaped!";
            std::this_thread::sleep_for(2s);
            return; 
        }
        //player does not succeed in fleeing
        else
        {
            std::cout << "You could not escape!\n\n";
            Battle(player, monster);
        }
    }
}

int main()
{
    while(!(Controls::g_input == 3 || Controls::g_input == 7)) //esc or ctrl-c
    {
        //character creation    
        std::string player_name{};
        std::cout << "Enter your name: ";
        std::getline(std::cin, player_name);
    
        Player player{player_name};
        std::cout << "Welcome " << player.getName() << "!\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        while( !(player.isDead() || player.hasWon()) )
            encounter(player);

        //end game
        if(player.isDead())
            std::cout << "\nYou have died.\nPress enter to exit.";
        if(player.hasWon())
            std::cout << "\nYou have won!\nPress enter to exit.";
    
        std::string str{};
        std::getline(std::cin, str);
    
        return 0;
    }
}