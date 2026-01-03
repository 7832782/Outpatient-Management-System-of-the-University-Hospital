// patientwindow.cpp
#include "patientwindow.h"
#include "ui_patientwindow.h"

#include "registerwindow.h"
#include "symptomwindow.h"
#include "checkpreswindow.h"

#include <QMessageBox>

#include "data.h"

PatientWindow::PatientWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientWindow)
{
    ui->setupUi(this);

    if(!patients.empty()){
        patientsIndex = 0;
        setPatientLabel(patientsIndex);
    }
}

PatientWindow::~PatientWindow()
{
    delete ui;
}

void PatientWindow::on_BackButton_clicked()
{
    this->close();
}


void PatientWindow::on_RegisterButton_clicked()
{
    RegisterWindow *win = new RegisterWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    win->setPWindow(this);

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    win->setWindowFlags(Qt::Window);
    // 保持模态
    win->setWindowModality(Qt::ApplicationModal);
    // 显示
    win->show();
    // 内存释放
    connect(win, &QWidget::destroyed, win, &QWidget::deleteLater);
}

void PatientWindow::on_lastButton_clicked()
{
    if(patients.empty()) return;
    patientsIndex--;
    if(patientsIndex == -1) patientsIndex = patients.size() - 1;
    this->setPatientLabel(patientsIndex);
}


void PatientWindow::on_nextButton_clicked()
{
    if(patients.empty()) return;
    patientsIndex++;
    if(patientsIndex == patients.size()) patientsIndex = 0;
    this->setPatientLabel(patientsIndex);
}

void PatientWindow::setPatientLabel(int index){
    ui->patientLabel->setText(QString("%1").arg(patients[index].getName()));
}

void PatientWindow::on_SubmitButton_clicked()
{
    if(patientsIndex == -1){
        QMessageBox::warning(this, "警告", "当前无患者！");
        return;
    }

    SymptomWindow *win = new SymptomWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    win->setWindowFlags(Qt::Window);
    // 保持模态
    win->setWindowModality(Qt::ApplicationModal);
    // 显示
    win->show();
    // 内存释放
    connect(win, &QWidget::destroyed, win, &QWidget::deleteLater);
}


void PatientWindow::on_PrescriptionsButton_clicked()
{
    if(patientsIndex == -1){
        QMessageBox::warning(this, "警告", "当前无患者！");
        return;
    }

    findIndex = -1;
    for(int i = 0; i < Prescriptions.size(); i++){
        if(Prescriptions[i].getPatiID() == patients[patientsIndex].getRegID()){
            findIndex = i;
            break;
        }
    }
    if(findIndex == -1){
        QMessageBox::warning(this, "警告", "该患者没有处方！");
        return;
    }

    CheckPresWindow *win = new CheckPresWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    win->setWindowFlags(Qt::Window);
    // 保持模态
    win->setWindowModality(Qt::ApplicationModal);
    // 显示
    win->show();
    // 内存释放
    connect(win, &QWidget::destroyed, win, &QWidget::deleteLater);
}

