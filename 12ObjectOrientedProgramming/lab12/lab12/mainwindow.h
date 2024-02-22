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
    void on_inputButton_clicked();

    void on_outputButton_clicked();

    void on_minButton_clicked();

    void on_maxButton_clicked();

    void on_avgButton_clicked();

    void on_clearButton_clicked();

    void on_createButton_clicked();

    void on_addColButton_clicked();

    void on_rmColButton_clicked();

    void on_getButton_clicked();

    void on_setButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
