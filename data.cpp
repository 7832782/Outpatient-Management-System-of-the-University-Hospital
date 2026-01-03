// data.cpp
#include "data.h"
#include "medicine.h"
#include "doctor.h"

// 患者数组分类
// ① 包括所有患者的
// ② 还未就诊的
// 挂号时，同时往这两个数组添加
// 就诊后，只移除②中被就诊的患者
std::vector<Patient> patients;
int patientsIndex = -1;
std::queue<Patient> unreceived;

// 患者查找处方时的索引，为-1时说明未找到处方
int findIndex = -1;

std::vector<Medicine> dispensary;

// 处方数组分类:
// ① 医生刚开，未核算的
// ② 收费员核算后的（患者此时才能看到）
std::vector<Prescription> uncheckPres;
std::vector<Prescription> Prescriptions;

// 接诊记录
// 开单时间、姓名、挂号编号、症状、处方详情
std::vector<std::vector<std::string>> receiveRecords;

// 营收记录
// 处方编号、缴费时间、收费员工号、药品列表、总金额
std::vector<std::vector<std::string>> revenueRecords;

Doctor doctor("邹医生","D0","全科诊室");
Cashier cashier("许师傅","C0","财务科");
