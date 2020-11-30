#pragma once

#include "cbase.h"

class ctriangle : public cbase
{
    Q_OBJECT
public:
    explicit ctriangle(int serial_nomber_figure, QObject* parent = 0);
    ~ctriangle();

private:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};
