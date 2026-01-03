// doctor.cpp
#include "doctor.h"

Doctor::Doctor(const std::string& name_, const std::string& ID_, const std::string& section_) :
    Staff(name_,ID_,section_) {
    receTimes = 0;
}

int Doctor::getReceTimes() const {
    return receTimes;
}

void Doctor::setReceTimes(int receTimes_) {
    receTimes = receTimes_;
}
