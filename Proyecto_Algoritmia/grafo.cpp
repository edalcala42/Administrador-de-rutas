#include "grafo.h"

int Grafo::getX() const
{
    return x;
}

int Grafo::getY() const
{
    return y;
}

int Grafo::getTam() const
{
    return tam;
}

Grafo::Grafo()
{
    over=false;
    x=0;
    y=0;
    tam=20;
}

Grafo::Grafo(int px, int py, int t, QString n)
{
    x=px;
    y=py;
    tam=t;
    over=false;
    name=n;
    //setFlag(ItemIsMovable);
}

void Grafo::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);

    over=true;
    update();

}

void Grafo::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent)
    over=false;

    update();
    emit selectedNode(x,y,tam,name);
}


QRectF Grafo::boundingRect() const
{
    return QRectF(x, y, tam, tam);
}

void Grafo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec=boundingRect();
    QBrush brush(Qt::red);
    QPen pen = painter->pen();
    pen.setCosmetic(true);
    pen.setColor(QColor(Qt::green));
    painter->setPen(pen);
    brush = painter->brush();
    QPixmap pa;
    pa.fill(Qt::white);
    brush.setTexture(pa);
    if(over)
        brush.setStyle(Qt::Dense7Pattern);
    else
        brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawEllipse(rec);
    pen.setColor(QColor(Qt::white));
    QFont font("Times", 15, QFont::Bold);
    painter->setFont(font);
    painter->drawText(rec,Qt::AlignCenter,name);

}
