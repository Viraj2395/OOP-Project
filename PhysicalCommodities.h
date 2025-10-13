#ifndef PHYSICALCOMMODITIES_H
#define PHYSICALCOMMODITIES_H

#include "Commodity.h"

class PhysicalCommodities : public Commodity {
 protected:
  int storageCost_;

 public:
  PhysicalCommodities();
  PhysicalCommodities(int quantityOwned, double initialPrice, int storageCost);

  int get_storageCost() const;
  void set_storageCost(int storageCost);
};

#endif
