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

    void Crypto::Update(){
        if (prices == nullptr) return; 
        
        double mu = 0.05

        double sigma = 0.4;

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

    string Crypto::get_trend(){
        return trend;
    }

    void Crypto::set_trend(string trend){
        this->trend=trend;
    }
