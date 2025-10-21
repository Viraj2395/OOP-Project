#include <iostream>
#include <random>
#include <cmath>


int main(){
    // St = Prices at time t. S is varialbe for Price dependant on varialbe t
    double prices[30];
    for (int i = 0; i < 30; i++){
        prices[i]=100;
    }

    std::random_device rd;  
    std::mt19937 gen(rd());  // Mersenne Twister RNG

    // Normal distribution with mean 0 and standard deviation 1
    std::normal_distribution<double> dist(0.0, 1.0);

    // Mu = drift: Expected increase over time
    double mu = 0.015;

    // Sigma = volatility: Proportional Standard Deviation of price change
    double sigma = 0.07;

    for(int j = 0; j<29; j++){
            // dWt = Random Change estimated dwt ~ Z(0,1)
            double dWt = dist(gen);

            // SDE dS = Mu * St * dt + Sigma * St * dWt
            double dS = mu * prices[29] * 1 + sigma * prices[29] * dWt;

        for (int i = 0; i < 29; i++)
        {
            prices[i] = prices[i+1];
        }
        
        prices[29] += dS;
    }  

    double maxValue = prices[0];
    for (int i = 1; i < 30; i++)
    {
        if(prices[i]>maxValue){
            maxValue = prices[i];
        }
    }

    int yValues[30];
    for (int i = 0; i < 30; i++){
        yValues[i]=prices[i]/maxValue * 15;
    }    


    for (int i = 0; i< 30; i++){
        std::cout<< prices[i] << "\n";
        std::cout<< yValues[i] << "\n";
    }

    std::cout<< maxValue << "\n";

    int lenG = 100;

    std::cout<<"┌";    

    for (int i = 0; i < lenG; i++)
    {
        std::cout<<"─";
    }
    
    std::cout<<"┐\n";


    for(int k=1; k<16; k++){
        std::cout<<"|";
        for (int j = 0; j < lenG; j++)
        {
            std::cout<<" ";
        }
        std::cout<<"|\n";
    }


    std::cout<<"└";    

    for (int i = 0; i < lenG; i++)
    {
        std::cout<<"─";
    }
    
    std::cout<<"┘\n";

    return(0);
}