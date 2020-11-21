#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lista_doblemente_ligada.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    grafo= new Graphic(ui->graphicsView);
    connect(grafo,SIGNAL(callNodeChanged(QString)),this,SLOT(NodeHasChanged(QString)));
    connect(this->ui->pushButton_AgregarCiudad, SIGNAL(clicked()), this, SLOT(AgregarCiudad()));
    ui->cbOption->addItem("------>");
    ui->cbOption->addItem("<------");
    ui->cbOption->addItem("<----->");
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
    grafo->eraseSelection();
    grafo->setSelected(name);
    int a=name.toInt()-1;
    if(a>=datos.size())return;
    ui->lblname->setText(QString::fromStdString(datos[a].getNombre()));
    ui->lblcost->setText(QString::number(datos[a].getCosto()));
    ui->lblstars->setText(QString::number(datos[a].getNumeroDeEstrellas()));
}

void MainWindow::AgregarCiudad(){
    std::string nombre = this->ui->lineEdit_Nombre->text().toStdString();
    double costo = this->ui->lineEdit_Costo->text().toDouble();
    unsigned int estrellas = this->ui->lineEdit_NumeroEstrellas->text().toUInt();
    Ciudad aux(nombre, estrellas, costo);
    //De aqui
    datos.push_back(aux);
    grafo->insertNode(QString::number(datos.size()));
    ActualizarCB();
    return;
    //hasta qui se quita XD
    ciudades.InsertarElemento(aux);
    ciudades.Imprimir();
    //GraphClass *grafo=new GraphClass(ui->graphicsView);
    QString qstr = QString::fromStdString(nombre);
    //connect(grafo,SIGNAL(callNodeChanged(QString)),this,SLOT(NodeHasChanged(QString)));
    grafo->insertNode(QString::number(ciudades.GetSize()));
    //grafo->insertNode(qstr);
    ActualizarCB();
}

void MainWindow::ActualizarCB()
{
    //aqui que itere y que en cada iteracion
    //agregue el nombre a los combobox.
    ui->cbFrom->clear();
    ui->cbTo->clear();
    for(auto &m:datos){
        ui->cbFrom->addItem(QString::fromStdString(m.getNombre()));
        ui->cbTo->addItem(QString::fromStdString(m.getNombre()));
    }
}


void MainWindow::on_btnAddArista_clicked()
{
    if(ui->cbOption->currentIndex()==-1||ui->cbOption->currentText()==-1){
        ui->spbWeight->setValue(0.00);
        return;
    }
    if(ui->cbOption->currentIndex()==0){
        matrix[QString::number(ui->cbFrom->currentIndex())][QString::number(ui->cbTo->currentIndex())]=ui->spbWeight->value();
        grafo->addConnection(QString::number(ui->cbFrom->currentIndex()+1),QString::number(ui->cbTo->currentIndex()+1),ui->spbWeight->value());
    }else if(ui->cbOption->currentIndex()==1){
        matrix[QString::number(ui->cbTo->currentIndex())][QString::number(ui->cbFrom->currentIndex())]=ui->spbWeight->value();
        grafo->addConnection(QString::number(ui->cbTo->currentIndex()+1),QString::number(ui->cbFrom->currentIndex()+1),ui->spbWeight->value());
    }else{
        matrix[QString::number(ui->cbFrom->currentIndex())][QString::number(ui->cbTo->currentIndex())]=ui->spbWeight->value();
        grafo->addConnection(QString::number(ui->cbFrom->currentIndex()+1),QString::number(ui->cbTo->currentIndex()+1),ui->spbWeight->value());
        matrix[QString::number(ui->cbTo->currentIndex())][QString::number(ui->cbFrom->currentIndex())]=ui->spbWeight->value();
        grafo->addConnection(QString::number(ui->cbTo->currentIndex()+1),QString::number(ui->cbFrom->currentIndex()+1),ui->spbWeight->value());
    }
    if(ui->btnShowW->isChecked()){
        grafo->showTextNode(QString::number(ui->cbFrom->currentIndex()+1),QString::number(ui->cbTo->currentIndex()+1));
    }
    ui->spbWeight->setValue(0.00);
}

void MainWindow::on_btnShowW_clicked()
{
    grafo->showWeight();
}

void MainWindow::on_btnhideW_clicked()
{
    grafo->hideWeight();
}
