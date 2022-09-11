#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QPrintDialog>
#include <QSaveFile>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QImageReader>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionNew_triggered() {
    ui->textEdit->setEnabled(true);
    ui->textEdit->setVisible(true);
    ui->imageLabel->setVisible(false);
    ui->imageLabel->setEnabled(false);
    setWindowTitle("New File");
}

void MainWindow::on_actionText_triggered() {
    ui->textEdit->setEnabled(true);
    ui->textEdit->setVisible(true);
    ui->imageLabel->setVisible(false);
    ui->imageLabel->setEnabled(false);
    ui->textEdit->clear();

    QFile file(QFileDialog::getOpenFileName(this, tr("Open File"), "/home/dmytro/", tr("(*)")));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
        ui->textEdit->setText(ui->textEdit->toPlainText() + line + "\n");

        line = in.readLine();
    }
    file.close();

    setWindowTitle(file.fileName());
}

void MainWindow::on_actionImage_triggered() {
    ui->textEdit->clear();
    ui->textEdit->setEnabled(false);
    ui->textEdit->setVisible(false);
    ui->imageLabel->setEnabled(true);
    ui->imageLabel->setVisible(true);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/dmytro/", tr("(*)"));
    QImageReader reader(fileName);
        reader.setAutoTransform(true);
        const QImage newImage = reader.read();

        QImage image = newImage;
            ui->imageLabel->setPixmap(QPixmap::fromImage(image));
            ui->imageLabel->setScaledContents(true);

        setWindowTitle(fileName);
}

void MainWindow::on_actionSave_triggered() {
    if (!windowTitle().contains("*")) {
        return;
    }

    QString filename= QFileDialog::getSaveFileName(this, "Save As");

    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << ui->textEdit->toPlainText() << "\n";

    setWindowTitle(file.fileName());

    file.close();
}

void MainWindow::on_textEdit_textChanged() {
    if (!windowTitle().contains("*"))
        setWindowTitle(windowTitle() + "*");
}

void MainWindow::on_actionClose_triggered() {
    ui->textEdit->clear();
    ui->imageLabel->clear();
    setWindowTitle("Notebook");
    ui->textEdit->setEnabled(false);
    ui->textEdit->setVisible(false);
    ui->imageLabel->setEnabled(false);
    ui->imageLabel->setVisible(false);

}

void MainWindow::on_actionPring_triggered() {

}

void MainWindow::on_actionFind_2_triggered() {

}

void MainWindow::on_actionFont_triggered() {
    ui->textEdit->setFont(QFontDialog::getFont(0, ui->textEdit->font()));

}

void MainWindow::on_actionColor_triggered() {
    ui->textEdit->setTextColor(QColorDialog().getColor());
}

void MainWindow::on_actionReplace_2_triggered() {

}

