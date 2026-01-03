// doctorwindow.cpp
#include "doctorwindow.h"
#include "ui_doctorwindow.h"

#include "receivewindow.h"
#include "receiverecordwindow.h"


#include "data.h"

#include <QMessageBox>

DoctorWindow::DoctorWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DoctorWindow)
{
    ui->setupUi(this);
}

DoctorWindow::~DoctorWindow()
{
    delete ui;
}

void DoctorWindow::on_BackButton_clicked()
{
    this->close();
}


void DoctorWindow::on_ReceptionButton_clicked()
{
    if(unreceived.empty()){
        QMessageBox::warning(this, "警告", "当前无患者！");
        return;
    }

    ReceiveWindow *win = new ReceiveWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    win->setWindowFlags(Qt::Window);
    // 保持模态
    win->setWindowModality(Qt::ApplicationModal);
    // 显示
    win->show();
    // 内存释放
    connect(win, &QWidget::destroyed, win, &QWidget::deleteLater);
}


void DoctorWindow::on_RecordsButton_clicked()
{
    ReceiveRecordWindow *win = new ReceiveRecordWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    win->setWindowFlags(Qt::Window);
    // 保持模态
    win->setWindowModality(Qt::ApplicationModal);
    // 显示
    win->show();
    // 内存释放
    connect(win, &QWidget::destroyed, win, &QWidget::deleteLater);
}

