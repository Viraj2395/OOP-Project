#include "Commodity.h"

using namespace std;

    Commodity::Commodity(){
        this->quantityOwned=0;
    }
    Commodity::Commodity(int quantityOwned){
        this->quantityOwned=quantityOwned;
    }

    bool Commodity::Buy(string commodity){
        
    }
    bool Commodity::Sell(string commodity){

    }

    bool Commodity::Update(){
        return true;
    }

    void Commodity::MakeGraph(){} //virtual func?????????

    //getters
    int Commodity::get_quantityOwned(){
        return quantityOwned;
    }
    double* Commodity::get_prices(){
        return prices;  //shud be a pointer right????????
    }

    //setters
    void Commodity::set_quantityOwned(int quantityOwned){
        this->quantityOwned=quantityOwned;
    }
    void Commodity::set_prices(double* prices){
        this->prices=prices;
    }
