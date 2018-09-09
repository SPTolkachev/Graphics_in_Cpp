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




    static const int  graphics_numbers = 1;
    static const int dots = 101;

    /*
    double **arrayXCoords = new double*[graphics_numbers];//[dots]; // gcc запоняет нулями
    double **arrayYCoords = new double*[graphics_numbers];//[dots];

    double **arrayCanvasXCoords = new double*[graphics_numbers];//[dots];
    double **arrayCanvasYCoords = new double*[graphics_numbers];//[dots];
    */












        /*
        double (*arrayXCoords)[dots] = new double[graphics_numbers][dots];
        double (*arrayYCoords)[dots] = new double[graphics_numbers][dots];
        double (*arrayCanvasXCoords)[dots] = new double[graphics_numbers][dots];
        double (*arrayCanvasYCoords)[dots] = new double[graphics_numbers][dots];
        */

        double *arrayXCoords = new double[dots];
        double *arrayYCoords = new double[dots];
        double *arrayCanvasXCoords = new double[dots];
        double *arrayCanvasYCoords = new double[dots];













    /*
    double *arrayXCoords0 = new double[dots];
    double *arrayXCoords1 = new double[dots];
    double *arrayXCoords2 = new double[dots];

    double **arrayXCoords[graphics_numbers] = { *arrayXCoords0, *arrayXCoords1, *arrayXCoords2 };
    double **arrayYCoords = new double*[graphics_numbers][dots];

    double **arrayCanvasXCoords = new double*[graphics_numbers][dots];
    double **arrayCanvasYCoords = new double*[graphics_numbers][dots];
    */


    std::string arrayGraphics[graphics_numbers];
    int         arrayGraphicsColors[graphics_numbers];


    static const int  usedColorsNums   = 8;
    QColor *usedColors[usedColorsNums] = {
        new QColor(  0,    0,    0), // black
        new QColor(  0,    0,  255), // blue
        new QColor(255,    0,  255), // fuchsia
        new QColor(255,  215,    0), // gold
        new QColor(  0,  128,    0), // green
        new QColor(173,  255,   47), // greenyellow
        new QColor(128,  128,  128), // grey
        new QColor(255,    0,    0), // red
    };





public:
    Graphics(Ui::MainWindow *ui, CoordPlane *cp, QGraphicsScene *scene);

    bool GetDebug();
    void SetDebug(bool debug);

    std::string GetGraphicString(int num);
    void        SetGraphicString(int num, QString exp);
    QColor     *GetGraphicColor(int num);
    void        SetGraphicColor(int num, int color);

    bool    CheckExpression(std::string exp);
    void    toDefaultCoordArrays();
    void    refillCoordArrays();
    double  calculateYValue(std::string exp, double X);
    int     GetDots();
    void    ShowLines();
    //* Del */ double *CorrectDot(double X0, double Y0, double X1, double Y1);
    double *CorrectY0(std::string exp, double X0, double Y0, double X1, double Y1);
    double *CorrectY1(std::string exp, double X0, double Y0, double X1, double Y1);
    void    Show();




};
#endif // GRAPHICS_H
