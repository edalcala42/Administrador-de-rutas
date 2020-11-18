#ifndef GRAFO_H
#define GRAFO_H
#include<QGraphicsObject>
#include <QBrush>
#include <QPainter>
#include<QMouseEvent>
#include<QWidget>
#include <iostream>
#include<QPixmap>
//#include "ui_mainwindow.h"

class Grafo: public QGraphicsObject
{Q_OBJECT

private:
    int x,y,tam;
    bool over;
    QString name;
signals:
    void selectedNode(int,int,int,QString);
public:
    Grafo();
    Grafo(int,int,int,QString);
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) ;

    int getX() const;
    int getY() const;
    int getTam() const;
};

#endif // GRAFO_H
