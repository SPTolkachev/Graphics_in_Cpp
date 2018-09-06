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

    double initialDouble = std::numeric_limits<double>::is_iec559;

    double arrayXCoords[10];
    double arrayYCoords[10];

    double arrayCanvasXCoords[10];
    double arrayCanvasYCoords[10];


public:
    Graphics(Ui::MainWindow *ui, CoordPlane *cp);
    void Show();




};
#endif // GRAPHICS_H
