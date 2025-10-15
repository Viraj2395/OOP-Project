#include "PhysicalCommodities.h"
#include "Commodity.h"
#include <string>

using namespace std;

PhysicalCommodities::PhysicalCommodities():Commodity(){
    this->storageCost=0;
}
PhysicalCommodities::PhysicalCommodities(int storageCost, int quantityOwned, string name, string type):Commodity(quantityOwned,name,type){
    this->storageCost=storageCost;
}

int PhysicalCommodities::get_storageCost(){
    return storageCost;
}

void PhysicalCommodities::set_storageCost(int storageCost){
    this->storageCost=storageCost;
}