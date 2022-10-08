#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_addPersonBtn_clicked();

    void on_actionby_Blood_Pressure_triggered();

    void on_actionType_and_RhD_triggered();

    void on_actionRhD_and_Heart_Rate_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
