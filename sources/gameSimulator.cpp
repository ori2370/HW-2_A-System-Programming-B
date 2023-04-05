#include "gameSimulator.hpp"

using namespace std;
using namespace ariel;

string gameSimulator::playTurn(const Card &c1, const Card &c2)
{
    if (c1.getRank() > c2.getRank())
    {
        return "p1";
    }
    else if (c1.getRank() < c2.getRank())
    {
        return "p2";
    }
    else
    {
        return "draw";
    }
}
