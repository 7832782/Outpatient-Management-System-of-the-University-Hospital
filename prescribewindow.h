// prescribewindow.h
// 开具处方界面类
#ifndef PRESCRIBEWINDOW_H
#define PRESCRIBEWINDOW_H

#include <QWidget>
#include "receivewindow.h"

namespace Ui {
class PrescribeWindow;
}

class PrescribeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PrescribeWindow(QWidget *parent = nullptr);
    ~PrescribeWindow();

    void loadMedicineToTable();

    void setRWindow(ReceiveWindow *p);

private slots:
    void onTableHeaderClicked(int columnIndex);

    void on_BackButton_clicked();

    void on_SubmitButton_clicked();

private:
    Ui::PrescribeWindow *ui;
    ReceiveWindow *rWindow;

    int priceSortOrder = 0;
    int inventorySortOrder = 0;
};

#endif // PRESCRIBEWINDOW_H
