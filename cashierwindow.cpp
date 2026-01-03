// cashierwindow.cpp
#include "cashierwindow.h"
#include "ui_cashierwindow.h"

#include "checkpaywindow.h"
#include "revenuewindow.h"

CashierWindow::CashierWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CashierWindow)
{
    ui->setupUi(this);
}

CashierWindow::~CashierWindow()
{
    delete ui;
}

void CashierWindow::on_BackButton_clicked()
{
    this->close();
}


void CashierWindow::on_CalculateButton_clicked()
{
    CheckPayWindow *win = new CheckPayWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    win->setWindowFlags(Qt::Window);
    // 保持模态
    win->setWindowModality(Qt::ApplicationModal);
    // 显示
    win->show();
    // 内存释放
    connect(win, &QWidget::destroyed, win, &QWidget::deleteLater);
}


void CashierWindow::on_RevenueButton_clicked()
{
    RevenueWindow *win = new RevenueWindow(this); // 父窗口仍设为主窗口（不影响独立显示）

    // 设置为独立窗口（带标题栏、可关闭、独立弹出）
    win->setWindowFlags(Qt::Window);
    // 保持模态
    win->setWindowModality(Qt::ApplicationModal);
    // 显示
    win->show();
    // 内存释放
    connect(win, &QWidget::destroyed, win, &QWidget::deleteLater);
}
