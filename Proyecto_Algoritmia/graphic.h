#ifndef GRAPHIC_H
#define GRAPHIC_H
#include<QMainWindow>
#include<QGraphicsView>
#include<unordered_map>
#include <ctime>
#include<math.h>
#include"nodegraphic.h"
class Graphic: public QMainWindow
{
    Q_OBJECT
private:
    struct Con{
        QGraphicsLineItem* Line;
        QGraphicsTextItem* Text;
        QGraphicsPolygonItem* Arrow;
    };
    QGraphicsView *updateView;
    QGraphicsScene* scene;
    std::vector<QString>selectedNodes;
    std::vector<std::pair<QString,QString>>path;
    std::unordered_map<QString,NodeGraphic*>nodes;
    std::unordered_map<QString,std::unordered_map<QString,Con>>connections;
private slots:
    void changedNodeT(int, int, int, QString );
signals:
    void callNodeChanged(QString);
public:
    void insertNode(QString);
    //    void insertCustomNode(QString,QColor,QFont);
    void addConnection(QString, QString, int);
    void deleteConnection(QString,QString);
    //void deleteNode(QString);
    void drawPath(QString,QString);
     //    void drawCustomPath(QString,QString,QPainter);
    void deletePath(QString,QString);
    void setSelected(QString);
    void eraseSelected(QString);
    void clearAll();
    void eraseSelection();
    //    ~GraphClass();
    Graphic(QGraphicsView*);
    void arrow(QPoint, QPoint, QPolygonF &);
};

#endif // GRAPHCLASS_H
