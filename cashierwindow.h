// cashierwindow.h
// 收费员界面类
#ifndef CASHIERWINDOW_H
#define CASHIERWINDOW_H

#include <QWidget>

namespace Ui {
class CashierWindow;
}

class CashierWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CashierWindow(QWidget *parent = nullptr);
    ~CashierWindow();

private slots:
    void on_BackButton_clicked();

    void on_CalculateButton_clicked();

    void on_RevenueButton_clicked();

private:
    Ui::CashierWindow *ui;
};

#endif // CASHIERWINDOW_H
