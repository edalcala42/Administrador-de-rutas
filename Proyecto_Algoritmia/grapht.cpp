#include "grapht.h"
#include "ui_grapht.h"

GraphT::GraphT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphT)
{
    ui->setupUi(this);
}

GraphT::~GraphT()
{
    delete ui;
}
