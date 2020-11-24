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
    connect(this->ui->Dijkstra_pushButton_3, SIGNAL(clicked()), this, SLOT(DeterminarDijkstra()));
    ui->cbOption->addItem("------>");
    ui->cbOption->addItem("<------");
    ui->cbOption->addItem("<----->");
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
    if(a>=ciudades.Max())return;
    //cout<<"A->B->C->D";
    Ciudad c=getCiudadFromPos(name.toInt());
    ui->lblname->setText(QString::fromStdString(c.getNombre()));
    ui->lblcost->setText(QString::number(c.getCosto()));
    ui->lblstars->setText(QString::number(c.getNumeroDeEstrellas()));
}

void MainWindow::AgregarCiudad(){
    std::string nombre = this->ui->lineEdit_Nombre->text().toStdString();
    double costo = this->ui->lineEdit_Costo->text().toDouble();
    unsigned int estrellas = this->ui->lineEdit_NumeroEstrellas->text().toUInt();
    Ciudad aux(nombre, estrellas, costo);
    int s=ciudades.GetSize();
    aux.SetNodo(s);
    if(ciudades.Buscar(aux)!=nullptr){
        QMessageBox::information(this, "Agregar", "La ciudad ya existe");
        return;
    }
    grafo->insertNode(QString::number(ciudades.GetSize()));
    ciudades.InsertarElemento(aux);
    ActualizarCB();
    updateCityTable();
}

void MainWindow::ActualizarCB()
{
    //aqui que itere y que en cada iteracion
    //agregue el nombre a los combobox.
    ui->cbFrom->clear();
    ui->cbTo->clear();
    Lista_Doblemente_Ligada *aux = ciudades.GetArregloCiudades();
    Iterador it;
    int node=0;
    while(node<ciudades.getNumElemCiudades()){
        for(int i=0; i<ciudades.Max(); i++){
            for(it = aux[i].Begin(); it != aux[i].End(); it++){
                Ciudad a= *it;
                if(node==ciudades.getNumElemCiudades())return;
                if(a.GetNodo()==node){
                    ui->cbFrom->addItem(QString::fromStdString(a.getNombre()));
                    ui->cbTo->addItem(QString::fromStdString(a.getNombre()));
                    node++;
                }
            }
            if(node==ciudades.getNumElemCiudades())return;
        }
    }
}

void MainWindow::DeterminarDijkstra()
{
    int NodoInicial = this->ui->Nodo_spinBox->text().toInt();
    Dijkstra(NodoInicial);
}


void MainWindow::on_btnAddArista_clicked()
{
    int id1=ui->cbFrom->currentIndex(),id2=ui->cbTo->currentIndex();
    if(ui->cbFrom->currentIndex()==-1||ui->cbTo->currentIndex()==-1){
        ui->spbWeight->setValue(0.00);
        return;
    }
    if(ui->cbOption->currentIndex()==0){
        matrix[id1][id2]=ui->spbWeight->value();
        grafo->addConnection(QString::number(id1),QString::number(id2),ui->spbWeight->value());
    }else if(ui->cbOption->currentIndex()==1){
        matrix[id2][id1]=ui->spbWeight->value();
        grafo->addConnection(QString::number(id2),QString::number(id1),ui->spbWeight->value());
    }else{
        matrix[id1][id2]=ui->spbWeight->value();
        grafo->addConnection(QString::number(id1),QString::number(id2),ui->spbWeight->value());
        matrix[id2][id1]=ui->spbWeight->value();
        grafo->addConnection(QString::number(id2),QString::number(id1),ui->spbWeight->value());
    }
    if(ui->btnShowW->isChecked()){
        grafo->showTextNode(QString::number(id1),QString::number(id2));
        grafo->showTextNode(QString::number(id2),QString::number(id1));
    }
    ui->spbWeight->setValue(0.00);
    updateAdjacencyTable();
}

void MainWindow::on_btnShowW_clicked()
{
    grafo->showWeight();
}

void MainWindow::on_btnhideW_clicked()
{
    grafo->hideWeight();
}

double MainWindow::getTime(int i,int j)
{
    double val=1e9;
    if(matrix.count(i) && matrix[i].count(j)){
        val=matrix[i][j];
    }else{
        val=1e9;
    }
    return val;
}

