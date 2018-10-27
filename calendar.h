#ifndef CALENDAR_H
#define CALENDAR_H

#include <QCalendarWidget>
#include <dialog.h>
#include <QPainter>
#include <QTextCharFormat>
#include <QObject>
#include <QDate>
#include <QColor>
#include <QComboBox>
#include <QVariant>
#include <QMap>
#include <QJsonDocument>
class Calendar : public QCalendarWidget
{
    Q_OBJECT

public:
    Calendar(QString _user_name, QString _addr = "", QWidget *parent = 0);
    Dialog* dia;
    QVector<QDate> dates;
    QVector<DateData> datedatas;
    QString addr;
    QString user_name;

    ~Calendar();
    QString read_data(QString address);
    void write_data(QString address);
    void fromVariantMap(QVariantMap const& v);
    DateData dfromVariantMap(QVariantMap const& v);
    QVariantMap toVariantMap() const;
    QVariantMap dtoVariantMap(DateData*) const;
    void setAddr_fresh(QString);
    void setUserName(QString);


public slots:
    void setDateBack(QDate, QColor);
    void set();

protected:
    //virtual void paintCell(QPainter * painter, const QRect & rect, const QDate & date) const;
};



#endif // CALENDAR_H
