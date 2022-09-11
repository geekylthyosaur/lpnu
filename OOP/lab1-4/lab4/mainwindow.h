#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    void spawnNumber();
    void updateTimeLabel();
    void win();
    void lose();
    void on_startButton_clicked();
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    QTimer *gameTimer;
    QTimer *labelTimer;
    QTimer *loseTimer;

};
#endif // MAINWINDOW_H
