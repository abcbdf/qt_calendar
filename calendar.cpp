#include "calendar.h"



Calendar::Calendar(QString _user_name, QString _addr, QWidget *parent):
    QCalendarWidget(parent),
    addr(_addr),
    user_name(_user_name)
{
//    if (addr.size() == 0)
//    {
//        QString path;
//        QDir dir;
//        addr = dir.currentPath() + "/" + "calendar.txt";
//        qDebug() << "addr.size() == 0";
//    }

    qDebug() << read_data(addr);
    connect(this, &Calendar::activated, [this](QDate date){
        if(dates.contains(date))
        {

        }
        else
        {
            dates.append(date);
            DateData* d = new DateData;
            datedatas.append(*d);
        }
        int index = dates.indexOf(date);
        dia = new Dialog(&datedatas[index]);
        dia->show();
        qDebug() << date;
        connect(dia, SIGNAL(turnoff()), this, SLOT(set()));
        connect(dia, &Dialog::refresh, [=](){
            dia -> close();
            emit activated(date);
        });
    });
    for(int i = 0; i < dates.size(); i ++)
    {
        setDateBack(dates[i], datedatas[i].color);
    }

}
void Calendar::set()
{
    for (int i = 0; i < dates.size(); i ++)
    {
        setDateBack(dates[i], datedatas[i].color);
    }
}

void Calendar::setDateBack(QDate date, QColor color)
{
    QBrush brush;
    brush.setColor(color);

    QTextCharFormat cf = this->dateTextFormat(date);
    cf.setBackground(brush);
    this->setDateTextFormat(date, cf);

}

Calendar::~Calendar()
{
    write_data(addr);
}


QString Calendar::read_data(QString address)
{
    qDebug() << "read: " << address;
    QFile file(address);
    if (file.exists())
    {

        file.open(QFile::ReadOnly);
        QString s = QTextStream(&file).readAll();
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(s.toUtf8(), &error);
        if(error.error == QJsonParseError::NoError)
        {
            if(jsonDoc.isObject())
            {
                qDebug() << "json success";
                fromVariantMap(jsonDoc.toVariant().toMap());
                return "yesyes";
            }
        }
        file.close();
        return "errrrrror";
    }
    else
    {
        file.open(QFile::ReadOnly);
        file.close();
        return "address error";
    }
}

void Calendar::write_data(QString address)
{
    qDebug() << "save:"  << address;
    QFile file(address);
    file.open(QFile::WriteOnly);
    QTextStream(&file) << QJsonDocument::fromVariant(toVariantMap()).toJson();
    file.close();
}

QVariantMap Calendar::toVariantMap() const
{
    QVariantMap v;
    QVariantList dateslist;
    for(auto x: dates)
    {
        dateslist.append(x);
    }
    v.insert("dateslist", dateslist);
    QVariantList datedataslist;
    for(auto x: datedatas)
    {
        datedataslist.append(dtoVariantMap(&x));
    }
    v.insert("datedataslist", datedataslist);
    qDebug() << v;
    return v;
}

QVariantMap Calendar::dtoVariantMap(DateData* d) const
{
    QVariantMap v;
    QVariantList Titlelist;
    for(auto x: d -> Title)
    {
        Titlelist.append(x);
    }
    v.insert("Titlelist", Titlelist);
    QVariantList Contentlist;
    for(auto x: d -> Content)
    {
        Contentlist.append(x);
    }
    v.insert("Contentlist", Contentlist);
    v.insert("color", d -> color);
    QVariantList labelslist;
    for(auto x: d -> labels)
    {
        labelslist.append(x -> text());
    }
    v.insert("labelslist", labelslist);
    return v;
}


void Calendar::fromVariantMap(QVariantMap const& v)
{
    qDebug() << v;
    dates.clear();
    for(auto x: v["dateslist"].toList())
    {
        dates.append(x.toDate());
    }
    datedatas.clear();
    for(auto x: v["datedataslist"].toList())
    {
        datedatas.append(dfromVariantMap(x.toMap()));
    }
}

DateData Calendar::dfromVariantMap(QVariantMap const& v)
{
    DateData* dd = new DateData;
    dd -> Title.clear();
    for(auto x: v["Titlelist"].toList())
    {
        dd -> Title.append(x.toString());
    }
    dd -> Content.clear();
    for(auto x: v["Contentlist"].toList())
    {
        dd -> Content.append(x.toString());
    }
    dd -> color = v["color"].value<QColor>();
    dd -> labels.clear();
    for(auto x: v["labelslist"].toList())
    {
        dd -> labels.append(new Label(x.toString()));
    }
    return *dd;
}

void Calendar::setAddr_fresh(QString _addr)
{
    //addr = _addr;
    if (_addr.size() == 0)
    {
        if (addr.size() == 0)
        {
            QString path;
            QDir dir;
            addr = dir.currentPath() + "/" + user_name + "_calendar.txt";
            qDebug() << "addr.size() == 0";
        }
        else
        {

        }

    }
    else
    {
        addr = _addr;
    }
    read_data(addr);
}

void Calendar::setUserName(QString _user_name)
{
    user_name = _user_name;
    if (addr.size() == 0)
    {
        QString path;
        QDir dir;
        addr = dir.currentPath() + "/" + user_name + "_calendar.txt";
        qDebug() << "addr.size() == 0";
    }
}






















