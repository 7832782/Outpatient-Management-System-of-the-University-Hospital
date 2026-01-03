// registerwindow.h
// 挂号界面类
#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include "PatientWindow.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

    void setPWindow(PatientWindow *p);

private slots:
    void on_pushButton_clicked();

    void on_registerButton_clicked();

private:
    Ui::RegisterWindow *ui;
    PatientWindow *pWindow;
};

#endif // REGISTERWINDOW_H
