#include "PhysicalCommodities.h"
#include "Commodity.h"
#include "Harvest.h"
#include <string>

using namespace std;


    Harvest::Harvest():PhysicalCommodities(){
        this->season="";
    }

    Harvest::Harvest(string season, int storageCost, int quantityOwned, string name, string type):PhysicalCommodities(storageCost, quantityOwned, name, type){
        this->season=season;
    }

    bool Harvest::Update(){
        //insert code
        return true;
    }

    string Harvest::get_season(){
        return season;
    }
    void Harvest::set_season(string season){
        this->season=season;
    }