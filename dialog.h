#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "datedata.h"
#include <QColorDialog>
#include <QCloseEvent>
#include <QPushButton>
#include <QVector>
#include "event.h"
#include <QVBoxLayout>
#include <QLabel>
#include "label.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFile>
#include <QDir>
#include <QDrag>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT


public:
    explicit Dialog(DateData* , QWidget *parent = 0);
    ~Dialog();
    void addNewButton(int index);
    void addNewLabel(int index);
    DateData* datedata;
    QVBoxLayout* topLayout;
    bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist);
    QString saveAd;
    void copy(QString);
    void dele(Label*);

private:
    Ui::Dialog *ui;    
    QColorDialog* colordialog;
    QVector<QPushButton*> Buttons;
    QPushButton* more;
    Event* e;

signals:
    void turnoff();
    void refresh();

protected:
    virtual void closeEvent(QCloseEvent*);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


};

#endif // DIALOG_H
