#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsItem>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include "graphclass.h"
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
private:
    Ui::MainWindow *ui;
    GraphClass *grafo;
    TablaHash ciudades;
};
#endif // MAINWINDOW_H
