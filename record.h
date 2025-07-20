#ifndef RECORD_H
#define RECORD_H


#include<QString>
#include<QDate>


enum class RecordType{
    Income,
    Expense,
    notype
};

struct Record
{
    double amount; //金额
    QString currency; //币种
    RecordType type;
    QString category;
    QDate date;
    QString comment;
    Record() {}
};


#endif // RECORD_H
