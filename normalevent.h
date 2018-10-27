#ifndef NORMALEVENT_H
#define NORMALEVENT_H

#include <QDialog>
#include <QDate>
#include <QDebug>
namespace Ui {
class NormalEvent;
}

class NormalEvent : public QDialog
{
    Q_OBJECT

public:
    explicit NormalEvent(int _sign, QWidget *parent = 0);// 1 everyday, 2 everyweek, 3 everymonth
    ~NormalEvent();
    int sign;

signals:
    void sen(QString, QString, QDate, int);
    void del(QString, QDate, int);

public slots:
    void send();


private:
    Ui::NormalEvent *ui;
};

#endif // NORMALEVENT_H
