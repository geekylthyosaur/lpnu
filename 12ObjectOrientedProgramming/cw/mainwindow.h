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
    void on_healthyPeople_triggered();
    void on_highPressureAndRate_triggered();
    void on_actionDefault_triggered();
    void on_bestDonors_triggered();
    void on_bestRecipients_triggered();
    void on_donorsRecepients_triggered();
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_actionClose_triggered();
    void on_actionType_triggered();
    void on_bSortByBloodPressure_clicked();
    void on_bSortByRhD_clicked();
    void on_bSortByBloodType_clicked();
    void on_bShowBestRecipients_clicked();
    void on_bShowBestDonors_clicked();
    void on_bShowDonorsAndRecipients_clicked();
    void on_bShowDefault_clicked();
    void on_bSortByRhDAndRate_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
