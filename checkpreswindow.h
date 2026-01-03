// checkpreswindow.h
// 查看处方界面类
#ifndef CHECKPRESWINDOW_H
#define CHECKPRESWINDOW_H

#include <QWidget>

namespace Ui {
class CheckPresWindow;
}

class CheckPresWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CheckPresWindow(QWidget *parent = nullptr);
    ~CheckPresWindow();

private slots:
    void on_BackButton_clicked();

private:
    Ui::CheckPresWindow *ui;
};

#endif // CHECKPRESWINDOW_H
