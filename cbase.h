#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>



class cbase : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES (QGraphicsItem)
public:
    explicit cbase(int serial_nomber_figure,QObject* parent = nullptr);
    explicit cbase(int serial_nomber_figure,const QPointF& p,QObject* parent = nullptr);
    virtual ~cbase();
    void action_moving(const bool status);
    bool get_status_moving() const ;

    void action_line(const bool status);
    bool get_status_line() const ;

    QPointF _central_pos;
    void newPosition(const QPointF& p);
    enum Base_Types
    {
       Circle_Type,
       Square_Type,
       Triangle_Type,
    };
    void set_type_figure(const int type);
    int get_type_figure() const;
    int id;
    QGraphicsLineItem* _item = nullptr;
signals:
    void PointPresed(cbase* );
    void newPos(cbase* );

private:
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) = 0;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    int _type_figure;
    bool _enable_moving = false;
    bool _enable_line = false;


};


