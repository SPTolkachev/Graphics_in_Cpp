#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "classes/coordPlane/coordplane.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->cplane = new CoordPlane(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowGraph() {
    this->cplane->Show();
}
