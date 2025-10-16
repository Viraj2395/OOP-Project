#include "PhysicalCommodities.h"
#include "Commodity.h"
#include "Gems.h"
#include <string>


using namespace std;

    Gems::Gems():PhysicalCommodities(){
        this->economicCycle="";
    }

    Gems::Gems(string economicCycle, int storageCost, int quantityOwned, string name, string type):PhysicalCommodities(storageCost, quantityOwned, name, type, (double[3]){1000,0.03, 0.15}){
        this->economicCycle=economicCycle;
    }

    bool Gems::Update(){
        //insert code
        return true;
    }

    string Gems::get_economicCycle(){
        return economicCycle;
    }
    void Gems::set_economicCycle(string economicCycle){
        this->economicCycle=economicCycle;
    }