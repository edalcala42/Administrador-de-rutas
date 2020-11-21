#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsItem>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include "graphic.h"
#include "ciudad.h"
#include "tablahash.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void NodeHasChanged(QString);
    void AgregarCiudad();
    void ActualizarCB();
private slots:
    void on_btnAddArista_clicked();

    void on_btnShowW_clicked();

    void on_btnhideW_clicked();

private:
    Ui::MainWindow *ui;
    Graphic *grafo;
    TablaHash ciudades;
    std::vector<Ciudad>datos;
    std::map<QString,std::map<QString,double>>matrix;

};
#endif // MAINWINDOW_H