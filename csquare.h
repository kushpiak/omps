#pragma once

#include "cbase.h"

class csquare : public cbase
{
    Q_OBJECT
public:
    explicit csquare(int serial_nomber_figure,QObject* parent = 0);
    ~csquare();

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};





