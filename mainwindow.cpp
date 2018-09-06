#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "classes/coordPlane/coordplane.h"
#include "classes/graphics/graphics.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->scene    = new QGraphicsScene(ui->graphicsView);
    this->cplane   = new CoordPlane(this->ui/*, this->scene*/);
    this->graphics = new Graphics(this->ui, this->cplane/*, this->scene*/);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowGraph() {
    this->cplane->Show();
    this->graphics->Show();

    std::cout << "-------------------------------------------\n\n\n";
}

void MainWindow::on_renderButton_clicked() { // Нажатие на кнопку "Отрис."
    this->ShowGraph();
}

/*
*********************************************************************
******  Кнопки изменения видимой части координатной плоскости   *****
*********************************************************************
*/
void MainWindow::on_scalePlane_valueChanged(double arg1) {
    this->cplane->SetScale(arg1);
    std::cout << "SetScale(" << arg1 << ")\n";
    this->ShowGraph(); // Отрисовка
}

void MainWindow::on_to_upButton_clicked() {
    double newY = this->cplane->GetY() + ui->to_upStep->value();
    //std::cout << "newY = " << this->cplane->GetY() << " + " << ui->to_upStep->value() << "\n";
    this->cplane->SetY(newY);
    std::cout << "SetY(" << newY << ")\n";
    this->ShowGraph(); // Отрисовка
}

void MainWindow::on_to_rightButton_clicked() {
    double newX = this->cplane->GetX() + ui->to_rightStep->value();
    this->cplane->SetX(newX);
    std::cout << "SetX+(" << newX << ")\n";
    this->ShowGraph(); // Отрисовка
}

void MainWindow::on_to_downButton_clicked() {
    double newY = this->cplane->GetY() - ui->to_downStep->value();
    //std::cout << "newY = " << this->cplane->GetY() << " - " << ui->to_downStep->value() << "\n";
    this->cplane->SetY(newY);
    std::cout << "SetY+(" << newY << ")\n";
    this->ShowGraph(); // Отрисовка
}


void MainWindow::on_to_leftButton_clicked() {
    double newX = this->cplane->GetX() - ui->to_leftStep->value();
    this->cplane->SetX(newX);
    std::cout << "SetX-(" << newX << ")\n";
    this->ShowGraph(); // Отрисовка
}

void MainWindow::on_to_leftUpButton_clicked() {
    this->on_to_leftButton_clicked();
    this->on_to_upButton_clicked();
}

void MainWindow::on_to_rightUpButton_clicked() {
    this->on_to_rightButton_clicked();
    this->on_to_upButton_clicked();
}

void MainWindow::on_to_rightBottomButton_clicked() {
    this->on_to_rightButton_clicked();
    this->on_to_downButton_clicked();
}

void MainWindow::on_to_leftDownButton_clicked() {
    this->on_to_leftButton_clicked();
    this->on_to_downButton_clicked();
}
