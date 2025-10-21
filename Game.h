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
    bool Sell(string commodity);//Is it okay If I remove this

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
    
    // Setup commodities array
    void initCommodities();

    // Main game loop
    void run();

};


// Forward declaration to help functions
void showPortfolio(Commodity* commodities[], int n, int coins);
void showHelp();
void handleCommand(const string& command, Commodity* commodities[], int n, int& coins, int& day);


#endif

