#include "ccircle.h"



ccircle::ccircle(int serial_nomber_figure,QObject *parent): cbase(serial_nomber_figure,parent)
{
    set_type_figure(Circle_Type);
}

ccircle::~ccircle()
{

}

QRectF ccircle::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}

void ccircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::blue);
    painter->drawEllipse(-30,-30,60,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
