#include "PhysicalCommodities.h"
#include "Commodity.h"
#include "Harvest.h"
#include <string>

using namespace std;


    Harvest::Harvest():PhysicalCommodities(){
        this->season="";
    }

    Harvest::Harvest(string season, int storageCost, int quantityOwned, string name, string type):PhysicalCommodities(storageCost, quantityOwned, name, type, new (double[3]){100,0.015, 0.07}){
        this->season=season;
    }

    void Harvest::Update(){
        if (prices == nullptr) return; 

        double mu = 0.015;

        double sigma = 0.07;

        std::random_device rd;  
        std::mt19937 gen(rd());  // Mersenne Twister RNG

        // Normal distribution with mean 0 and standard deviation 1
        std::normal_distribution<double> dist(0.0, 1.0);

        double dWt = dist(gen);

        double dS = mu * this->prices[29] * 1 + sigma * this->prices[29] * dWt;        

        for(int i = 0; i < 29; i++){
            this->prices[i] = this->prices[i+1];          
        }
        this->prices[29] += dS;
        }

    string Harvest::get_season(){
        return season;
    }
    void Harvest::set_season(string season){
        this->season=season;
    }