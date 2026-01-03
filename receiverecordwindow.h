// receiverecordwindow.h
// 查看接诊记录界面类
#ifndef RECEIVERECORDWINDOW_H
#define RECEIVERECORDWINDOW_H

#include <QWidget>

namespace Ui {
class ReceiveRecordWindow;
}

class ReceiveRecordWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiveRecordWindow(QWidget *parent = nullptr);
    ~ReceiveRecordWindow();

    void loadRecordToTable();

private slots:
    void on_BackButton_clicked();

    void onTableHeaderClicked(int columnIndex);

private:
    Ui::ReceiveRecordWindow *ui;

    int timeSortOrder;
    int patiIDSortOrder;
};

#endif // RECEIVERECORDWINDOW_H
