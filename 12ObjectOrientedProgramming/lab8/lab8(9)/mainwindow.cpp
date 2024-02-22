#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "deposit.h"
#include "termdeposit.h"
#include "accumulativedeposit.h"
#include "vipdeposit.h"

#include "QMessageBox"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

Deposit *d;

void MainWindow::on_startButton_clicked() {
    if (
            ui->startMoneyEdit->text() == "" || ui->startTermEdit->text() == "" ||
            ui->startRateEdit->text() == "" ||
            (ui->typeComboBox->currentIndex() == 2 && (ui->startRateIncCoefEdit->text() == ""
                                                       || ui->startMaxRateEdit->text() == ""))
        ) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Information");
        msgBox.setText("Fill in all the fields to get started!");
        msgBox.exec();
        return;
    }

    double money = ui->startMoneyEdit->text().toDouble();
    double term = ui->startTermEdit->text().toDouble();
    double rate = ui->startRateEdit->text().toDouble();

    if (ui->typeComboBox->currentIndex() == 0) {
        d = new TermDeposit(money, rate, term);
    } else if (ui->typeComboBox->currentIndex() == 1) {
        d = new AccumulativeDeposit(money, rate, term);
    } else if (ui->typeComboBox->currentIndex() == 2) {
        double rateIncCoef = ui->startRateIncCoefEdit->text().toDouble();
        double maxRate = ui->startMaxRateEdit->text().toDouble();
        d = new VIPDeposit(rateIncCoef, maxRate, money, rate, term);
    }
    ui->startGroupBox->setEnabled(false);
    ui->currentGroupBox->setEnabled(true);
    ui->moneyEdit->setText(QString::number(d->getMoney()));
    ui->rateEdit->setText(QString::number(d->getRate()));
}

void MainWindow::on_typeComboBox_currentIndexChanged(int index) {
    if (index == 2) {
        ui->startGroupBox->setFixedHeight(240);
        ui->currentGroupBox->setFixedHeight(180);
    } else if (index == 1) {
        ui->startGroupBox->setFixedHeight(180);
        ui->currentGroupBox->setFixedHeight(150);
    } else {
        ui->startGroupBox->setFixedHeight(180);
        ui->currentGroupBox->setFixedHeight(120);
    }
}

void MainWindow::on_addMoneyButton_clicked() {
    double money = ui->addMoneyEdit->text().toDouble();
    static_cast<VIPDeposit*>(d)->putMoney(money);
    static_cast<VIPDeposit*>(d)->setRate(d->getRate() + (static_cast<VIPDeposit*>(d)->getRateIncCoef() / 100) * money);
    if (d->getRate() > static_cast<VIPDeposit*>(d)->getMaxRate())
        static_cast<VIPDeposit*>(d)->setRate(static_cast<VIPDeposit*>(d)->getMaxRate());
    ui->moneyEdit->setText(QString::number(d->getMoney()));
    ui->rateEdit->setText(QString::number(d->getRate()));
}

void MainWindow::on_profitButton_clicked() {
    if (ui->typeComboBox->currentIndex() == 0) {
        if (ui->profitMonthsEdit->text() == "") {
            ui->profitEdit->setText(QString::number(static_cast<TermDeposit*>(d)->calculateProfit()));
            ui->paidEdit->setText(QString::number(static_cast<TermDeposit*>(d)->calculateProfit()));
        }
        else {
            ui->profitEdit->setText(QString::number(static_cast<TermDeposit*>(d)->calculateProfit(ui->profitMonthsEdit->text().toDouble())));
            ui->paidEdit->setText(QString::number(static_cast<TermDeposit*>(d)->calculateProfit(ui->profitMonthsEdit->text().toDouble())));
        }
    } else if (ui->typeComboBox->currentIndex() == 1) {
        if (ui->profitMonthsEdit->text() == "") {
            ui->profitEdit->setText(QString::number(static_cast<AccumulativeDeposit*>(d)->calculateProfit()));
            ui->paidEdit->setText(QString::number(static_cast<AccumulativeDeposit*>(d)->calculateProfit()));
        }
        else {
            ui->profitEdit->setText(QString::number(static_cast<AccumulativeDeposit*>(d)->calculateProfit(ui->profitMonthsEdit->text().toDouble())));
            ui->paidEdit->setText(QString::number(static_cast<AccumulativeDeposit*>(d)->calculateProfit(ui->profitMonthsEdit->text().toDouble())));
        }
    } else if (ui->typeComboBox->currentIndex() == 2) {
        if (ui->profitMonthsEdit->text() == "") {
            QString profit = QString::number(static_cast<VIPDeposit*>(d)->calculateProfit());
            ui->profitEdit->setText(profit);
            ui->paidEdit->setText(profit);
        }
        else {
            ui->profitEdit->setText(QString::number(static_cast<VIPDeposit*>(d)->calculateProfit(ui->profitMonthsEdit->text().toDouble())));
            ui->paidEdit->setText(QString::number(static_cast<VIPDeposit*>(d)->calculateProfit(ui->profitMonthsEdit->text().toDouble())));
        }
    }
}

void MainWindow::on_clearButton_clicked() {
    ui->startGroupBox->setEnabled(true);
    delete d;

    ui->startMaxRateEdit->clear();
    ui->startMoneyEdit->clear();
    ui->startRateEdit->clear();
    ui->startRateIncCoefEdit->clear();
    ui->startTermEdit->clear();

    ui->moneyEdit->clear();
    ui->paidEdit->clear();
    ui->profitEdit->clear();
    ui->profitMonthsEdit->clear();
    ui->rateEdit->clear();
    ui->addMoneyEdit->clear();

    ui->currentGroupBox->setEnabled(false);
}

void MainWindow::on_printButton_clicked() {
    ui->printLabel->setText(Deposit::print()+" "+TermDeposit::print()+" "+AccumulativeDeposit::print()+" "+VIPDeposit::print());
}

void MainWindow::on_writeButton_clicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Save As");

    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);

    Deposit * deposit = new Deposit(d->getMoney(), d->getRate(), d->getTerm());

    out << "Money:" << deposit->getMoney() << " Rate:" << deposit->getRate() << " Term:" << deposit->getTerm() << "\n";
    file.close();
    delete deposit;
}

