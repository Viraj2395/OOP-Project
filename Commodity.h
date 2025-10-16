#ifndef COMMODITY_H
#define COMMODITY_H

#include <string>
#include <iostream>
#include <random>

using namespace std;

class Commodity{
    protected:
    int quantityOwned;
    double* prices; 
    string name;
    string type;

    public:

    //constructors
    Commodity();
    Commodity(int quantityOwned, string name, string type);
    Commodity(int quantityOwned, string name, string type, double stats[3]);

    virtual bool Update()=0;
    void MakeGraph(); 

    //getters
    int get_quantityOwned();
    double* get_prices();
    string get_name();
    string get_type();

    //setters
    void set_quantityOwned(int quantityOwned);
    void set_prices(double* prices);
    void set_name(string name);
    void set_type(string type);

    //destructor
    virtual ~Commodity();
};


#endif
