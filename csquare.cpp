#include "csquare.h"

csquare::csquare(int serial_nomber_figure,QObject* parent) : cbase(serial_nomber_figure,parent)
{
    set_type_figure( Square_Type);
}

csquare::~csquare()
{

}

QRectF csquare::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}

void csquare::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::red);
    painter->drawRect(-30,-30,60,60);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}






