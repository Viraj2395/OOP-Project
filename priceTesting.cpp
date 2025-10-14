#include <iostream>

int main(){
    // St = Prices at time t. S is varialbe for Price dependant on varialbe t
    double prices[30];
    for (int i = 0; i < 30; i++){
        prices[i]=i;
    }

    // Mu = drift: Expected increase over time
    double mu = 0.04;

    // Sigma = volatility: Proportional Standard Deviation of price change
    double sigma = 0.25;

    // dWt = Random Change estimated dwt ~ Z(0,1)
    double dWt = 0.2;

    // SDE dS = Mu * St * dt + Sigma * St * dWt
    double dS = mu * prices[29] * 1 + sigma * prices[29] * dWt;

    for(int j = 0; j<30; j++){
        for (int i = 0; i < 29; i++)
        {
            prices[i] = prices[i+1];
        }
        
        prices[29] += dS;
    }  
    
    for (int i = 0; i< 30; i++){
        std::cout<< prices[i] << "\n";
    }

    return(0);
}