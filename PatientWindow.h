// PatientWindow.h
// 患者界面类
#ifndef PATIENTWINDOW_H
#define PATIENTWINDOW_H

#include <QWidget>

namespace Ui {
class PatientWindow;
}

class PatientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PatientWindow(QWidget *parent = nullptr);
    ~PatientWindow();

    void setPatientLabel(int index);

private slots:
    void on_BackButton_clicked();

    void on_RegisterButton_clicked();

    void on_lastButton_clicked();

    void on_nextButton_clicked();

    void on_SubmitButton_clicked();

    void on_PrescriptionsButton_clicked();

private:
    Ui::PatientWindow *ui;
};

#endif // PATIENTWINDOW_H
