#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <calendar.h>
#include <QVBoxLayout>
#include <normalevent.h>
#include <QTranslator>
#include <login.h>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = 0);
    Calendar* cal;
    QString cfaddr;
    QVBoxLayout *layout;
    ~MainWindow();
    NormalEvent* ne;
    LogIn* login;
    QVector<QString> usernames;
    QVector<QString> passwords;
    QVector<QString> useraddrs;
    QString user_name;
    QString dataAddr;
    void setNe(int);
    void addthing(QString title, QString content, QDate);
    bool transparent;
    void delthing(QString title, QDate date);
    void read(QString);
    void write_data(QString address);
    void fromVariantMap(QVariantMap const& v);
    QVariantMap toVariantMap() const;

public slots:
    void fixed();
};

#endif // MAINWINDOW_H
