// symptomwindow.cpp
#include "symptomwindow.h"
#include "ui_symptomwindow.h"

#include <QMessageBox>

#include "data.h"
#include "tool.h"

SymptomWindow::SymptomWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SymptomWindow)
{
    ui->setupUi(this);

    // 读取原有的症状
    ui->SymptomEdit->setPlainText(QString::fromStdString(patients[patientsIndex].getDescription()));
}

SymptomWindow::~SymptomWindow()
{
    delete ui;
}

void SymptomWindow::on_BackButton_clicked()
{
    this->close();
}


void SymptomWindow::on_SubmitButton_clicked()
{
    // 获取症状
    std::string symptom = ui->SymptomEdit->toPlainText().trimmed().toStdString();
    patients[patientsIndex].setDescription(symptom);
    writePatientsToFile();

    QMessageBox::information(this, "成功", "症状提交成功！");
    this->close();
}

