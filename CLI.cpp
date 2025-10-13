#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <limits>
#include <sstream>

struct Row
{
    std::string name;
    std::string type;
    double price;
    double prev;
    int qty;
};

static std::mt19937& rng() {
    static thread_local std::mt19937 gen{ std::random_device{}() };
    return gen;
}

double pct_step_for(const std::string &type){
    if(type == "Harvest") return 0.010;
    if(type == "Gem") return 0.015;
    if(type == "Crypto") return 0.06;
    if (type == "Digital") return 0.012;
    return 0.015;
}

void next_day(std::vector<Row>& rows) {
    for (auto& r : rows) {
        r.prev = r.price;

        const double step = pct_step_for(r.type);
        std::normal_distribution<double> dist(0.0, step);

        const double factor = 1.0 + dist(rng());
        r.price = std::max(0.1, r.price * factor);
    }
}

double delta(const Row& r){
    return r.price - r.prev;
}

void P_Table(const std::vector<Row>& rows, double coins, int day){
    using std::setw;
    const int Wc=12, Wp = 12, Wd=10, Wq=16, Wt=10;

    std::cout<< "\n TRADING GAME - Day" <<day<<" - coins: " << coins << "\n\n";

    std::cout << std::left  << setw(Wc) << "Commodity"
          << std::right << setw(Wp) << "Price"
          << std::right << setw(Wd) << "ΔPrice"
          << std::right << setw(Wq) << "Quantity Owned"
          << std::right << setw(Wt) << "Type" << "\n";

    std::cout << std::string(Wc+Wp+Wd+Wq+Wt, '-') << "\n";

        
    for(const auto& r : rows){
        double d = r.price - r.prev;
        std::ostringstream dss;
        dss.setf(std::ios::fixed); dss <<std::setprecision(2) << (d>= 0 ? "+" : "") <<d;

            std::cout << std::left  << setw(Wc) << r.name
              << std::right << setw(Wp) << r.price
              << std::right << setw(Wd) << dss.str()
              << std::right << setw(Wq) << r.qty
              << std::right << setw(Wt) << r.type
              << "\n";
    }
}

void clear_cin(){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

Row* find_by_name(std::vector<Row>& rows, std::string name) {
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    for (auto& r : rows) {
        std::string n = r.name;
        std::transform(n.begin(), n.end(), n.begin(), ::tolower);
        if (n == name) return &r;
    }
    return nullptr;
}

int main() {
  
    std::vector<Row> rows = {
        {"Wheat",    "Harvest", 120.0, 120.0, 0},
        {"Rice",     "Harvest", 110.0, 110.0, 0},
        {"Corn",     "Harvest", 100.0, 100.0, 0},
        {"Gold",     "Gem",    2400.0, 2400.0, 0},
        {"Silver",   "Gem",      30.0,   30.0, 0},
        {"Platinum", "Gem",     950.0,  950.0, 0},
        {"Bitcoin",  "Crypto", 45000.0,45000.0,0},
        {"Stock",    "Digital",  210.0, 210.0, 0},
        {"Shares",   "Digital",  200.0, 200.0, 0}
    };

    double coins = 10000.0;   
    int day = 1;


    for (;;) {
        P_Table(rows, coins, day);

        std::cout << "\nCommands: next | commodity | help | exit\n> ";
        std::string cmd;
        if (!(std::cin >> cmd)) break;
        std::string lc = cmd; std::transform(lc.begin(), lc.end(), lc.begin(), ::tolower);

        if (lc == "exit") {
            std::cout << "Goodbye!\n";
            break;
        }
        else if (lc == "help") {
            std::cout << "next       -> advance a day and update prices\n"
                         "commodity  -> open a submenu for a specific commodity (buy/sell)\n"
                         "exit       -> quit\n";
        }
        else if (lc == "next") {
            next_day(rows);
            ++day;
        }
        else if (lc == "commodity") {
            std::cout << "Enter commodity name (e.g., Wheat, Gold, Bitcoin, Shares): ";
            std::string name; 
            if (!(std::cin >> name)) { clear_cin(); continue; }
            Row* r = find_by_name(rows, name);
            if (!r) { std::cout << "Not found.\n"; continue; }

            for (;;) {
                std::cout << "\n[" << r->name << "] price=" << std::fixed << std::setprecision(2) << r->price
                          << "  owned=" << r->qty
                          << "  coins=" << coins
                          << "  actions: buy | sell | back\n> ";
                std::string act; 
                if (!(std::cin >> act)) { clear_cin(); break; }
                if (act == "back") break;

                if (act == "buy") {
                    std::cout << "Quantity to buy: ";
                    int q; if (!(std::cin >> q)) { clear_cin(); std::cout << "Invalid.\n"; continue; }
                    if (q <= 0) { std::cout << "Must be positive.\n"; continue; }
                    double cost = r->price * q;
                    if (cost > coins) { std::cout << "Not enough coins (need " << cost << ").\n"; continue; }
                    coins -= cost; r->qty += q;
                    std::cout << "Bought " << q << " " << r->name << ". Coins left: " << coins << "\n";
                }
                else if (act == "sell") {
                    std::cout << "Quantity to sell: ";
                    int q; if (!(std::cin >> q)) { clear_cin(); std::cout << "Invalid.\n"; continue; }
                    if (q <= 0) { std::cout << "Must be positive.\n"; continue; }
                    if (q > r->qty) { std::cout << "You own only " << r->qty << ".\n"; continue; }
                    double rev = r->price * q;
                    r->qty -= q; coins += rev;
                    std::cout << "Sold " << q << " " << r->name << ". Coins now: " << coins << "\n";
                }
                else {
                    std::cout << "Unknown action.\n";
                }
            }
        }
        else {
            std::cout << "Unknown command. Type 'help' for options.\n";
        }
    }

    return 0;
}
