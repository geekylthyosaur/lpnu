#include "list.h"

List::List()
{

}

void operator << (QFile &out, const Person &p)
{
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
       }
       inputFile.close();
    }
}

void operator >> (Person &p, QFile &in)
{

}
