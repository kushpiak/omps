#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <algorithm>

/* Функция для получения рандомного числа
 * в диапазоне от минимального до максимального
 * */
static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget* parent) :
   QMainWindow(parent),
    ui(new Ui::Widget)
{


    ui->setupUi(this);
    addToolBar(Qt::TopToolBarArea,createToolBar());
    this->setWindowTitle("Test task OMP (Kushpiak D.A.)");

    this->resize(640,640);
    this->setFixedSize(640,640);

    try
    {
        scene = new QGraphicsScene(this);
        scene->setItemIndexMethod(QGraphicsScene::NoIndex);

        ui->graphicsView->resize(640,640);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setRenderHint(QPainter::Antialiasing);
        ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
        ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

        scene->setSceneRect(0,0,500,500);

    }
    catch (const std::exception& e )
    {
        std::cout<<e.what()<<std::endl;
    }


}

Widget::~Widget()
{
    delete ui;
    for (auto& elem : lines)
    {
        delete elem;
    }
    for (auto& elem : data)
    {
        delete elem;
    }
    data.clear();
    lines.clear();
}


void Widget::pushTr()
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    try
    {
        cbase* item = new ctriangle(serial_nomber_figure++);        // Создаём графический элемент
        item->setPos(randomBetween(30, 470),    // Устанавливаем случайную позицию элемента
                     randomBetween(30, 470));
        scene->addItem(item);   // Добавляем элемент на графическую сцену
        item->newPosition(item->pos());
        item->action_moving(false);
        data.push_back(item);
        connect(item,SIGNAL(PointPresed(cbase*)),this,SLOT(onPointPresed(cbase*)));
        connect(item,SIGNAL(newPos(cbase*)),this,SLOT(onNewPos(cbase*)));
    }
    catch (const std::exception& e )
    {
        std::cout<<e.what()<<std::endl;
    }
}

void Widget::pushCr()
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    try
    {
        cbase* item = new ccircle(serial_nomber_figure++);
        item->setPos(randomBetween(30, 470),
                     randomBetween(30, 470));

        scene->addItem(item);
        item->newPosition(item->pos());
        item->action_moving(false);
        data.push_back(item);
        connect(item,SIGNAL(PointPresed(cbase*)),this,SLOT(onPointPresed(cbase*)));
        connect(item,SIGNAL(newPos(cbase*)),this,SLOT(onNewPos(cbase*)));
    }
    catch (const std::exception& e )
    {
        std::cout<<e.what()<<std::endl;
    }
}

void Widget::pushSq()
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    try
    {
        cbase* item = new csquare(serial_nomber_figure++);
        item->setPos(randomBetween(30, 470),
                     randomBetween(30, 470));

        scene->addItem(item);
        item->newPosition(item->pos());
        item->action_moving(false);
        data.push_back(item);
        connect(item,SIGNAL(PointPresed(cbase*)),this,SLOT(onPointPresed(cbase*)));
        connect(item,SIGNAL(newPos(cbase*)),this,SLOT(onNewPos(cbase*)));
    }
    catch (const std::exception& e )
    {
        std::cout<<e.what()<<std::endl;
    }
}

void Widget::pushLn()
{
    this->setCursor(QCursor(Qt::CrossCursor));
    _line_count = 0;
    _line_figura1 = nullptr;
    _line_figura2 = nullptr;
    for (auto& figura:data )
    {
        figura->action_moving(false);
        figura->action_line(true);
    }
}

void Widget::pushHn()
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    for (auto& figura:data )
    {
        figura->action_moving(true);
        figura->action_line(false);
    }
}

void Widget::pushClear()
{
    for (auto& lin : lines)
    {
        delete lin;
    }
    for (auto& elem : data)
    {
        delete elem;
    }
    data.clear();
    lines.clear();
    scene->clear();
}

void Widget::pushSave()
{
    QString file_name =QFileDialog::getSaveFileName(this, tr("Enter save file"),
                                                    ".",
                                                    tr("JSON (*.json )"));
    QFile file(file_name);
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonObject currJSO;
        currJSO=QJsonObject();
        json_data_write(currJSO);
        file.write(QJsonDocument(currJSO).toJson(QJsonDocument::Indented));
        file.close();
    }
    else std::cout<<"Error of file opening!"<<std::endl;
}

