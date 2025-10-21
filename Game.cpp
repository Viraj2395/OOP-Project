#include <iostream>
#include <cmath>
#include <iomanip>
#include "Crypto.h"
#include "Game.h"
#include "Gems.h"
#include "Harvest.h"
#include <cstdlib> 
#include <fstream> 

using namespace std;

void saveGame(const string& filename, int coins, int day, Commodity* commodities[], int n);
void loadGame(const string& filename, int& coins, int& day, Commodity* commodities[], int n);
void print_market_table(Commodity* commodities[], int n, int coins, int day);

// For case sensitive input
string getLowerCaseInput(){
    string input;
    cin>>input;
    for (char &c : input)
    {
        c = tolower(c);
    }
    return input;
}

//For clearing terminal
void clearScreen(){
    #ifndef _WIN32
        system("clear");
    #else
        system("cls");
    #endif
}

void showPortfolio(Commodity* commodities[], int n, int coins){
    double totalValue = coins;

    cout << "\n=== YOUR PORTFOLIO ===\n";
    cout << "Cash: " << coins << " coins\n\n";
    cout << std::left << std::setw(12) << "Commodity"
         << std::right << std::setw(8) << "Owned"
         << std::right << std::setw(12) << "Price"
         << std::right << std::setw(12) << "Value" << "\n";
    cout << "-------------------------------------\n";

    for (int i = 0; i < n; i++)
    {
        Commodity* c = commodities[i];
        int owned = c->get_quantityOwned();
        if (owned > 0)
        {
            double price = c->get_prices()[29];
            double value = owned * price;
            totalValue += value;

                cout << std::left << std::setw(12) << c->get_name()
                << std::right << std::setw(8) << owned
                << std::right << std::setw(12) << std::fixed << std::setprecision(2) << price
                << std::right << std::setw(12) << std::fixed << std::setprecision(2) << value << "\n";
        }
        
    }
    cout << "-------------------------------------\n";
    cout << "Total Portfolio Value: " << std::fixed << std::setprecision(2) << totalValue << " coins\n";
}
  
void showHelp() {
    cout << "\n=== TRADING GAME HELP ===\n";
    cout << "Available Commands:\n";
    cout << "  next      - Advance to next day and update prices\n";
    cout << "  commodity - Buy/sell specific commodities\n";
    cout << "  portfolio - View your current holdings and value\n";
    cout << "  save      - Save your game progress\n";        
    cout << "  load      - Load a saved game\n";             
    cout << "  help      - Show this help message\n";
    cout << "  exit      - Quit the game\n\n";
    
    cout << "Trading Tips:\n";
    cout << "- Buy low, sell high!\n";
    cout << "- Monitor price trends (N-Price column)\n";
    cout << "- Different commodities have different volatility\n";
    cout << "- Manage your risk by diversifying investments\n";
}

