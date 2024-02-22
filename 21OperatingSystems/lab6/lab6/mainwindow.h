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
    void update();

private slots:
    void on_bStart_clicked();

    void on_bCheck_clicked();

    void on_bSetPriority_clicked();

    void on_bDetach_clicked();

    void on_bCancel_clicked();

    void on_bSetAffinity_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
