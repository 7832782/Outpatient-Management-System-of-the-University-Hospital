// receiverecordwindow.cpp
#include "receiverecordwindow.h"
#include "ui_receiverecordwindow.h"

#include "data.h"

#include <QTableWidget>
#include <QTextEdit>
#include <QInputDialog>

ReceiveRecordWindow::ReceiveRecordWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReceiveRecordWindow)
{
    ui->setupUi(this);

    connect(ui->RecordTable->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &ReceiveRecordWindow::onTableHeaderClicked);

    loadRecordToTable();

    ui->CountLabel->setText("接诊人数：" + QString::number(doctor.getReceTimes()));
}

ReceiveRecordWindow::~ReceiveRecordWindow()
{
    delete ui;
}

void ReceiveRecordWindow::on_BackButton_clicked()
{
    this->close();
}

// 开单时间、姓名、挂号编号、症状、处方详情
void ReceiveRecordWindow::loadRecordToTable() {
    // 清空表格原有数据
    // 删除所有行
    ui->RecordTable->setRowCount(0);

    // 遍历uncheckPres，逐个添加处方数据
    for (const std::vector<std::string> &record : receiveRecords)
    {
        // 获取当前表格的行数
        int row = ui->RecordTable->rowCount();
        ui->RecordTable->insertRow(row);

        // 给每一列设置数据
        // 列0：开单时间
        QTableWidgetItem *timeItem = new QTableWidgetItem(
            QString::fromStdString(record[0]));
        ui->RecordTable->setItem(row, 0, timeItem);

        // 列1：姓名
        QTableWidgetItem *nameItem = new QTableWidgetItem(
            QString::fromStdString(record[1]));
        ui->RecordTable->setItem(row, 1, nameItem);

        // 列2：挂号编号
        QTableWidgetItem *doctIDItem = new QTableWidgetItem(
            QString::fromStdString(record[2]));
        ui->RecordTable->setItem(row, 2, doctIDItem);

        // 列3：症状
        QString qSymListStr = QString::fromStdString(record[3]);
        QTextEdit *symTextEdit = new QTextEdit(ui->RecordTable);
        symTextEdit->setPlainText(qSymListStr);
        ui->RecordTable->setCellWidget(row, 3, symTextEdit);

        // 列4：处方详情
        QString qPresListStr = QString::fromStdString(record[4]);
        QTextEdit *presTextEdit = new QTextEdit(ui->RecordTable);
        presTextEdit->setPlainText(qPresListStr);
        ui->RecordTable->setCellWidget(row, 4, presTextEdit);
    }
}

void ReceiveRecordWindow::onTableHeaderClicked(int columnIndex) {
    switch (columnIndex)
    {
    case 0:
        timeSortOrder = !timeSortOrder; // 切换排序状态
        if (timeSortOrder == 0)
        {
            // 开单时间升序排序
            sort(receiveRecords.begin(), receiveRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return s1[0] < s2[0];
                 }
                 );
        }
        else
        {
            // 开单时间降序排序
            sort(receiveRecords.begin(), receiveRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return s1[0] > s2[0];
                 }
                 );
        }
        break;
    case 1:
        // 点击“姓名”列
        {
            bool ok;
            QString keyword = QInputDialog::getText(
                this,
                "姓名搜索",
                "请输入关键词：",
                QLineEdit::Normal,
                "", // 默认输入为空
                &ok
                );
            if (ok && !keyword.isEmpty()) { // 用户点击了“确定”且输入不为空
                int rowCount = ui->RecordTable->rowCount(); // 获取表格总行数

                std::vector<int> keywordIndex;

                for (int row = 0; row < rowCount; row++)
                {
                    // 获取当前行的姓名
                    QTableWidgetItem *nameItem = ui->RecordTable->item(row, 1);
                    if (nameItem == nullptr) continue;

                    QString name = nameItem->text();
                    if(name.contains(keyword)) keywordIndex.push_back(row);
                }

                std::vector<std::vector<std::string>> keywordName;
                for(int i = keywordIndex.size() - 1; i >=0; i--){
                    keywordName.push_back(receiveRecords[keywordIndex[i]]);
                    receiveRecords.erase(receiveRecords.begin() + keywordIndex[i]);
                }
                keywordName.insert(keywordName.end(),receiveRecords.begin(),receiveRecords.end());
                receiveRecords = keywordName;
            }
            break;
        }


    case 2:
        // 点击“挂号编号”列
        patiIDSortOrder = !patiIDSortOrder; // 切换排序状态
        if (patiIDSortOrder == 0)
        {
            // 挂号编号升序排序
            sort(receiveRecords.begin(), receiveRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return s1[2] < s2[2];
                 }
                 );
        }
        else
        {
            // 挂号编号降序排序
            sort(receiveRecords.begin(), receiveRecords.end(),
                 [](const std::vector<std::string>& s1, const std::vector<std::string>& s2) {
                     return s1[2] > s2[2];
                 }
                 );
        }
        break;
    case 3:
        // 点击“症状”列
        {
            bool ok;
            QString keyword = QInputDialog::getText(
                this,
                "症状搜索",
                "请输入关键词：",
                QLineEdit::Normal,
                "", // 默认输入为空
                &ok
                );
            if (ok && !keyword.isEmpty()) { // 用户点击了“确定”且输入不为空
                int rowCount = ui->RecordTable->rowCount(); // 获取表格总行数

                std::vector<int> keywordIndex;

                for (int row = 0; row < rowCount; row++)
                {
                    QWidget *embedWidget = ui->RecordTable->cellWidget(row, 3);
                    // 将通用QWidget强制转换为QTextEdit类型
                    QTextEdit *symTextEdit = qobject_cast<QTextEdit*>(embedWidget);
                    QString symptom = symTextEdit->toPlainText();
                    if(symptom.contains(keyword)) keywordIndex.push_back(row);
                }

                std::vector<std::vector<std::string>> keywordSym;
                for(int i = keywordIndex.size() - 1; i >=0; i--){
                    keywordSym.push_back(receiveRecords[keywordIndex[i]]);
                    receiveRecords.erase(receiveRecords.begin() + keywordIndex[i]);
                }
                keywordSym.insert(keywordSym.end(),receiveRecords.begin(),receiveRecords.end());
                receiveRecords = keywordSym;
            }
            break;
        }
    default:
        break;
    }
    loadRecordToTable();
}

