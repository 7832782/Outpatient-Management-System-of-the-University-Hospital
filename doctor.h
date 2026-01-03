// doctor.h
// 医生类
#pragma once
#include "staff.h"

class Doctor : public Staff
{
public:
    Doctor(const std::string& name_, const std::string& ID_, const std::string& section_);
    // 获取接诊次数
    int getReceTimes() const;
    // 设置接诊次数
    void setReceTimes(int receTimes_);

private:
    // 接诊次数
    int receTimes;
};
