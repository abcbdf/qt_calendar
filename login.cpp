#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    connect (this, &LogIn::accepted, [this](){
        emit sen(ui -> lineEdit -> text(), ui -> lineEdit_2 -> text(), s, ui -> checkBox -> isChecked());
    });
    connect (this, &LogIn::rejected, [this](){
        exit(0);
    });
    connect (ui -> pushButton_3, &QPushButton::clicked, [this](){
        QFileDialog* f = new QFileDialog;
        f -> setWindowModality(Qt::ApplicationModal);
        f -> show();
        connect (f, &QFileDialog::fileSelected, [this](QString _s){
            s = _s;
        });
    });
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_pushButton_clicked()
{
    accept();
}

void LogIn::on_pushButton_2_clicked()
{
    reject();
}
