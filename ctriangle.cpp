#include "ctriangle.h"



ctriangle::ctriangle(int serial_nomber_figure, QObject* parent): cbase(serial_nomber_figure,parent)
{
     set_type_figure(Triangle_Type);
}

ctriangle::~ctriangle()
{

}

QRectF ctriangle::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}

void ctriangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    QPolygonF polygon;

    polygon << QPointF(-30+60/2, -30)
                << QPointF(-30,-30+60)
                << QPointF(-30+60,-30+60);
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
