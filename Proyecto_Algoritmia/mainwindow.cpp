#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Graphic *grafo=new Graphic(ui->graphicsView);
    connect(grafo,SIGNAL(callNodeChanged(QString)),this,SLOT(NodeHasChanged(QString)));
    grafo->insertNode("A");
    grafo->insertNode("B");
    grafo->insertNode("C");
    grafo->insertNode("D");
    grafo->addConnection("A","B",100);
    grafo->addConnection("D","A",200);
    grafo->addConnection("C","D",300);
    grafo->insertNode("E");
    grafo->addConnection("A","C",400);
    grafo->addConnection("D","E",500);
    grafo->addConnection("D","C",500);
    grafo->insertNode("F");
    grafo->addConnection("E","F",600);
    grafo->insertNode("G");
    grafo->deleteConnection("A","B");
    grafo->addConnection("G","F",700);
    grafo->drawPath("G","F");
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NodeHasChanged(QString name)
{
    QMessageBox message;
    message.setText(name);
    message.setIcon(QMessageBox::Information);
    message.exec();

    qDebug() << name;
}



