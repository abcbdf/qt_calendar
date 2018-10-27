#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(DateData* _datedata, QWidget *parent) :
    QDialog(parent),
    datedata (_datedata),
    ui(new Ui::Dialog),
    saveAd(""),
    colordialog(new QColorDialog(_datedata -> color))
{
    ui->setupUi(this);
    QString path;
    QDir dir;
    saveAd = dir.currentPath();
    topLayout = new QVBoxLayout;
    ui -> scrollAreaWidgetContents -> setLayout(topLayout);
    connect (ui -> pushButton, &QPushButton:: clicked, [this](){colordialog -> show();} );
    connect (colordialog, &QColorDialog :: colorSelected, [this](QColor color){
        datedata -> color = color;
        qDebug() << color;});

    if (datedata -> Title.size() != 0)
    {
        for (int i = 0; i < datedata -> Title.size(); i ++)
        {
            addNewButton(i);
        }
    }
    else
    {

    }
    if (datedata -> labels.size() != 0)
    {
        for (int i = 0; i < datedata -> labels.size(); i ++)
        {
            addNewLabel(i);
        }
    }
    else
    {

    }
    more = new QPushButton(tr("add more..."));
    topLayout -> addWidget(more);
    qDebug() << datedata -> Title.size();
    connect (more, &QPushButton::clicked, [=](){
        qDebug() << "click";
        e = new Event("", "", datedata -> Title.size());
        e -> show();
        connect (e, &Event::sen, [=](QString _title, QString _content, QTime t, int _index){
            datedata -> Title.append(_title);
            datedata -> Content.append(_content);
            datedata -> times.append(t);
            //this -> close();
            addNewButton(_index);
            emit refresh();
            //this -> show();
        });
    });
}

void Dialog::addNewButton(int index)
{
    QPushButton* but = new QPushButton(datedata -> Title[index]);
    topLayout -> addWidget(but);
    Buttons.append(but);
    connect (but, &QPushButton::clicked, [=](){
        e = new Event(datedata -> Title[index], datedata -> Content[index], index);
        e -> show();
        connect (e, &Event::sen, [=](QString _title, QString _content, QTime t, int _index){
            datedata -> Title[index] = _title;
            datedata -> Content[index] = _content;
            datedata -> times[index] = t;
        });
        connect (e, &Event::del, [this](int _index){
            if (_index < datedata -> Title.size() && _index < datedata -> Content.size())
            {
                datedata -> Title.remove(_index);
                datedata -> Content.remove(_index);
                delete Buttons[_index];
                Buttons.remove(_index);
                emit refresh();
                /*this -> close();
                this -> show();*/
                //qDebug() << _index << _index;
                //qDebug() << "yes" << datedata -> Title.size();
            }
        });
    });
    //qDebug() << index;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::closeEvent(QCloseEvent*e)
{
    emit turnoff();
    e -> accept();
}



void Dialog::dragEnterEvent(QDragEnterEvent *event)
{


    if (event->mimeData()->hasFormat("text/uri-list"))
       event->acceptProposedAction();
}


void Dialog::dropEvent(QDropEvent *event)
{

    QList<QUrl> urls = event->mimeData()->urls();
    qDebug() << ".......";
    if(urls.isEmpty())
        return;


    foreach(QUrl url, urls) {
        QString file_name = url.toLocalFile();
        int index = file_name.lastIndexOf("/");
        QString temp = file_name;
        temp.remove(0, index + 1);
        QString path = saveAd;
        path = path + "/" + temp;
        if (file_name != path)
        {
            copyFileToPath(file_name, path, true);
            Label* label = new Label(temp);
            topLayout -> addWidget(label);
            datedata -> labels.append(label);
            connect (label, &Label::click, [this](QString title){
                    copy(title);
            });
            connect (label, &Label::del, this, &Dialog::dele);
            refresh();
        }
        else{};
    }
}


bool Dialog::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        qDebug() << "sfsfsfjslf";
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
            qDebug() << "remove";
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}



void Dialog::copy(QString title)
{
    QMimeData *QD = new QMimeData;
    QList<QUrl> urls;
    QString filename = saveAd + "/" + title;
    urls.append(QUrl::fromLocalFile(filename));
    QD->setUrls(urls);
    //QApplication::clipboard()->setMimeData(QD);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(QD);
    drag->exec(Qt::CopyAction);
    qDebug()<<filename<<urls;
}

void Dialog::dele(Label* lab)
{
    if (datedata -> labels.contains(lab))
    {
        int index = datedata -> labels.indexOf(lab);
        QString tit = lab -> text();
        QString filename = saveAd + "/" + tit;
        QDir* d = new QDir;
        d -> remove(filename);
        delete lab;
        datedata -> labels.remove(index);
    }
}

void Dialog::addNewLabel(int index)
{
    topLayout -> addWidget(datedata -> labels[index]);
    connect (datedata -> labels[index], &Label::click, [this](QString title){
            copy(title);
    });
    connect (datedata -> labels[index], &Label::del, this, &Dialog::dele);
}