void Widget::pushLoad()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("JSON files (*.json)"));
    QFile file;
    if(file_name != "")
    {
        file.setFileName(file_name);
       if (file.open(QIODevice::ReadOnly))
       {
            std::cout<<"File open!"<<std::endl;
            QByteArray saveData = file.readAll();
            file.close();
            if ( saveData.size()>0 )
            {
                QJsonDocument doc=QJsonDocument::fromJson(saveData);
                QJsonObject root=doc.object();
                if (json_data_load(root)) std::cout<< "Success: data load"<<std::endl;
                else std::cout<< "Failue: data  not load"<<std::endl;
            }
            else std::cout<< " Error of file.readAll()"<<std::endl;
       }
       else std::cout<< " Error of file opening"<<std::endl;
    }
    else std::cout<< " Error of IsFileExist()"<<std::endl;
}

void Widget::onPointPresed(cbase* figura)
{
    _line_count++;
    if (_line_count == 1) _line_figura1 = figura;
    if (_line_count == 2)
    {
        _line_figura2 = figura;

        QLineF lin(_line_figura1->pos().x(), _line_figura1->pos().y(),_line_figura2->pos().x(), _line_figura2->pos().y());

        try
        {
            clines* clin = new clines(lin);
            clin->_nach = _line_figura1;
            clin->_end = _line_figura2;
            QGraphicsLineItem* item = scene->addLine(clin->_lf) ;
            clin->_item = item;
            lines.push_back(clin);
        }
        catch (const std::exception& e )
        {
            std::cout<<e.what()<<std::endl;
        }
        _line_count =0;
        _line_figura1 = nullptr;
        _line_figura2 = nullptr;
    }
}

void Widget::onNewPos(cbase* figura)
{
    for (auto & linija : lines)
    {
        if (linija->_nach == figura)
        {
            scene->removeItem(linija->_item);
            linija->_lf.setP1(linija->_nach->_central_pos);
            linija->_lf.setP2(linija->_end->_central_pos);
            linija->_item = scene->addLine(linija->_lf);
        }
        if (linija->_end == figura)
        {
            scene->removeItem(linija->_item);
            linija->_lf.setP1(linija->_nach->_central_pos);
            linija->_lf.setP2(linija->_end->_central_pos);
            linija->_item = scene->addLine(linija->_lf);
        }
    }
}



QToolBar* Widget::createToolBar()
{
    try
    {
        QToolBar* tb = new QToolBar("Tool bar");
        QPixmap pm_cr;
        if (!pm_cr.load("../icons/circle.png"))
        {
            qWarning("Failed to load picture ");
        }
        tb->addAction(pm_cr,"circle",this,SLOT(pushCr()));

        QPixmap pm_sq;
        if (!pm_sq.load("../icons/square.png"))
        {
            qWarning("Failed to load picture ");
        }
        tb->addAction(pm_sq,"square",this,SLOT(pushSq()));

        QPixmap pm_tr;
        if (!pm_tr.load("../icons/tr.png"))
        {
            qWarning("Failed to load picture ");
        }
        tb->addAction(pm_tr,"triangle",this,SLOT(pushTr()));
        tb->addSeparator();

        QPixmap pm_ln;
        if (!pm_ln.load("../icons/line.png"))
        {
            qWarning("Failed to load picture ");
        }
        tb->addAction(pm_ln,"line",this,SLOT(pushLn()));

        QPixmap pm_hand;
        if (!pm_hand.load("../icons/hand.png"))
        {
            qWarning("Failed to load picture ");
        }
        tb->addAction(pm_hand,"hand",this,SLOT(pushHn()));

        QPixmap pm_clear;
        if (!pm_clear.load("../icons/clear.png"))
        {
            qWarning("Failed to load picture ");
        }
        tb->addAction(pm_clear,"clear",this,SLOT(pushClear()));

        tb->addSeparator();
        QPixmap pm_save;
        if (!pm_save.load("../icons/save.png"))
        {
            qWarning("Failed to load picture ");
        }
        tb->addAction(pm_save,"save",this,SLOT(pushSave()));
        QPixmap pm_load;
        if (!pm_load.load("../icons/load.png"))
        {
            qWarning("Failed to load picture ");
        }
        tb->addAction(pm_load,"load",this,SLOT(pushLoad()));
        return tb;
    }
    catch (const std::exception& e )
    {
        std::cout<<e.what()<<std::endl;
    }
    return nullptr;
}

