#include "app.h"
#include "QDebug"

App::App(Ui::MainWindow* ui)
{
    this->list = new List();
    this->ui = ui;
}

void App::addPerson()
{
    bool ok;
    if (ui->nLE->text().toInt(&ok) == 0)
        if (!ok)
            throw 1;
    if (ui->ageLE->text().toInt(&ok) == 0)
        if (!ok)
            throw 3;
    if (ui->bloodtypeLE->text() != "O" && ui->bloodtypeLE->text() != "A" && ui->bloodtypeLE->text() != "B" && ui->bloodtypeLE->text() != "AB")
        throw 4;
    if (!ui->bloodpressureLE->text().contains("/"))
        throw 5;
    if (ui->rhdLE->text() != "+" && ui->rhdLE->text() != "-")
        throw 6;
    if (ui->heartrateLE->text().toInt(&ok) == 0)
        if (!ok)
            throw 7;
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
    ui->tableHealthy->setVisible(false);
    ui->tableWidget->setVisible(true);
    ui->tableDonorsAndRecipients->setVisible(false);
    this->clearTable();
    for (int i = 0; i < list->len(); i++)
    {
        ui->tableWidget->insertRow(i);
        Person * p = this->list->get(i);
        for (int j = 0; j < 7; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
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
                item->setText(p->getBlood()->getTypeStr());
                break;
            case 4:
                item->setText(p->getBlood()->getRhDStr());
                break;
            case 5:
                item->setText(p->getBlood()->getPressureStr());
                break;
            case 6:
                item->setText(QString::number(p->getHeartRate()));
                break;
            }
            ui->tableWidget->setItem(i, j, item);
        }
    }
}

void App::healthyPeople()
{
    ui->tableHealthy->setVisible(true);
    ui->tableWidget->setVisible(false);
    ui->tableDonorsAndRecipients->setVisible(false);
    ui->tableHealthy->setColumnCount(2);
    ui->tableHealthy->setRowCount(0);
    ui->tableHealthy->setColumnWidth( 0, 360 );
    ui->tableHealthy->setColumnWidth( 1, 360 );
    QStringList labels;
    labels << "Surname" << "Message";
    ui->tableHealthy->setHorizontalHeaderLabels(labels);
    int r = 0;
    for (int i = 0; i < list->len(); i++)
    {
        Person * p = this->list->get(i);
        bool healthy = p->getBlood()->getPressureHigh() <= 140 &&
                       p->getBlood()->getPressureLow() <= 100 &&
                       p->getBlood()->getPressureHigh() >= 100 &&
                       p->getBlood()->getPressureLow() >= 60;

        if (healthy)
            ui->tableHealthy->insertRow(r);
        else
            continue;
        for (int j = 0; j < 2; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
            switch (j)
            {
            case 0:
                item->setText(p->getSurname());
                break;
            case 1:
                item->setText(QString::fromStdString("Healthy"));
                break;
            }
            ui->tableHealthy->setItem(r, j, item);
        }
        r++;
    }
}

void App::highPressureAndRate(int age)
{
    ui->tableHealthy->setVisible(false);
    ui->tableWidget->setVisible(true);
    ui->tableDonorsAndRecipients->setVisible(false);
    this->clearTable();
    int r = 0;
    for (int i = 0; i < list->len(); i++)
    {
        Person * p = this->list->get(i);
        bool highPressureAndRate = p->getHeartRate() >= 100 &&
                p->getBlood()->getPressureHigh() >= 140 &&
                p->getBlood()->getPressureLow() >= 100 &&
                p->getAge() == age;

        if (highPressureAndRate)
            ui->tableWidget->insertRow(r);
        else
            continue;
        for (int j = 0; j < 7; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
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
                item->setText(p->getBlood()->getTypeStr());
                break;
            case 4:
                item->setText(p->getBlood()->getRhDStr());
                break;
            case 5:
                item->setText(p->getBlood()->getPressureStr());
                break;
            case 6:
                item->setText(QString::number(p->getHeartRate()));
                break;
            }
            ui->tableWidget->setItem(r, j, item);
        }
        r++;
    }
}

void App::bestDonors()
{
    ui->tableHealthy->setVisible(false);
    ui->tableWidget->setVisible(true);
    ui->tableDonorsAndRecipients->setVisible(false);
    this->clearTable();
    int r = 0;
    for (int i = 0; i < list->len(); i++)
    {
        Person * p = this->list->get(i);
        bool bestDonor = p->getBlood()->getTypeStr() == p->getBlood()->BEST_DONOR;

        if (bestDonor)
            ui->tableWidget->insertRow(r);
        else
            continue;
        for (int j = 0; j < 7; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
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
                item->setText(p->getBlood()->getTypeStr());
                break;
            case 4:
                item->setText(p->getBlood()->getRhDStr());
                break;
            case 5:
                item->setText(p->getBlood()->getPressureStr());
                break;
            case 6:
                item->setText(QString::number(p->getHeartRate()));
                break;
            }
            ui->tableWidget->setItem(r, j, item);
        }
        r++;
    }
}

