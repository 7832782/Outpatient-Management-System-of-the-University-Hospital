// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "tool.h"

#include "PatientWindow.h"
#include "doctorwindow.h"
#include "cashierwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int patiNum = readPatientsFromFile();
    int mediNum = readMedicinesFromFile();
    int presNum = readPrescriptionsFromFile();

    QString patiStr;
    QString mediStr;
    QString presStr;
    if(patiNum == -1) patiStr = "患者信息文件读取失败！";
    else patiStr = "已读取" + QString::number(patiNum) + "条患者信息数据！";
    if(mediNum == -1) mediStr = "药品信息文件读取失败！";
    else mediStr = "已读取" + QString::number(mediNum) + "条药品信息数据！";
    if(presNum == -1) presStr = "处方信息文件读取失败！";
    else presStr = "已读取" + QString::number(presNum) + "条处方信息数据！";

    QMessageBox::information(this, "加载", patiStr + "\n" + mediStr + "\n" + presStr);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PatientButton_clicked()
{
    PatientWindow *patientWin = new PatientWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    patientWin->setWindowFlags(Qt::Window);
    // 保持模态
    patientWin->setWindowModality(Qt::ApplicationModal);
    // 显示
    patientWin->show();
    // 内存释放
    connect(patientWin, &QWidget::destroyed, patientWin, &QWidget::deleteLater);
}


void MainWindow::on_DoctorButton_clicked()
{
    DoctorWindow *doctorWin = new DoctorWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    doctorWin->setWindowFlags(Qt::Window);
    // 保持模态
    doctorWin->setWindowModality(Qt::ApplicationModal);
    // 显示
    doctorWin->show();
    // 内存释放
    connect(doctorWin, &QWidget::destroyed, doctorWin, &QWidget::deleteLater);
}


void MainWindow::on_CashierButton_clicked()
{
    CashierWindow *cashierWin = new CashierWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    cashierWin->setWindowFlags(Qt::Window);
    // 保持模态
    cashierWin->setWindowModality(Qt::ApplicationModal);
    // 显示
    cashierWin->show();
    // 内存释放
    connect(cashierWin, &QWidget::destroyed, cashierWin, &QWidget::deleteLater);
}

