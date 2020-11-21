#include "nodegraphic.h"

int NodeGraphic::getX() const
{
    return x;
}

int NodeGraphic::getY() const
{
    return y;
}

int NodeGraphic::getTam() const
{
    return tam;
}

bool NodeGraphic::getOver() const
{
    return over;
}

void NodeGraphic::setOver(bool value)
{
    over = value;
}

NodeGraphic::NodeGraphic()
{
    over=false;
    x=0;
    y=0;
    tam=20;
}

NodeGraphic::NodeGraphic(int px, int py, int t, QString n)
{
    x=px;
    y=py;
    tam=t;
    over=false;
    name=n;
}

void NodeGraphic::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    update();
}

void NodeGraphic::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent)
    update();
    over=true;
    emit selectedNode(x,y,tam,name);
}


QRectF NodeGraphic::boundingRect() const
{
    return QRectF(x, y, tam, tam);
}

void NodeGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec=boundingRect();
    QBrush brush(painter->brush());
    QPen pen(painter->pen());
    if(over)
        brush.setColor(QColor(36,207,213));
    else
        brush.setColor(QColor(Qt::black));
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawEllipse(rec);
    if(over)
        pen.setColor(QColor(Qt::black));
    else
        pen.setColor(QColor(Qt::white));
    painter->setPen(pen);
    QFont font("Times", 12, QFont::Bold);
    painter->setFont(font);
    painter->drawText(rec,Qt::AlignCenter,name);
}
