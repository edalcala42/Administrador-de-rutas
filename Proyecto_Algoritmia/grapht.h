#ifndef GRAPHT_H
#define GRAPHT_H

#include <QWidget>
#include<QGraphicsView>
namespace Ui {
class GraphT;
}

class GraphT : public QWidget
{
    Q_OBJECT

public:
    explicit GraphT(QWidget *parent = nullptr);
    ~GraphT();
private slots:
    void changedNode(int, int, int, QString );
signals:
    void callNodeChanged(QString);
public:
    GraphT(QGraphicsView*);
private:
    Ui::GraphT *ui;
};

#endif // GRAPHT_H
