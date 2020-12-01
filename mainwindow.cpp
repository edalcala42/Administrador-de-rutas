#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<bits/stdc++.h>
#include "lista_doblemente_ligada.h"
using namespace  std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    grafo= new Graphic(ui->graphicsView);
    connect(grafo,SIGNAL(callNodeChanged(QString)),this,SLOT(NodeHasChanged(QString)));
    connect(this->ui->pushButton_AgregarCiudad, SIGNAL(clicked()), this, SLOT(AgregarCiudad()));
    connect(this->ui->pushButton_DeterminarDijkstra, SIGNAL(clicked()), this, SLOT(DeterminarDijkstra()));
    ui->cbOption->addItem("------>");
    ui->cbOption->addItem("<------");
    ui->cbOption->addItem("<----->");
    srand(unsigned(time(0)));
    ciudades=new TablaHash();
    clearMainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NodeHasChanged(QString name)
{
    grafo->eraseSelection();
    grafo->setSelected(name);
    int a=name.toInt();
    if(a>=ciudades->getNumElemCiudades())return;
    //cout<<"A->B->C->D";
    if(ui->rbprim->isChecked()){
        callPrim(name.toInt());
    }else if(ui->rbdijkstra->isChecked()){
        if(!upd){
            selectDij.first=a;
            upd=true;
        }else{
            //selectDij.se=selectDij.second;
            selectDij.second=a;
            grafo->insertCustomNode(QString::number(selectDij.first),QColor(255,152,152));
            grafo->insertCustomNode(QString::number(a),QColor(141,216,103));
            upd=false;
            updateDAlgorithm(selectDij.first);
            shortestPath(selectDij.second);
        }
    }
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
    int s=ciudades->GetSize();
    aux.SetNodo(s);
    if(ciudades->Buscar(aux)!=nullptr){
        QMessageBox::information(this, "Agregar", "La ciudad ya existe");
        return;
    }
    grafo->insertNode(QString::number(ciudades->GetSize()));
    ciudades->InsertarElemento(aux);
    ActualizarCB();
    updateCityTable();
    clearMainWindow();
}

void MainWindow::ActualizarCB()
{
    ui->cbFrom->clear();
    ui->cbTo->clear();
    Lista_Doblemente_Ligada *aux = ciudades->GetArregloCiudades();
    Iterador it;
    std::string nombre;
    int node=0;
    while(node<ciudades->getNumElemCiudades()){
        for(int i=0; i<ciudades->Max(); i++){
            for(it = aux[i].Begin(); it != aux[i].End(); it++){
                Ciudad a= *it;
                if(node==ciudades->getNumElemCiudades())return;
                if(a.GetNodo()==node){
                    ui->cbFrom->addItem(QString::fromStdString(a.getNombre()));
                    ui->cbTo->addItem(QString::fromStdString(a.getNombre()));
                    node++;
                }
            }
            if(node==ciudades->getNumElemCiudades())return;
        }
    }
}


