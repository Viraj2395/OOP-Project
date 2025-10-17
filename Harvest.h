#ifndef HARVEST_H
#define HARVEST_H
#include <string>
#include "PhysicalCommodities.h"
#include "Commodity.h"

using namespace std;

class Harvest: public PhysicalCommodities{
    private:
    string season;

    public:
    Harvest();
    Harvest(string season, int storageCost, int quantityOwned, string name, string type);

    void Update(); 

    string get_season();
    void set_season(string season);    
};


#endif