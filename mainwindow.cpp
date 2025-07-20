#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QMessageBox>
#include "addrecorddialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"金额"<<"币种"<<"类型"<<"分类"<<"日期"<<"备注");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->actionAddRecord, &QAction::triggered, this, &MainWindow::onAddRecord);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddRecord()
{
    // 这里写你点击“添加记录”后要执行的逻辑
    AddRecordDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted){
        Record r = dialog.getRecord();
        addRecordToTable(r);

        //recordList.append(r);


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

bool MainWindow::validateInputData(){
    bool valid=true;
    int row = ui->tableWidget->currentRow();

    if (ui->tableWidget->item(row,0)->text().isEmpty()||ui->tableWidget->item(row,2)->text().isEmpty()){
        valid=false;
    }
    return valid;
}
