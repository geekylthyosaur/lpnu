#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qdebug.h"
#include <string.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<QString> filterIfContains(QList<QString>, QString);
    QList<QString> filterIfNotContains(QList<QString>, QString);

private slots:
    void on_pushButton_Find_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    std::string requestFilePath = "/home/dmytro/req";
    std::string responseFilePath = "/home/dmytro/res";

    char separator = '@';
    char iseparator = '#';
};
#endif // MAINWINDOW_H
