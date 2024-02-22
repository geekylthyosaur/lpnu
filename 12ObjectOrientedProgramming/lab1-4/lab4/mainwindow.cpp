#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->gameTimer = new QTimer(this);
    this->labelTimer = new QTimer(this);
    this->loseTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::spawnNumber);
    connect(labelTimer, &QTimer::timeout, this, &MainWindow::updateTimeLabel);
    connect(loseTimer, &QTimer::timeout, this, &MainWindow::lose);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    ui->tableWidget->setEnabled(true);
    ui->startButton->setEnabled(false);

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText("0");
            ui->tableWidget->setItem(i, j, item);
        }
    }

    int row = rand() % ( ui->tableWidget->rowCount() );
    int col = rand() % ( ui->tableWidget->columnCount() );
    ui->tableWidget->item(row, col)->setText("1");
    gameTimer->start((10 - ui->levelSpinBox->value()) * 500);
    labelTimer->start(100);
    loseTimer->start(20000);
}


void MainWindow::spawnNumber() {

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
            ui->tableWidget->item(i, j)->setText("0");

    int row = rand() % ( ui->tableWidget->rowCount() );
    int col = rand() % ( ui->tableWidget->columnCount() );
    ui->tableWidget->item(row, col)->setText("1");
    gameTimer->stop();
    gameTimer->start((10 - ui->levelSpinBox->value()) * 500);

}


void MainWindow::updateTimeLabel() {
    ui->timeLabel->setText(QString::number(loseTimer->remainingTime() / 1000));
}


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if (ui->tableWidget->item(row, column)->text() == "1") {
        ui->levelSpinBox->setValue(ui->levelSpinBox->value() + 1);
        ui->tableWidget->item(row, column)->setText("0");
        if (ui->levelSpinBox->value() == 9) win();
        else spawnNumber();
    } else {
        if (ui->attemptLabel->text() == "0" || ui->timeLabel->text() == "0") lose();
        else ui->attemptLabel->setText(QString::number(ui->attemptLabel->text().toInt() - 1));
    }
}


void MainWindow::win() {
    labelTimer->stop();
    gameTimer->stop();
    loseTimer->stop();
    QMessageBox msgBox;
    msgBox.setText("Ви виграли.");
    msgBox.exec();
    ui->tableWidget->setEnabled(false);
    ui->startButton->setEnabled(true);
    ui->levelSpinBox->setValue(1);
    ui->timeLabel->setText("20");
    ui->attemptLabel->setText("10");
}


void MainWindow::lose() {
    labelTimer->stop();
    gameTimer->stop();
    loseTimer->stop();
    QMessageBox msgBox;
    msgBox.setText("Ви програли.");
    msgBox.exec();
    ui->tableWidget->setEnabled(false);
    ui->startButton->setEnabled(true);
    ui->levelSpinBox->setValue(1);
    ui->timeLabel->setText("20");
    ui->attemptLabel->setText("10");
}
