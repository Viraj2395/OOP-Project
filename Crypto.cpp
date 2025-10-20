#include <string>
#include "Crypto.h"
#include "Commodity.h"
#include "DigitalCommodities.h"

using namespace std;

    Crypto::Crypto():DigitalCommodities(){
        this->trend="";
    }
    
    Crypto::Crypto(string trend, int transactionFee, int quantityOwned, string name, string type): DigitalCommodities(transactionFee, quantityOwned, name, type, (double[3]){1500,0.05, 0.4}){
        this->trend=trend;
    }

    bool Crypto::Update(){
        //insert code
        return true;
    }

    string Crypto::get_trend(){
        return trend;
    }

    void Crypto::set_trend(string trend){
        this->trend=trend;
    }
