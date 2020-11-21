#ifndef ARROWLINE_H
#define ARROWLINE_H
#include<QGraphicsLineItem>
#include<QPainter>#include<math.h>
class ArrowLine: public QWidget
{
    Q_OBJECT
private:
    QPoint a,b;
public:
    ArrowLine(QPoint,QPoint);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) ;
    void DrawLineWithArrow(QPainter *painter, QPoint start, QPoint end);

};

#endif // ARROWLINE_H
