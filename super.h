#ifndef SUPER_H
#define SUPER_H

#include <QDialog>
#include <mainwindow.h>
#include <QApplication>
#include <QDebug>
#include <shell.h>
namespace Ui {
class Super;
}

class Super : public QDialog
{
    Q_OBJECT

public:
    explicit Super(Shell* _s, QApplication* a, QWidget *parent = 0);
    Shell* s;
    //MainWindow* w;
    ~Super();
    int sign;


private:
    Ui::Super *ui;
};

#endif // SUPER_H