void MainWindow::on_btnAddArista_clicked()
{
    clearMainWindow();
    int id1=ui->cbFrom->currentIndex(),id2=ui->cbTo->currentIndex();
    if(ui->cbFrom->currentIndex()==-1||ui->cbTo->currentIndex()==-1){
        ui->spbWeight->setValue(0.00);
        return;
    }
    if(ui->cbOption->currentIndex()==0){
        if(matrix.count(id1)&&matrix[id1].count(id2)){
            matrix[id1][id2]=std::min(matrix[id1][id2],ui->spbWeight->value());
            grafo->changeText(QString::number(id1),QString::number(id2),matrix[id1][id2]);
            QMessageBox::information(this,"Ruta","La ruta mínima es "+QString::number( matrix[id1][id2]));
        }else{
            matrix[id1][id2]=ui->spbWeight->value();
            grafo->addConnection(QString::number(id1),QString::number(id2),matrix[id1][id2]);
        }
        changeTableAdjacency(id1,id2,matrix[id1][id2]);
    }else if(ui->cbOption->currentIndex()==1){
        id1=ui->cbTo->currentIndex(),id2=ui->cbFrom->currentIndex();
        if(matrix.count(id1)&&matrix[id1].count(id2)){
            matrix[id1][id2]=std::min(matrix[id1][id2],ui->spbWeight->value());
            grafo->changeText(QString::number(id1),QString::number(id2),matrix[id1][id2]);
            QMessageBox::information(this,"Ruta","La ruta mínima es "+QString::number( matrix[id1][id2]));
        }else{
            matrix[id1][id2]=ui->spbWeight->value();
            grafo->addConnection(QString::number(id1),QString::number(id2),matrix[id1][id2]);
        }
        changeTableAdjacency(id1,id2,matrix[id1][id2]);
    }else{
        id1=ui->cbTo->currentIndex(),id2=ui->cbFrom->currentIndex();
        if(matrix.count(id1)&&matrix[id1].count(id2)){
            matrix[id1][id2]=std::min(matrix[id1][id2],ui->spbWeight->value());
            grafo->changeText(QString::number(id1),QString::number(id2),matrix[id1][id2]);
            QMessageBox::information(this,"Ruta","La ruta mínima es "+QString::number( matrix[id1][id2]));
        }else{
            matrix[id1][id2]=ui->spbWeight->value();
            grafo->addConnection(QString::number(id1),QString::number(id2),matrix[id1][id2]);
        }
        id1=ui->cbFrom->currentIndex(),id2=ui->cbTo->currentIndex();
        if(matrix.count(id1)&&matrix[id1].count(id2)){
            matrix[id1][id2]=std::min(matrix[id1][id2],ui->spbWeight->value());
            grafo->changeText(QString::number(id1),QString::number(id2),matrix[id1][id2]);
            QMessageBox::information(this,"Ruta","La ruta mínima es "+QString::number( matrix[id1][id2]));
        }else{
            matrix[id1][id2]=ui->spbWeight->value();
            grafo->addConnection(QString::number(id1),QString::number(id2),matrix[id1][id2]);
        }
        changeTableAdjacency(id1,id2,matrix[id1][id2]);
        changeTableAdjacency(id2,id1,matrix[id1][id2]);

    }
    if(ui->btnShowW->isChecked()){
        grafo->showTextNode(QString::number(id1),QString::number(id2));
        grafo->showTextNode(QString::number(id2),QString::number(id1));
    }
    //updateAdjacencyTable();
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

void MainWindow::updateCityTable()
{

    ui->cityTable->setVisible(1);
    ui->cityTable->setColumnCount(4);
    ui->cityTable->setRowCount(ciudades->getNumElemCiudades());
    ui->cityTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->cityTable->verticalHeader()->setVisible(false);
    QStringList labels;
    labels << "Id" << "Nombre" << "Costo" << "Número de estrellas";
    ui->cityTable->setHorizontalHeaderLabels(labels);
    Lista_Doblemente_Ligada *aux = ciudades->GetArregloCiudades();
    Iterador it;
    std::string nombre;
    int node=0,k=0;
    while(node<ciudades->getNumElemCiudades()){
        for(int i=0; i<ciudades->Max(); i++){
            for(it = aux[i].Begin(); it != aux[i].End(); it++){
                Ciudad a= *it;
                if(node==ciudades->getNumElemCiudades())return;
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
            if(node==ciudades->getNumElemCiudades())return;
        }
    }
}

void MainWindow::updateAdjacencyTable()
{
    ui->adjacencyTable->setVisible(1);
    ui->adjacencyTable->setColumnCount(ciudades->getNumElemCiudades()+1);
    ui->adjacencyTable->setRowCount(ciudades->getNumElemCiudades()+1);
    ui->adjacencyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->adjacencyTable->verticalHeader()->setVisible(false);
    ui->adjacencyTable->horizontalHeader()->setVisible(false);
    int tam=ciudades->getNumElemCiudades();
    QTableWidgetItem *cost;
    cost=  new QTableWidgetItem("#");
    ui->adjacencyTable->setItem(0, 0, cost);
    for(int m=0;m<tam;m++){
        cost=  new QTableWidgetItem(
                    QString::number(m));
        ui->adjacencyTable->setItem(0, m+1, cost);
        cost=  new QTableWidgetItem(
                    QString::number(m));
        ui->adjacencyTable->setItem(m+1, 0, cost);
    }
    for(auto m:matrix){
        for(auto n:m.second){
            cost=  new QTableWidgetItem(
                        QString::number(n.second));
            ui->adjacencyTable->setItem(m.first+1,n.first+1, cost);
        }
    }
}

Ciudad MainWindow::getCiudadFromPos(int pos)
{
    Ciudad a;
    Lista_Doblemente_Ligada *aux = ciudades->GetArregloCiudades();
    Iterador it;
    for(int i=0; i<ciudades->Max(); i++){
        for(it = aux[i].Begin(); it != aux[i].End(); it++){
            a= *it;
            if(a.GetNodo()==pos){
                return  a;
            }
        }
    }
    return a;
}

bool MainWindow::isNotdigraph()
{
    for(auto k:matrix){
        for(auto m:k.second){
            if(!matrix.count(m.first)&&!matrix[m.first].count(k.first)){
                return false;
            }
            if(matrix[m.first][k.first]!=matrix[k.first][m.first]){
                return false;
            }
        }
    }
    return true;
}

double MainWindow::prim(int n)
{
    ui->lblpath->setPlainText("Ruta: ");
    struct greaterpair
    {
        bool operator() (std::pair<int,std::pair<int,double>> const &a,std::pair<int,std::pair<int,double>> const &b) { return a.second.second > b.second.second; }
    };
    std::priority_queue<std::pair<int,std::pair<int,double>>,std::vector<std::pair<int,std::pair<int,double>>>,greaterpair>datos;
    double suma=0;
    std::set<int>rec;
    datos.push({n,{n,0}});
    QString auxpath;
    while(datos.size()){
        std::pair<int,std::pair<int,double>> aux=datos.top();
        datos.pop();
        int val=aux.first;
        if (!rec.count(val)){
            suma+=aux.second.second;
            rec.insert(val);
            grafo->drawPath(QString::number(aux.second.first),QString::number(aux.first));
            auxpath=ui->lblpath->toPlainText();
            ui->lblpath->setPlainText(auxpath+QString::number(aux.second.first)+"->"+QString::number(aux.first)+", ");
            for(auto m:matrix[val]){
                if(!rec.count(m.first)){
                    datos.push({m.first,{val,m.second}});
                }
            }
        }
    }
    ui->lblprim->setText("Tiempo mínimo para la ruta cobertora: "+QString::number(suma));

    if(rec.size()<ciudades->getNumElemCiudades()){
        grafo->eraseSelection();
        ui->lblprim->setText("");
        ui->lblpath->setPlainText("");
        QMessageBox::warning(this,"Ruta cobertora","La ciudad no tiene una ruta cobertora");

    }

    return suma;
}

void MainWindow::callPrim(int n)
{
    if(!isNotdigraph()){
        QMessageBox::warning(this,"Ruta cobertora","La ciudad no tiene una ruta cobertora");
        return;
    }
    prim(n);
}

void MainWindow::clearMainWindow()
{
    ui->lblprim->setText("");
    ui->lblpath->clear();
    nodoDUpdated=-1;
    grafo->eraseSelection();
}

std::string MainWindow::getCityName(int n)
{
    std::vector<std::string> citiesName{
        "Tokio", "Nueva York", "Los Ángeles", "Seúl", "Londres", "París", "Osaka", "Shanghái", "Chicago", "Moscú", "Pekín", "Colonia", "Houston", "Washington D. C.", "São Paulo", "Hong Kong", "Dallas", "Ciudad de México", "Cantón", "Tianjin", "Singapur", "Nagoya", "Shenzhen", "Boston", "Estambul", "Filadelfia", "Suzhou", "San Francisco", "Taipéi", "Yakarta", "Ámsterdam", "Buenos Aires", "Chongqing", "Milán", "Bangkok", "Busan", "Atlanta", "Delhi", "Toronto", "Seattle", "Miami", "Madrid", "Bruselas", "Chengdu", "Wuhan", "Frankfurt", "Sídney", "Múnich", "Hangzhou", "Wuxi", "Minneapolis", "Qingdao", "Detroit", "Phoenix", "Nanjing", "San Diego", "Dalian"};

    if(n>=citiesName.size()){
        return "Ciudad"+std::to_string(n);
    }else{
        return citiesName[n];
    }
}

void MainWindow::addCity(Ciudad &aux2)
{
    Ciudad aux(aux2.getNombre(),aux2.getNumeroDeEstrellas(),aux2.getCosto());
    int s=ciudades->GetSize();
    aux.SetNodo(s);
    if(ciudades->Buscar(aux)==nullptr){
        //        QMessageBox::information(this, "Agregar", "La ciudad ya existe");
        //        return;
        ciudades->InsertarElemento(aux);
    }
    grafo->insertNode(QString::number(s));

}

void MainWindow::addRoutes(int n, int opc)
{
    if(n<=0)return;
    int val=(rand()%n),val2,n1,n2;
    std::vector<int>dat;
    for(int i=0;i<n;i++){
        dat.push_back(i);
    }
    n1=dat[val];
    dat.erase(dat.begin()+val);
    while(dat.size()){
        val2=rand()%dat.size();
        //if(val==val2)continue;
        n2=dat[val2];
        addAristaNodes(n1,n2,opc);
        dat.erase(dat.begin()+val2);
        n1=n2;
    }
}

void MainWindow::addAristaNodes(int a, int b, int i)
{
    double c=(rand()%10000);
    c/=100.00;
    if(i==0){
        matrix[a][b]=c;
        matrix[b][a]=c;
        grafo->addConnection(QString::number(a),QString::number(b),c);
        grafo->addConnection(QString::number(b),QString::number(a),c);
    }else{
        matrix[a][b]=c;
        grafo->addConnection(QString::number(a),QString::number(b),c);

    }

}

void MainWindow::changeTableAdjacency(int i, int j, double b)
{
    if(ui->adjacencyTable->rowCount()<=ciudades->getNumElemCiudades()){
        int k=ui->adjacencyTable->rowCount();
        int ma=ciudades->getNumElemCiudades();
        ui->adjacencyTable->setRowCount(ma+1);
        ui->adjacencyTable->setColumnCount(ma+1);
        QTableWidgetItem * cost;
        for(int i=k;i<=ma;i++){
            cost=  new QTableWidgetItem(
                        QString::number(i-1));
            ui->adjacencyTable->setItem(0, i, cost);
            cost=  new QTableWidgetItem(
                        QString::number(i-1));
            ui->adjacencyTable->setItem(i, 0, cost);
        }
    }
    QTableWidgetItem *cost;
    cost=  new QTableWidgetItem(QString::number(b));
    ui->adjacencyTable->removeCellWidget(i+1,j+1);
    ui->adjacencyTable->setItem(i+1,j+1,cost);
}

int MainWindow::ObtenerMasCercano(double dist[]){
    size_t tam = matrix.size();
    int size = static_cast<int>(tam);
    int key = 0 ;
    double min = INT_MAX ;
    for(int i=0;i < size ; i++){
        if(!visitado[i] && dist[i]<min){
            min = dist[i] ;
            key = i ;
        }
    }
    return key ;
}

void MainWindow::Dijkstra(int nodoInicial)
{
    QString str;
    QString ruta;
    QString flecha;
    ui->plainTextEdit_Impresion_Dijkstra->setReadOnly(true);

    if(nodoInicial+1 > ciudades->getNumElemCiudades()){
        QMessageBox::information(this, "Dijkstra", "La ciudad no existe.\n");
        return;
    }
    ui->plainTextEdit_Impresion_Dijkstra->clear();
    size_t tam = matrix.size();
    int size = static_cast<int>(tam);
    double costo[100][100];
    int par[100];
    double dist[100];

    for(int q=0; q<size; q++){
        dist[q] = 9999;
        visitado[q] = false;
    }

    double costoLeido=0;
    for(int z=0; z<size; z++){
        for(int j=0; j<size; j++){
            costoLeido = getTime(z, j);
            costo[z][j] = costoLeido;
            //dist[z] = 9999;
        }
    }

    dist[nodoInicial] =0 ;
    par[nodoInicial] =-1 ;

    for(int g = 0  ;g<size-1 ; g++){
        int u = ObtenerMasCercano(dist);
        visitado[u] = true ;
        std::cout<< " min = " << u <<std::endl;
        for(int v =0 ; v< size ;v++){
            if(!visitado[v] && (dist[u]+costo[u][v]) <  dist[v] && costo[u][v] != 9999)
            {
                par[v] = u ;
                dist[v] = dist[u] + costo[u][v] ;
            }
        }
    }

    int j=0;
    for(int i =0 ;i < size ;i++){
        if(i != nodoInicial) {
            int caux=i;
            std::string distancia_a_imprimir = "\nDistancia del nodo " + std::to_string(caux) + " = ";
            double aux2 = dist[i];
            std::string d = std::to_string(aux2);
            distancia_a_imprimir.append(d);
            str = QString::fromStdString(distancia_a_imprimir);
            ui->plainTextEdit_Impresion_Dijkstra->insertPlainText(str);
            std::string r = "\nCon el siguiente camino: " + std::to_string(i);
            ruta = QString::fromStdString(r);
            ui->plainTextEdit_Impresion_Dijkstra->insertPlainText(ruta);
            j=i;
            do {
                j=par[j];
                std::string fl = "<- " + std::to_string(j);
                flecha = QString::fromStdString(fl);
                ui->plainTextEdit_Impresion_Dijkstra->insertPlainText(flecha);
            } while(j!=nodoInicial);
        }
    }

}

void MainWindow::clearAll()
{
    //ciudades->deleteAll();
    delete ciudades;
    ciudades=new TablaHash();
    matrix.clear();
    grafo->clearAll();
    nodoDUpdated=-1;
    ui->twdijkstra->clear();
    ui->adjacencyTable->clear();
}

void MainWindow::on_btnprim_clicked()
{
    callPrim(0);
}

void MainWindow::on_btnGenerateTreePrim_clicked()
{
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int>distribuition(0,1000000);
    auto dice=bind(distribuition,generator);
    int cityNumber=ui->numberCities->value();
    int aristasNumber=ui->numberAristas->value();
    int val,val2;
    clearAll();
    Ciudad aux;
    for(int i=0;i<cityNumber;i++){
        val=dice()%100000;
        val2=dice()%10;
        aux.setNombre(getCityName(i));
        aux.setCosto((double(val)/100.00));
        aux.setNumeroDeEstrellas(val2);
        addCity(aux);
    }
    addRoutes(cityNumber,0);
    int k=aristasNumber-(cityNumber);
    int random,random2;
    int maxic;
    for(int l=0;l<k;l++){
        maxic=100;
        while(maxic--){
            if(cityNumber<2)break;
            random=(rand()%cityNumber);
            random2=(rand()%cityNumber);
            if(random!=random2)break;
        }
        addAristaNodes(random,random2,0);
    }
    //addRoutes(aristasNumber-cityNumber);
    updateAdjacencyTable();
    ActualizarCB();
    updateCityTable();
}

void MainWindow::on_numberCities_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(ui->numberCities->value()>0)
        ui->numberAristas->setMinimum(arg1-1);
}

void MainWindow::on_btnGenerateTreeD_clicked()
{
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int>distribuition(0,1000000);
    auto dice=bind(distribuition,generator);
    int cityNumber=ui->numberCities->value();
    int aristasNumber=ui->numberAristas->value();
    int val,val2;
    Ciudad aux;
    clearAll();
    for(int i=0;i<cityNumber;i++){
        val=dice()%100000;
        val2=dice()%10;
        aux.setNombre(getCityName(i));
        aux.setCosto((double(val)/100.00));
        aux.setNumeroDeEstrellas(val2);
        addCity(aux);
    }
    addRoutes(cityNumber,1);
    int k=aristasNumber-(cityNumber);
    int random,random2;
    int maxic;
    for(int l=0;l<k;l++){
        maxic=100;
        while(maxic--){
            if(cityNumber<2)break;
            random=(rand()%cityNumber);
            random2=(rand()%cityNumber);
            if(random!=random2)break;
        }
        addAristaNodes(random,random2,1);
    }
    //addRoutes(aristasNumber-cityNumber);
    updateAdjacencyTable();
    ActualizarCB();
    updateCityTable();
}

void MainWindow::DeterminarDijkstra()
{
    int nodoInicial = this->ui->spinBox_NodoInicial->text().toInt();
    Dijkstra(nodoInicial);
}
std::unordered_map<int,pair<int,double>> MainWindow::dijkstra(int a){
    vector<vector<pair<double,int>>>table(ciudades->getNumElemCiudades(),vector<pair<double,int>>(ciudades->getNumElemCiudades(),{1e9,0}));
    std::unordered_map<int,pair<int,double>>cost;
    cost[a]={a,0};
    int emp=a,aux2,aux3=0;
    double sum=0,val=0,aux;
    int tam=ciudades->getNumElemCiudades();
    ui->twdijkstra->setVisible(1);
    ui->twdijkstra->setColumnCount(tam);
    ui->twdijkstra->setRowCount(1);
    ui->twdijkstra->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->twdijkstra->verticalHeader()->setVisible(false);
    ui->twdijkstra->horizontalHeader()->setVisible(false);

    QTableWidgetItem *cost2;
    cost2=  new QTableWidgetItem("#");
    ui->twdijkstra->setItem(0, 0, cost2);
    for(int m=0,k=1;m<tam&&k<tam;m++){
        if(a==m)continue;
        cost2=  new QTableWidgetItem(
                    QString::number(m));
        ui->twdijkstra->setItem(0, k++, cost2);
    }
    while(true){
        if(cost.size()==tam)break;
        aux=1e9+2;aux2=0;
        for(int i=0;i<tam;i++){
            if(a!=i){
                if(!matrix.count(emp)||!matrix[emp].count(i)){
                    val=1e9;
                }else{
                    val=matrix[emp][i];
                }
                if(table[aux3][i].first>sum+val){
                    table[emp][i].first=sum+val;
                    table[emp][i].second=emp;
                }else{
                    table[emp][i].first=table[aux3][i].first;
                    table[emp][i].second=table[aux3][i].second;
                }
                if(table[emp][i].first<aux && !cost.count(i)){
                    aux2=i;
                    aux=table[emp][i].first;
                }
            }
        }
        updateTableDJ(table[emp],emp);
        aux3=emp;
        cost[aux2]={table[emp][aux2].second,aux};
        emp=aux2;
        sum=aux;

    }
    //tableD=table;
    return cost;
}

void MainWindow::updateTableDJ(vector<pair<double,int>>dat,int e)
{
    size_t s=ui->twdijkstra->rowCount();
    ui->twdijkstra->insertRow(s);
    QTableWidgetItem *cost;
    cost=  new QTableWidgetItem(
                QString::number(e));
    ui->twdijkstra->setItem(s,0,cost);
    for(int i=0,j=1;i<dat.size() && j<dat.size();i++){
        if(i==nodoDUpdated)continue;
        if(dat[i].first>=1e9){
            cost=  new QTableWidgetItem("∞");
        }else{
            cost=  new QTableWidgetItem(
                        QString::number(dat[i].first));
        }
        ui->twdijkstra->setItem(s,j++,cost);
    }
}

void MainWindow::updateDAlgorithm(int a)
{
    if(nodoDUpdated!=a){
        nodoDUpdated=a;
        tableD=dijkstra(a);
    }
}

void MainWindow::shortestPath( int b){
    stack<int>data;
    int m=b;
    if(tableD.count(b)){
        if(tableD[b].second>=1e9){
            QMessageBox::warning(this,"Dijkstra","No hay camino");
            ui->lblprim->clear();
            ui->lblpath->clear();
            return;
        }
        data.push(b);
        while(true){
            if(!tableD.count(b))break;
            if(b==tableD[b].first)break;
            data.push(tableD[b].first);
            b=tableD[b].first;
        }
        //data.push(tableD[m].second);
    }
    int aux,aux2;
    if(data.size()){
        aux=data.top();
        data.pop();
    }else{
        return;
    }
    ui->lblprim->setText("Mínimo camino: "+QString::number(tableD[m].second));
    ui->lblpath->setPlainText("Ruta: ");
    QString au3;
    au3=ui->lblpath->toPlainText();
    while(data.size()){
        aux2=data.top();
        data.pop();
        grafo->drawPath(QString::number(aux),QString::number(aux2));
        au3+=QString::number(aux)+"->"+QString::number(aux2)+", ";
        aux=aux2;
    }
    ui->lblpath->setPlainText(au3);
}

void MainWindow::on_rbprim_clicked()
{
    grafo->eraseSelection();
    grafo->setSelected(QString::number(0));
    callPrim(0);
}

void MainWindow::on_rbclean_clicked()
{
    grafo->eraseSelection();
    clearMainWindow();
}

void MainWindow::on_rbdijkstra_clicked()
{
    grafo->eraseSelection();
    updateDAlgorithm(0);
    upd=true;
    grafo->insertCustomNode(QString::number(0),QColor(255,152,152));
    selectDij.first=0;
}


