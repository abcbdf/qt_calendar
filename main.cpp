#include "mainwindow.h"
#include <QApplication>
#include <calendar.h>
#include <super.h>
#include <shell.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Shell s;
    Super p(&s, &a);
    p.show();

    p.exec();
    qDebug() << s.i << "ksjfljfjsklfjkldjflsjflsfjslfjskf";
    QTranslator translator;
    if (s.i == 1)
    {
        bool b = false;
        b = translator.load("cn.qm");
        qDebug() << b;
        a.installTranslator(&translator);
        qDebug() << "aaaaaaaaaa";
    }

    MainWindow m;
    m.show();
    return a.exec();
}
