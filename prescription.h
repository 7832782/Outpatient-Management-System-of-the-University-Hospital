// prescription.h
// 处方类
#pragma once

#include <unordered_map>
#include <string>

class Prescription
{
public:
    Prescription();
    Prescription(const std::string& presID_, const std::string& patiID_, const std::string& doctID_, std::unordered_map<std::string, int> medList_, float totFee_, time_t createTime_, bool isPaid_);

    // 获取处方ID
    std::string getPresID() const;
    // 获取患者ID
    std::string getPatiID() const;
    // 获取医生ID
    std::string getDoctID() const;
    // 获取药品列表
    std::unordered_map<std::string, int> getMedList() const;
    // 获取总金额
    float getTotFee() const;
    // 获取开具时间
    time_t getCreateTime() const;
    // 获取缴费状态
    bool getIsPaid() const;
    // 获取药品列表
    std::string getMedListStr() const;

    // 添加药品
    void addMedicine(const std::string& med, int num);

    // 设置总金额
    void setTotalFee(float fee);
    // 设置缴费状态
    void setPaid(bool state);
    // 设置处方ID
    void setPresID(std::string presID_);
    // 设置患者ID
    void setPatiID(std::string patiID_);
    // 设置医生ID
    void setDoctID(std::string doctID_);
    // 设置开具时间
    void setCreateTime(time_t createTime_);

    // 计算总金额
    void sumPaid();

private:
    // 处方ID
    std::string presID;
    // 患者ID
    std::string patiID;
    // 医生ID
    std::string doctID;
    // 药品列表
    std::unordered_map<std::string,int> medList;
    // 总金额
    float totFee;
    // 开具时间
    time_t createTime;
    // 缴费状态
    bool isPaid;
};
