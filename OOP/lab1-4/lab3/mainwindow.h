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
    void on_actionNew_triggered();
    void on_actionText_triggered();
    void on_actionImage_triggered();
    void on_actionSave_triggered();
    void on_textEdit_textChanged();
    void on_actionClose_triggered();
    void on_actionPring_triggered();
    void on_actionFind_2_triggered();
    void on_actionFont_triggered();
    void on_actionColor_triggered();
    void on_actionReplace_2_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
