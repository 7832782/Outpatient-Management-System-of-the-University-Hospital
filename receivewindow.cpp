// receivewindow.cpp
#include "receivewindow.h"
#include "ui_receivewindow.h"

#include "data.h"
#include "tool.h"

#include "prescribewindow.h"

#include <QMessageBox>

void ReceiveWindow::updateUi(){
    if(unreceived.empty()){
        QMessageBox::warning(this, "警告", "当前无患者！");
        this->close();
        return;
    }
    ui->NameLabel->setText("姓名：" + QString("%1").arg(unreceived.front().getName()));
    ui->AgeLabel->setText("年龄：" + QString("%1").arg(unreceived.front().getAge()));
    ui->RegIDLabel->setText("挂号编号：" + QString("%1").arg(unreceived.front().getRegID()));
    ui->SexLabel->setText("性别：" + QString("%1").arg(sexToString(unreceived.front().getSex())));
    ui->TelLabel->setText("手机号：" + QString("%1").arg(unreceived.front().getTelnumber()));
    ui->DescriptionLabel->setText("症状描述：" + QString("%1").arg(unreceived.front().getDescription()));
}

ReceiveWindow::ReceiveWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReceiveWindow)
{
    ui->setupUi(this);

    updateUi();
}

ReceiveWindow::~ReceiveWindow()
{
    delete ui;
}

void ReceiveWindow::on_BackButton_clicked()
{
    this->close();
}


void ReceiveWindow::on_PrescribeButton_clicked()
{
    PrescribeWindow *win = new PrescribeWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    win->setRWindow(this);

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    win->setWindowFlags(Qt::Window);
    // 保持模态
    win->setWindowModality(Qt::ApplicationModal);
    // 显示
    win->show();
    // 内存释放
    connect(win, &QWidget::destroyed, win, &QWidget::deleteLater);
}

