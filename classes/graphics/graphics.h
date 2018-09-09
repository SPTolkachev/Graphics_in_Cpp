#ifndef GRAPHICS_H
#define GRAPHICS_H

//#include <QMainWindow>
#include "ui_mainwindow.h"
//#include <QGraphicsTextItem>
//#include "coordplane.h"
//#include "mainwindow.h"
#include "../coordPlane/coordplane.h"
#include "../../libs/parsemathex/parsemathex.h"


class Graphics {
protected:
    bool debug = true;

    Ui::MainWindow *ui;
    CoordPlane *cp;
    QGraphicsScene *scene;
    QWidget *canvas;

    double initialDouble = -1000;//std::numeric_limits<double>::is_iec559;

    static const int dots = 101;
    double *arrayXCoords  = new double[dots]; // gcc запоняет нулями
    double *arrayYCoords  = new double[dots];

    double *arrayCanvasXCoords = new double[dots];
    double *arrayCanvasYCoords = new double[dots];


public:
    Graphics(Ui::MainWindow *ui, CoordPlane *cp, QGraphicsScene *scene);

    bool GetDebug();
    void SetDebug(bool debug);

    void    toDefaultCoordArrays();
    void    refillCoordArrays();
    double  calculateYValue(std::string exp, double X);
    int     GetDots();
    void    ShowLines();
    /* Del */ double *CorrectDot(double X0, double Y0, double X1, double Y1);
    double *CorrectY0(std::string exp, double X0, double Y0, double X1, double Y1);
    double *CorrectY1(std::string exp, double X0, double Y0, double X1, double Y1);
    //void  clearScene();
    void    Show();




};
#endif // GRAPHICS_H
