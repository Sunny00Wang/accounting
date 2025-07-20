#ifndef RECORD_H
#define RECORD_H


#include<QString>
#include<QDate>


enum class RecordType{
    Income,
    Expense
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

inline QString recordTypeToString(RecordType type){//类型转换为字符串
    switch(type){
    case RecordType::Income: return "收入";
    case RecordType::Expense: return "支出";
    }
    return "未知";
}

inline RecordType recordTypeFromString(const QString &str) {//字符串转换为类型
    if (str =="收入") return RecordType::Income;
    if (str =="支出") return RecordType::Expense;
    return RecordType::Expense;
}

inline QString recordDateToString(const QDate &date){
    return date.toString("yyyy-MM-dd");
}

inline QDate recordDateFromString(const QString &str) {
    return QDate::fromString(str, "yyyy-MM-dd");
}


#endif // RECORD_H
