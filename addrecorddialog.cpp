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
        QMessageBox::warning(this, "输入错误", "金额必须大于0！");
        return;
    }

    if (!ui->radioIncome->isChecked() && !ui->radioExpense->isChecked()) {
        QMessageBox::warning(this, "选择错误", "请选择收入或支出类型");
        return;
    }

    // ✅ 所有校验通过后再开始赋值
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
    accept();  // ✅ 最后统一执行

    // double amount = ui->lineEditAmount->text().toDouble();
    // QString currency = ui->comboBoxCurrency->currentText();//选择币种，欧元或是人民币
    // QString category = ui->comboBoxCategory->currentText();//写入金额分类
    // QDate date = ui->dateEditDate->date();//写入日期
    // QString comment;//写入备注

    // if (ui->lineEditAmount->text().trimmed().isEmpty()){    //如果金额为空那么弹出错误框，如果正常那么就提取字符串并且转换为double类型
    //     QMessageBox::warning(this, "输入错误", "请输入金额");
    //     return;}

    // else if (amount <= 0){
    //      QMessageBox::warning(this, "输入错误", "金额必须大于0！");
    //     return;}
    // else if(ui->radioExpense->isChecked()){ //选择金额类型，必须选择支出或者收入
    //     r.type = RecordType::Expense;
    // }
    // else if (ui->radioIncome->isChecked()){
    //     r.type = RecordType::Income;
    // }
    // else if (!ui->radioIncome->isChecked()&&!ui->radioExpense->isChecked()){
    //     QMessageBox::warning(this, "选择错误", "请选择收入支出类型");
    //     return;
    // }
    // else{
    //     r.amount = amount;
    //     r.currency = currency;
    //     r.category = category;
    //     r.date = date;
    //     r.comment = comment;
    //     recordData = r;//把临时变量r保存到成员变量RecordData里面
    //     accept();}



}

Record AddRecordDialog::getRecord() const{
    return recordData;
}

