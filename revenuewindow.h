// revenuewindow.h
// 查看营收界面类
#ifndef REVENUEWINDOW_H
#define REVENUEWINDOW_H

#include <QWidget>

namespace Ui {
class RevenueWindow;
}

class RevenueWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RevenueWindow(QWidget *parent = nullptr);
    ~RevenueWindow();

    void loadRecordToTable();

private slots:
    void on_BackButton_clicked();

    void onTableHeaderClicked(int columnIndex);

private:
    Ui::RevenueWindow *ui;

    int presIDSortOrder;
    int timeSortOrder;
    int cashierIDSortOrder;
    int feeSortOrder;
};

#endif // REVENUEWINDOW_H
