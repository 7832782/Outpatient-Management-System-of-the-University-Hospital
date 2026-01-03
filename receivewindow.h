// receivewindow.h
// 接诊界面类
#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H

#include <QWidget>

namespace Ui {
class ReceiveWindow;
}

class ReceiveWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiveWindow(QWidget *parent = nullptr);
    ~ReceiveWindow();
    void updateUi();


private slots:
    void on_BackButton_clicked();

    void on_PrescribeButton_clicked();

private:
    Ui::ReceiveWindow *ui;
};

#endif // RECEIVEWINDOW_H
