// staff.h
// 工作人员类
#pragma once

#include <string>

class Staff
{
public:
    Staff(const std::string& name_, const std::string& ID_, const std::string& section_);

    // 获取名字
    std::string getName() const;
    // 获取工作人员ID
    std::string getID() const;
    // 获取部门
    std::string	getSection() const;

    // 设置名字
    void setName(std::string name_);
    // 设置工作人员ID
    void setID(std::string ID_);
    // 设置部门
    void setSection(std::string section_);

private:
    // 名字
    std::string name;
    // 工作人员ID
    std::string ID;
    // 部门
    std::string section;
};
