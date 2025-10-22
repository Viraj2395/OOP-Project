#ifndef CRYPTO_H
#define CRYPTO_H
#include <string>
#include "DigitalCommodities.h"
#include "Commodity.h"

using namespace std;

class Crypto: public DigitalCommodities{
    private:
    string trend; //uptrend or downtrend

    public:
    Crypto();
    Crypto(string trend, int transactionFee, int quantityOwned, string name, string type);

    void Update();

    // Getters and Setters
    string get_trend();
    void set_trend(string trend);    
};

#endif