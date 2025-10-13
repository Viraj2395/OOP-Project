#include "Commodity.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>

Commodity::Commodity() : quantityOwned_(0), prices_(nullptr), pricesCount_(0) {}

Commodity::Commodity(int quantityOwned, double initialPrice)
: quantityOwned_(quantityOwned), pricesCount_(1) {
    prices_ = new double[1];
    prices_[0] = initialPrice;
}

Commodity::~Commodity() {
    delete[] prices_;
    prices_ = nullptr;
}

bool Commodity::Update() {
    if (pricesCount_ == 0) {
        prices_ = new double[1];
        prices_[0] = 100.0;
        pricesCount_ = 1;
        return true;
    }

    double current = prices_[pricesCount_ - 1];
    static thread_local std::mt19937 rng(std::random_device{}());
    std::normal_distribution<double> pct(0.0, 0.02); // ±2%
    double next = std::max(0.1, current * (1.0 + pct(rng)));

    pushPrice(next);
    return true;
}

void Commodity::MakeGraph(double* pricesArray) {
    std::cout << "[Graph Placeholder] Prices:\n";
    for (int i = 0; i < pricesCount_; ++i)
        std::cout << "Day " << i + 1 << ": " << pricesArray[i] << "\n";
}

int Commodity::get_quantityOwned() const { return quantityOwned_; }

void Commodity::set_quantityOwned(int quantityOwned) {
    quantityOwned_ = quantityOwned;
}

double* Commodity::get_prices() { return prices_; }

void Commodity::set_prices(double* prices) {
    if (prices == nullptr) return;
    delete[] prices_;
    pricesCount_ = 1;
    prices_ = new double[1];
    prices_[0] = *prices;
}

int Commodity::get_pricesCount() const { return pricesCount_; }

double Commodity::currentPrice() const {
    if (pricesCount_ == 0) return 0.0;
    return prices_[pricesCount_ - 1];
}

void Commodity::pushPrice(double newPrice) {
    double* newArr = new double[pricesCount_ + 1];
    for (int i = 0; i < pricesCount_; ++i)
        newArr[i] = prices_[i];
    newArr[pricesCount_] = newPrice;

    delete[] prices_;
    prices_ = newArr;
    pricesCount_++;
}
