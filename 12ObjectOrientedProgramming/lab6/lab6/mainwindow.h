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
    void on_set1Button_clicked();
    void on_set2Button_clicked();
    void on_areaPushButton_clicked();
    void on_anglesPushButton_clicked();
    void on_perimeterPushButton_clicked();
    void on_mediansPushButton_clicked();
    void on_isRightPushButton_clicked();
    void on_increasePushButton_clicked();
    void on_increaseMPushButton_clicked();
    void on_comparePushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
