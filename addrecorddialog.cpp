#include "addrecorddialog.h"
#include "ui_addrecorddialog.h"
#include "record.h"
#include <QMessageBox>


AddRecordDialog::AddRecordDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddRecordDialog)
{
    ui->setupUi(this);
    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddRecordDialog::onAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddRecordDialog::reject);
    ui->dateEditDate->setDate(QDate::currentDate());
    ui->radioExpense->setChecked(true);
}

AddRecordDialog::~AddRecordDialog()
{
    delete ui;
}


void AddRecordDialog::onAccept(){

    Record r;

    QString amountStr = ui->lineEditAmount->text().trimmed();
    if (amountStr.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入金额");
        return;
    }

    double amount = amountStr.toDouble();
    if (amount <= 0) {
        QMessageBox::warning(this, "输入错误", "金额必须是数字且大于0！");
        return;
    }

    if (!ui->radioIncome->isChecked() && !ui->radioExpense->isChecked()) {
        QMessageBox::warning(this, "选择错误", "请选择收入或支出类型");
        return;
    }

    //  所有校验通过后再开始赋值
    r.amount = amount;
    r.currency = ui->comboBoxCurrency->currentText();
    r.category = ui->comboBoxCategory->currentText();
    r.date = ui->dateEditDate->date();
    r.comment = ui->lineEditcomment->text(); // 假设备注控件名是这个

    if (ui->radioExpense->isChecked())
        r.type = RecordType::Expense;
    else
        r.type = RecordType::Income;

    recordData = r;
    accept();  //  最后统一执行



}

Record AddRecordDialog::getRecord() const{
    return recordData;
}

