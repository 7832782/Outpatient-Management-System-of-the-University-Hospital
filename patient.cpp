// patient.cpp
#include "patient.h"

Patient::Patient() {

}

Patient::Patient(const std::string& name_, int age_, int sex_, const std::string& telNumber_, const std::string& regID_, const std::string& description_, time_t regTime_) :
    name(name_), age(age_), sex(sex_), telNumber(telNumber_), regID(regID_), description(description_), regTime(regTime_) {

}

std::string Patient::getName() const {
    return name;
}

int Patient::getAge() const {
    return age;
}

int Patient::getSex() const {
    return sex;
}

std::string Patient::getTelnumber() const {
    return telNumber;
}

std::string Patient::getRegID() const {
    return regID;
}

std::string Patient::getDescription() const {
    return description;
}

std::vector<std::string> Patient::getRecord() const {
    return record;
}

time_t Patient::getRegTime() const {
    return regTime;
}

void Patient::setName(std::string name_) {
    name = name_;
}

void Patient::setAge(int age_) {
    age = age_;
}

void Patient::setSex(int sex_) {
    sex = sex_;
}

void Patient::setTelNumber(std::string telNumber_) {
    telNumber = telNumber_;
}

void Patient::setRegID(std::string regID_) {
    regID = regID_;
}

void Patient::setDescription(std::string description_) {
    description = description_;
}

void Patient::setRegTime(time_t regTime_) {
    regTime = regTime_;
}

void Patient::addRecord(std::string str) {
    record.push_back(str);
}
