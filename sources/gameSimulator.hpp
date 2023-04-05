#ifndef GAMESIMULATOR_HPP
#define GAMESIMULATOR_HPP
#include "card.hpp"
#include "player.hpp"
#include <string>

using namespace std;
namespace ariel
{
    class gameSimulator
    {
    public:
        gameSimulator(){};
        string playTurn(const Card &c1, const Card &c2);
    };
}

#endif