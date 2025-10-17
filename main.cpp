#include <iostream>
#include <cmath>
#include <iomanip>
#include "Commodity.h"
#include "Crypto.h"
#include "DigitalCommodities.h"
#include "Game.h"
#include "Gems.h"
#include "Harvest.h"
#include "PhysicalCommodities.h"

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
              << std::right << std::setw(8) << "ΔPrice"
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
        for (int i = 0; i < NumberOfCommodities; ++i) {
            commodities[i]->Update();
        }
        day++;
        print_market_table(commodities, NumberOfCommodities, coins, day);
    }
    else if (command == "commodity") {
        // Handle commodity trading logic
    }
    else if (command == "help") {
        // Show help message
    }
    else if (command == "exit") {
        // Exit the program
        break;
    }
    else {
        std::cout << "Unknown command. Try again.\n";
}
}

int main() {
    const int NumberOfCommodities = 9;
    int coins = 1000;
    int day = 1;
    Commodity* commodities[NumberOfCommodities];

    commodities[0] = new Harvest("Spring", 10, 0, "Wheat", "Harvest");
    commodities[1] = new Harvest("Summer", 10, 0, "Rice", "Harvest");
    commodities[2] = new Harvest("Autumn", 10, 0, "Corn", "Harvest");
    commodities[3] =
        new Gems("XYZ", 5, 0, "Gold",
                 "Gem");  // I am not sure what to write instead of xyz
    commodities[4] = new Gems("XYZ", 5, 0, "Silver", "Gem");
    commodities[5] = new Gems("XYZ", 5, 0, "Platinum", "Gem");
    commodities[6] = new Crypto("Uptrend", 2, 0, "Bitcoin", "Crypto");


  
    return 0;
}