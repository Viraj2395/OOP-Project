#ifndef DIGITALCOMMODITIES_H
#define DIGITALCOMMODITIES_H
#include "Commodity.h"
#include <string>

using namespace std;

class DigitalCommodities : public Commodity{
    protected:
    int transactionFee;

    public:
    DigitalCommodities();
    DigitalCommodities(int transactionFee, int quantityOwned, string name, string type);

    int get_transactionFee();
    void set_transactionFee(int transactionfee);
};

#endif