void App::bestRecipients()
{
    ui->tableHealthy->setVisible(false);
    ui->tableWidget->setVisible(true);
    ui->tableDonorsAndRecipients->setVisible(false);
    this->clearTable();
    int r = 0;
    for (int i = 0; i < list->len(); i++)
    {
        Person * p = this->list->get(i);
        bool bestRecipient = p->getBlood()->getTypeStr() == p->getBlood()->BEST_RECIPIENT;

        if (bestRecipient)
            ui->tableWidget->insertRow(r);
        else
            continue;
        for (int j = 0; j < 7; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
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
                item->setText(p->getBlood()->getTypeStr());
                break;
            case 4:
                item->setText(p->getBlood()->getRhDStr());
                break;
            case 5:
                item->setText(p->getBlood()->getPressureStr());
                break;
            case 6:
                item->setText(QString::number(p->getHeartRate()));
                break;
            }
            ui->tableWidget->setItem(r, j, item);
        }
        r++;
    }
}

void App::donorsAndRecipients()
{
    ui->tableHealthy->setVisible(false);
    ui->tableWidget->setVisible(true);
    ui->tableDonorsAndRecipients->setVisible(false);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(5);
    QStringList labels;
    labels << "N" << "Surname" << "Age" << "Donor to" << "Recipient from";
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->setColumnWidth( 0, 40 );
    ui->tableWidget->setColumnWidth( 1, 400 );
    ui->tableWidget->setColumnWidth( 2, 40 );
    ui->tableWidget->setColumnWidth( 3, 100 );
    ui->tableWidget->setColumnWidth( 4, 100 );

    for (int i = 0; i < list->len(); i++)
    {
        ui->tableWidget->insertRow(i);
        Person * p = this->list->get(i);
        for (int j = 0; j < 5; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
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
                item->setText(QString::fromStdString("..."));
                break;
            case 4:
                item->setText(QString::fromStdString("..."));
                break;
            }
            ui->tableWidget->setItem(i, j, item);
        }
    }
}

void App::showDonorsTo(int i)
{
    this->clearTable();
    int personBloodType = list->get(i)->getBlood()->getType();
    int r = 0;
    for (int i = 0; i < list->len(); i++)
    {
        Person * p = this->list->get(i);
        bool donorTo = p->getBlood()->getType() >= personBloodType;
        if (personBloodType == 2 && p->getBlood()->getType() == 3)
            continue;
        if (donorTo)
            ui->tableWidget->insertRow(r);
        else
            continue;
        for (int j = 0; j < 7; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
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
                item->setText(p->getBlood()->getTypeStr());
                break;
            case 4:
                item->setText(p->getBlood()->getRhDStr());
                break;
            case 5:
                item->setText(p->getBlood()->getPressureStr());
                break;
            case 6:
                item->setText(QString::number(p->getHeartRate()));
                break;
            }
            ui->tableWidget->setItem(r, j, item);
        }
        r++;
    }
}

void App::showRecipientsFrom(int i)
{
    this->clearTable();
    int personBloodType = list->get(i)->getBlood()->getType();
    int r = 0;
    for (int i = 0; i < list->len(); i++)
    {
        Person * p = this->list->get(i);
        bool recipientFrom = p->getBlood()->getType() <= personBloodType;
        if (personBloodType == 3 && p->getBlood()->getType() == 2)
            continue;
        if (recipientFrom)
            ui->tableWidget->insertRow(r);
        else
            continue;
        for (int j = 0; j < 7; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
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
                item->setText(p->getBlood()->getTypeStr());
                break;
            case 4:
                item->setText(p->getBlood()->getRhDStr());
                break;
            case 5:
                item->setText(p->getBlood()->getPressureStr());
                break;
            case 6:
                item->setText(QString::number(p->getHeartRate()));
                break;
            }
            ui->tableWidget->setItem(r, j, item);
        }
        r++;
    }
}

void App::clearTable()
{
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(0);
    QStringList labels;
    labels << "N" << "Surname" << "Age" << "Type" << "RhD" << "Pressure" << "Rate";
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->setColumnWidth( 0, 40 );
    ui->tableWidget->setColumnWidth( 1, 400 );
    ui->tableWidget->setColumnWidth( 2, 40 );
    ui->tableWidget->setColumnWidth( 3, 40 );
    ui->tableWidget->setColumnWidth( 4, 20 );
    ui->tableWidget->setColumnWidth( 5, 80 );
    ui->tableWidget->setColumnWidth( 6, 40 );
}

void App::readFromFile(QString fileName)
{
    QFile file(fileName);
    this->list->clear();
    file >> this->list;
}

void App::writeToFile(QString fileName)
{
    if (this->list->len() == 0)
        throw 1;
    QFile file(fileName);
    file << this->list;
}

void App::sort(int columnIndex)
{
    this->list->quickSort(columnIndex, 0, this->list->len() - 1);
}
