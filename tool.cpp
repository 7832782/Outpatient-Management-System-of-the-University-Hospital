// tool.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "tool.h"
#include "data.h"

#include <fstream>


#include <QMessageBox>

time_t getCurrentTime() {
    return time(nullptr);
}

time_t addMinutes(time_t base, int minutes) {
    return base + minutes * 60;
}

std::string padZero(int num) {
    return num < 10 ? "0" + std::to_string(num) : std::to_string(num);
}

std::string timeToString(time_t t) {
    tm tm = *localtime(&t);
    int year = tm.tm_year + 1900;
    int mon = tm.tm_mon + 1;
    int day = tm.tm_mday;
    int hour = tm.tm_hour;
    int min = tm.tm_min;
    int sec = tm.tm_sec;

    // 拼接
    return std::to_string(year) + "/" + padZero(mon) + "/" + padZero(day) + " " + padZero(hour) + ":" + padZero(min) + ":" + padZero(sec);
}

std::string timeToID(time_t t){
    tm tm = *localtime(&t);
    int year = tm.tm_year - 100; // 2025 -> 25
    int mon = tm.tm_mon + 1;
    int day = tm.tm_mday;
    int hour = tm.tm_hour;
    int min = tm.tm_min;
    int sec = tm.tm_sec;

    // 拼接
    return std::to_string(year) + padZero(mon) + padZero(day) + padZero(hour) + padZero(min) + padZero(sec);
}

int medToID(const std::string& medName) {
    for(int i = 0; i < dispensary.size(); i++){
         if (dispensary[i].getName() == medName) return i;
    }
    return -1;
}

bool isTel(const std::string& tel){
    if(tel.size() != 11) return false;
    if(tel[0] != '1') return false;
    for(int i = 1; i < tel.size(); i++){
        if(!(tel[i] >= '0' && tel[i] <= '9')) return false;
    }
    return true;
}

std::string sexToString(int sex){
    if(sex == 0) return "女";
    else if(sex == 1) return "男";
    return "未知";
}

std::string stateToString(bool state){
    return state ? "已缴费" : "未缴费";
}

std::string listToString(const std::unordered_map<std::string,int> &list){
    std::string str;
    for(const auto &pair : list){
        str += pair.first + ":" + std::to_string(pair.second) + "\n";
        //str += pair.first + ":" + std::to_string(pair.second) + "(单价:" + std::to_string(dispensary[medToID(pair.first)].getPrice()) + ")" + "\n";
    }
    return str;
}

void registerPati(Patient &patient){
    patients.push_back(patient);
    unreceived.push(patient);
}

std::vector<std::string> parseCsvLine(const std::string& line){
    std::vector<std::string> fieldList; // 存储拆分后的所有字段
    std::string currentField; // 临时存储当前正在拼接的字段
    bool inQuotes = false; // 标记：是否处于双引号内部

    // 遍历每行的每个字符，逐字符处理
    for (char c : line) {
        // 遇到双引号，切换引号状态
        if (c == '"') {
            inQuotes = !inQuotes; // 取反
            continue; // 不将双引号加入字段内容
        }

        // 有“不在引号内”时，逗号才是分隔符
        if (c == ',' && !inQuotes) {
            fieldList.push_back(currentField); // 将拼接好的当前字段加入列表
            currentField.clear(); // 清空临时变量，准备接收下一个字段
        } else {
            // 引号内的逗号/普通字符加入当前字段
            currentField += c;
        }
    }

    // 遍历结束后，将最后一个字段加入列表
    fieldList.push_back(currentField);

    return fieldList;
}

int readPatientsFromFile(const std::string& filename) {
    // 清空原有患者列表
    patients.clear();

    // 打开文件
    std::ifstream file(filename);
    if (!file.is_open()) {
        QMessageBox::warning(nullptr, "错误", "无法打开文件" + QString::fromStdString(filename) + "！");
        return -1;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        lineNum++;
        // 跳过空行
        if (line.empty()) {
            continue;
        }

        // 解析当前行
        std::vector<std::string> fields = parseCsvLine(line);

        // 提取并转换各字段
        Patient newPatient;
        newPatient.setRegID(fields[0]);
        newPatient.setName(fields[1]);

        // 年龄
        newPatient.setAge(std::stoi((fields[2])));

        // 性别
        newPatient.setSex(fields[3] == "男");

        newPatient.setTelNumber(fields[4]);
        newPatient.setDescription(fields[5]); // 症状（已完整保留逗号）

        // 时间戳
        long long timeStamp = std::stoll(fields[6]);
        newPatient.setRegTime(timeStamp);

        // 将解析后的患者加入列表
        registerPati(newPatient);
    }

    //QMessageBox::information(nullptr, "加载成功", "已读取" + QString::fromStdString(filename) + "，共" + QString::number(lineNum) + "条数据！");
    // 关闭文件
    file.close();

    return lineNum;
}

int writePatientsToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) {
        QMessageBox::warning(nullptr, "错误", "无法创建/打开文件" + QString::fromStdString(filename) + "！");
        return -1;
    }

    // 遍历患者列表，逐行写入
    int lineNum = 0;
    for (const auto& patient : patients) {
        lineNum++;
        std::string csvLine;
        csvLine += patient.getRegID() + ",";
        csvLine += patient.getName() + ",";
        csvLine += std::to_string(patient.getAge()) + ",";
        std::string sex = "女";
        if(patient.getSex()) sex = "男";
        csvLine += sex + ",";
        csvLine += patient.getTelnumber() + ",\"";
        csvLine += patient.getDescription() + "\",";
        csvLine += std::to_string(patient.getRegTime());

        // 写入文件并换行
        file << csvLine << std::endl;
    }

    // 关闭文件
    file.close();

    return lineNum;
}

int readMedicinesFromFile(const std::string& filename){
    // 清空原有药品列表
    dispensary.clear();

    // 打开文件
    std::ifstream file(filename);
    if (!file.is_open()) {
        //QMessageBox::warning(nullptr, "错误", "无法打开文件" + QString::fromStdString(filename) + "！");
        return -1;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        lineNum++;
        // 跳过空行
        if (line.empty()) {
            continue;
        }

        // 解析当前行
        std::vector<std::string> fields = parseCsvLine(line);

        // 提取并转换各字段
        Medicine newMedicine;
        newMedicine.setName(fields[0]);
        newMedicine.setEfficacy(fields[1]);
        newMedicine.setPrice(std::stof(fields[2]));
        newMedicine.setInventory(std::stoi(fields[3]));

        // 将解析后的药品加入列表
        dispensary.push_back(newMedicine);
    }

    //QMessageBox::information(nullptr, "加载成功", "已读取" + QString::fromStdString(filename) + "，共" + QString::number(lineNum) + "条数据！");
    // 关闭文件
    file.close();

    return lineNum;
}

int writeMedicinesToFile(const std::string& filename){
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) {
        QMessageBox::warning(nullptr, "错误", "无法创建/打开文件" + QString::fromStdString(filename) + "！");
        return -1;
    }

    // 遍历药品列表，逐行写入
    int lineNum = 0;
    for (const auto& medicine : dispensary) {
        lineNum++;
        std::string csvLine;
        csvLine += medicine.getName() + ",\"";
        csvLine += medicine.getEfficacy() + "\",";
        csvLine += std::to_string(medicine.getPrice()) + ",";
        csvLine += std::to_string(medicine.getInventory());

        // 写入文件并换行
        file << csvLine << std::endl;
    }

    // 关闭文件
    file.close();

    return lineNum;
}

int readPrescriptionsFromFile(const std::string& filename){
    // 清空原有处方列表
    Prescriptions.clear();

    // 打开文件
    std::ifstream file(filename);
    if (!file.is_open()) {
        //QMessageBox::warning(nullptr, "错误", "无法打开文件" + QString::fromStdString(filename) + "！");
        return -1;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        lineNum++;
        // 跳过空行
        if (line.empty()) {
            continue;
        }

        // 解析当前行
        std::vector<std::string> fields = parseCsvLine(line);

        // 提取并转换各字段
        Prescription newPrescription;
        newPrescription.setPresID(fields[0]);
        newPrescription.setPatiID(fields[1]);
        newPrescription.setDoctID(fields[2]);

        // 读取药品列表
        // 布洛芬:20,创可贴:10,...,阿莫西林:5
        int l = 0;
        int m = 0;
        int r = 0;
        std::string str = fields[3];
        if(!str.empty()){
            while(r < str.size()){
                if(str[r] == ':'){
                    m = r;
                }
                else if(str[r] == ','){
                    std::string medName = str.substr(l, m - l);
                    m++;
                    int medInventory = std::stoi(str.substr(m, r - m));
                    l = r + 1;
                    newPrescription.addMedicine(medName,medInventory);
                }
                r++;
            }
            std::string medName = str.substr(l, m - l);
            m++;
            int medInventory = std::stoi(str.substr(m));
            newPrescription.addMedicine(medName,medInventory);
        }

        newPrescription.setTotalFee(std::stof(fields[4]));
        newPrescription.setCreateTime(std::stoll(fields[5]));

        // 将解析后的处方加入列表
        Prescriptions.push_back(newPrescription);
    }

    //QMessageBox::information(nullptr, "加载成功", "已读取" + QString::fromStdString(filename) + "，共" + QString::number(lineNum) + "条数据！");
    // 关闭文件
    file.close();

    return lineNum;
}

int writePrescriptionsToFile(const std::string& filename){
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) {
        //QMessageBox::warning(nullptr, "错误", "无法创建/打开文件" + QString::fromStdString(filename) + "！");
        return -1;
    }

    // 遍历处方列表，逐行写入
    int lineNum = 0;
    for (const auto& pres : Prescriptions) {
        lineNum++;
        std::string csvLine;
        csvLine += pres.getPresID() + ",";
        csvLine += pres.getPatiID() + ",";
        csvLine += pres.getDoctID() + ",\"";

        std::string medList;
        for(const auto& pair : pres.getMedList()){
            medList += pair.first + ":" + std::to_string(pair.second) + ",";
        }
        if(!medList.empty()) medList.pop_back();
        csvLine += medList + "\",";

        csvLine += std::to_string(pres.getTotFee()) + ",";
        csvLine += std::to_string(pres.getCreateTime());

        // 写入文件并换行
        file << csvLine << std::endl;
    }

    // 关闭文件
    file.close();

    return lineNum;
}
