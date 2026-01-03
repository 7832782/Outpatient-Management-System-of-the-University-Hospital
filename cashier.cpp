// cashier.cpp
#include "cashier.h"

Cashier::Cashier(const std::string& name_, const std::string& ID_, const std::string& section_) :
    Staff(name_, ID_, section_) {
    collection = 0;
}

float Cashier::getCollection() const {
    return collection;
}

void Cashier::setCollection(float collection_) {
    collection = collection_;
}

void Cashier::confirmPay(Prescription& pres) {
    collection += pres.getTotFee();
}
