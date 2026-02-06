#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

//This header-only Random namespace implements a self-seeding Mersenne Twister
//Requires c++17 or newer.
namespace Random
{
    //Returns a seeded Mersenne Twister
    inline std::mt19937 generate()
    {
        std::random_device rd{};
    

    //Create seed_seq with clock and 7 Random numbers from std::random_device
    std::seed_seq ss{
        static_cast<std::seed_seq::result_type>
         (std::chrono::steady_clock::now().time_since_epoch().count()),
            rd(), rd(), rd(), rd(), rd(), rd(), rd() };

    return std::mt19937{ss}; 
    }

    //global std::mt19937 object.
    //The inline keyword means we only have one global instance for our whole program.
    inline std::mt19937 mt{ generate() }; //generate a seeded std::mt19937 and copies it into our global object

    //Generate a random int between [min, max] (inclusive)
    inline int get(int min, int max)
    {
        return std::uniform_int_distribution{min, max}(mt);
    }

    //The following function templates can be used to generate random numbers
    //when min and/or max are not type int

    //Generate a random value between [min, max](inclusive)
    //* min and max have same type
    // * Return value has same type as min and max
    // * Supported types:
    // *    short, int, long, long long
    // *    unsigned short, unsigned int, unsigned long, or unsigned long long
    // Sample call: Random::get(1L, 6L);        //returns long
    // Sample call: Random::get(1u, 6u);        //returns unsigned int
    template <typename T>
    T get (T min, T max)
    {
        return std::uniform_int_distribution<T>{min, max}(mt);
    }

    //Generate a random value between [min, max] (inclusive)
    // * min and max can have different types
    // * Must explicitly specify return type as template type argument
    // * min and max will be converted to the return type
    // Sample call: Random::get<std::size_t>(0, 6);     //returns std::size_t
    // Sample call: Random::get<std::size_t>(0, 6u);    //returns std::size_t
    // Sample call: Random::get<std::int>(0, 6u);       //returns int

    template <typename R, typename S, typename T>
    R get(S min, T max)
    {
        return get<R>(static_cast<R>(min), static_cast<R>(max));
    }

    //quick 50/50 just using system clock
    bool coinFlip()
    {
        return static_cast<bool>(static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count()) & 1);
    }
}

#endif