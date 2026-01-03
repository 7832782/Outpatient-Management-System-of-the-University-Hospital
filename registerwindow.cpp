// registerwindow.cpp
#include "registerwindow.h"
#include "ui_registerwindow.h"

#include <QMessageBox> // QT弹窗提示（用于显示挂号成功/失败）
#include "tool.h"
#include "data.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::setPWindow(PatientWindow *p){
    pWindow = p;
}

void RegisterWindow::on_pushButton_clicked()
{
    this->close();
}


void RegisterWindow::on_registerButton_clicked()
{
    // 从QT控件中收集用户输入
    std::string name = ui->nameEdit->text().toUtf8().data(); // 姓名
    int age = ui->ageSpin->value(); // 年龄
    // 性别：0=女，1=男
    int sex = ui->sexCombo->currentIndex();
    std::string tel = ui->telEdit->text().toUtf8().data(); // 手机号

    // 合法性校验
    if (name.empty() || tel.empty()) {
        QMessageBox::warning(this, "输入警告", "姓名和手机号不能为空！");
        return; // 校验失败，直接返回
    }

    if(!isTel(tel)) {
        QMessageBox::warning(this, "输入警告", "这不是一个合法手机号！");
        return; // 校验失败，直接返回
    }

    // 生成挂号编号，格式：P年月日时分秒，如 P20251227195123

    time_t regTime = getCurrentTime(); // 挂号时间
    std::string regID = "P" + timeToID(regTime);

    // 创建对象
    Patient patient;
    patient.setName(name);
    patient.setAge(age);
    patient.setSex(sex);
    patient.setTelNumber(tel);
    patient.setRegID(regID);
    patient.setRegTime(regTime);

    registerPati(patient);
    QMessageBox::information(this, "操作成功", QString("挂号成功！你的挂号编号：%1").arg(regID));
    if(patientsIndex == -1){
        patientsIndex = 0;
        pWindow->setPatientLabel(patientsIndex);
    }

    writePatientsToFile();

    this->close();
}

