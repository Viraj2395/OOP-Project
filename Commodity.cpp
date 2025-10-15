#include "Commodity.h"
#include <string>

using namespace std;

    Commodity::Commodity(){
        this->quantityOwned=0;
        this->name="";
        this->type="";
    }
    Commodity::Commodity(int quantityOwned, string name, string type){
        this->quantityOwned=quantityOwned;
        this->name=name;
        this->type=type;
    }

    void Commodity::MakeGraph(){
        //make graph using prices array
    }

    //getters
    int Commodity::get_quantityOwned(){
        return quantityOwned;
    }
    double* Commodity::get_prices(){
        return prices;  
    }
    string Commodity::get_name(){
        return name;
    }
    string Commodity::get_type(){
        return type;
    }


    //setters
    void Commodity::set_quantityOwned(int quantityOwned){
        this->quantityOwned=quantityOwned;
    }
    void Commodity::set_prices(double* prices){
        this->prices=prices;
    }
    void Commodity::set_name(string name){
        this->name=name;
    }
    void Commodity::set_type(string type){
        this->type=type;
    }

    //destructor
    Commodity::~Commodity() {
    delete[] prices; 
    prices = nullptr;
    }
