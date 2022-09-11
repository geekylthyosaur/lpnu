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
    void on_createButton_clicked();
    void on_findButton_clicked();
    void on_multiplyButton_clicked();
    void on_findDerButton_clicked();
    void on_findIntegralButton_clicked();
    void on_findRootsButton_clicked();
    void on_addButton_clicked();
    void updatePolynomial();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
