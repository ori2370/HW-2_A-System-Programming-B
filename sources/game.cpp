#include "game.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
using namespace std;
using namespace ariel;

Game::Game(Player &p1, Player &p2) : p1(p1), p2(p2), turn_oprator()
{
    if (p1.getid() == p2.getid())
    { // checking by unique if and not name as two persons can have the same name
        throw invalid_argument("players cannot play himself");
    }
    for (int i = 1; i <= 13; i++)
    {
        card_deck.push_back(Card(i, "hearts"));
        card_deck.push_back(Card(i, "clubs"));
        card_deck.push_back(Card(i, "spades"));
        card_deck.push_back(Card(i, "diamonds"));
    }
    mixCards();

    for (int i = 0; i < 26; i++)
    {
        p1_stack.push_back(card_deck.back());
        card_deck.pop_back();
        p2_stack.push_back(card_deck.back());
        card_deck.pop_back();
    }
    p1.setStackSize(p1_stack.size());
    p2.setStackSize(p2_stack.size());
}
// took the mixing cards method from this https://www.techiedelight.com/shuffle-vector-cpp/
// from the website above: 3. Using Fisher-Yates Shuffle Algorithm
void Game::mixCards()
{
    srand(time(NULL));
    unsigned int n = card_deck.size();
    unsigned int i = 0;
    for (i = 0; i < n - 1; i++)
    {
        unsigned int j = i + static_cast<unsigned int>(rand()) % (n - i);
        swap(card_deck[i], card_deck[j]);
    }
}

void Game::playTurn()
{
    string turn_result = turn_oprator.playTurn(p1_stack.back(), p2_stack.back());

    if (turn_result == "p1")
    {
        last_turn_result = "" + p1.getPlayerName() + " played " + p1_stack.back().toString() + " " + p2.getPlayerName() + " played " + p2_stack.back().toString() + ". " + p1.getPlayerName() + " wins.";
        p1.addWin();
        p1_stack.pop_back();
        p2_stack.pop_back();
        p1.decreaseStackSize();
        p2.decreaseStackSize();
        turn_results.push_back(last_turn_result);
    }
    else if (turn_result == "p2")
    {
        last_turn_result = "" + p1.getPlayerName() + " played " + p1_stack.back().toString() + " " + p2.getPlayerName() + " played " + p2_stack.back().toString() + ". " + p2.getPlayerName() + " wins.";
        p2.addWin();
        p1_stack.pop_back();
        p2_stack.pop_back();
        p1.decreaseStackSize();
        p2.decreaseStackSize();
        turn_results.push_back(last_turn_result);
    }
    else
    {
        string result = playdraw();
        if (result == "p1")
        {
            p1.addWin();
            p1.addWin();
        }
        else if (result == "p2")
        {
            p2.addWin();
            p2.addWin();
        }
        else if (result == "draw")
        {
        }
    }
}

string Game::playdraw()
{
    return "draw";
}

void Game::printLastTurn()
{
    cout << last_turn_result << endl;
}

void Game::playAll()
{
}

void Game::printWiner()
{
    if (p1.cardesTaken() > p2.cardesTaken())
    {
        cout << p1.getPlayerName() << " won the game" << endl;
    }
    else if (p1.cardesTaken() < p2.cardesTaken())
    {
        cout << p2.getPlayerName() << " won the game" << endl;
    }
    else
    {
        throw invalid_argument("there is no winner");
    }
}

void Game::printLog()
{
    for (unsigned int i = 0; i < turn_results.size(); i++)
    {
        cout << turn_results[i] << endl;
    }
}

void Game::printStats()
{
}
