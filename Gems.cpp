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
        if (prices == nullptr) return; 
        
        // Expected Upward Trend
        double mu = 0.03;

        // Expected Randomness
        double sigma = 0.15;

        std::random_device rd;  
        std::mt19937 gen(rd());  // Mersenne Twister RNG

        // Normal distribution with mean 0 and standard deviation 1
        std::normal_distribution<double> dist(0.0, 1.0);

        double dWt = dist(gen);

        // Change from day to day
        double dS = mu * this->prices[29] * 1 + sigma * this->prices[29] * dWt;        

        // Move all the prices down a day
        for(int i = 0; i < 29; i++){
            this->prices[i] = this->prices[i+1];          
        }
        this->prices[29] += dS;
        }

    // Getters and Setters
    string Gems::get_economicCycle(){
        return economicCycle;
    }
    void Gems::set_economicCycle(string economicCycle){
        this->economicCycle=economicCycle;
    }