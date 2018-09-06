#ifndef GRAPHICS_H
#define GRAPHICS_H

//#include <QMainWindow>
#include "ui_mainwindow.h"
//#include <QGraphicsTextItem>
//#include "coordplane.h"
//#include "mainwindow.h"
#include "../coordPlane/coordplane.h"


class Graphics {
protected:
    Ui::MainWindow *ui;
    CoordPlane *cp;
    QGraphicsScene *scene;
    QWidget *canvas;

    double initialDouble = -1000;//std::numeric_limits<double>::is_iec559;

    static const int    steps = 10;
    double arrayXCoords[steps]; // gcc запоняет нулями
    double arrayYCoords[steps];

    double arrayCanvasXCoords[steps];
    double arrayCanvasYCoords[steps];


public:
    Graphics(Ui::MainWindow *ui, CoordPlane *cp/*, QGraphicsView *scene*/);
    void   toDefaultCoordArrays();
    void   refillCoordArrays();
    double calculateYValue(double X);
    int    GetDots();
    //void   clearScene();
    void   Show();




};
#endif // GRAPHICS_H
