// data.h
// 全局变量声明
#pragma once

#include "patient.h"
#include "medicine.h"
#include "prescription.h"
#include "doctor.h"
#include "cashier.h"

#include <vector>
#include <queue>

// 全局变量声明
extern std::vector<Patient> patients;
extern int patientsIndex;
extern std::queue<Patient> unreceived;

extern int findIndex;

extern std::vector<Medicine> dispensary;

extern std::vector<Prescription> uncheckPres;
extern std::vector<Prescription> Prescriptions;

extern std::vector<std::vector<std::string>> receiveRecords;

extern std::vector<std::vector<std::string>> revenueRecords;

extern Doctor doctor;
extern Cashier cashier;
