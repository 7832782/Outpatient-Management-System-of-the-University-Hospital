// doctorwindow.h
// 医生界面类
#ifndef DOCTORWINDOW_H
#define DOCTORWINDOW_H

#include <QWidget>

namespace Ui {
class DoctorWindow;
}

class DoctorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorWindow(QWidget *parent = nullptr);
    ~DoctorWindow();

private slots:
    void on_BackButton_clicked();

    void on_ReceptionButton_clicked();

    void on_RecordsButton_clicked();

private:
    Ui::DoctorWindow *ui;
};

#endif // DOCTORWINDOW_H
