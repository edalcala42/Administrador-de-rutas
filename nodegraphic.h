#ifndef NODEGRAPHIC_H
#define NODEGRAPHIC_H
#include<QGraphicsObject>
#include <QBrush>
#include <QPainter>
#include<QMouseEvent>
#include<QWidget>
#include <iostream>
#include<QPixmap>
//#include "ui_mainwindow.h"

class NodeGraphic: public QGraphicsObject
{Q_OBJECT

private:
    int x,y,tam;
    bool over;
    QString name;
signals:
    void selectedNode(int,int,int,QString);
public:
    NodeGraphic();
    NodeGraphic(int,int,int,QString);
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) ;

    int getX() const;
    int getY() const;
    int getTam() const;
    bool getOver() const;
    void setOver(bool value);
};

#endif // GRAFO_H
