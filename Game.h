#ifndef GAME_H
#define GAME_H
#include "Commodity.h"

using namespace std;

class Game{
    private:
    int coins;
    int day;
    Commodity** commodities;

    public:

    bool Buy(string commodity);
    bool Sell(string commodity);

    //constructors
    Game();
    Game(int coins, int day);

    void change_day(int day);

    //getters
    int get_day();
    int get_coins();

    //setters
    void set_day(int day);
    void set_coins(int coins);

};

#endif

