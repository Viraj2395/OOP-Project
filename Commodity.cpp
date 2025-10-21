#include "Commodity.h"
#include <string>

using namespace std;

    Commodity::Commodity(){
        this->quantityOwned=0;
        this->name="";
        this->type="";
        this->prices= nullptr;
    }

    Commodity::Commodity(int quantityOwned, string name, string type){
        this->quantityOwned=quantityOwned;
        this->name=name;
        this->type=type;
        this->prices= nullptr;
    }


    Commodity::Commodity(int quantityOwned, string name, string type, double stats[3]){
        this->quantityOwned=quantityOwned;
        this->name=name;
        this->type=type;
        this->prices = new double[30];

        // St = Prices at time t. S is varialbe for Price dependant on varialbe t
        for (int i = 0; i < 30; i++){
            this->prices[i]=stats[0];
        }

        std::random_device rd;  
        std::mt19937 gen(rd());  // Mersenne Twister RNG

        // Normal distribution with mean 0 and standard deviation 1
        std::normal_distribution<double> dist(0.0, 1.0);

        // Mu = drift: Expected increase over time
        double mu = stats[1];

        // Sigma = volatility: Proportional Standard Deviation of price change
        double sigma = stats[2];

        for(int j = 0; j<29; j++){
                // dWt = Random Change estimated dwt ~ Z(0,1)
                double dWt = dist(gen);

                // SDE dS = Mu * St * dt + Sigma * St * dWt
                double dS = mu * this->prices[29] * 1 + sigma * this->prices[29] * dWt;

            for (int i = 0; i < 29; i++)
            {
                this->prices[i] = this->prices[i+1];
            }
            
            this->prices[29] += dS;
        }  

    }

    void Commodity::MakeGraph(){
    double maxValue = this->prices[0];
    for (int i = 1; i < 30; i++)
    {
        if(this->prices[i]>maxValue){
            maxValue = this->prices[i];
        }
    }

    int yValues[30];
    for (int i = 0; i < 30; i++){
        yValues[i]=this->prices[i]/maxValue * 15;
    }    


    int lenG = 100;

    std::cout<<"┌";    

    for (int i = 0; i < lenG; i++)
    {
        std::cout<<"─";
    }
    
    std::cout<<"┐\n";

    std::cout<<"|";
    for (int i = 0; i < 44; i++)
    {
        std::cout<<" ";
    }
    std::cout<<"Day vs Price";
    for (int i = 0; i < 44; i++)
    {
        std::cout<<" ";
    }    
    std::cout<<"|\n";

    for(int k=0; k<15; k++){
        std::cout<<"|";
        for (int j = 0; j < 6; j++)
        {
            std::cout<<" ";
        }

        if(yValues[0]==15-k){
            std::cout<<"*";
        }
        else{
            std::cout<<" ";
        }

        for(int i = 1; i<30; i++){
            std::cout<<"  ";
            if(yValues[i]==15-k){
                std::cout<<"*";
            }
            else{
                std::cout<<" ";
            }            
        }


        for (int j = 0; j < 6; j++)
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
