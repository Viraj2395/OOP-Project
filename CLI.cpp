#include "Commodity.h"
#include "Harvest.h"
#include "Gems.h"
#include "Crypto.h"
#include "DigitalCommodities.h"
#include "Game.h"
#include "Harvest.h"
#include "PhysicalCommodities.h"

const int NumberOfCommodities = 9;
Commodity * commodities[NumberOfCommodities];

commodities[0] = new Harvest("Spring", 10, 0, "Wheat", "Harvest");
commodities[1] = new Harvest("Summer", 10, 0, "Rice", "Harvest");
commodities[2] = new Harvest("Autumn", 10, 0, "Corn", "Harvest");
commodities[3] = new Gems("XYZ", 5, 0, "Gold", "Gem");//I am not sure what to write instead of xyz
commodities[4] = new Gems("XYZ", 5, 0, "Silver", "Gem");
commodities[5] = new Gems("XYZ", 5, 0, "Platinum", "Gem");
commodities[6] = new Crypto("Uptrend", 2, 0, "Bitcoin", "Crypto");
commodities[7] = new DigitalCommodities(1, 0, "Stock", "Digital");
commodities[8] = new DigitalCommodities(1, 0, "Shares", "Digital");

for (int i = 0; i < NumberOfCommodities ; ++i) {
    std::cout << commodities[i]->get_name() << " (" << commodities[i]->get_type() << ") - Owned: " << commodities[i]->get_quantityOwned() << "\n";
    
}

