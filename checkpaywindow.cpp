// checkpaywindow.cpp
#include "checkpaywindow.h"
#include "ui_checkpaywindow.h"

#include <QCheckBox>
#include <QTextEdit>
#include <QMessageBox>

#include "data.h"
#include "tool.h"

void CheckPayWindow::loadPresToTable(){
    // 清空表格原有数据
    // 删除所有行
    ui->PresTable->setRowCount(0);

    // 遍历uncheckPres，逐个添加处方数据
    for (Prescription& pres : uncheckPres)
    {
        // 获取当前表格的行数
        int row = ui->PresTable->rowCount();
        ui->PresTable->insertRow(row);

        // 给每一列设置数据
        // 列0：处方编号
        QTableWidgetItem *presIDItem = new QTableWidgetItem(
            QString::fromStdString(pres.getPresID()));
        ui->PresTable->setItem(row, 0, presIDItem);

        // 列1：挂号编号
        QTableWidgetItem *patiIDItem = new QTableWidgetItem(
            QString::fromStdString(pres.getPatiID()));
        ui->PresTable->setItem(row, 1, patiIDItem);

        // 列2：医生工号
        QTableWidgetItem *doctIDItem = new QTableWidgetItem(
            QString::fromStdString(pres.getDoctID()));
        ui->PresTable->setItem(row, 2, doctIDItem);

        // 列3：开具时间
        QTableWidgetItem *timeItem = new QTableWidgetItem(
            QString::fromStdString(timeToString(pres.getCreateTime())));
        ui->PresTable->setItem(row, 3, timeItem);

        // 列4：药物列表
        QString qMedListStr = QString::fromStdString(listToString(pres.getMedList()));
        QTextEdit *medTextEdit = new QTextEdit(ui->PresTable);
        medTextEdit->setPlainText(qMedListStr);
        ui->PresTable->setCellWidget(row, 4, medTextEdit);

        pres.sumPaid();
        // 列5：总金额
        QTableWidgetItem *feeItem = new QTableWidgetItem(
            QString("%1").arg(pres.getTotFee()));
        ui->PresTable->setItem(row, 5, feeItem);

        // 列6：勾选框
        // 创建QCheckBox对象，父控件设为表格
        QCheckBox *checkBox = new QCheckBox(ui->PresTable);
        ui->PresTable->setCellWidget(row, 6, checkBox);
    }
}

CheckPayWindow::CheckPayWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CheckPayWindow)
{
    ui->setupUi(this);

    connect(ui->PresTable->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &CheckPayWindow::onTableHeaderClicked);

    loadPresToTable();
}

CheckPayWindow::~CheckPayWindow()
{
    delete ui;
}

void CheckPayWindow::on_BackButton_clicked()
{
    this->close();
}

void CheckPayWindow::onTableHeaderClicked(int columnIndex) {
    switch (columnIndex)
    {
    case 0: // 处方编号列
        PresIDSortOrder = !PresIDSortOrder; // 切换排序状态
        if (PresIDSortOrder == 0)
        {
            // 处方编号升序排序
            sort(uncheckPres.begin(), uncheckPres.end(),
                 [](const Prescription& p1, const Prescription& p2) {
                     return p1.getPresID() < p2.getPresID();
                 }
                 );
        }
        else
        {
            // 处方编号降序排序
            sort(uncheckPres.begin(), uncheckPres.end(),
                 [](const Prescription& p1, const Prescription& p2) {
                     return p1.getPresID() > p2.getPresID();
                 }
                 );
        }
        break;
    case 1: // 挂号编号列
        PatiIDSortOrder = !PatiIDSortOrder; // 切换排序状态
        if (PatiIDSortOrder == 0)
        {
            // 挂号编号升序排序
            sort(uncheckPres.begin(), uncheckPres.end(),
                 [](const Prescription& p1, const Prescription& p2) {
                     return p1.getPatiID() < p2.getPatiID();
                 }
                 );
        }
        else
        {
            // 挂号编号降序排序
            sort(uncheckPres.begin(), uncheckPres.end(),
                 [](const Prescription& p1, const Prescription& p2) {
                     return p1.getPatiID() > p2.getPatiID();
                 }
                 );
        }
        break;
    case 2: // 医生工号列
        break;
    case 3: // 开具时间列
        TimeSortOrder = !TimeSortOrder; // 切换排序状态
        if (TimeSortOrder == 0)
        {
            // 开具时间升序排序
            sort(uncheckPres.begin(), uncheckPres.end(),
                 [](const Prescription& p1, const Prescription& p2) {
                     return p1.getCreateTime() < p2.getCreateTime();
                 }
                 );
        }
        else
        {
            // 开具时间降序排序
            sort(uncheckPres.begin(), uncheckPres.end(),
                 [](const Prescription& p1, const Prescription& p2) {
                     return p1.getCreateTime() > p2.getCreateTime();
                 }
                 );
        }
        break;
    case 5: // 总金额列
        feeSortOrder = !feeSortOrder; // 切换排序状态
        if (feeSortOrder == 0)
        {
            // 总金额升序排序
            sort(uncheckPres.begin(), uncheckPres.end(),
                 [](const Prescription& p1, const Prescription& p2) {
                     return p1.getTotFee() < p2.getTotFee();
                 }
                 );
        }
        else
        {
            // 总金额降序排序
            sort(uncheckPres.begin(), uncheckPres.end(),
                 [](const Prescription& p1, const Prescription& p2) {
                     return p1.getTotFee() > p2.getTotFee();
                 }
                 );
        }
        break;
    default:
        break;
    }
    // 排序后刷新表格
    loadPresToTable();
}


void CheckPayWindow::on_SubmitButton_clicked()
{

    int rowCount = ui->PresTable->rowCount(); // 获取表格总行数

    std::vector<int> checkedIndex;

    for (int row = 0; row < rowCount; row++) {
        // 获取当前行的QCheckBox
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(ui->PresTable->cellWidget(row, 6));
        if (checkBox->isChecked()){
            checkedIndex.push_back(row);
        }
    }

    // 倒序遍历，删除时不会破坏索引
    for(int i = checkedIndex.size() - 1; i >= 0; i--) {
        Prescriptions.push_back(uncheckPres[checkedIndex[i]]);
        uncheckPres.erase(uncheckPres.begin() + checkedIndex[i]);

        // 加入营收
        std::vector<std::string> revenue(5);
        revenue[0] = Prescriptions.back().getPresID();
        revenue[1] = timeToString(getCurrentTime());
        revenue[2] = cashier.getID();
        revenue[3] = listToString(Prescriptions.back().getMedList());
        cashier.confirmPay(Prescriptions.back());
        revenue[4] = std::to_string(Prescriptions.back().getTotFee());
        revenueRecords.push_back(revenue);
    }
    writePrescriptionsToFile();
    QMessageBox::information(this, "操作成功", "处方核算成功!");

    this->close();
}
