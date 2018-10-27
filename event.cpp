#include "event.h"
#include "ui_event.h"

Event::Event(QString _title, QString _content, int _index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Event),
    title(_title),
    content(_content),
    index (_index)
{
    ui->setupUi(this);
    ui -> lineEdit -> setText(title);
    ui -> textEdit -> setText(content);
    connect (this, &Event::accepted, this, &Event::send);
    connect (ui -> pushButton, &QPushButton::clicked, [this](){
        this -> close();
        emit del(index);
    });
}

void Event::send()
{
    emit sen(ui -> lineEdit -> text(), ui -> textEdit -> toPlainText(), ui -> timeEdit -> time(), index);
    qDebug() << "closeEvent " << "title:" << title << " content:" << content << " index:" << index;
}

Event::~Event()
{

    delete ui;
}


void Event::on_pushButton_2_clicked()
{
    accept();
}

void Event::on_pushButton_3_clicked()
{
    reject();
}
