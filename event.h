#ifndef Event_H
#define Event_H

#include <QDialog>
#include <QString>
#include <QCloseEvent>
#include <QDebug>
#include <QTime>
namespace Ui {
class Event;
}

class Event : public QDialog
{
    Q_OBJECT

public:
    explicit Event(QString _title, QString _content, int _index, QWidget *parent = 0);
    ~Event();

signals:
    void sen(QString _title, QString _content, QTime t, int _index);
    void del(int _index);

public slots:
    void send();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Event *ui;
    QString title;
    QString content;
    int index;
};

#endif // Event_H
