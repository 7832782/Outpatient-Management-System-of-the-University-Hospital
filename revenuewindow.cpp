#include "revenuewindow.h"
#include "ui_revenuewindow.h"

#include "data.h"

#include <QTextEdit>

RevenueWindow::RevenueWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RevenueWindow)
{
    ui->setupUi(this);

    connect(ui->RecordTable->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &RevenueWindow::onTableHeaderClicked);

    loadRecordToTable();
    ui->AmountLabel->setText(QString("处方数量:%1").arg(revenueRecords.size()));
    ui->RevenueLabel->setText(QString("营收额:%1").arg(cashier.getCollection()));
}

RevenueWindow::~RevenueWindow()
{
    delete ui;
}

void RevenueWindow::on_BackButton_clicked()
{
    this->close();
}

void RevenueWindow::loadRecordToTable(){
    // 清空表格原有数据
    // 删除所有行
    ui->RecordTable->setRowCount(0);

    for (const std::vector<std::string> &record : revenueRecords)
    {
        // 获取当前表格的行数
        int row = ui->RecordTable->rowCount();
        ui->RecordTable->insertRow(row);

        // 给每一列设置数据
        // 列0：处方编号
        QTableWidgetItem *presItem = new QTableWidgetItem(
            QString::fromStdString(record[0]));
        ui->RecordTable->setItem(row, 0, presItem);

        // 列1：缴费时间
        QTableWidgetItem *timeItem = new QTableWidgetItem(
            QString::fromStdString(record[1]));
        ui->RecordTable->setItem(row, 1, timeItem);

        // 列2：收费员工号
        QTableWidgetItem *cashierItem = new QTableWidgetItem(
            QString::fromStdString(record[2]));
        ui->RecordTable->setItem(row, 2, cashierItem);

        // 列3：药品列表
        QString qMedListStr = QString::fromStdString(record[3]);
        QTextEdit *medTextEdit = new QTextEdit(ui->RecordTable);
        medTextEdit->setPlainText(qMedListStr);
        ui->RecordTable->setCellWidget(row, 3, medTextEdit);

        // 列4：总金额
        QTableWidgetItem *feeItem = new QTableWidgetItem(
            QString::fromStdString(record[4]));
        ui->RecordTable->setItem(row, 4, feeItem);
    }
}

void RevenueWindow::onTableHeaderClicked(int columnIndex) {
    switch (columnIndex)
    {
    case 0:
        // 点击“处方编号”列
        presIDSortOrder = !presIDSortOrder; // 切换排序状态
        if (presIDSortOrder == 0)
        {
            // 处方编号升序排序
            sort(revenueRecords.begin(), revenueRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return s1[0] < s2[0];
                 }
                 );
        }
        else
        {
            // 处方编号降序排序
            sort(revenueRecords.begin(), revenueRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return s1[0] > s2[0];
                 }
                 );
        }
        break;
    case 1:
        // 点击“缴费时间”列
        timeSortOrder = !timeSortOrder; // 切换排序状态
        if (timeSortOrder == 0)
        {
            // 缴费时间升序排序
            sort(revenueRecords.begin(), revenueRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return s1[1] < s2[1];
                 }
                 );
        }
        else
        {
            // 缴费时间降序排序
            sort(revenueRecords.begin(), revenueRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return s1[1] > s2[1];
                 }
                 );
        }
        break;
    case 2:
        // 点击“收费员工号”列
        cashierIDSortOrder = !cashierIDSortOrder; // 切换排序状态
        if (cashierIDSortOrder == 0)
        {
            // 收费员工号升序排序
            sort(revenueRecords.begin(), revenueRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return s1[2] < s2[2];
                 }
                 );
        }
        else
        {
            // 收费员工号降序排序
            sort(revenueRecords.begin(), revenueRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return s1[2] > s2[2];
                 }
                 );
        }
        break;
    case 4:
        // 点击“总金额”列
        feeSortOrder = !feeSortOrder; // 切换排序状态
        if (feeSortOrder == 0)
        {
            // 总金额升序排序
            sort(revenueRecords.begin(), revenueRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return std::stof(s1[4]) < std::stof(s2[4]);
                 }
                 );
        }
        else
        {
            // 总金额降序排序
            sort(revenueRecords.begin(), revenueRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return std::stof(s1[4]) > std::stof(s2[4]);
                 }
                 );
        }
        break;

    default:
        break;
    }
    loadRecordToTable();
}

