#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lista_doblemente_ligada.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    grafo= new GraphClass(ui->graphicsView);
    connect(grafo,SIGNAL(callNodeChanged(QString)),this,SLOT(NodeHasChanged(QString)));
    connect(this->ui->pushButton_AgregarCiudad, SIGNAL(clicked()), this, SLOT(AgregarCiudad()));
    //this->ui->pushButton_AgregarCiudad->clicked(true);
    /*Lista_Doblemente_Ligada *aux = ciudades.GetArregloCiudades();
    std::cout << "Ciudades recuperadas: ";
    aux->Imprimir();
    for(int i=0; i<aux->size(); i++){
        for(int j=0; j<aux[i].size(); j++){
            Ciudad c = aux[i].eliminarAlFinal();
            std::string str = c.getNombre();
            QString qstr = QString::fromStdString(str);
            grafo->insertNode(qstr);
        }
    }*/
    /*grafo->insertNode("A");
    grafo->insertNode("B");
    grafo->insertNode("C");
    grafo->insertNode("D");
    grafo->addConnection("A","B");
    grafo->addConnection("B","C");
    grafo->addConnection("C","D");
    grafo->addConnection("A","C");*/
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

void MainWindow::AgregarCiudad(){
    std::string nombre = this->ui->lineEdit_Nombre->text().toStdString();
    double costo = this->ui->lineEdit_Costo->text().toDouble();
    unsigned int estrellas = this->ui->lineEdit_NumeroEstrellas->text().toUInt();
    Ciudad aux(nombre, estrellas, costo);
    ciudades.InsertarElemento(aux);
    ciudades.Imprimir();
    //GraphClass *grafo=new GraphClass(ui->graphicsView);
    QString qstr = QString::fromStdString(nombre);
    connect(grafo,SIGNAL(callNodeChanged(QString)),this,SLOT(NodeHasChanged(QString)));
    grafo->insertNode(QString::number(ciudades.GetSize()));
    //grafo->insertNode(qstr);
}
