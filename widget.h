#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QToolBar>
#include <iostream>

#include <csquare.h>
#include <ccircle.h>
#include <clines.h>
#include <ctriangle.h>

namespace Ui {
class Widget;
}

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = nullptr);
    ~Widget();

private slots:
    void pushTr();
    void pushCr();
    void pushSq();
    void pushLn();
    void pushHn();
    void pushClear();
    void pushSave();
    void pushLoad();
    void onPointPresed(cbase*);
    void onNewPos(cbase* );
private:
    int serial_nomber_figure = 0;

    std::vector<cbase* > data;
    std::vector<clines* > lines;

    int _line_count = 0;
    cbase* _line_figura1 = nullptr;
    cbase* _line_figura2 = nullptr;

    void json_data_write(QJsonObject& currJSO);
    bool json_data_load(QJsonObject& root);
    QToolBar* createToolBar();

    Ui::Widget* ui;
    QGraphicsScene* scene;
};


