#pragma once
#include "cbase.h"

class clines :public QObject
{
    Q_OBJECT
public:
    explicit clines(QLineF l);
    QLineF _lf;
    cbase* _nach = nullptr;
    cbase* _end = nullptr;
    QGraphicsLineItem* _item = nullptr;
    ~clines();
};
