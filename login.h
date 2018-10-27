#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QFileDialog>
#include <QPushButton>

namespace Ui {
class LogIn;
}

class LogIn : public QDialog
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = 0);
    ~LogIn();
    QString s;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    sen(QString name, QString password, QString addr, bool isNew);

private:
    Ui::LogIn *ui;
};

#endif // LOGIN_H
