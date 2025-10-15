#ifndef GEMS_H
#define GEMS_H
#include <string>
#include "PhysicalCommodities.h"
#include "Commodity.h"


using namespace std;

class Gems: public PhysicalCommodities{
    private:
    string economicCycle;

    public:
    Gems();
    Gems(string economicCycle, int storageCost, int quantityOwned, string name, string type);

    bool Update();

    string get_economicCycle();
    void set_economicCycle(string economicCycle);    
};



#endif