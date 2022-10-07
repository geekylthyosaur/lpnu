#include "app.h"
#include "QDebug"

App::App(Ui::MainWindow* ui)
{
    this->list = new List();
    this->ui = ui;
}

void App::addPerson()
{
    QString s = ui->nLE->text() + "," +
            ui->surnameLE->text() + "," +
            ui->ageLE->text() + "," +
            ui->bloodpressureLE->text() + " " +
            ui->bloodtypeLE->text() +
            ui->rhdLE->text() + "," +
            ui->heartrateLE->text();
    Person p = Person(s);
    this->list->push(p);
}

void App::updateTable()
{
    this->clearTable();
    for (int i = 0; i < list->len(); i++)
    {
        ui->tableWidget->insertRow(i);
        Person * p = this->list->get(i);
        for (int j = 0; j < 7; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem();

            switch (j)
            {
            case 0:
                item->setText(QString::number(p->getN()));
                break;
            case 1:
                item->setText(p->getSurname());
                break;
            case 2:
                item->setText(QString::number(p->getAge()));
                break;
            case 3:
                item->setText(p->getBlood()->getType());
                break;
            case 4:
                item->setText(p->getBlood()->getRhDStr());
                break;
            case 5:
                item->setText(p->getBlood()->getPressure());
                break;
            case 6:
                item->setText(QString::number(p->getHeartRate()));
                break;
            }
            ui->tableWidget->setItem(i, j, item);
        }
    }
}

void App::clearTable()
{
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(0);
}

void App::readFromFile(QString fileName)
{
    QFile file(fileName);
    this->list->clear();
    file >> this->list;
}

void App::writeToFile(QString fileName)
{
    QFile file(fileName);
    file << this->list;
}

void App::sort(int columnIndex)
{
    this->list->quickSort(columnIndex, 0, this->list->len() - 1);
}
