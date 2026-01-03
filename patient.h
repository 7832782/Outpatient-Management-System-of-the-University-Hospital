// patient.h
// 患者类
#pragma once

#include <string>
#include <vector>

class Patient
{
public:
    Patient();
    Patient(const std::string& name_, int age_, int sex_, const std::string& telNumber_, const std::string& regID_, const std::string& description_, time_t regTime_);

    // 获取名字
    std::string getName() const;
    // 获取年龄
    int getAge() const;
    // 获取性别
    int getSex() const;
    // 获取手机号
    std::string getTelnumber() const;
    // 获取挂号ID
    std::string getRegID() const;
    // 获取症状
    std::string getDescription() const;
    // 获取就诊记录列表
    std::vector<std::string> getRecord() const;
    // 获取挂号时间
    time_t getRegTime() const;

    // 设置名字
    void setName(std::string name_);
    // 设置年龄
    void setAge(int age_);
    // 设置性别
    void setSex(int sex_);
    // 设置手机号
    void setTelNumber(std::string telNumber_);
    // 设置挂号ID
    void setRegID(std::string regID_);
    // 设置症状
    void setDescription(std::string description_);
    // 设置就诊记录列表
    void setRegTime(time_t regTime_);

    // 增加就诊记录
    void addRecord(std::string str);

private:
    // 名字
    std::string name;
    // 年龄
    int age;
    // 性别
    int sex;// 0为女，1为男
    // 电话号码
    std::string telNumber;
    // 挂号ID
    std::string regID;
    // 症状
    std::string description;
    // 就诊记录列表
    std::vector<std::string> record;
    // 挂号时间
    time_t regTime;
};
