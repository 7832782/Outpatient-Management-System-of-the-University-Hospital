// symptomwindow.h
// 提交症状界面类
#ifndef SYMPTOMWINDOW_H
#define SYMPTOMWINDOW_H

#include <QWidget>

namespace Ui {
class SymptomWindow;
}

class SymptomWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SymptomWindow(QWidget *parent = nullptr);
    ~SymptomWindow();

private slots:


    void on_BackButton_clicked();

    void on_SubmitButton_clicked();

private:
    Ui::SymptomWindow *ui;
};

#endif // SYMPTOMWINDOW_H
