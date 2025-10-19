#include "PhysicalCommodities.h"
#include "Commodity.h"
#include "Harvest.h"
#include <string>

using namespace std;


    Harvest::Harvest():PhysicalCommodities(){
        this->season="";
    }

    Harvest::Harvest(string season, int storageCost, int quantityOwned, string name, string type):PhysicalCommodities(storageCost, quantityOwned, name, type, (double[3]){100,0.015, 0.07}){
        this->season=season;
    }

    void Harvest::Update(){
        if (prices == nullptr) return; 

        for(int i = 0; i < 29; i++){
            this->prices[i] = this->prices[i+1];          
        }
        this->prices[29] +=1;
        //insert code
        }

    string Harvest::get_season(){
        return season;
    }
    void Harvest::set_season(string season){
        this->season=season;
    }