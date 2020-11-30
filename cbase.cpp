#include "cbase.h"

cbase::cbase(int serial_nomber_figure,QObject *parent) : QObject(parent)
{
    id = serial_nomber_figure;
}

cbase::cbase(int serial_nomber_figure,const QPointF& p, QObject *parent): QObject(parent), QGraphicsItem()
{
    Q_UNUSED(p);
    id = serial_nomber_figure;
}



cbase::~cbase()
{
    _item = nullptr;
}

void cbase::newPosition(const QPointF& p)
{
    _central_pos = p;
}

void cbase::set_type_figure(const int type)
{
    _type_figure = type;
}

int cbase::get_type_figure() const
{
    return _type_figure;
}

void cbase::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (get_status_moving())
    {

        this->setPos(mapToScene(event->pos()));
        _central_pos =pos();
        emit newPos(this);
    }
}

void cbase::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (get_status_line())
    {
        emit PointPresed(this);
    }
    Q_UNUSED(event);
}

void cbase::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
}

void cbase::action_moving(const bool status)
{
    if (status) _enable_moving = true;
    else _enable_moving = false;
}

bool cbase::get_status_moving() const
{
    return _enable_moving;
}

void cbase::action_line(const bool status)
{
    if (status) _enable_line = true;
    else _enable_line = false;
}

bool cbase::get_status_line() const
{
    return  _enable_line;
}

