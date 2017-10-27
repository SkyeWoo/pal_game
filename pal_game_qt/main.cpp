#include "controller.h"
#include <QApplication>
#include <QTime>

QPainter p;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    Controller w;
    w.show();

    return a.exec();
}
