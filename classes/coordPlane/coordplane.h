#ifndef COORDPLANE_H
#define COORDPLANE_H

//#include <QMainWindow>
#include "ui_mainwindow.h"
//#include "graphics.h"
#include <QGraphicsTextItem>
//#include "mainwindow.h"

class CoordPlane {
protected:
    bool debug = false;
    double defaultDouble = -10000; // std::numeric_limits<double>::is_iec559;

    double X  = 0.0;
    double Xe = 0.0;
    double Y  = 0.0;
    double Ye = 0.0;
    double scale = 0.0;


    int steps = 0;
    double step = 0.0;
    double stepCanvasWidth  = 0.0;
    double stepCanvasHeight = 0.0;

    /**
     * scale
     *   min = 0.01
     *   max = 100
     */
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QWidget *canvas;
    int realWidthCanvas = 0;
    double GetUsedCanvasWidth();
    void   SetUsedCanvasWidth(double width);


    int realHeightCanvas = 0;
    double GetUsedCanvasHeight();
    void   SetUsedCanvasHeight(double height);

    //int const cLArrayLength0 = 2;
    //int cLArrayLength1 = 11;
    int maxLines = 11;
    int displayedLines = maxLines;
    /*
    double coordLinesArray[2][11] = {         // Обнуляем, чтобы не было мусора
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // вертикальные
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // горизонтальные
    };
    */
    //double FirstCoordLineX = 0.0;
    double EndCoordLineX = 0.0;
    double coordLinesX[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // вертикальные
    double coordLinesY[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // горизонтальные
    //    double canvasLinesTypes[2]   = {10.0, 1.0};
    //double canvasLinesMargins[2] = {0.0,  0.0};
    //double default_canvasLeftMargin = defaultDouble;
    double canvasLeftMargin = defaultDouble;
    double GetCanvasLeftMargin();
    void   SetCanvasLeftMargin(double canvasLeftMargin);

    //double default_canvasTopMargin = std::numeric_limits<double>::is_iec559;
    double canvasTopMargin = defaultDouble; // горизонтальный отступ
    double GetCanvasTopMargin();
    void   SetCanvasTopMargin(double canvasTopMargin);

    double canvasVMargin = 0.0; // вертикальный отступ

    double fromX = 0;
    double GetFromX();
    void   SetFromX(double fromX);

    double toX = 0;
    double GetToX();
    void SetToX(double toX);

    double fromY = 0;
    double GetFromY();
    void   SetFromY(double fromY);

    double toY = 0;
    double GetToY();
    void SetToY(double toY);

    int  X_lines = 0;
    int  GetXLines();
    void SetXLines(int lines);

    int  Y_lines = 0;
    int  GetYLines();
    void SetYLines(int lines);

    //double default_procentMarginLeft = std::numeric_limits<double>::is_iec559;
    double procentMarginLeft = defaultDouble;
    double GetProcentMarginLeft();
    void   SetProcentMarginLeft(double pml);

    //double default_procentMarginRight = std::numeric_limits<double>::is_iec559;
    double procentMarginRight = defaultDouble;
    double GetProcentMarginRight();
    void   SetProcentMarginRight(double pmr);

    //double default_procentMarginTop = std::numeric_limits<double>::is_iec559;
    double procentMarginTop = defaultDouble;
    double GetProcentMarginTop();
    void   SetProcentMarginTop(double pmt);

    //double default_procentMarginBottom = std::numeric_limits<double>::is_iec559;
    double procentMarginBottom = defaultDouble;
    double GetProcentMarginBottom();
    void   SetProcentMarginBottom(double pmb);


    void refillCoordLinesArray();
    void ShowCoordLines();
    void ShowCoordLineNums();

    double GetStepCanvasWidth();
    double GetStepCanvasHeight();
    std::string toHandleNumber(std::string str);

    //int CorrectSteps();
    void SetStep(double step);
    void SetStepCanvasWidth(double width);
    void SetStepCanvasHeight(double height);
    void resetWorkProperties();
    void clearScene();

    double X_PsiP = 0.0;
    double Y_PsiP = 0.0;

public:
    CoordPlane(Ui::MainWindow *ui, QGraphicsScene *scene, double x = -5, double y = 5, double scale = 10);

    bool GetDebug();
    void SetDebug(bool debug);

    double GetX();
    void   SetX(double x);
    //double GetXc(); // X center
    double GetXe(); // X end
    void   SetXe(double x);

    double GetY();
    void   SetY(double y);
    //double GetYc(); // Y center
    double GetYe(); // Y end
    void   SetYe(double y);

    double GetScale();
    void   SetScale(double sc);

    int    GetSteps();
    void   SetSteps(int steps);
    double GetStep();

    double GetX_PsiP();
    void   SetX_PsiP(double coeff);

    double GetY_PsiP();
    void   SetY_PsiP(double coeff);

    //QGraphicsScene *GetScene();
    //void            SetScene();

    void   Show();
};

#endif // COORDPLANE_H
