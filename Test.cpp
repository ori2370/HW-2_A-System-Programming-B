#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
#include <stdexcept>

using namespace ariel;

TEST_CASE("intilizing the game")
{
    Player p1("Shlomo");
    Player p2("Dani");
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
    CHECK(p1.getPlayerName() == "Shlomo");
    CHECK(p2.getPlayerName() == "Dani");
    Game g(p1, p2);
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
}
TEST_CASE("checking for errors in same player and empty name")
{
    Player p1("Shlomo");
    Player p2("Shlomo");
    CHECK_THROWS(Player(""));
    CHECK_THROWS(Game(p1, p1));
    CHECK_NOTHROW(Game(p1, p2));
    CHECK(p1.getid() != p2.getid());
    CHECK(p1.getPlayerName() == p2.getPlayerName());
}

TEST_CASE("checking for decreasing number of cards in stack")
{
    Player p1("Shlomo");
    Player p2("Dani");
    Game g(p1, p2);
    for (int i = 0; i < 5; i++)
    {
        g.playTurn();
    }
    CHECK(p1.stacksize() <= 21);
    CHECK(p2.stacksize() <= 21);
    CHECK(p1.cardesTaken() > 0);
    CHECK(p2.cardesTaken() > 0);
}

TEST_CASE("players cannot have more than 52 cards or negative card_deck number")
{
    Player p1("Shlomo");
    Player p2("Dani");
    Game g(p1, p2);
    for (int i = 0; i < 25; i++)
    {
        g.playTurn();
    }
    CHECK_FALSE(p1.cardesTaken() > 52);
    CHECK_FALSE(p2.cardesTaken() > 52);
    CHECK_FALSE(p1.stacksize() < 0);
    CHECK_FALSE(p2.stacksize() < 0);
}

TEST_CASE("correct printing for winner")
{
    Player p1("Shlomo");
    Player p2("Dani");
    Game g(p1, p2);
    for (int i = 0; i < 25; i++)
    {
        g.playTurn();
    } // after playALL all the cards decks should be empty
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);

    if (p1.cardesTaken() > p2.cardesTaken())
    {
        CHECK(p1.isWinner());
        // should print: Shlomo won the game
    }
    else if (p1.cardesTaken() < p2.cardesTaken())
    {
        CHECK(p2.isWinner());
        // should print: Dani won the game
    }
    else
    {
        CHECK(p1.isWinner() == false);
        CHECK(p2.isWinner() == false);
        // should print:There is no winner
    }
}