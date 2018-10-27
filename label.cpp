#include "label.h"

Label::Label(QString title):
    QLabel(title)
{

}

void Label::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
         emit click(this -> text());
    }
    else if(e->button()==Qt::RightButton)
    {
        emit del(this);
    }

}

/*void Label::mouseDoubleClickEvent(QMouseEvent *event)
{

}*/
