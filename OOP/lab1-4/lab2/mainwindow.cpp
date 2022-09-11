#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculator.h"
#include "math.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Calculator calculator = Calculator();

void MainWindow::on_buttonClearAll_clicked()
{
    ui->mainTextBox->setText("0");
    ui->debugLabel->setText("");
    calculator.reset();
}


void MainWindow::on_buttonClear_clicked()
{
    if (ui->mainTextBox->text().length() == 1 || ui->mainTextBox->text() == "Error") {
        ui->mainTextBox->setText("0");
    } else {
        QString text = ui->mainTextBox->text();
        text.chop(1);
        ui->mainTextBox->setText(text);
    }
}

void unaryOperation(Ui::MainWindow *ui, Calculator::operation op, std::string opName) {
    if (isnan(calculator.lValue)) {
        calculator.lValue = ui->mainTextBox->text().toDouble();
    }    calculator.op = op;
    calculator.calculate();
    if (isnan(calculator.result) || isinf(calculator.result)) {
        ui->mainTextBox->setText("Error");
        ui->debugLabel->setText("");
        return;
    }
    ui->mainTextBox->setText(QString::number(calculator.result));
    ui->debugLabel->setText(QString::fromStdString(opName) + "(" + QString::number(calculator.lValue) + ") = " + QString::number(calculator.result));
    calculator.reset();
}


void binaryOperation(Ui::MainWindow *ui, Calculator::operation op, std::string opName) {
    calculator.lValue = ui->mainTextBox->text().toDouble();
    calculator.op = op;
    ui->mainTextBox->setText("0");
    ui->debugLabel->setText(QString::number(calculator.lValue) + QString::fromStdString(opName));
}


void MainWindow::on_button1_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("1");
    } else {
        ui->mainTextBox->setText(ui->mainTextBox->text() + "1");
    }
}


void MainWindow::on_button2_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("2");
    } else {
        ui->mainTextBox->setText(ui->mainTextBox->text() + "2");
    }
}


void MainWindow::on_button3_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("3");
    } else {
        ui->mainTextBox->setText(ui->mainTextBox->text() + "3");
    }
}


void MainWindow::on_button4_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("4");
    } else {
        ui->mainTextBox->setText(ui->mainTextBox->text() + "4");
    }
}


void MainWindow::on_button5_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("5");
    } else {
        ui->mainTextBox->setText(ui->mainTextBox->text() + "5");
    }
}


void MainWindow::on_button6_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("6");
    } else {
        ui->mainTextBox->setText(ui->mainTextBox->text() + "6");
    }
}


void MainWindow::on_button7_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("7");
    } else {
        ui->mainTextBox->setText(ui->mainTextBox->text() + "7");
    }
}


void MainWindow::on_button8_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("8");
    } else {
        ui->mainTextBox->setText(ui->mainTextBox->text() + "8");
    }
}


void MainWindow::on_button9_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("9");
    } else {
        ui->mainTextBox->setText(ui->mainTextBox->text() + "9");
    }
}


void MainWindow::on_button0_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("0");
    } else {
        ui->mainTextBox->setText(ui->mainTextBox->text() + "0");
    }
}


void MainWindow::on_buttonDot_clicked()
{
    if (!ui->mainTextBox->text().contains(".")) {
        ui->mainTextBox->setText(ui->mainTextBox->text() + ".");
    }
}


void MainWindow::on_buttonEqual_clicked()
{
    if (isnan(calculator.lValue)) {return;}
    calculator.rValue = ui->mainTextBox->text().toDouble();
    calculator.calculate();
    if (isnan(calculator.result) || isinf(calculator.result)) {
        ui->mainTextBox->setText("Error");
        ui->debugLabel->setText("");
        return;
    }
    ui->mainTextBox->setText(QString::number(calculator.result));
    ui->debugLabel->setText(ui->debugLabel->text() + QString::number(calculator.rValue)  + " = " + QString::number(calculator.result));

    calculator.reset();
}


void MainWindow::on_buttonDivide_clicked()
{
    binaryOperation(ui, Calculator::operation::Divide, " ÷ ");
}


void MainWindow::on_buttonMultiply_clicked()
{
    binaryOperation(ui, Calculator::operation::Multiply, " × ");
}


void MainWindow::on_buttonSubstract_clicked()
{
    if (ui->mainTextBox->text() == "0") {
        ui->mainTextBox->setText("-");
        return;
    }
    binaryOperation(ui, Calculator::operation::Substract, " - ");

}


void MainWindow::on_buttonAdd_clicked()
{
    binaryOperation(ui, Calculator::operation::Add, " + ");

}


void MainWindow::on_buttonSqrt_clicked()
{
    unaryOperation(ui, Calculator::operation::Sqrt, "√");
}


void MainWindow::on_buttonMod_clicked()
{
    binaryOperation(ui, Calculator::operation::Mod, " % ");
}


void MainWindow::on_buttonPow_clicked()
{
    binaryOperation(ui, Calculator::operation::Pow, "^");
}


void MainWindow::on_buttonSin_clicked()
{
    unaryOperation(ui, Calculator::operation::Sin, "sin");
}


void MainWindow::on_buttonCos_clicked()
{
    unaryOperation(ui, Calculator::operation::Cos, "cos");
}


void MainWindow::on_buttonTan_clicked()
{
    unaryOperation(ui, Calculator::operation::Tan, "tan");
}


void MainWindow::on_buttonPi_clicked()
{
    ui->mainTextBox->setText(QString::number(calculator.PI));
}


void MainWindow::on_buttonE_clicked()
{
    ui->mainTextBox->setText(QString::number(calculator.E));

}
