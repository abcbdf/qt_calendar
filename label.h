#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QMouseEvent>
class Label : public QLabel
{
    Q_OBJECT
public:
    Label(QString);

signals:
    void click(QString);
    void del(Label*);
protected:
    virtual void mousePressEvent(QMouseEvent *ev);
    //virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // LABEL_H
