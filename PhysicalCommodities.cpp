#include "PhysicalCommodities.h"

PhysicalCommodities::PhysicalCommodities()
: Commodity(), storageCost_(0) {}

PhysicalCommodities::PhysicalCommodities(int quantityOwned, double initialPrice, int storageCost)
: Commodity(quantityOwned, initialPrice), storageCost_(storageCost) {}

int PhysicalCommodities::get_storageCost() const { return storageCost_; }
void PhysicalCommodities::set_storageCost(int storageCost) { storageCost_ = storageCost; }
