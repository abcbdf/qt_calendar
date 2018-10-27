#ifndef DATEDATA_H
#define DATEDATA_H

#include <QString>
#include <QVector>
#include <QColor>
#include <QDebug>
#include <label.h>
class DateData
{
public:
    DateData();
    QVector<QString> Title;
    QVector<QString> Content;
    QVector<QTime> times;
    QColor color;
    QVector<Label*> labels;
};

#endif // DATEDATA_H
