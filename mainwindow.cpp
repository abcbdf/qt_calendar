#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    transparent(false),
    cfaddr("config.txt")
{
    ui->setupUi(this);
    cal = new Calendar(user_name, dataAddr);
    read(cfaddr);
    login = new LogIn;
    login -> show();
    connect (login, &LogIn::sen, [this](QString name, QString password, QString ad, bool isNew){
        if (!isNew)
        {
            if (usernames.contains(name))
            {
                int index = usernames.indexOf(name);
                if (passwords[index] == password)
                {
                    user_name = name;
                    if (ad.size() != 0)
                    {
                        useraddrs[index] = ad;
                        dataAddr = ad;
                        cal -> setUserName(user_name);
                        cal -> setAddr_fresh(dataAddr);
                    }
                    else
                    {
                        dataAddr = useraddrs[index];
                        cal -> setUserName(user_name);
                        cal -> setAddr_fresh(dataAddr);
                    }
                }
                else
                {
                    QMessageBox::warning(0, tr("Warning"), tr("error password"));
                    login -> show();
                }
            }
            else
            {
                QMessageBox::warning(0, tr("Warning"), tr("error username"));
                login -> show();
            }
        }
        else
        {
            usernames.append(name);
            passwords.append(password);
            useraddrs.append(ad);
            user_name = name;
            dataAddr = ad;
            cal -> setUserName(user_name);
            cal -> setAddr_fresh(dataAddr);
        }
    });

    //qDebug() << "dataAddr: " << dataAddr;

    layout = new QVBoxLayout;
    layout->addWidget(cal);
    ui -> centralWidget->setLayout(layout);
    ui -> actionFix ->setShortcut(Qt::Key_F5);
    connect(ui -> actionFix,SIGNAL(triggered()),this,SLOT(fixed()));
    connect (ui -> actionEveryday, &QAction::triggered, [this](){
        setNe(1);
    });
    connect (ui -> actionEveryweek, &QAction::triggered, [this](){
        setNe(2);
    });
    connect (ui -> actionEverymonth, &QAction::triggered, [this](){
        setNe(3);
    });

}

void MainWindow::setNe(int sign)
{
    ne = new NormalEvent(sign);
    ne -> show();
    connect (ne, &NormalEvent::sen, [this](QString title, QString content, QDate date, int sign)
    {
        switch (sign)
        {
            case 1:
                for (int i = 0; i < 2000; i ++)
                {
                    QDate newdate = date.addDays(i);
                    addthing(title, content, newdate);
                }
                break;
            case 2:
                for (int i = 0; i < 1000; i ++)
                {
                    QDate newdate = date.addDays(i * 7);
                    addthing(title, content, newdate);
                }
                break;
            case 3:
                for (int i = 0; i < 1000; i ++)
                {
                    QDate newdate = date.addMonths(i);
                    addthing(title, content, newdate);
                }
                break;

        }
    });
    connect (ne, &NormalEvent::del, [this](QString title, QDate date, int sign)
    {
        switch (sign)
        {
            case 1:
                for (int i = 0; i < 2000; i ++)
                {
                    QDate newdate = date.addDays(i);
                    delthing(title, newdate);
                }
                break;
            case 2:
                for (int i = 0; i < 1000; i ++)
                {
                    QDate newdate = date.addDays(i * 7);
                    delthing(title, newdate);
                }
                break;
            case 3:
                for (int i = 0; i < 1000; i ++)
                {
                    QDate newdate = date.addMonths(i);
                    delthing(title, newdate);
                }
                break;

        }
    });
}

MainWindow::~MainWindow()
{
    write_data(cfaddr);
    delete ui;
}

void MainWindow::addthing(QString title, QString content, QDate date)
{
    if(cal -> dates.contains(date))
    {

    }
    else
    {
        cal -> dates.append(date);
        DateData* d = new DateData;
        cal -> datedatas.append(*d);
    }
    int index = cal -> dates.indexOf(date);
    cal -> datedatas[index].Title.append(title);
    cal -> datedatas[index].Content.append(content);
}


void MainWindow::fixed()
{
    if(!transparent)
    {
        this->close();
        this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setWindowOpacity(0.5);
        this->show();
        qDebug() << "transparent";
        transparent = true;
    }
    else
    {
        this->close();
        this->setAttribute(Qt::WA_TransparentForMouseEvents,false);
        this->setWindowFlags(Qt::WindowFlags());
        this->setWindowOpacity(1);
        this->show();
        qDebug() << "no transparent";
        transparent = false;
    }
}

void MainWindow::delthing(QString title, QDate date)
{
    if(cal -> dates.contains(date))
    {
        int index = cal -> dates.indexOf(date);
        if (cal -> datedatas[index].Title.contains(title))
        {
            int _index = cal -> datedatas[index].Title.indexOf(title);
            cal -> datedatas[index].Title.remove(_index);
            cal -> datedatas[index].Content.remove(_index);
        }
    }

}



void MainWindow::read(QString _addr)
{
    qDebug() << "read_config";
    QFile file(_addr);
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
                qDebug() << "yesyes";
            }
        }
        file.close();
        qDebug() <<  "errrrrror";
    }
    else
    {
        qDebug() << "address error";
    }
}

void MainWindow::write_data(QString address)
{
    qDebug() << "save";
    QFile file(address);
    file.open(QFile::WriteOnly);
    QTextStream(&file) << QJsonDocument::fromVariant(toVariantMap()).toJson();
    file.close();
}

QVariantMap MainWindow::toVariantMap() const
{
    QVariantMap v;
    QVariantList usernameslist;
    for(auto x: usernames)
    {
        usernameslist.append(x);
    }
    v.insert("usernameslist", usernameslist);
    QVariantList passwordslist;
    for(auto x: passwords)
    {
        passwordslist.append(x);
    }
    v.insert("passwordslist", passwordslist);
    QVariantList useraddrslist;
    for(auto x: useraddrs)
    {
        useraddrslist.append(x);
    }
    v.insert("useraddrslist", useraddrslist);
    qDebug() << v;
    return v;
}

void MainWindow::fromVariantMap(QVariantMap const& v)
{
    qDebug() << v;
    usernames.clear();
    for(auto x: v["usernameslist"].toList())
    {
        usernames.append(x.toString());
        qDebug() << x.toString();
    }
    passwords.clear();
    for(auto x: v["passwordslist"].toList())
    {
        passwords.append(x.toString());
        qDebug() << x.toString();
    }
    useraddrs.clear();
    for(auto x: v["useraddrslist"].toList())
    {
        useraddrs.append(x.toString());
        qDebug() << x.toString();
    }
}






