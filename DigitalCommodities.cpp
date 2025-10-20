#include "DigitalCommodities.h"
#include "Commodity.h"
#include <string>

using namespace std;

DigitalCommodities::DigitalCommodities():Commodity(){
    this->transactionFee=0;
}
DigitalCommodities::DigitalCommodities(int transactionFee, int quantityOwned, string name, string type, double stats[3]):Commodity(quantityOwned,name,type,stats){
    this->transactionFee=transactionFee;
}

int DigitalCommodities::get_transactionFee(){
    return transactionFee;
}

void DigitalCommodities::set_transactionFee(int transactionFee){
    this->transactionFee=transactionFee;
}