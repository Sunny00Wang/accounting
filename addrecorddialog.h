#ifndef ADDRECORDDIALOG_H
#define ADDRECORDDIALOG_H
#include "record.h"
#include <QDialog>

namespace Ui {
class AddRecordDialog;
}

class AddRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecordDialog(QWidget *parent = nullptr);
    ~AddRecordDialog();
    Record getRecord() const;

private slots:
    void onAccept();

private:
    Ui::AddRecordDialog *ui;
    Record recordData;//成员变量，用来传递数据
};

#endif // ADDRECORDDIALOG_H
