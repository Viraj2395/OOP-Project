#ifndef COMMODITY_H
#define COMMODITY_H

using namespace std;

class Commodity{
    protected:
    int quantityOwned;
    double prices[30]; //whats the size or shud this be a vector?

    public:

    //constructors
    Commodity();
    Commodity(int quantityOwned);


    bool Buy(string commodity);
    bool Sell(string commodity);

    virtual bool Update();
    void MakeGraph(); //virtual func?????????????

    //getters
    int get_quantityOwned();
    double* get_prices();

    //setters
    void set_quantityOwned(int quantityOwned);
    void set_prices(double* prices);

};


#endif
