#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GraphClass *grafo=new GraphClass(ui->graphicsView);
    connect(grafo,SIGNAL(callNodeChanged(QString)),this,SLOT(NodeHasChanged(QString)));
    grafo->insertNode("A");
    grafo->insertNode("B");
    grafo->insertNode("C");
    grafo->insertNode("D");
    grafo->addConnection("A","B");
    grafo->addConnection("B","C");
    grafo->addConnection("C","D");
    grafo->addConnection("A","C");
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



