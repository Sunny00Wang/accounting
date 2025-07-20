#include "jsonutils.h"
#include "record.h"


QJsonObject toJson(const Record &r){
    QJsonObject obj;
    obj["amount"] = r.amount;
    obj["currency"] = r.currency;
    obj["type"] = recordTypeToString(r.type);
    obj["category"] = r.category;
    obj["date"] = recordDateToString(r.date);
    obj["comment"] = r.comment;
    return obj;
}
//==========================================数据读写相关
bool saveRecordToJson(const Record &record, const QString &filename){//把表格数据写入json
    QJsonArray dataArray;
    QFile file(filename);

    //读取旧数据
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (doc.isArray()) dataArray = doc.array();
        file.close();
    }

    dataArray.append(toJson(record));

    //写入新数据

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QJsonDocument doc(dataArray);
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        return true;
    }
    return false;
}


QList<Record> loadRecordsFromJson(const QString &filename){//把json数据载入表格
    QList<Record> records;
    QFile file(filename);

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            QJsonArray array = doc.array();
            for (const QJsonValue &val : array){
                QJsonObject obj = val.toObject();
                Record r;
                r.amount = obj["amount"].toDouble();
                r.currency = obj["currency"].toString();
                r.type = recordTypeFromString(obj["type"].toString());
                r.category =  obj["category"].toString() ;
                r.date = recordDateFromString(obj["date"].toString());
                r.comment = obj["comment"].toString();

                records.append(r);
            }
        }
        file.close();
    }

    return records;

}
//============================================数据删除
bool removeRecordFromJson(int index, const QString &filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return false;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) return false;

    QJsonArray array = doc.array();
    if (index < 0 || index >= array.size()) return false;

    array.removeAt(index);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;
    file.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

