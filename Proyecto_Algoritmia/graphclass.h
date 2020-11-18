#ifndef GRAPHCLASS_H
#define GRAPHCLASS_H
#include<QMainWindow>
#include<QGraphicsView>
#include<unordered_map>
#include <ctime>
#include"grafo.h"
class GraphClass: public QMainWindow
{
    Q_OBJECT
private:
    QGraphicsView *updateView;
    QGraphicsScene* scene;
    std::unordered_map<QString,Grafo*>nodes;
    std::unordered_map<QString,std::unordered_map<QString,QGraphicsLineItem*>>connections;
private slots:
    void changedNodeT(int, int, int, QString );
signals:
    void callNodeChanged(QString);
public:
    void insertNode(QString);
    //    void insertCustomNode(QString,QColor,QFont);
    void addConnection(QString,QString);
    //    void deleteConnection(QString,QString);
    //    void deleteNode(QString);
    //    void drawPath(QString,QString);
    //    void drawCustomPath(QString,QString,QPainter);
    //    void deletePath(QString,QString);
    //    void setSelected(QString);
    //    void eraseSelected(QString);
    //    void clearAll();
    //    void eraseSelection();
    //    ~GraphClass();
    GraphClass(QGraphicsView*);
};

#endif // GRAPHCLASS_H
