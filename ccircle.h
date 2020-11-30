#pragma once

#include "cbase.h"

class ccircle : public cbase
{
    Q_OBJECT
public:
    explicit ccircle(int serial_nomber_figure,QObject* parent = 0);
    ~ccircle();

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

