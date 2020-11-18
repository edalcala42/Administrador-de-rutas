#include "graphclass.h"

void GraphClass::changedNodeT(int x, int y, int d, QString aux)
{
    Q_UNUSED(d);Q_UNUSED(y);Q_UNUSED(d);
    emit callNodeChanged(aux);
}

void GraphClass::insertNode(QString n)
{
    srand((unsigned)time(0));
    int max=(nodes.size()+5)*30;
    int val = (rand()%(max))-max;
    Grafo *nuevo=new Grafo(nodes.size()*30+(nodes.size()*30),val,30,n);
    nuevo->setZValue(1);
    nodes[n]=nuevo;
    connect(nuevo,SIGNAL(selectedNode(int,int,int,QString)),this,SLOT(changedNodeT(int,int,int,QString)));
    scene->addItem(nuevo);
}

void GraphClass::addConnection(QString a, QString b)
{
    Grafo* aux=nodes[a];
    Grafo* aux2=nodes[b];

    int tam=aux->getTam();
    int px=aux->getX(),py=aux->getY();
    std::pair<int,int> z,z2;
    z={px+(tam/2),py+(tam/2)};
    px=aux2->getX(),py=aux2->getY();
    z2={px+(tam/2),py+(tam/2)};
    QGraphicsLineItem *line=new QGraphicsLineItem(z.first,z.second,z2.first,z2.second,NULL);
    connections[a][b]=line;
    QPen p;
    p.setWidth(2);
    line->setZValue(-1);
    //p.setColor(Qt::green);
    line->setPen(p);
    scene->addItem(line);
}

GraphClass::GraphClass(QGraphicsView * v)
{
    updateView=v;
    scene=new QGraphicsScene(nullptr);
    v->setScene(scene);

}
