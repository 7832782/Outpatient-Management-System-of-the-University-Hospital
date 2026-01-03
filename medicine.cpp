// medicine.cpp
#include "medicine.h"

Medicine::Medicine() {

}

Medicine::Medicine(const std::string& name_, const std::string& efficacy_, float price_, int inventory_) :
    name(name_), efficacy(efficacy_), price(price_), inventory(inventory_) {

}

std::string Medicine::getName() const {
    return name;
}

std::string Medicine::getEfficacy() const {
    return efficacy;
}

float Medicine::getPrice() const {
    return price;
}

int Medicine::getInventory() const {
    return inventory;
}

void Medicine::setName(std::string name_) {
    name = name_;
}

void Medicine::setEfficacy(std::string efficacy_) {
    efficacy = efficacy_;
}

void Medicine::setPrice(float price_) {
    price = price_;
}

void Medicine::setInventory(int inventory_) {
    inventory = inventory_;
}

void Medicine::useInventory(int inventory_){
    inventory -= inventory_;
}
