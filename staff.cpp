// staff.cpp
#include "staff.h"

Staff::Staff(const std::string& name_, const std::string& ID_, const std::string& section_) :
    name(name_), ID(ID_), section(section_) {

}

std::string Staff::getName() const {
    return name;
}

std::string Staff::getID() const {
    return ID;
}

std::string	Staff::getSection() const {
    return section;
}

void Staff::setName(std::string name_) {
    Staff::name = name_;
}

void Staff::setID(std::string ID_) {
    ID = ID_;
}

void Staff::setSection(std::string section_) {
    section = section_;
}
