#ifndef JSONUTILS_H
#define JSONUTILS_H

#include "record.h"
#include <Qjsonobject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

QJsonObject toJson(const Record &r);
bool saveRecordToJson(const Record &record, const QString &filename = "data.json");
QList<Record> loadRecordsFromJson(const QString &filename);
bool removeRecordFromJson(int index, const QString &filename="data.json");

#endif // JSONUTILS_H
