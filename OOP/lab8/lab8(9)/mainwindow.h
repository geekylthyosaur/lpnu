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
    void on_startButton_clicked();
    void on_typeComboBox_currentIndexChanged(int index);
    void on_addMoneyButton_clicked();
    void on_profitButton_clicked();
    void on_clearButton_clicked();

    void on_printButton_clicked();

    void on_writeButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
