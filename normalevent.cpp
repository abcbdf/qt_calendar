#include "normalevent.h"
#include "ui_normalevent.h"

NormalEvent::NormalEvent(int _sign, QWidget *parent) :
    QDialog(parent),
    sign(_sign),
    ui(new Ui::NormalEvent)
{
    ui->setupUi(this);
    ui -> dateEdit ->setDate(QDate::currentDate());
    connect (this, &NormalEvent::accepted, this, &NormalEvent::send);
    connect (ui -> pushButton, &QPushButton::clicked, [this](){
        this -> close();
        emit del(ui -> lineEdit -> text(), ui -> dateEdit -> date(), sign);
    });
}

void NormalEvent::send()
{
    emit sen(ui -> lineEdit -> text(), ui -> textEdit -> toPlainText(), ui -> dateEdit -> date(), sign);
    qDebug() << ui -> lineEdit -> text() ;
}

NormalEvent::~NormalEvent()
{
    delete ui;
}
