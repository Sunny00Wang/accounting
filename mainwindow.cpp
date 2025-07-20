#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QMessageBox>
#include "addrecorddialog.h"
#include "jsonutils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"金额"<<"币种"<<"类型"<<"分类"<<"日期"<<"备注");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->actionAddRecord, &QAction::triggered, this, &MainWindow::onAddRecord);
    connect(ui->actionDeleteRecord, &QAction::triggered, this, &MainWindow::onDeleteRecord);
    connect(ui->pushButtonAddRecord, &QPushButton::clicked, this, &MainWindow::onAddRecord);
    connect(ui->pushButtonDeleteRecord, &QPushButton::clicked, this, &MainWindow::onDeleteRecord);
    QList<Record> records = loadRecordsFromJson("data.json");
    for (const Record &r : records){
        addRecordToTable(r);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddRecord() {
    // 这里写你点击“添加记录”后要执行的逻辑
    AddRecordDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted){
        Record r = dialog.getRecord();
        addRecordToTable(r);
        bool suc = saveRecordToJson(r);
        if (!suc){
            QMessageBox::warning(this, "保存失败","无法写入data.json文件！");
                return;
        }
    }
}

void MainWindow::onDeleteRecord() {

    int row = ui->tableWidget->currentRow();//确保用户选择了一条记录
    if (row < 0 ){
        QMessageBox::warning(this, "未选择","请先选中一条记录");
        return;
    }

    QMessageBox::StandardButton reply;//删除之前先确认，防止误删
    reply = QMessageBox::question(
        this,
        "确认删除",
        "你确定要删除这条记录吗？",
        QMessageBox::Yes | QMessageBox::No);
    if (reply!= QMessageBox::Yes){return;}


    ui->tableWidget->removeRow(row);//确认之后再删除
    if (!removeRecordFromJson(row)){//json文件同步删除
        QMessageBox::warning(this, "删除失败","删除记录失败！");
    }
}

void MainWindow::addRecordToTable(const Record &r){
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    QString typeStr = (r.type == RecordType::Income) ? "收入" : "支出";

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(r.amount,'f',2)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(r.currency));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(typeStr));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(r.category));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(r.date.toString("yyyy-MM-dd")));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(r.comment));
}

// bool MainWindow::validateInputData(){
//     bool valid=true;
//     int row = ui->tableWidget->currentRow();

//     if (ui->tableWidget->item(row,0)->text().isEmpty()||ui->tableWidget->item(row,2)->text().isEmpty()){
//         valid=false;
//     }
//     return valid;
// }
