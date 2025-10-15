#ifndef PHYSICALCOMMODITIES_H
#define PHYSICALCOMMODITIES_H
#include "Commodity.h"
#include <string>

using namespace std;

class PhysicalCommodities : public Commodity{
    protected:
    int storageCost;

    public:

    PhysicalCommodities();
    PhysicalCommodities(int storageCost, int quantityOwned, string name, string type);

    int get_storageCost();
    void set_storageCost(int storageCost);
};

#endif