// checkpreswindow.cpp
#include "checkpreswindow.h"
#include "ui_checkpreswindow.h"

#include <QMessageBox>

#include "data.h"
#include "tool.h"

CheckPresWindow::CheckPresWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CheckPresWindow)
{
    ui->setupUi(this);

    ui->RegiLabel->setText(QString("处方编号：%1").arg(Prescriptions[findIndex].getPresID()));
    ui->DoctLabel->setText(QString("医生工号：%1").arg(Prescriptions[findIndex].getDoctID()));
    ui->PatiLabel->setText(QString("挂号编号：%1").arg(Prescriptions[findIndex].getPatiID()));
    ui->TimeLabel->setText(QString("开单时间：%1").arg(timeToString(Prescriptions[findIndex].getCreateTime())));
    ui->PayLabel->setText(QString("总金额：%1").arg(Prescriptions[findIndex].getTotFee()));
    ui->StateLabel->setText(QString("缴费状态：%1").arg(stateToString(Prescriptions[findIndex].getIsPaid())));
    ui->ListLabel->setText(QString("药品列表：\n%1").arg(listToString(Prescriptions[findIndex].getMedList())));
}

CheckPresWindow::~CheckPresWindow()
{
    delete ui;
}

void CheckPresWindow::on_BackButton_clicked()
{
    this->close();
}