void Widget::json_data_write(QJsonObject& currJSO)
{
    const int data_size = data.size();
    QJsonArray bigArr = currJSO["FIGURELst"].toArray();
    if (data_size <= 0) return;
    for (const auto& figura:data)
        {
            QJsonObject obj;
            obj["type"] = figura->get_type_figure();
            obj["id"] = figura->id;
            obj["_central_pos.x"] = figura->_central_pos.x();
            obj["_central_pos.y"] = figura->_central_pos.y();

            bigArr.append(obj);
        }
    currJSO["FIGURELst"] = bigArr;


    QJsonArray otherArr = currJSO["LINESLst"].toArray();
    for (const auto& lin:lines)
        {
            QJsonObject obj;
            obj["nach_id"] = lin->_nach->id;
            obj["end_id"] = lin->_end->id;
            otherArr.append(obj);
        }
    currJSO["LINESLst"] = otherArr;

}

bool Widget::json_data_load(QJsonObject& root)
{
    bool rezult = true;
    cbase* structVar = nullptr;
    QJsonValue jsonV = root.value("FIGURELst");

    if(jsonV.isNull()) { rezult = false; }


    if (jsonV.isArray())
    {
        QJsonArray jsonArr = jsonV.toArray();

        for (int i = 0; i < jsonArr.count(); i++)
        {
            QJsonObject obj = jsonArr.at(i).toObject();
            int temp_id = obj.value("id").toInt();
            try
            {
                switch (obj.value("type").toInt())
                {
                case cbase::Circle_Type:
                    structVar = new ccircle(temp_id);
                    break;
                case cbase::Square_Type:
                    structVar = new csquare(temp_id);
                    break;
                case cbase::Triangle_Type:
                    structVar = new ctriangle(temp_id);
                    break;
                default:
                    break;
                }

                structVar->_central_pos.setX(obj.value("_central_pos.x").toDouble());
                structVar->_central_pos.setY(obj.value("_central_pos.y").toDouble());
                structVar->setPos(structVar->_central_pos);

                scene->addItem(structVar);
                structVar->newPosition(structVar->pos());
                structVar->action_moving(false);

                connect(structVar,SIGNAL(PointPresed(cbase*)),this,SLOT(onPointPresed(cbase*)));
                connect(structVar,SIGNAL(newPos(cbase*)),this,SLOT(onNewPos(cbase*)));



                data.push_back(structVar);
                serial_nomber_figure = structVar->id+1;
                rezult = rezult && true;
            }
            catch (const std::exception& e )
            {
                std::cout<<e.what()<<std::endl;
                rezult = false;
            }

        }
    }
    else rezult =false;

    jsonV = root.value("LINESLst");
    if (jsonV.isArray())
        {
            QJsonArray jsonArr = jsonV.toArray();

            for (int i = 0; i < jsonArr.count(); i++)
            {
                QJsonObject obj = jsonArr.at(i).toObject();
                int beg_id = obj.value("nach_id").toInt();
                int end_id = obj.value("end_id").toInt();
                cbase* beg_fig = nullptr;
                cbase* end_fig = nullptr;
                for (const auto& fig:data)
                {
                    if (fig->id == beg_id) beg_fig = fig;
                    if (fig->id == end_id) end_fig = fig;
                }

                if (beg_fig && end_fig)
                {
                    QLineF lin(beg_fig->pos().x(), beg_fig->pos().y(),end_fig->pos().x(), end_fig->pos().y());
                    try
                    {
                        clines* clin = new clines(lin);
                        clin->_nach = beg_fig;
                        clin->_end = end_fig;


                        QGraphicsLineItem* item = scene->addLine(clin->_lf) ;
                        clin->_item = item;
                        lines.push_back(clin);
                    }
                    catch (const std::exception& e )
                    {
                        std::cout<<e.what()<<std::endl;
                        rezult = false;
                    }

                }
            }
        }
    return rezult;
}




