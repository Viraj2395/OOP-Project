#include "Game.h"
#include "Commodity.h"
//is change day and set day the same thing 

using namespace std;

    //constructors
    Game::Game(){
        this->day=0;
        this->coins=0;
    }
    
    Game::Game(int coins, int day){
        this->day=day;
        this->coins=coins;
    }

    void Game::change_day(int day){
        this->day=day;
    }

    //getters
    int Game::get_day(){
        return day;
    }

    int Game::get_coins(){
        return coins;
    }

    //setters
    void Game::set_day(int day){
        this->day=day;
    }
    
    void Game::set_coins(int coins){
        this->coins=coins;
    }


