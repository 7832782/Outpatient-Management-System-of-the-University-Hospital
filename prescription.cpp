// prescription.cpp
#include "prescription.h"

#include "tool.h"
#include "data.h"

Prescription::Prescription(){

}

Prescription::Prescription(const std::string& presID_, const std::string& patiID_, const std::string& doctID_, std::unordered_map<std::string, int> medList_, float totFee_, time_t createTime_, bool isPaid_) :
    presID(presID_), patiID(patiID_), doctID(doctID_), medList(medList_), totFee(totFee_), createTime(createTime_), isPaid(isPaid_) {

}

std::string Prescription::getPresID() const {
    return presID;
}

std::string Prescription::getPatiID() const {
    return patiID;
}

std::string Prescription::getDoctID() const {
    return doctID;
}

std::unordered_map<std::string, int> Prescription::getMedList() const {
    return medList;
}

float Prescription::getTotFee() const {
    return totFee;
}

time_t Prescription::getCreateTime() const {
    return createTime;
}

bool Prescription::getIsPaid() const {
    return isPaid;
}

void Prescription::addMedicine(const std::string& med, int num) {
    medList[med] = num;
}

void Prescription::setTotalFee(float fee) {
    totFee = fee;
}

void Prescription::setPaid(bool state) {
    isPaid = state;
}

void Prescription::setPresID(std::string presID_) {
    presID = presID_;
}

void Prescription::setPatiID(std::string patiID_) {
    patiID = patiID_;
}

void Prescription::setDoctID(std::string doctID_) {
    doctID = doctID_;
}

void Prescription::setCreateTime(time_t createTime_) {
    createTime = createTime_;
}

std::string Prescription::getMedListStr() const {
    std::string str;
    if (medList.empty()) return str;
    for (auto &pair : medList) {
        str += pair.first + ":" + std::to_string(pair.second) + ",";
    }
    str.pop_back();
    return str;
}

void Prescription::sumPaid(){
    totFee = 0;
    for (const auto &pair : medList) {
        totFee += dispensary[medToID(pair.first)].getPrice() * pair.second;
    }
}
