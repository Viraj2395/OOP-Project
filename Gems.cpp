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

    void Gems::Update(){
        
        for(int i = 0; i < 29; i++){
            this->prices[i] = this->prices[i+1]            
        }
        this->prices[29] +=1
        //insert code
    }

    string Gems::get_economicCycle(){
        return economicCycle;
    }
    void Gems::set_economicCycle(string economicCycle){
        this->economicCycle=economicCycle;
    }