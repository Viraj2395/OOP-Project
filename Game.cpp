#include "Game.h"
#include "Commodity.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include "Commodity.h"
// #include "Crypto.h"
#include "DigitalCommodities.h"
#include "Game.h"
#include "Gems.h"
#include "Harvest.h"
#include "PhysicalCommodities.h"
#include <cstdlib> 
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
    
void Game::initCommodities() {
    const int NumberOfCommodities = 6;
    commodities = new Commodity*[NumberOfCommodities];
    commodities[0] = new Harvest("Spring", 10, 0, "Wheat", "Harvest");
    commodities[1] = new Harvest("Summer", 10, 0, "Rice", "Harvest");
    commodities[2] = new Harvest("Autumn", 10, 0, "Corn", "Harvest");
    commodities[3] = new Gems("XYZ", 5, 0, "Gold", "Gem");
    commodities[4] = new Gems("XYZ", 5, 0, "Silver", "Gem");
    commodities[5] = new Gems("XYZ", 5, 0, "Platinum", "Gem");
    // commodities[6] = new Crypto("Uptrend", 2, 0, "Bitcoin", "Crypto");
}

void print_market_table(Commodity* commodities[], int n, int coins, int day); // Forward declaration

void Game::run() {
    const int NumberOfCommodities = 6;
    coins = 1000;
    day = 1;
    initCommodities();
    print_market_table(commodities, NumberOfCommodities, coins, day);

    // Clean up after game ends
    for (int i = 0; i < NumberOfCommodities; ++i) {
        if (commodities[i]) delete commodities[i];
    }
    delete[] commodities;
}
    void print_market_table(Commodity* commodities[], int n, int coins, int day) {
    // Clear terminal
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    std::cout << " TRADING GAME - Day" << day << " - coins: " << coins << "\n\n";
    std::cout << std::left << std::setw(12) << "Commodity"
              << std::right << std::setw(8) << "Price"
              << std::right << std::setw(12) << "N-Price"
              << std::right << std::setw(16) << "Quantity Owned"
              << std::right << std::setw(10) << "Type" << "\n";
    std::cout << "------------------------------------------------------------\n";

    for (int i = 0; i < n; ++i) {
        Commodity* c = commodities[i];
        double price = c->get_prices()[29]; 
        double prev = c->get_prices()[28];  
        double delta = price - prev;

    std::cout << std::left << std::setw(12) << c->get_name()
        << std::right << std::setw(8) << std::fixed << std::setprecision(2) << price
        << std::right << std::setw(8) << (delta >= 0 ? "+" : "") << std::fixed << std::setprecision(2) << delta
        << std::right << std::setw(16) << c->get_quantityOwned()
         << std::right << std::setw(10) << c->get_type() << "\n";
    }
    std::cout << "\nCommands: next | commodity | help | exit\n";
    std::string command;
    std::cout << "Enter command: ";
    std::cin >> command;

    if (command == "next") {
        // Update prices and advance day

        for (int i = 0; i < n; ++i) {
            commodities[i]->Update();
        }
        day++;
        print_market_table(commodities, n, coins, day);
    }
    else if (command == "commodity") {
        int choice = -1;

        if (!(std::cin>>choice))
        {
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            std::cout<< "invalide output.\n";
            print_market_table(commodities, n, coins, day);
            return;
        }

        if (choice == 0)    
        {
            print_market_table(commodities, n, coins, day);
            return;
        }
        if (choice < 1 || choice >n)
        {
            std::cout<< "invalid choice. \n";
            print_market_table(commodities, n, coins, day);
            return;
        }

        int idx = choice -1; // Making index according to array
        Commodity* item = commodities[idx];

        for (;;) // infinite loop until user types "back"
        {
            double price = item->get_prices()[29];
            int owned = item->get_quantityOwned();

            std::cout <<"\n[ " <<item->get_name() << "] Price: "<<std::fixed<< std::setprecision(2) <<price
            << " Owed: "<< owned
            << " Coins: " <<coins
            <<"\nActions : buy | sell | back\n ";
            
            std::string action;
            if (!(std::cin>>action))
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n'); //Discard the rest of the line
                std::cout<<"Invalid quantity. \n";
                continue;
            }
            if (action == "back")
            {
                //Return to the market view
                print_market_table(commodities, n, coins, day); // Re-render the market
                return; 
            }
            else if(action == "buy"){
                std::cout<< "Quantity to buy: ";
                int qty;
                if (!(std::cin>>qty))
                {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n'); //Discard the rest of the line
                    std::cout<<"Invalid quantity. \n";
                    continue;
                }
                if (qty<=0)
                {
                    std::cout<<"Quantity must be positive and more than 0. \n";
                    continue;
                }
                double cost = price*qty;
                if (cost>coins)
                {
                    std::cout << "Not enough coins (need " << std::fixed << std::setprecision(2)
                    << cost << ").\n";
                    continue;
                }
                //Buy Logic
                coins = coins - cost;
                item->set_quantityOwned(owned+qty);
                std::cout << "Bought " << qty << " " << item->get_name()
                << ". Coins left: " << std::fixed << std::setprecision(2) << coins << "\n";
            }
            else if (action == "sell")
            {
                std::cout<< "Quantity to sell: ";
                int qty;
                if (!(std::cin >> qty)) {              
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid quantity.\n";
                    continue; 
                }
                if (qty <= 0) {                         
                    std::cout << "Quantity must be positive.\n";
                    continue;
                }
                if (qty > owned) {                      
                 std::cout << "You only own " << owned << ".\n";
                 continue;
                }
                double revenue = price * qty;
                item->set_quantityOwned(owned - qty);
                coins = coins + revenue;
                std::cout << "Sold " << qty << " " << item->get_name()
                << ". Coins now: " << std::fixed << std::setprecision(2) << coins << "\n";

                
                
            }
            
            else{
                std::cout<<"Choose the correct option";
            }
            
            
        }

        
    }
    else if (command == "help") {
        // Show help message
    }
    else if (command == "exit") {
        return;
    }
    else {
        std::cout << "Unknown command. Try again.\n";
}
}


