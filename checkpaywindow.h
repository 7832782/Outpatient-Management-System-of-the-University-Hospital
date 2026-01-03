// checkpaywindow.h
// 核算费用界面类
#ifndef CHECKPAYWINDOW_H
#define CHECKPAYWINDOW_H

#include <QWidget>

namespace Ui {
class CheckPayWindow;
}

class CheckPayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CheckPayWindow(QWidget *parent = nullptr);
    ~CheckPayWindow();

    void loadPresToTable();

private slots:
    void on_BackButton_clicked();
    void onTableHeaderClicked(int columnIndex);

    void on_SubmitButton_clicked();

private:
    Ui::CheckPayWindow *ui;

    int PresIDSortOrder = 0;
    int PatiIDSortOrder = 0;
    int TimeSortOrder = 0;
    int feeSortOrder = 0;
};

#endif // CHECKPAYWINDOW_H
