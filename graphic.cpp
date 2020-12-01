#include "graphic.h"

void Graphic::changedNodeT(int x, int y, int d, QString aux)
{
    Q_UNUSED(d);Q_UNUSED(y);Q_UNUSED(d);
    emit callNodeChanged(aux);
}

void Graphic::insertNode(QString n)
{
    if(nodes.count(n))return;
    //srand((unsigned)time(0));
    int max=(nodes.size()+5)*30;
    if(nodes.size()>=13)max=18*30;
    int val = (rand()%(max))-max;
    NodeGraphic *nuevo=new NodeGraphic(nodes.size()*30+(nodes.size()*20),val,30,n);
    nuevo->setZValue(1);
    nodes[n]=nuevo;
    connect(nuevo,SIGNAL(selectedNode(int,int,int,QString)),this,SLOT(changedNodeT(int,int,int,QString)));
    scene->addItem(nuevo);
}

void Graphic::insertCustomNode(QString a, QColor b)
{
    if(!nodes.count(a))return;
    nodes[a]->setOver(true);
    selectedNodes.push_back(a);
    nodes[a]->setColor(b);
    nodes[a]->update();
}

void Graphic::addConnection(QString a, QString b, double weight)
{
    if(!nodes.count(a)||!nodes.count(b))return;
    if(connections.count(a) && connections[a].count(b)){
        QString w2=QString::number(weight);
        connections[a][b].Text->setPlainText(w2);
        return;
    }
    NodeGraphic* aux=nodes[a];
    NodeGraphic* aux2=nodes[b];
    std::pair<int,int> z,z2;
    z={aux->getX()+(aux->getTam()/2),aux->getY()+(aux->getTam()/2)};
    z2={aux2->getX()+(aux->getTam()/2),aux2->getY()+(aux->getTam()/2)};
    QGraphicsLineItem *line=new QGraphicsLineItem(z.first,z.second,z2.first,z2.second,NULL);
    QPen p;
    p.setWidth(1);
    line->setZValue(-1);
    line->setPen(p);
    QGraphicsTextItem *text=new QGraphicsTextItem(QString::number(weight),NULL);
    int mid=abs(z.second-z2.second)/2;
    int y=z.second>z2.second?(z.second-mid):mid+z.second;
    mid=abs(z.first-z2.first)/2;
    int x=z.first>z2.first?(z.first-mid):z.first+mid;
    if(connections.count(b)&& connections[b].count(a)){
        text->setPos(QPointF(x-10,y-15));
    }
    else{
        text->setPos(QPointF(x-10,y));
    }
    text->hide();
    scene->addItem(line);
    scene->addItem(text);
    QPolygonF pp; arrow({z2.first,z2.second},{z.first,z.second},pp);
    QGraphicsPolygonItem *pt=new QGraphicsPolygonItem(pp);
    connections[a][b].Text=text;
    connections[a][b].Line=line;
    connections[a][b].Arrow=pt;
    scene->addItem(pt);
}

void Graphic::deleteConnection(QString a, QString b)
{
    if(!connections.count(a)||!connections[a].count(b))return;
    auto it=connections[a].find(b);
    scene->removeItem(connections[a][b].Line);
    scene->removeItem(connections[a][b].Text);
    scene->removeItem(connections[a][b].Arrow);
    connections[a].erase (it);
}

void Graphic::drawPath(QString a, QString b)
{
    if(!connections.count(a)||!connections[a].count(b))return;
    QPen p;
    p.setWidth(4);
    p.setColor(QColor(255,94,153));
    connections[a][b].Line->setPen(p);
    connections[a][b].Text->show();
    path.push_back({a,b});
    if(!connections.count(b)||!connections[b].count(a))return;
    connections[b][a].Line->setPen(p);
    // connections[b][a].Text->show();
    path.push_back({b,a});

}

void Graphic::deletePath(QString a, QString b)
{
    if(!connections.count(a)||!connections[a].count(b))return;
    QPen p;
    p.setWidth(1);
    connections[a][b].Line->setPen(p);
    connections[a][b].Text->hide();
}

void Graphic::setSelected(QString a)
{
    if(!nodes.count(a))return;
    nodes[a]->setOver(true);
    selectedNodes.push_back(a);
}

void Graphic::showTextNode(QString a, QString b)
{
    if(!connections.count(a)||!connections[a].count(b))return;
    connections[a][b].Text->show();
}

void Graphic::hideTextNode(QString a, QString b)
{
    if(!connections.count(a)||!connections[a].count(b))return;
    connections[a][b].Text->hide();
}

void Graphic::eraseSelected(QString a)
{
    if(!nodes.count(a))return;
    nodes[a]->setOver(false);
}

void Graphic::changeText(QString a, QString b, int t)
{
    if(!connections.count(a)||!connections[a].count(b))return;
    connections[a][b].Text->setPlainText(QString::number(t));
}

void Graphic::clearAll()
{
    scene->clear();
    connections.clear();
    selectedNodes.clear();
    path.clear();
    nodes.clear();
    connections.clear();
    scene->clearFocus();

}

void Graphic::showWeight()
{
    for(auto &k:connections){
        for(auto &m:k.second){
            m.second.Text->show();
        }
    }
}

void Graphic::hideWeight()
{
    for(auto &k:connections){
        for(auto &m:k.second){
            m.second.Text->hide();
        }
    }
}

void Graphic::eraseSelection()
{
    for(auto &n:selectedNodes){
        nodes[n]->setOver(false);
        nodes[n]->update();
    }
    for(auto &m:path){
        QPen p;
        p.setWidth(1);
        connections[m.first][m.second].Line->setPen(p);
        connections[m.first][m.second].Text->hide();
    }
}

Graphic::Graphic(QGraphicsView * v)
{
    updateView=v;
    scene=new QGraphicsScene(nullptr);
    v->setScene(scene);
}

void Graphic::arrow(QPoint end, QPoint start, QPolygonF &p)
{
    qreal arrowSize = 25; // size of head
    QLineF line(end, start);
    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                          cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                          cos(angle + M_PI - M_PI / 3) * arrowSize);
    p.clear();
    p << line.p1() << arrowP1 << arrowP2;

}
