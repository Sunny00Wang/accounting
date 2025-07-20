#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"record.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void onAddRecord();
    void onDeleteRecord();
    void addRecordToTable(const Record &r);
    //bool validateInputData();
    };
#endif // MAINWINDOW_H
