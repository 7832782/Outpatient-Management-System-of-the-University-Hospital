// prescribewindow.cpp
#include "prescribewindow.h"
#include "ui_prescribewindow.h"

#include <QTableWidgetItem>
#include <QSpinBox>
#include <QMessageBox>
#include <QInputDialog>

#include "prescription.h"
#include "data.h"
#include "tool.h"
#include "doctor.h"

// 定义加载药品到表格的函数
void PrescribeWindow::loadMedicineToTable()
{
    // 清空表格原有数据
    // 删除所有行
    ui->MedicineTable->setRowCount(0);

    // 遍历dispensary，逐个添加药品数据
    for (const Medicine& med : dispensary)
    {
        // 获取当前表格的行数
        int row = ui->MedicineTable->rowCount();
        ui->MedicineTable->insertRow(row);

        // 给每一列设置数据
        // 列0：药品名称
        QTableWidgetItem *nameItem = new QTableWidgetItem(
            QString::fromStdString(med.getName())
            );
        ui->MedicineTable->setItem(row, 0, nameItem);

        // 列1：功效
        QTableWidgetItem *efficacyItem = new QTableWidgetItem(
            QString::fromStdString(med.getEfficacy())
            );
        ui->MedicineTable->setItem(row, 1, efficacyItem);

        // 列2：单价
        QTableWidgetItem *priceItem = new QTableWidgetItem(
            QString::number(med.getPrice(), 'f', 2) // 保留2位小数
            );
        ui->MedicineTable->setItem(row, 2, priceItem);

        // 列3：库存
        QTableWidgetItem *inventoryItem = new QTableWidgetItem(
            QString::number(med.getInventory())
            );
        ui->MedicineTable->setItem(row, 3, inventoryItem);

        // 列4：开具数量
        // 创建QSpinBox对象，父控件设为表格
        QSpinBox *countSpinBox = new QSpinBox(ui->MedicineTable);
        // 设置SpinBox属性
        countSpinBox->setMinimum(0); // 最小开具数量为0
        countSpinBox->setMaximum(med.getInventory()); // 最大数量=药品库存

        ui->MedicineTable->setCellWidget(row, 4, countSpinBox);
    }
}

PrescribeWindow::PrescribeWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PrescribeWindow)
{
    ui->setupUi(this);

    connect(ui->MedicineTable->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &PrescribeWindow::onTableHeaderClicked);

    loadMedicineToTable();
}

PrescribeWindow::~PrescribeWindow()
{
    delete ui;
}