void handleBuy(Commodity* item, int &coins){
    double price = item->get_prices()[29];
    int maxAffordable = static_cast<int>(coins/price);
    //This will convert fraction in int ("Find how many whole items the playter can afford with 
    //Their current coins, given the item price, and store that as an integer. ")

    if (maxAffordable == 0)
    {
        cout<<"You cannot afford any units at current price. \n";
        return;
    }
    
    cout << "Current price: "<<std::fixed<<std::setprecision(2)<<price<<"\n";
    cout << "You can afford up to " << maxAffordable << " units. \n";
    cout << "Quantity to buy: ";

    string input;
    cin >> input;

    int qty;
    if (input == "max")
    {
        qty = maxAffordable;
    }
    else{
        try
        {
            qty = stoi(input);
        }
        catch(...)
        {
            cout << "Invalid quantity.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
    }
        if (qty <= 0)
        {
            cout<<"Quantity must be positive and none zero.\n";
            return;    
        }

        double cost = price * qty;
        if (cost>coins)
        {
            cout<<"Not enough coins (Need "<<std::fixed<<std::setprecision(2)<<cost<<", have "<<coins<<coins<<").\n";
            return;
        }
        coins -= cost;
        item->set_quantityOwned(item->get_quantityOwned() + qty);
        cout << "Bought " << qty << " " << item->get_name() 
        << " for " << std::fixed << std::setprecision(2) << cost 
        << " coins. Remaining: " << coins << " coins.\n";

    }

    void handleSell(Commodity* item, int& coins){
        double price = item->get_prices()[29];
        int owned = item->get_quantityOwned();

        if (owned == 0)
        {
            cout<<item->get_name() <<" is Not Found in your portfolio to sell.\n";
            return;
        }
        
            cout << "Current price: " << std::fixed << std::setprecision(2) << price << "\n";
    cout << "You own: " << owned << " units\n";
    cout << "Quantity to sell (or 'all' to sell everything): ";
    
    string input;
    cin >> input;
    
    int qty;
    if (input == "all") {
        qty = owned;
    } else {
        try {
            qty = stoi(input);
        } catch (...) {
            cout << "Invalid quantity.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
    }

        if (qty <= 0) {
        cout << "Quantity must be positive.\n";
        return;
    }
    
    if (qty > owned) {
        cout << "You only own " << owned << " units.\n";
        return;
    }

    double revenue = price * qty;
    item->set_quantityOwned(owned-qty);
    coins += revenue;

    cout << "Sold " << qty << " " << item->get_name()
    << " for " << std::fixed << std::setprecision(2) << revenue 
    << " coins. Total coins now: " << coins << "\n";
    }

    void showCommodityDetail(Commodity* item, int &coins, Commodity* commodities[], int n, int &day){
        while (true)
        {
            double price = item->get_prices()[29];
            int owned = item->get_quantityOwned();
            double prev = item->get_prices()[28];
            double delta = price - prev;
            double changePercent = (delta / prev) * 100;

            cout << "\n=== " << item->get_name() << " ===\n";
            cout << "Current Price: " << std::fixed << std::setprecision(2) << price << " coins\n";
            cout << "Daily Change: " << (delta >= 0 ? "+" : "") << std::fixed << std::setprecision(2) 
             << delta << " (" << (delta >= 0 ? "+" : "") << std::fixed << std::setprecision(1) 
             << changePercent << "%)\n";
            cout << "You Own: " << owned << " units\n";
            cout << "Your Cash: " << coins << " coins\n";
            cout << "Your Position Value: " << std::fixed << std::setprecision(2) << (owned * price) << " coins\n";
        
            item->MakeGraph();

            cout << "\nActions: buy | sell | back | market\n";
            cout << "Enter action: ";

            string action = getLowerCaseInput();

            if (action == "back")
            {
                print_market_table(commodities, n, coins, day);
                return;
            }

            if (action == "market") 
            {
            print_market_table(commodities, n, coins, day);
            return;
            }

            if (action == "buy") handleBuy(item, coins);

            else if (action == "sell") handleSell(item, coins);

            else cout << "Invalid action.\n";
            
            cout<< "Press enter to continue...";
            cin.ignore();
            cin.get();
        }
        
    }    

    void handleCommodityMenu(Commodity* commodities[], int n, int& coins, int& day){
        cout << "\nAvailable Commodities:\n";
    for (int i = 0; i < n; ++i) {
        cout << "  " << (i + 1) << ". " << commodities[i]->get_name() 
             << " (" << commodities[i]->get_type() << ")\n";
    }
    cout << "  0. Back to market\n";
    cout << "Choose commodity (0-" << n << "): ";
    
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input.\n";
        cout << "Press Enter to continue...";
        cin.get();
        handleCommodityMenu(commodities, n, coins, day);
        return;
    }
    
    if (choice == 0) return;
    if (choice < 1 || choice > n) {
        cout << "Invalid choice.\n";
        cout << "Press Enter to continue...";
        cin.get();
        handleCommodityMenu(commodities, n, coins, day); 
        return;
    }
    
    int idx = choice - 1;
    showCommodityDetail(commodities[idx], coins, commodities, n, day);
}
    void handleCommand(const string& command, Commodity* commodities[], int n, int& coins, int& day){
        if (command == "next")
        {
            for (int i = 0; i < n; i++)
            {
                commodities[i]->Update();
            }
            day++;
        }
        else if (command == "commodity")
        {
            handleCommodityMenu(commodities, n, coins, day);
            return;
        }
        else if (command == "help") {
            showHelp();
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (command == "portfolio") {
            showPortfolio(commodities, n, coins);
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (command == "save") {
            saveGame("savegame.txt", coins, day, commodities, n);
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
         }
        else if (command == "load") {
            loadGame("savegame.txt", coins, day, commodities, n);
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
            else if (command == "exit") {
            showPortfolio(commodities, n, coins);
            return;
        }
        else {
            cout << "Unknown command. Type 'help' for available commands.\n";
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
    }
    
    print_market_table(commodities, n, coins, day);
        
    }

    

    void saveGame(const string& filename, int coins, int day, Commodity* commodities[], int n) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "Error: Could not save game!\n";
        return;
    }
    
    file << coins << "\n";
    file << day << "\n";
    
    for (int i = 0; i < n; i++) {
        file << commodities[i]->get_name() << " "
             << commodities[i]->get_quantityOwned() << " "
             << commodities[i]->get_prices()[29] << "\n";
    }
    
    file.close();
    cout << "Game saved successfully!\n";
}

    void loadGame(const string& filename, int& coins, int& day, Commodity* commodities[], int n) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Could not load saved game!\n";
        return;
    }
    
    file >> coins;
    file >> day;
    
    string name;
    int quantity;
    double price;
    
    for (int i = 0; i < n; i++) {
        file >> name >> quantity >> price;
        
        for (int j = 0; j < n; j++) {
            if (commodities[j]->get_name() == name) {
                commodities[j]->set_quantityOwned(quantity);
                double* prices = commodities[j]->get_prices();
                prices[29] = price;
                break;
            }
        }
    }
    
    file.close();
    cout << "Game loaded successfully!\n";
}

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
    const int NumberOfCommodities = 7;
    commodities = new Commodity*[NumberOfCommodities];
    commodities[0] = new Harvest("Spring", 10, 0, "Wheat", "Harvest");
    commodities[1] = new Harvest("Summer", 10, 0, "Rice", "Harvest");
    commodities[2] = new Harvest("Autumn", 10, 0, "Corn", "Harvest");
    commodities[3] = new Gems("XYZ", 5, 0, "Gold", "Gem");
    commodities[4] = new Gems("XYZ", 5, 0, "Silver", "Gem");
    commodities[5] = new Gems("XYZ", 5, 0, "Platinum", "Gem");
    commodities[6] = new Crypto("Uptrend", 2, 0, "Ethereum", "Crypto");
}

    void print_market_table(Commodity* commodities[], int n, int coins, int day); 

    void Game::run() {
        const int NumberOfCommodities = 7;
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
    clearScreen(); 

    std::cout << " TRADING GAME - Day " << day << " - Coins: " << coins << "\n\n";
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
    

    std::cout << "\nCommands: next | commodity | portfolio | save | load | help | exit\n";
    std::string command;
    std::cout << "Enter command: ";
    
    command = getLowerCaseInput();

    handleCommand(command, commodities, n, coins, day);
}



























