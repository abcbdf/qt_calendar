#include "super.h"
#include "ui_super.h"


Super::Super(Shell* _s, QApplication* a, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Super),
    s(_s)
{
    ui->setupUi(this);
    connect (ui -> pushButton, &QPushButton::clicked, [=](){
        s -> i = 1;
        qDebug() << "here1";
        QString path;
        QDir dir;
        QString addr = dir.currentPath() + "/" + "cn.qm";
        qDebug() << "addr.size() == 0";
        QTranslator translator;
        bool b = false;
        b = translator.load(addr);
        qDebug() << b;
        a -> installTranslator(&translator);
        //w = new MainWindow;
        //w -> show();
        close();
    });
    connect (ui -> pushButton_2, &QPushButton::clicked, [=](){
        s -> i = 2;
        qDebug() << "here2";
        QTranslator translator;
        bool b = false;
        b = translator.load("en.qm");
        qDebug() << b;
        a -> installTranslator(&translator);
        //w = new MainWindow;
        //w -> show();
        close();
    });
}

Super::~Super()
{
    delete ui;
}
