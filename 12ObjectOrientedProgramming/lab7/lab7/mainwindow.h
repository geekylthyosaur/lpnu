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
    void on_clearDequeButton_clicked();
    void on_getTablePushButton_clicked();
    void on_setTablePushButton_clicked();
    void on_addColPushButton_clicked();
    void on_rmColPushButton_clicked();
    void on_getListPushButton_clicked();
    void on_setListPushButton_clicked();
    void on_getLinePushButton_clicked();
    void on_setLinePushButton_clicked();
    void on_addRowPushButton_clicked();
    void on_rmRowPushButton_clicked();
    void on_minPushButton_clicked();
    void on_maxPushButton_clicked();
    void on_avgPushButton_clicked();
    void on_multiplyPushButton_clicked();
    void on_nPushButton_clicked();
    void on_emptyPushButton_clicked();

    void on_rmHeadPushButton_clicked();

    void on_rmTailPushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
