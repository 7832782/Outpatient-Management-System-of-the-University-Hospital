// medicine.h
// 药品类
#pragma once

#include <string>

class Medicine
{
public:
    Medicine();
    Medicine(const std::string& name_, const std::string& efficacy_,float price_,int inventory_);
    // 获取药品名
    std::string getName() const;
    // 获取药效
    std::string getEfficacy() const;
    // 获取单价
    float getPrice() const;
    // 获取库存
    int getInventory() const;

    // 设置药品名
    void setName(std::string name_);
    // 设置药效
    void setEfficacy(std::string efficacy_);
    // 设置单价
    void setPrice(float price_);
    // 设置库存
    void setInventory(int inventory_);

    // 消耗库存
    void useInventory(int inventory_);

private:
    // 药品名
    std::string name;
    // 药效
    std::string efficacy;
    // 单价
    float price;
    // 库存
    int inventory;
};
