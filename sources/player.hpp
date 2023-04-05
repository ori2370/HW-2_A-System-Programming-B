#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "card.hpp"
#include <string>
using namespace std;
namespace ariel
{
    class Player
    {
    private:
        int cards_won;
        int stack_size;
        string player_name;
        int id;
        static int next_id;

    public:
        Player(string name);
        int cardesTaken();
        int stacksize();
        void addWin();
        void setStackSize(int size);
        string getPlayerName();
        int getid();
        void decreaseStackSize() { this->stack_size--; }
    };
}
#endif
