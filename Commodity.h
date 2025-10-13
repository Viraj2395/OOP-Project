#ifndef COMMODITY_H
#define COMMODITY_H

#include <string>
#include <cstddef>

class Commodity {
protected:
    int quantityOwned_;
    double* prices_;       
    int pricesCount_;    

public:
    Commodity();
    Commodity(int quantityOwned, double initialPrice);
    virtual ~Commodity();  

    
    virtual bool Update();  
    virtual void MakeGraph(double* pricesArray);  

    
    int get_quantityOwned() const;
    void set_quantityOwned(int quantityOwned);

    double* get_prices();
    void set_prices(double* prices);

    
    int get_pricesCount() const;   
    double currentPrice() const; 
    void pushPrice(double newPrice);
};

#endif 
