// cashier.h
// 收费员类
#pragma once
#include "staff.h"
#include "prescription.h"

class Cashier : public Staff
{
public:
    Cashier(const std::string& name_, const std::string& ID_, const std::string& section_);
    // 获取营收额
    float getCollection() const;
    // 设置营收额
    void setCollection(float collection_);
    // 核算处方
    void confirmPay(Prescription& pres);

private:
    // 营收额
    float collection;
};