void MainWindow::Dijkstra(int &nodoInicial)
{
    QString str;
    QString ruta;
    QString flecha;
    ui->Dijkstra_plainTextEdit->setReadOnly(true);

    if(nodoInicial+1 > ciudades.getNumElemCiudades()){
        QMessageBox::information(this, "Dijkstra", "La ciudad no existe.\n");
        return;
    }
    ui->Dijkstra_plainTextEdit->clear();
    size_t tamanio = matrix.size();
    double costo[tamanio][tamanio],distancia[tamanio];
    double mindistance;
    int visited[tamanio], caminos[tamanio];
    int count, nextnode, i, j;
    double costoLeido = 0;
    int totalDeElementos = ciudades.GetSize();
    for(i=0; i<totalDeElementos; i++){
        for(j=0; j<totalDeElementos; j++){
            costoLeido = getTime(i, j);
            costo[i][j] = costoLeido;
        }
    }
    for(i=0;i<totalDeElementos;i++) {
        distancia[i]=costo[nodoInicial][i];
        caminos[i]=nodoInicial;
        visited[i]=0;
    }
    distancia[nodoInicial]=0;
    visited[nodoInicial]=1;
    count=1;
    while(count<totalDeElementos-1) {
        mindistance = 9999;
        for(i=0;i<totalDeElementos;i++){
            if(distancia[i]<mindistance&&!visited[i]) {
                mindistance = distancia[i];
                nextnode=i;
             }
        }
        visited[nextnode]=1;
        for(i=0;i<totalDeElementos;i++){
            if(!visited[i]){
                if(mindistance+costo[nextnode][i]<distancia[i]) {
                    distancia[i]=mindistance+costo[nextnode][i];
                    caminos[i]=nextnode;
                }
             }
        }
        count++;
    }
    for(i=0;i<totalDeElementos;i++){
        if(i != nodoInicial) {
            std::string dist = "\nDistancia del nodo " + std::to_string(i) + " = ";
            std::string d = std::to_string(distancia[i]);
            dist.append(d);
            str = QString::fromStdString(dist);
            ui->Dijkstra_plainTextEdit->insertPlainText(str);
            std::string r = "\nCon el siguiente camino: " + std::to_string(i);
            ruta = QString::fromStdString(r);
            ui->Dijkstra_plainTextEdit->insertPlainText(ruta);
            j=i;
            do {
                j=caminos[j];
                std::string fl = "<- " + std::to_string(j);
                flecha = QString::fromStdString(fl);
                ui->Dijkstra_plainTextEdit->insertPlainText(flecha);
            } while(j!=nodoInicial);
        }
    }
}

void MainWindow::updateCityTable()
{

    ui->cityTable->setVisible(1);
    ui->cityTable->setColumnCount(4);
    ui->cityTable->setRowCount(ciudades.getNumElemCiudades());
    ui->cityTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->cityTable->verticalHeader()->setVisible(false);
    QStringList labels;
    labels << "Id" << "Nombre" << "Costo" << "Número de estrellas";
    ui->cityTable->setHorizontalHeaderLabels(labels);
    Lista_Doblemente_Ligada *aux = ciudades.GetArregloCiudades();
    Iterador it;
    std::string nombre;
    int node=0,k=0;
    while(node<ciudades.getNumElemCiudades()){
        for(int i=0; i<ciudades.Max(); i++){
            for(it = aux[i].Begin(); it != aux[i].End(); it++){
                Ciudad a= *it;
                if(node==ciudades.getNumElemCiudades())return;
                if(a.GetNodo()==node){
                    QTableWidgetItem *id =
                            new QTableWidgetItem(
                                QString::number(node));
                    QTableWidgetItem *name =
                            new QTableWidgetItem(
                                QString::fromStdString(a.getNombre()));
                    QTableWidgetItem *cost =
                            new QTableWidgetItem(
                                QString::number(a.getCosto()));
                    QTableWidgetItem *stars =
                            new QTableWidgetItem(
                                QString::number(a.getNumeroDeEstrellas()));
                    ui->cityTable->setItem(k, 0, id);
                    ui->cityTable->setItem(k, 1, name);
                    ui->cityTable->setItem(k, 2, cost);
                    ui->cityTable->setItem(k, 3, stars);
                    k++;
                    node++;
                }
            }
            if(node==ciudades.getNumElemCiudades())return;
        }
    }
}

void MainWindow::updateAdjacencyTable()
{
    ui->adjacencyTable->setVisible(1);
    ui->adjacencyTable->setColumnCount(ciudades.getNumElemCiudades()+1);
    ui->adjacencyTable->setRowCount(ciudades.getNumElemCiudades()+1);
    ui->adjacencyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->adjacencyTable->verticalHeader()->setVisible(false);
    ui->adjacencyTable->horizontalHeader()->setVisible(false);
    int tam=ciudades.getNumElemCiudades();
    QTableWidgetItem *cost;
    cost=  new QTableWidgetItem("#");
    ui->adjacencyTable->setItem(0, 0, cost);
    for(int m=0;m<tam;m++){
        cost=  new QTableWidgetItem(
                    QString::number(m));
        ui->adjacencyTable->setItem(0, m+1, cost);
    }
    for(int i=0;i<tam;i++){
        cost=  new QTableWidgetItem(
                    QString::number(i));
        ui->adjacencyTable->setItem(i+1, 0, cost);
        for(int j=0;j<tam;j++){
            if(getTime(i,j)<1e8){
                cost=  new QTableWidgetItem(
                            QString::number(getTime(i,j)));
            }
            else{
                cost=  new QTableWidgetItem("∞");
            }
            ui->adjacencyTable->setItem(i+1, j+1, cost);
        }
    }
}

Ciudad MainWindow::getCiudadFromPos(int pos)
{
    Ciudad a;
    Lista_Doblemente_Ligada *aux = ciudades.GetArregloCiudades();
    Iterador it;
    for(int i=0; i<ciudades.Max(); i++){
        for(it = aux[i].Begin(); it != aux[i].End(); it++){
            a= *it;
            if(a.GetNodo()==pos){
                return  a;
            }
        }
    }
    return a;
}