void PrescribeWindow::onTableHeaderClicked(int columnIndex){
    switch (columnIndex)
    {
    case 0:
        // 点击“药品”列
        {
            bool ok;
            QString keyword = QInputDialog::getText(
                this,
                "药品搜索",
                "请输入关键词：",
                QLineEdit::Normal,
                "", // 默认输入为空
                &ok
                );
            if (ok && !keyword.isEmpty()) { // 用户点击了“确定”且输入不为空
                int rowCount = ui->MedicineTable->rowCount(); // 获取表格总行数

                std::vector<int> keywordIndex;

                for (int row = 0; row < rowCount; row++)
                {
                    // 获取当前行的药品
                    QTableWidgetItem *medItem = ui->MedicineTable->item(row, 0);

                    QString medicine = medItem->text();
                    if(medicine.contains(keyword)) keywordIndex.push_back(row);
                }

                std::vector<Medicine> keywordMed;
                for(int i = keywordIndex.size() - 1; i >=0; i--){
                    keywordMed.push_back(dispensary[keywordIndex[i]]);
                    dispensary.erase(dispensary.begin() + keywordIndex[i]);
                }
                keywordMed.insert(keywordMed.end(),dispensary.begin(),dispensary.end());
                dispensary = keywordMed;
            }
            break;
        }
    case 1:
        // 点击“功效”列
        {
            bool ok;
            QString keyword = QInputDialog::getText(
                this,
                "功效搜索",
                "请输入关键词：",
                QLineEdit::Normal,
                "", // 默认输入为空
                &ok
                );
            if (ok && !keyword.isEmpty()) { // 用户点击了“确定”且输入不为空
                int rowCount = ui->MedicineTable->rowCount(); // 获取表格总行数

                std::vector<int> keywordIndex;

                for (int row = 0; row < rowCount; row++)
                {
                    // 获取当前行的功效
                    QTableWidgetItem *efficacyItem = ui->MedicineTable->item(row, 1);

                    QString efficacy = efficacyItem->text();
                    if(efficacy.contains(keyword)) keywordIndex.push_back(row);
                }

                std::vector<Medicine> keywordMed;
                for(int i = keywordIndex.size() - 1; i >=0; i--){
                    keywordMed.push_back(dispensary[keywordIndex[i]]);
                    dispensary.erase(dispensary.begin() + keywordIndex[i]);
                }
                keywordMed.insert(keywordMed.end(),dispensary.begin(),dispensary.end());
                dispensary = keywordMed;
            }
            break;
        }


    case 2:
        // 点击“单价”列
        priceSortOrder = !priceSortOrder; // 切换排序状态
        if (priceSortOrder == 0)
        {
            // 单价升序排序
            sort(dispensary.begin(), dispensary.end(),
                 [](const Medicine& m1, const Medicine& m2) {
                     return m1.getPrice() < m2.getPrice();
                 }
                 );
        }
        else
        {
            // 单价降序排序
            sort(dispensary.begin(), dispensary.end(),
                 [](const Medicine& m1, const Medicine& m2) {
                     return m1.getPrice() > m2.getPrice();
                 }
                 );
        }
        break;
    case 3:
        // 点击“库存”列
        inventorySortOrder = !inventorySortOrder; // 切换排序状态
        if (inventorySortOrder == 0)
        {
            // 库存升序排序
            sort(dispensary.begin(), dispensary.end(),
                 [](const Medicine& m1, const Medicine& m2) {
                     return m1.getInventory() < m2.getInventory();
                 }
                 );
        }
        else
        {
            // 库存降序排序
            sort(dispensary.begin(), dispensary.end(),
                 [](const Medicine& m1, const Medicine& m2) {
                     return m1.getInventory() > m2.getInventory();
                 }
                 );
        }
        break;
    default:
        break;
    }
    loadMedicineToTable();
}

void PrescribeWindow::on_BackButton_clicked()
{
    this->close();
}


void PrescribeWindow::on_SubmitButton_clicked()
{
    // 创建处方
    Prescription pres;

    int rowCount = ui->MedicineTable->rowCount(); // 获取表格总行数

    for (int row = 0; row < rowCount; row++)
    {
        // 获取当前行的QSpinBox
        QSpinBox *countSpinBox = qobject_cast<QSpinBox*>(ui->MedicineTable->cellWidget(row, 4));

        // 获取开具数量，筛选数量>0的药品
        int prescribeCount = countSpinBox->value();
        if (prescribeCount <= 0) continue; // 数量为0，跳过

        // 获取当前行的药品名称
        QTableWidgetItem *nameItem = ui->MedicineTable->item(row, 0);

        std::string medicineName = nameItem->text().toStdString();
        pres.addMedicine(medicineName,prescribeCount);

        // 消耗药品
        dispensary[medToID(medicineName)].useInventory(prescribeCount);
        writeMedicinesToFile();
    }

    pres.setPatiID(unreceived.front().getRegID());
    pres.setPresID("R" + timeToID(getCurrentTime()));
    pres.setDoctID(doctor.getID());
    pres.setCreateTime(getCurrentTime());

    doctor.setReceTimes(doctor.getReceTimes() + 1);

    // 开单时间、姓名、挂号编号、症状、处方详情
    std::vector<std::string> record(5);
    record[0] = timeToString(pres.getCreateTime());
    record[1] = unreceived.front().getName();
    record[2] = pres.getPatiID();
    record[3] = unreceived.front().getDescription();
    record[4] = listToString(pres.getMedList());
    receiveRecords.push_back(record);

    uncheckPres.push_back(pres);
    unreceived.pop();


    QMessageBox::information(this, "操作成功", QString("开具处方成功！处方编号：%1").arg(pres.getPresID()));

    rWindow->updateUi();

    this->close();
}

void PrescribeWindow::setRWindow(ReceiveWindow *p) {
    rWindow = p;
}

