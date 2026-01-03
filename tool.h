// tool.h
#pragma once

#include "patient.h"
#include <unordered_map>

// 时间工具函数声明

// 获取当前时间戳
time_t getCurrentTime();

// 时间戳增加指定分钟
time_t addMinutes(time_t base, int minutes);

// 补0的to_string
std::string padZero(int num);

// 时间戳转字符串
std::string timeToString(time_t t);

// 时间戳转编号
std::string timeToID(time_t t);

// 将药名转换为该药在药库的索引
int medToID(const std::string& medName);

// 检查电话号码合法性(11 位、开头为 1、只含 0-9)
bool isTel(const std::string& tel);

// 将性别对应的数字转换为字符串
std::string sexToString(int sex);

// 将缴费状态转换为字符串
std::string stateToString(bool state);

// 将药品列表转换为字符串
std::string listToString(const std::unordered_map<std::string,int> &list);

// 挂号
void registerPati(Patient &patient);

// 输入字符串，输出一个字符串数组，由前者用逗号分隔得到，不含引号内逗号
std::vector<std::string> parseCsvLine(const std::string& line);


// 返回数据量，读/写失败则返回-1
int readPatientsFromFile(const std::string& filename = "Patients.txt");
int writePatientsToFile(const std::string& filename = "Patients.txt");

int readMedicinesFromFile(const std::string& filename = "Medicines.txt");
int writeMedicinesToFile(const std::string& filename = "Medicines.txt");

int readPrescriptionsFromFile(const std::string& filename = "Prescriptions.txt");
int writePrescriptionsToFile(const std::string& filename = "Prescriptions.txt");
